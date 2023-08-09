// joy_to_cmd_vel/joy_to_cmd_vel.h
#ifndef JOY_TO_CMD_VEL_H
#define JOY_TO_CMD_VEL_H

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>

#define CMD_MAX 0.22
#define ACC_LINEAR 0.05
#define ACC_ANGULAR 0.05

class JoyToCmdVelConverter
{
public:
    JoyToCmdVelConverter();

    void run();

private:
    void joyCallback(const sensor_msgs::Joy::ConstPtr &joy_msg);

    ros::NodeHandle nh_;
    ros::Subscriber joy_sub_;
    ros::Publisher cmd_vel_pub_;

    float target_lin;
    float target_ang;
    float current_lin;
    float current_ang;

    float acceleration(float current, float target, float acc);
};

#endif // JOY_TO_CMD_VEL_H
