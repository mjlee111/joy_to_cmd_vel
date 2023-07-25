#include "joy_to_cmd_vel/joy_to_cmd_vel.h"

JoyToCmdVelConverter::JoyToCmdVelConverter()
{
    nh_ = ros::NodeHandle("~");

    joy_sub_ = nh_.subscribe("/joy", 10, &JoyToCmdVelConverter::joyCallback, this);

    cmd_vel_pub_ = nh_.advertise<geometry_msgs::Twist>("/joy_to_cmd", 10);
}

void JoyToCmdVelConverter::joyCallback(const sensor_msgs::Joy::ConstPtr &joy_msg)
{
    geometry_msgs::Twist cmd_vel_msg;
    cmd_vel_msg.linear.x = joy_msg->axes[1];
    cmd_vel_msg.angular.z = joy_msg->axes[3];

    cmd_vel_pub_.publish(cmd_vel_msg);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "joy_to_cmd_vel_converter");
    JoyToCmdVelConverter converter;
    ros::spin();
    return 0;
}
