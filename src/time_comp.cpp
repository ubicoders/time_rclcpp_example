#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;

class TimeComparisonNode : public rclcpp::Node
{
public:
    TimeComparisonNode() : Node("time_comparison_node")
    {
        timer_ = this->create_wall_timer(1s, std::bind(&TimeComparisonNode::compare_time, this));
    }

private:
    void compare_time()
    {
        // ROS Time (sim_time)
        rclcpp::Time ros_time = this->now();

        // System Time
        rclcpp::Clock system_clock(RCL_SYSTEM_TIME);
        rclcpp::Time system_time = system_clock.now();

        // Steady Time
        rclcpp::Clock steady_clock(RCL_STEADY_TIME);
        rclcpp::Time steady_time = steady_clock.now();

        RCLCPP_INFO(this->get_logger(), "ROS Time: %ld", ros_time.nanoseconds());
        RCLCPP_INFO(this->get_logger(), "System Time: %ld", system_time.nanoseconds());
        RCLCPP_INFO(this->get_logger(), "Steady Time: %ld", steady_time.nanoseconds());
    }

    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TimeComparisonNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
