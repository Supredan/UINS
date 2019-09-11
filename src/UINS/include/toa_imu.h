#include <ros/ros.h>
//#include <zbar.h>
#include <iostream>
#include <iomanip>
#include <sensor_msgs/image_encodings.h>
#include <geometry_msgs/PointStamped.h>
#include "sensor_msgs/PointCloud.h"
#include <visualization_msgs/Marker.h>
#include <sensor_msgs/Imu.h>
#include <nav_msgs/Path.h>

#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Core>
#include <ceres/ceres.h>

#include <camera_info_manager/camera_info_manager.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/core/core.hpp>
#include <opencv2/core/eigen.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <std_msgs/Header.h>
#include <std_msgs/Float32.h>


#include <cmath>

#include "imu_factor.h"
#include "integration_base.h"
#include "utility.h"



using namespace cv;
using namespace Eigen;
using namespace std;
using namespace message_filters;
using namespace ceres;



class Calculator
{
    public:
    Vector3d f;
    Vector3d pi;
    double td;
    double IMU_dt;
    
    // int WINDOW_SIZE;
    int count;
    int AP_NUM;

    // MatrixXd AP;
    MatrixXd AP_temp;
    VectorXd distance;    
    int frame_count;
    int current_time;
    int WINDOW_SIZE;
    double dis[11][8];
   

    IntegrationBase *pre_integrations[11];
    Vector3d acc_0, gyr_0;
    std_msgs::Header Headers[11];
    Vector3d Bas[11];       
    Vector3d Bgs[11];
    Vector3d Ps[11];
    Vector3d Vs[11];
    Matrix3d Rs[11];    
    bool first_imu;

    double p_Pose[12][3];
    double q_Pose[12][4];
    double para_Pose[12][7];
    double para_SpeedBias[12][9];


    double dis_now_msg[6];
    double latest_time{0};
    Vector3d latest_P{0,0,0}, delta_P{0,0,0}, latest_V{0,0,0}, latest_Ba{-0.0127947,0.64387,0.0560138}, latest_Bg{-0.00358294,0.0218833,0.0794294},
    latest_acc_0{0,0,0}, latest_gyr_0{0,0,0}, g{0,0,9.8}, imu_P{0,0,0};
    // Matrix<double, 15, 15> jacobian, covariance;
    Quaterniond latest_Q{0,0,0,0};
    Quaterniond delta_q{0,0,0,0};
    Quaterniond result_delta_q{0,0,0,0};

    Calculator() :  f(Vector3d::Zero()),pi(Vector3d::Zero()),td(0),IMU_dt(0),count(0),AP_NUM(6),AP_temp(MatrixXd::Zero(6,3)),
                    distance(VectorXd::Zero(6)),frame_count(0),current_time(-1),WINDOW_SIZE(10)
    {
    }
    ~Calculator(){}


// void Imu_predict(double t, Eigen::Vector3d linear_acceleration, Eigen::Vector3d angular_velocity)
    void processIMU(double t, const Vector3d &linear_acceleration, const Vector3d &angular_velocity);
    void slidewindow();
    void vector2double();
};


void distance_callback(const crazyflie_driver::GenericLogDataConstPtr& dis_msg);

void imu_callback(const sensor_msgs::ImuConstPtr& imu_msg);

//void ba_callback(const geometry_msgs::PointStamped::ConstPtr &ba_msg);
//void bg_callback(const geometry_msgs::PointStamped::ConstPtr &bg_msg);

void Visualization(const Eigen::Vector3d &pi, const std_msgs::Header &header);
void optimization();    
