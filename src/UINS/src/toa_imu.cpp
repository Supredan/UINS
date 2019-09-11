#include <stdio.h>
#include <queue>
#include <map>
#include <thread>
#include <mutex>
#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <std_msgs/Header.h>
#include <std_msgs/Float32.h>
#include <condition_variable>
#include <vector>

#include "sensor_msgs/Imu.h"
#include "crazyflie_driver/GenericLogData.h"

#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>

#include "toa_imu.h"

queue<sensor_msgs::ImuConstPtr> imu_buf;
queue<crazyflie_driver::GenericLogDataConstPtr> dis_buf;
//queue<sensor_msgs::PointCloudConstPtr> dis_buf;
queue<geometry_msgs::PointStamped> bg_buf;
queue<geometry_msgs::PointStamped> ba_buf;

crazyflie_driver::GenericLogData distance_receive;
//sensor_msgs::PointCloud distance_receive;
geometry_msgs::PointStamped bg_receive;
geometry_msgs::PointStamped ba_receive;
nav_msgs::Path path;
std_msgs::Header header;
// geometry_msgs::PointStamped distance_stamp;
ros::Publisher marker_pub;
ros::Publisher point;
ros::Publisher pub_path;

int imu_flag;
int bias_flag;
int dis_receive_flag;
int imu_first = 0;

std::mutex m_buf, m_estimator;

Calculator calculator;

std::condition_variable con;



//void bg_callback(const geometry_msgs::PointStamped::ConstPtr &bg_msg)
//{
//    bg_receive = *bg_msg;
//    //cout<<"receive bg msg"<<endl;
//    //cout<<"bg_x:"<<bg_msg->point.x<<endl;
//    //cout<<"bg_time"<<bg_msg->header.stamp.toSec()<<endl;
//    if(bg_receive.point.x != 0)
//    {
//        m_buf.lock();
//        bg_buf.push(bg_receive);
//        m_buf.unlock();
//        bias_flag = 1;
//        //ROS_INFO("receive bias data, process begin");
//    }
//    con.notify_one();
//}
//
//void ba_callback(const geometry_msgs::PointStamped::ConstPtr &ba_msg)
//{
//    //cout<<"receive ba msg"<<endl;
//    if(bias_flag == 1)
//    {
//        ba_receive = *ba_msg;
//        m_buf.lock();
//        ba_buf.push(ba_receive);
//        m_buf.unlock();
//    }
//    con.notify_one();
//}

void distance_callback(const crazyflie_driver::GenericLogDataConstPtr &dis_msg)
{
    //dis_tnow = ros::Time::now().toSec();
    //cout<<"receive dis msg"<<endl;
    if(bias_flag == 1)
    {
        m_buf.lock();
        dis_buf.push(dis_msg);
        m_buf.unlock();
        //cout<<"here is dis msg"<<endl;
        // con.notify_one();    
        if (dis_receive_flag == 0)
        {
            cout << "first dis time" << dis_msg->header.stamp.toSec()<<endl;
            cout <<"real delta_dis time " <<  ros::Time::now().toSec() - distance_receive.header.stamp.toSec()<<endl;
            dis_receive_flag = 1;
        }      
    }
    con.notify_one();
}

void imu_callback(const sensor_msgs::ImuConstPtr &imu_msg)
{
    if(bias_flag == 1)
    {
        if(dis_receive_flag == 1)
        {
            m_buf.lock();
            imu_buf.push(imu_msg);//存imu数据
            m_buf.unlock();

            if(imu_flag == 0)
            {
                calculator.latest_time = imu_msg->header.stamp.toSec();
                imu_flag = 1;
            }

            if (imu_first == 0)
            {
                imu_first = 1;
                calculator.td = imu_msg->header.stamp.toSec()- ros::Time::now().toSec();
                cout<<"first imu time: "<< imu_msg->header.stamp.toSec()<<endl;
                cout<<"real imu time " <<  ros::Time::now().toSec()<<endl;
                cout<<"td"<<calculator.td<<endl;
            }
        }        
    }
    con.notify_one();
}


std::vector<std::pair<std::vector<sensor_msgs::ImuConstPtr>, crazyflie_driver::GenericLogDataConstPtr>>
getMeasurements()
{
    std::vector<std::pair<std::vector<sensor_msgs::ImuConstPtr>, crazyflie_driver::GenericLogDataConstPtr>> measurements;

    while (true)
    {
        if (imu_buf.empty() || dis_buf.empty())
            return measurements;

        if (!(imu_buf.back()->header.stamp.toSec() > dis_buf.front()->header.stamp.toSec() + calculator.td))
        {
            return measurements;
        }

        if (!(imu_buf.front()->header.stamp.toSec() < dis_buf.front()->header.stamp.toSec() + calculator.td))
        {
            ROS_WARN("throw img, only should happen at the beginning");
            dis_buf.pop();
            continue;
        }
        crazyflie_driver::GenericLogDataConstPtr dis_msg = dis_buf.front();
        dis_buf.pop();

        std::vector<sensor_msgs::ImuConstPtr> IMUs;
        while (imu_buf.front()->header.stamp.toSec() < dis_msg->header.stamp.toSec() + calculator.td)
        {
            IMUs.emplace_back(imu_buf.front());
            imu_buf.pop();
        }
        IMUs.emplace_back(imu_buf.front());
        if (IMUs.empty())
            ROS_WARN("no imu between two image");
        measurements.emplace_back(IMUs, dis_msg);
    }
    return measurements;
}

