#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joy.hpp"
#include "geometry_msgs/msg/twist.hpp"

class JoyToCmdVelConverter : public rclcpp::Node
{
public:
    JoyToCmdVelConverter() : Node("joy_to_cmd_vel_converter")
    {
        joy_sub_ = this->create_subscription<sensor_msgs::msg::Joy>(
            "/joy", 10, std::bind(&JoyToCmdVelConverter::joyCallback, this, std::placeholders::_1));

        cmd_vel_pub_ = this->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);
    }

private:
    void joyCallback(const sensor_msgs::msg::Joy::SharedPtr joy_msg)
    {
        auto cmd_vel_msg = std::make_unique<geometry_msgs::msg::Twist>();
        cmd_vel_msg->linear.x = joy_msg->axes[1];
        cmd_vel_msg->angular.z = joy_msg->axes[0];

        cmd_vel_pub_->publish(std::move(cmd_vel_msg));
    }

    rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr joy_sub_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_pub_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<JoyToCmdVelConverter>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
