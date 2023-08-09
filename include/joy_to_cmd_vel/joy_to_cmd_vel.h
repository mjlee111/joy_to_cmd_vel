#ifndef JOY_TO_CMD_VEL_H
#define JOY_TO_CMD_VEL_H

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>

#define ACC 0.001
#define ACC_LINEAR 0.001
#define ACC_ANGULAR 0.001

class JoyToCmdVelConverter
{
public:
    JoyToCmdVelConverter();
    float currnet_lin = 0.0;
    float current_ang = 0.0;
    float acceleration(float current, float target);

private:
    void joyCallback(const sensor_msgs::Joy::ConstPtr &joy_msg);

    ros::NodeHandle nh_;
    ros::Subscriber joy_sub_;
    ros::Publisher cmd_vel_pub_;
};

#endif // JOY_TO_CMD_VEL_H