void process()
{
    while(true)
    {
        std::vector<std::pair<std::vector<sensor_msgs::ImuConstPtr>, crazyflie_driver::GenericLogDataConstPtr>> measurements;
        std::unique_lock<std::mutex> lk(m_buf);
        con.wait(lk, [&]
                 {
            return (measurements = getMeasurements()).size() != 0;
                 });
        lk.unlock();
        for (auto &measurement : measurements)
        {
            auto dis_msg = measurement.second;
            double dx = 0, dy = 0, dz = 0, rx = 0, ry = 0, rz = 0;
            for (auto &imu_msg : measurement.first)
            {
                double t = imu_msg->header.stamp.toSec();
                // double img_t = dis_msg->header.stamp.toSec() + calculator.td;

                if (calculator.current_time < 0)
                    calculator.current_time = t;
                double dt = t - calculator.current_time;
                ROS_ASSERT(dt >= 0);
                calculator.current_time = t;
                dx = imu_msg->linear_acceleration.x;
                dy = imu_msg->linear_acceleration.y;
                dz = imu_msg->linear_acceleration.z;
                rx = imu_msg->angular_velocity.x;
                ry = imu_msg->angular_velocity.y;
                rz = imu_msg->angular_velocity.z;
                // cout<<"dt:"<<dt<<endl;
                calculator.processIMU(dt, Vector3d(dx, dy, dz), Vector3d(rx, ry, rz));
            }        
            
            if(calculator.frame_count == 10)
            {
                for(int i = 0; i<6; i++)
                {
                    calculator.dis[calculator.frame_count][i] = dis_msg->values[i];
                }
                calculator.Bas[calculator.frame_count](0) = 0;
                calculator.Bas[calculator.frame_count](1) = 0;
                calculator.Bas[calculator.frame_count](2) = 0;

                calculator.Bgs[calculator.frame_count](0) = 0;
                calculator.Bgs[calculator.frame_count](1) = 0;
                calculator.Bgs[calculator.frame_count](2) = 0;
//                calculator.Bas[calculator.frame_count](0) = ba_buf.front().point.x;
//                calculator.Bas[calculator.frame_count](1) = ba_buf.front().point.y;
//                calculator.Bas[calculator.frame_count](2) = ba_buf.front().point.z;
//
//                calculator.Bgs[calculator.frame_count](0) = bg_buf.front().point.x;
//                calculator.Bgs[calculator.frame_count](1) = bg_buf.front().point.y;
//                calculator.Bgs[calculator.frame_count](2) = bg_buf.front().point.z;
                calculator.Headers[calculator.frame_count] = dis_msg->header;
                calculator.vector2double();
                optimization();
                cout<<"optimize finished"<<endl;
                cout<<"frame_count:"<<calculator.frame_count<<endl;
                for(int i = 0; i < 10; i++)
                {
                    calculator.Ps[i] = Vector3d (calculator.para_Pose[i][0], calculator.para_Pose[i][1], calculator.para_Pose[i][2]);
                }    
                
                cout<<"Ps:"<<calculator.para_Pose[0][0]<<","<<calculator.para_Pose[0][1]<<","<<calculator.para_Pose[0][2]<<endl;
                Visualization(calculator.Ps[0], calculator.Headers[0]);
                calculator.slidewindow();           

            }
            else
            {
                for(int i = 0; i<6; i++)
                {
                    calculator.dis[calculator.frame_count][i] = dis_msg->values[i];
                    cout<<"ap_dis"<<i<<":"<<dis_msg->values[i]<<endl;
                }
                calculator.Bas[calculator.frame_count](0) = 0;
                calculator.Bas[calculator.frame_count](1) = 0;
                calculator.Bas[calculator.frame_count](2) = 0;

                calculator.Bgs[calculator.frame_count](0) = 0;
                calculator.Bgs[calculator.frame_count](1) = 0;
                calculator.Bgs[calculator.frame_count](2) = 0;
                calculator.Headers[calculator.frame_count] = dis_msg->header;
                calculator.frame_count ++;
            }
            


        }
    }
}

