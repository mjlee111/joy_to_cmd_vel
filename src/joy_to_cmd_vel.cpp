// joy_to_cmd_vel/joy_to_cmd_vel.cpp
#include "joy_to_cmd_vel/joy_to_cmd_vel.h"

JoyToCmdVelConverter::JoyToCmdVelConverter()
    : target_lin(0.0), target_ang(0.0), current_lin(0.0), current_ang(0.0)
{
    nh_ = ros::NodeHandle("~");

    joy_sub_ = nh_.subscribe("/joy", 10, &JoyToCmdVelConverter::joyCallback, this);

    cmd_vel_pub_ = nh_.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
}

void JoyToCmdVelConverter::run()
{
    geometry_msgs::Twist cmd_vel_msg;

    current_lin = acceleration(current_lin, target_lin, ACC_LINEAR);
    current_ang = acceleration(current_ang, target_ang, ACC_ANGULAR);

    // Limit linear and angular velocities
    if (current_lin > LINEAR_MAX)
        current_lin = LINEAR_MAX;
    else if (current_lin < -LINEAR_MAX)
        current_lin = -LINEAR_MAX;

    if (current_ang > ANGULAR_MAX)
        current_ang = ANGULAR_MAX;
    else if (current_ang < -ANGULAR_MAX)
        current_ang = -ANGULAR_MAX;

    cmd_vel_msg.linear.x = current_lin;
    cmd_vel_msg.angular.z = current_ang;

    cmd_vel_pub_.publish(cmd_vel_msg);
}

void JoyToCmdVelConverter::joyCallback(const sensor_msgs::Joy::ConstPtr &joy_msg)
{
    target_lin = joy_msg->axes[1];
    target_ang = joy_msg->axes[3];
}

float JoyToCmdVelConverter::acceleration(float current, float target, float acc)
{
    if (current < target)
    {
        current = std::min(current + acc, target);
    }
    else if (current > target)
    {
        current = std::max(current - acc, target);
    }
    return current;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "joy_to_cmd_vel_converter");
    JoyToCmdVelConverter converter;
    ros::Rate loop_rate(33);
    while (ros::ok())
    {
        converter.run();
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}
