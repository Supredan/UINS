cmake_minimum_required(VERSION 3.5.1)
project(toa_imu)


set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "-std=c++11")
#-DEIGEN_USE_MKL_ALL")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -g")

find_package(catkin REQUIRED COMPONENTS
    roscpp
    std_msgs
    geometry_msgs
    nav_msgs
    tf
    cv_bridge
    image_transport
    message_generation
    crazyflie_cpp
    crazyflie_driver
)

find_package(OpenCV REQUIRED)

message(WARNING "OpenCV_VERSION: ${OpenCV_VERSION}")

find_package(Ceres REQUIRED)

include_directories(${catkin_INCLUDE_DIRS} ${CERES_INCLUDE_DIRS})

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
find_package(Eigen3)
include_directories(
  ${catkin_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIR}
  include
)


catkin_package(
        CATKIN_DEPENDS
        message_runtime
        std_msgs
        tf
        crazyflie_cpp
)
#catkin_package(  INCLUDE_DIRS include
#  CATKIN_DEPENDS  roscpp geometry_msgs)
#
add_library(toa_imu_lib
    include/toa_imu.h
    include/utility.h
    include/integration_base.h)


target_link_libraries(toa_imu_lib ${catkin_LIBRARIES} ${OpenCV_LIBS} ${CERES_LIBRARIES})


add_executable(toa_imu src/toa_imu.cpp)
add_dependencies(toa_imu
        crazyflie_driver_generate_messages_cpp
        )
target_link_libraries(toa_imu toa_imu_lib) 