void Calculator::processIMU(double dt, const Vector3d &linear_acceleration, const Vector3d &angular_velocity)
{
    if (!first_imu)
    {
        first_imu = true;
        acc_0 = linear_acceleration;
        gyr_0 = angular_velocity;
    }

    if (!pre_integrations[frame_count])
    {
        pre_integrations[frame_count] = new IntegrationBase{acc_0, gyr_0, Bas[frame_count], Bgs[frame_count]};
    }
    if (frame_count != 0)
    {
        pre_integrations[frame_count]->push_back(dt, linear_acceleration, angular_velocity);
        // int j = frame_count;         
        // Vector3d un_acc_0 = Rs[j] * (acc_0 - Bas[j]) - g;
        // Vector3d un_gyr = 0.5 * (gyr_0 + angular_velocity) - Bgs[j];
        // Rs[j] *= Utility::deltaQ(un_gyr * dt).toRotationMatrix();
        // Vector3d un_acc_1 = Rs[j] * (linear_acceleration - Bas[j]) - g;
        // Vector3d un_acc = 0.5 * (un_acc_0 + un_acc_1);
        // Ps[j] += dt * Vs[j] + 0.5 * dt * dt * un_acc;
        // Vs[j] += dt * un_acc;
        // cout<<"Ps"<<j<<","<<Ps[j]<<endl;
    }
    acc_0 = linear_acceleration;
    gyr_0 = angular_velocity;
}

struct toa_cost_function_define {

    template <typename T>
    bool operator()(const T* const x, T* residual) const{
    
    // calculator.AP_temp(8,3);
    calculator.AP_temp << 0, 0, 1.85,
                        0, 1.3, 0.15,
                        0, 2.6, 0.15,
                        2, 0, 1.85,
                        0, 4, 1.85,
                        2, 4, 1.85;

    double a1[6], a2[6], a3[6];

    
    for(int i = 0; i < calculator.AP_NUM; i++)
    {
        a1[i] = calculator.AP_temp(i,0);
        a2[i] = calculator.AP_temp(i,1);
        a3[i] = calculator.AP_temp(i,2);
        residual[i] = (T(a1[i]) - x[0]) * (T(a1[i]) - x[0]) +
                    (T(a2[i]) - x[1]) * (T(a2[i]) - x[1]) +
                    (T(a3[i]) - x[2]) * (T(a3[i]) - x[2]) - T(calculator.distance(i) * T(calculator.distance(i)));
    }
    return true;
    }
};

void optimization()
{
    using ceres::AutoDiffCostFunction;
    using ceres::CostFunction;
    using ceres::Problem;
    using ceres::Solver;
    using ceres::Solve;
    // MatrixXd AP(3,AP_NUM);
    // MatrixXd AP_temp(AP_NUM,3);
    // VectorXd distance(AP_NUM);
    // Vector3d delta_AP2P[AP_NUM];
    // calculator.AP1 << 2, 2, 1;
    // calculator.AP2 << 3, -4, -1;
    // calculator.AP3 << 6, 1, 2;  //ap_position
    //AP = AP_temp.trampose();
    Problem problem;
    Solver::Options options;
    options.max_num_iterations = 100;
    options.linear_solver_type = ceres::DENSE_QR;
    //options.minimizer_progress_to_stdout = true;
    Solver::Summary summary;


    for(int i = 0; i < calculator.WINDOW_SIZE; i++)
    {
        for(int j = 0; j < calculator.AP_NUM; j++)
        {
            calculator.distance(j) = calculator.dis[i][j];
            CostFunction* toa_costfunction = new AutoDiffCostFunction<toa_cost_function_define, 6, 7>(
            new toa_cost_function_define);
            // problem.AddResidualBlock(toa_costfunction,NULL,calculator.p_Pose[i]);
            problem.AddResidualBlock(toa_costfunction,NULL,calculator.para_Pose[i]);
        }
    }

    for (int i = 0; i < calculator.WINDOW_SIZE; i++)
    {
        int j = i + 1;
        IMUFactor* imu_factor = new IMUFactor(calculator.pre_integrations[j]);
        problem.AddResidualBlock(imu_factor, NULL, calculator.para_Pose[i], calculator.para_SpeedBias[i], 
                                                calculator.para_Pose[j], calculator.para_SpeedBias[j]);
        // problem.AddResidualBlock(imu_factor, NULL, calculator.p_Pose[i], calculator.q_Pose[i], calculator.para_SpeedBias[i], 
        //                                         calculator.p_Pose[j], calculator.q_Pose[j], calculator.para_SpeedBias[j]);
    }
    Solve(options,&problem,&summary);
}

