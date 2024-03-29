#include <memory>
#include <utility>

#include "rclcpp/rclcpp.hpp"
#include "rclcpp/time_source.hpp"
#include "rosgraph_msgs/msg/clock.hpp"
#include "std_msgs/msg/header.hpp"


int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);

  auto node = rclcpp::Node::make_shared("time_example_node");
  auto time_publisher = node->create_publisher<rosgraph_msgs::msg::Clock>("clock", 10);
  rosgraph_msgs::msg::Clock msg;

  rclcpp::WallRate loop_rate(1.0);
  rclcpp::Duration duration(-500000000, 0);

  while (rclcpp::ok()) {
    static rclcpp::Time past = node->now();

    rclcpp::Time now = node->now();
    RCLCPP_INFO(node->get_logger(), "sec %lf nsec %ld", now.seconds(), now.nanoseconds());

    if ((now - past).nanoseconds() * 1e-9 > 5) {
      RCLCPP_INFO(node->get_logger(), "Over 5 seconds!");
      past = node->now();
    }

    msg.clock.sec = now.seconds() + duration.seconds();
    time_publisher->publish(msg);

    rclcpp::spin_some(node);
    loop_rate.sleep();
  }

  rclcpp::shutdown();

  return 0;
}
