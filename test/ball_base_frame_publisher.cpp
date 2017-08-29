#include <ros/ros.h>
#include <geometry_msgs/TransformStamped.h>
#include <tf/transform_listener.h>
#include <tf/transform_datatypes.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "ball_base_frame_publisher_node");
    ros::NodeHandle n;

    ros::Publisher stamped_transform_publisher = n.advertise<geometry_msgs::TransformStamped>("/ball_position_base_frame", 1000);
    tf::StampedTransform transform;
    tf::TransformListener listener;
    geometry_msgs::TransformStamped msg;

    ros::Rate rate(200);

    while(ros::ok()){
        try {
            listener.lookupTransform("base", "ball/base_link", ros::Time(0), transform);
            tf::transformStampedTFToMsg(transform, msg);
            stamped_transform_publisher.publish(msg);
        }
        catch (tf::TransformException &ex) {
            ROS_ERROR("%s",ex.what());
        }
        rate.sleep();
    }
    
    return 0;
}
