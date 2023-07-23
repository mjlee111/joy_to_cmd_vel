#ifndef JOY_TO_CMD_VEL_H
#define JOY_TO_CMD_VEL_H

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>

class JoyToCmdVelConverter
{
public:
    JoyToCmdVelConverter();

private:
    void joyCallback(const sensor_msgs::Joy::ConstPtr &joy_msg);

    ros::NodeHandle nh_;
    ros::Subscriber joy_sub_;
    ros::Publisher cmd_vel_pub_;
};

#endif // JOY_TO_CMD_VEL_H
