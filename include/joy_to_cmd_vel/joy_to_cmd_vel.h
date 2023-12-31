// joy_to_cmd_vel/joy_to_cmd_vel.h
#ifndef JOY_TO_CMD_VEL_H
#define JOY_TO_CMD_VEL_H

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>
#include "joy_to_cmd_vel/JOY2RPM.h"

#define LINEAR_MAX 0.5
#define ANGULAR_MAX 1.0
#define ACC_LINEAR 0.1
#define ACC_ANGULAR 0.2

#define M_PI 3.14159265359

#define WHEEL_RADIUS 0.1  // Meter

class JoyToCmdVelConverter
{
public:
  JoyToCmdVelConverter();

  void run();

private:
  void joyCallback(const sensor_msgs::Joy::ConstPtr& joy_msg);

  ros::NodeHandle nh_;
  ros::Subscriber joy_sub_;
  ros::Publisher cmd_vel_pub_;
  ros::Publisher rpm_;

  float target_lin;
  float target_ang;
  float current_lin;
  float current_ang;

  float rpm_to_mps = 60 / (2 * M_PI * WHEEL_RADIUS);

  float acceleration(float current, float target, float acc);
};

#endif  // JOY_TO_CMD_VEL_H
