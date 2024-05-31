#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/vector3.hpp"
#include <memory>

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<rclcpp::Node>("node_pub2");
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
    auto mypub = node->create_publisher<geometry_msgs::msg::Vector3>("topic_pub2", 
qos_profile );
    geometry_msgs::msg::Vector3 message;
    std::cin >> message.x >> message.y >> message.z;
    rclcpp::WallRate loop_rate(1.0);

    while(rclcpp::ok())
    {
        RCLCPP_INFO(node->get_logger(), "x : %lf y : %lf z : %lf", message.x, message.y, message.z);
        mypub->publish(message);

        //rclcpp::spin_some(node);
        loop_rate.sleep(); //반복주파수에서 남은 시간 만큼 sleep
    }
    rclcpp::shutdown();
    return 0;
}
