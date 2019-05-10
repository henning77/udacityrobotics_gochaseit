#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "ball_chaser/DriveToTarget.h"
#include <std_msgs/Float64.h>

// ROS::Publisher motor commands;
ros::Publisher motor_command_publisher;

// handle_drive_request callback function that executes whenever a drive_bot service is requested
// This function publishes the requested linear x and angular velocities to the robot wheel joints
// After publishing the requested velocities, a message feedback should be returned with the requested wheel velocities
bool handle_drive_request(ball_chaser::DriveToTarget::Request& req,
    ball_chaser::DriveToTarget::Response& res)
{
    ROS_INFO("DriveToTarget request received - j1:%1.2f, j2:%1.2f", (float)req.linear_x, (float)req.angular_z);

    // TODO Publish velocities to topic
    // motor_command_publisher.publish(...);

    // TODO Return a response message
    // res.msg_feedback = "...";
    // ROS_INFO_STREAM(res.msg_feedback);

    return true;
}

int main(int argc, char** argv)
{
    // Init ROS node
    ros::init(argc, argv, "drive_bot");
    ros::NodeHandle n;

    // Inform ROS master that we will be publishing a message of type geometry_msgs::Twist on the robot actuation topic with a publishing queue size of 10
    motor_command_publisher = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

    // Define service
    ros::ServiceServer service = n.advertiseService("/ball_chaser/command_robot", handle_drive_request);
    ROS_INFO("Ready to send drive commands");

    ros::spin();
    return 0;
}