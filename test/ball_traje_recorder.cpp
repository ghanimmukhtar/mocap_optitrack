#include <ros/ros.h>
#include <string>
#include <iostream>
#include <fstream>
#include <geometry_msgs/TransformStamped.h>
#include <tf/transform_listener.h>
#include <tf/transform_datatypes.h>


geometry_msgs::TransformStamped msg;
std::ofstream _output_file;

void record_ball_trajectory_callback(const geometry_msgs::PointStamped::ConstPtr& ball_position){
    _output_file << ball_position->point.x << "," << ball_position->point.y << "," << ball_position->point.z << "\n";
    /*if(ball_position->point.x != ball_position->point.x)
        return;
    if(msg.transform.translation.x == 0 && msg.transform.translation.y == 0 && msg.transform.translation.z == 0 )
        return;
    _output_file << msg.transform.translation.x << "," << msg.transform.translation.y << "," << msg.transform.translation.z << "\n";*/
    ROS_INFO("RECORDER: I am recording ball trajectory");
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "ball_trajectory_recorder_node");
    ros::NodeHandle n;

    ros::Subscriber ball_trajectory_subscriber = n.subscribe<geometry_msgs::PointStamped>("/optitrack/ball/position", 1000, record_ball_trajectory_callback);

    tf::StampedTransform transform;
    tf::TransformListener listener;

    ros::Rate rate(200);
    _output_file.open("ball_trajectory_robot_frame.csv");
    while(ros::ok()){
        ros::spinOnce();
        /*try {
            listener.lookupTransform("base", "optitrack/ball/base_link", ros::Time(0), transform);
            tf::transformStampedTFToMsg(transform, msg);
        }
        catch (tf::TransformException &ex) {
            ROS_ERROR("%s",ex.what());
        }*/
        rate.sleep();
    }
    _output_file.close();
    return 0;
}