void Calculator::slidewindow()
{
    Eigen::Vector3d bb_temp_0(0,0,0);
    for (int i = 0; i < WINDOW_SIZE; i++)
    {
        Rs[i].swap(Rs[i + 1]);

        std::swap(pre_integrations[i], pre_integrations[i + 1]);
        Headers[i] = Headers[i + 1];
        Bas[i].swap(Bas[i + 1]);
        Bgs[i].swap(Bgs[i + 1]);
        for (int j = 0; j < AP_NUM; j++)
        {
            std::swap(dis[i][j], dis[i+1][j]);
        }
        

    }
    Headers[WINDOW_SIZE] = Headers[WINDOW_SIZE - 1];
    Bas[WINDOW_SIZE] = Bas[WINDOW_SIZE - 1];
    Bgs[WINDOW_SIZE] = Bgs[WINDOW_SIZE - 1];


    delete pre_integrations[WINDOW_SIZE];
    pre_integrations[WINDOW_SIZE] = new IntegrationBase{acc_0, gyr_0, Bas[WINDOW_SIZE], Bgs[WINDOW_SIZE]};

}

void Visualization(const Eigen::Vector3d &pi, const std_msgs::Header &header)
{
    visualization_msgs::Marker marker;

    marker.header.stamp = ros::Time::now();
    marker.header.frame_id = "world";
    

    // 设置该标记的命名空间和ID，ID应该是独一无二的
    // 具有相同命名空间和ID的标记将会覆盖前一个
    marker.ns = "basic_shapes";
    marker.id = 0;
 
    // 设置标记类型，初始值为立方体。在立方体、球体、箭头和 圆柱体之间循环
    marker.type = visualization_msgs::Marker::CUBE;

    // 设置标记行为：ADD（添 加），DELETE（删 除）
    marker.action = visualization_msgs::Marker::ADD;

    //设置标记位姿。 
    marker.pose.position.x = pi.x();
    marker.pose.position.y = pi.y();
    marker.pose.position.z = pi.z();

    //统一设置旋转，大小，颜色
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;

    marker.scale.x = 0.17;
    marker.scale.y = 0.17;
    marker.scale.z = 0.01;


    marker.color.r = 0.0f;
    marker.color.g = 0.0f;
    marker.color.b = 1.0f;
    marker.color.a = 1.0f;

    marker_pub.publish(marker);
}





void Calculator::vector2double()
{
    for (int i = 0; i <= WINDOW_SIZE; i++)
    {
        // p_Pose[i][0] = Ps[i].x();
        // p_Pose[i][1] = Ps[i].y();
        // p_Pose[i][2] = Ps[i].z();
        // Quaterniond q{Rs[i]};
        // q_Pose[i][0] = q.x();
        // q_Pose[i][1] = q.y();
        // q_Pose[i][2] = q.z();
        // q_Pose[i][3] = q.w();

        para_Pose[i][0] = Ps[i].x();
        para_Pose[i][1] = Ps[i].y();
        para_Pose[i][2] = Ps[i].z();
        Quaterniond q{Rs[i]};
        para_Pose[i][3] = q.x();
        para_Pose[i][4] = q.y();
        para_Pose[i][5] = q.z();
        para_Pose[i][6] = q.w();

        para_SpeedBias[i][0] = Vs[i].x();
        para_SpeedBias[i][1] = Vs[i].y();
        para_SpeedBias[i][2] = Vs[i].z();

        para_SpeedBias[i][3] = Bas[i].x();
        para_SpeedBias[i][4] = Bas[i].y();
        para_SpeedBias[i][5] = Bas[i].z();

        para_SpeedBias[i][6] = Bgs[i].x();
        para_SpeedBias[i][7] = Bgs[i].y();
        para_SpeedBias[i][8] = Bgs[i].z();
    }
    cout<<"P:"<<p_Pose[0][0]<<"q:"<<q_Pose[0][0]<<"speed:"<<para_SpeedBias[0][0]<<endl;
}


int main(int argc, char **argv) {

    ros::init(argc,argv,"toa_imu");
    ros::NodeHandle n;
    cout<<"waiting for distance and imu......"<<endl;
    imu_flag = 0;
    
    point = n.advertise<geometry_msgs::Point>("/dis_point",100);
    marker_pub = n.advertise<visualization_msgs::Marker>("dis_pose_marker", 100);
    pub_path = n.advertise<nav_msgs::Path>("path", 100);

//    ros::Subscriber bg_sub = n.subscribe("/bg",100, &bg_callback);
//    ros::Subscriber ba_sub = n.subscribe("/ba",100, &ba_callback);
    ros::Subscriber distance_sub = n.subscribe("/crazyflie/log_ranges", 1000, distance_callback);
    ros::Subscriber imu_sub = n.subscribe("/crazyflie/imu", 2000, imu_callback, ros::TransportHints().tcpNoDelay());

    std::thread measurement_process{process};
    
    ros::spin();
    return 0;

}