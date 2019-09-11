#pragma once
#include <ros/assert.h>
#include <iostream>
#include <eigen3/Eigen/Dense>

#include "utility.h"
#include "integration_base.h"

#include <ceres/ceres.h>

class IMUFactor : public ceres::SizedCostFunction<15, 7, 9, 7, 9>
{
  public:
    IMUFactor() = delete;
    IMUFactor(IntegrationBase* _pre_integration):pre_integration(_pre_integration)
    {
    }
    virtual bool Evaluate(double const *const *parameters, double *residuals, double **jacobians) const
    {

      Eigen::Vector3d Pi(parameters[0][0], parameters[0][1], parameters[0][2]);
      Eigen::Quaterniond Qi(parameters[0][3], parameters[0][4], parameters[0][5], parameters[0][6]);

      Eigen::Vector3d Vi(parameters[1][0], parameters[1][1], parameters[1][2]);
      Eigen::Vector3d Bai(parameters[1][3], parameters[1][4], parameters[1][5]);
      Eigen::Vector3d Bgi(parameters[1][6], parameters[1][7], parameters[1][8]);

      Eigen::Vector3d Pj(parameters[2][0], parameters[2][1], parameters[2][2]);
      Eigen::Quaterniond Qj(parameters[2][3], parameters[2][4], parameters[2][5], parameters[2][6]);

      Eigen::Vector3d Vj(parameters[3][0], parameters[3][1], parameters[3][2]);
      Eigen::Vector3d Baj(parameters[3][3], parameters[3][4], parameters[3][5]);
      Eigen::Vector3d Bgj(parameters[3][6], parameters[3][7], parameters[3][8]);

      // Eigen::Vector3d Pi(parameters[0][0], parameters[0][1], parameters[0][2]);

      // Eigen::Quaterniond Qi(parameters[1][0], parameters[1][1], parameters[1][2], parameters[1][3]);

      // Eigen::Vector3d Vi(parameters[2][0], parameters[2][1], parameters[2][2]);
      // Eigen::Vector3d Bai(parameters[2][3], parameters[2][4], parameters[2][5]);
      // Eigen::Vector3d Bgi(parameters[2][6], parameters[2][7], parameters[2][8]);

      // Eigen::Vector3d Pj(parameters[3][0], parameters[3][1], parameters[3][2]);

      // Eigen::Quaterniond Qj(parameters[4][0], parameters[4][1], parameters[4][2], parameters[4][3]);

      // Eigen::Vector3d Vj(parameters[5][0], parameters[5][1], parameters[5][2]);
      // Eigen::Vector3d Baj(parameters[5][3], parameters[5][4], parameters[5][5]);
      // Eigen::Vector3d Bgj(parameters[5][6], parameters[5][7], parameters[5][8]);


      Eigen::Map<Eigen::Matrix<double, 15, 1>> residual(residuals);
      residual = pre_integration->evaluate(Pi, Qi, Vi, Bai, Bgi,
                                          Pj, Qj, Vj, Baj, Bgj);

      Eigen::Matrix<double, 15, 15> sqrt_info = Eigen::LLT<Eigen::Matrix<double, 15, 15>>(pre_integration->covariance.inverse()).matrixL().transpose();
      //sqrt_info.setIdentity();
      residual = sqrt_info * residual;

      if (jacobians)
      {
          double sum_dt = pre_integration->sum_dt;
          Eigen::Matrix3d dp_dba = pre_integration->jacobian.template block<3, 3>(0, 9);
          Eigen::Matrix3d dp_dbg = pre_integration->jacobian.template block<3, 3>(0, 12);

          Eigen::Matrix3d dq_dbg = pre_integration->jacobian.template block<3, 3>(3, 12);

          Eigen::Matrix3d dv_dba = pre_integration->jacobian.template block<3, 3>(6, 9);
          Eigen::Matrix3d dv_dbg = pre_integration->jacobian.template block<3, 3>(6, 12);

          if (pre_integration->jacobian.maxCoeff() > 1e8 || pre_integration->jacobian.minCoeff() < -1e8)
          {
            ROS_WARN("numerical unstable in preintegration");
            //std::cout << pre_integration->jacobian << std::endl;
            //ROS_BREAK();
          }

          if (jacobians[0])
          {
            Eigen::Map<Eigen::Matrix<double, 15, 7, Eigen::RowMajor>> jacobian_pose_i(jacobians[0]);
            jacobian_pose_i.setZero();

            jacobian_pose_i.block<3, 3>(0, 0) = -Qi.inverse().toRotationMatrix();
            jacobian_pose_i.block<3, 3>(0, 3) = Utility::skewSymmetric(Qi.inverse() * (0.5 * G * sum_dt * sum_dt + Pj - Pi - Vi * sum_dt));
#if 0
        jacobian_pose_i.block<3, 3>(3, 3) = -(Qj.inverse() * Qi).toRotationMatrix();
#else
            Eigen::Quaterniond corrected_delta_q = pre_integration->delta_q * Utility::deltaQ(dq_dbg * (Bgi - pre_integration->linearized_bg));
            jacobian_pose_i.block<3, 3>(3, 3) = -(Utility::Qleft(Qj.inverse() * Qi) * Utility::Qright(corrected_delta_q)).bottomRightCorner<3, 3>();
#endif

            jacobian_pose_i.block<3, 3>(6, 3) = Utility::skewSymmetric(Qi.inverse() * (G * sum_dt + Vj - Vi));

            jacobian_pose_i = sqrt_info * jacobian_pose_i;

            if (jacobian_pose_i.maxCoeff() > 1e8 || jacobian_pose_i.minCoeff() < -1e8)
            {
                ROS_WARN("numerical unstable in preintegration");
                //std::cout << sqrt_info << std::endl;
                //ROS_BREAK();
            }
          }
          if (jacobians[1])
          {
            Eigen::Map<Eigen::Matrix<double, 15, 9, Eigen::RowMajor>> jacobian_speedbias_i(jacobians[1]);
            jacobian_speedbias_i.setZero();
            jacobian_speedbias_i.block<3, 3>(0, 6 - 6) = -Qi.inverse().toRotationMatrix() * sum_dt;
            jacobian_speedbias_i.block<3, 3>(0, 9 - 6) = -dp_dba;
            jacobian_speedbias_i.block<3, 3>(0, 12 - 6) = -dp_dbg;

#if 0
        jacobian_speedbias_i.block<3, 3>(3, 12 - 6) = -dq_dbg;
#else
            //Eigen::Quaterniond corrected_delta_q = pre_integration->delta_q * Utility::deltaQ(dq_dbg * (Bgi - pre_integration->linearized_bg));
            //jacobian_speedbias_i.block<3, 3>(3, 12 - 6) = -Utility::Qleft(Qj.inverse() * Qi * corrected_delta_q).bottomRightCorner<3, 3>() * dq_dbg;
            jacobian_speedbias_i.block<3, 3>(3, 12 - 6) = -Utility::Qleft(Qj.inverse() * Qi * pre_integration->delta_q).bottomRightCorner<3, 3>() * dq_dbg;
#endif

            jacobian_speedbias_i.block<3, 3>(6, 6 - 6) = -Qi.inverse().toRotationMatrix();
            jacobian_speedbias_i.block<3, 3>(6, 9 - 6) = -dv_dba;
            jacobian_speedbias_i.block<3, 3>(6, 12 - 6) = -dv_dbg;

            jacobian_speedbias_i.block<3, 3>(9, 9 - 6) = -Eigen::Matrix3d::Identity();

            jacobian_speedbias_i.block<3, 3>(12, 12 - 6) = -Eigen::Matrix3d::Identity();

            jacobian_speedbias_i = sqrt_info * jacobian_speedbias_i;

            //ROS_ASSERT(fabs(jacobian_speedbias_i.maxCoeff()) < 1e8);
            //ROS_ASSERT(fabs(jacobian_speedbias_i.minCoeff()) < 1e8);
          }
          if (jacobians[2])
          {
            Eigen::Map<Eigen::Matrix<double, 15, 7, Eigen::RowMajor>> jacobian_pose_j(jacobians[2]);
            jacobian_pose_j.setZero();

            jacobian_pose_j.block<3, 3>(0, 0) = Qi.inverse().toRotationMatrix();

#if 0
        jacobian_pose_j.block<3, 3>(3, 3) = Eigen::Matrix3d::Identity();
#else
            Eigen::Quaterniond corrected_delta_q = pre_integration->delta_q * Utility::deltaQ(dq_dbg * (Bgi - pre_integration->linearized_bg));
            jacobian_pose_j.block<3, 3>(3, 3) = Utility::Qleft(corrected_delta_q.inverse() * Qi.inverse() * Qj).bottomRightCorner<3, 3>();
#endif

            jacobian_pose_j = sqrt_info * jacobian_pose_j;

            //ROS_ASSERT(fabs(jacobian_pose_j.maxCoeff()) < 1e8);
            //ROS_ASSERT(fabs(jacobian_pose_j.minCoeff()) < 1e8);
          }
          if (jacobians[3])
          {
            Eigen::Map<Eigen::Matrix<double, 15, 9, Eigen::RowMajor>> jacobian_speedbias_j(jacobians[3]);
            jacobian_speedbias_j.setZero();

            jacobian_speedbias_j.block<3, 3>(6, 6 - 6) = Qi.inverse().toRotationMatrix();

            jacobian_speedbias_j.block<3, 3>(9, 9 - 6) = Eigen::Matrix3d::Identity();

            jacobian_speedbias_j.block<3, 3>(12, 12 - 6) = Eigen::Matrix3d::Identity();

            jacobian_speedbias_j = sqrt_info * jacobian_speedbias_j;

            //ROS_ASSERT(fabs(jacobian_speedbias_j.maxCoeff()) < 1e8);
            //ROS_ASSERT(fabs(jacobian_speedbias_j.minCoeff()) < 1e8);
          }
      }
      return true;
    }
    Eigen::Vector3d G{0.0, 0.0, 9.8};
    IntegrationBase* pre_integration;
};

