#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/Vector3.h>
#include <geometry_msgs/Twist.h> 
#include <visualization_msgs/Marker.h>
#include <vector>
#include <string>
#include <sstream>

ros::Publisher marker_pub;
visualization_msgs::Marker line_strip;

//quaternion values
float q_x;
float q_y;
float q_z;
float q_w;

void chatterCallback(const geometry_msgs::Vector3& msg) {
	ROS_INFO_STREAM("I Heard: " <<msg.x << ", " << msg.y << ", "
		<< msg.z); 
	visualization_msgs::Marker marker;
	
	marker.header.frame_id = line_strip.header.frame_id = "/my_frame";
    	marker.header.stamp = line_strip.header.stamp = ros::Time::now();	
	marker.ns =  line_strip.ns = "basic_shapes";
    	marker.id = 0;
        marker.type = visualization_msgs::Marker::CUBE;
	marker.action = line_strip.action = visualization_msgs::Marker::ADD;
	marker.pose.position.x = msg.x;
    	marker.pose.position.y = msg.z;
    	marker.pose.position.z = msg.y;
    	marker.pose.orientation.x = q_x;
   	marker.pose.orientation.y = q_y;
    	marker.pose.orientation.z = q_z;
    	marker.pose.orientation.w = q_w;
 	marker.scale.x = 1.0;
   	marker.scale.y = 1.0;
   	marker.scale.z = 1.0;
	marker.color.r = 0.0f;
    	marker.color.g = 1.0f;
    	marker.color.b = 0.0f;
    	marker.color.a = 1.0;	
        marker.lifetime = ros::Duration();
	marker_pub.publish(marker);


        line_strip.pose.orientation.w = 1.0;
    	line_strip.id = 1;
    	line_strip.type = visualization_msgs::Marker::LINE_STRIP;
	line_strip.scale.x = 0.01;
	line_strip.color.r = 1.0;
        line_strip.color.a = 1.0;

	geometry_msgs::Point p;	
	p.x = msg.x;
	p.y = msg.z;
	p.z = msg.y; 
	line_strip.points.push_back(p); 
	marker_pub.publish(line_strip);
	

}

void quaternionCallback(const geometry_msgs::Twist& msg)
{
	q_y = msg.linear.x;
	q_w = msg.linear.y; 
	q_x = -msg.linear.z; 
	q_z = msg.angular.x; 
	ROS_INFO_STREAM("I Heard Quaternion: " << q_x << ", " << q_y << ", " << q_z << ", " << q_w); 

}


int main(int argc, char **argv)
{
	
	
	ros::init(argc, argv, "listener"); 
	ros::NodeHandle n; 
	marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

	ros::Subscriber sub = n.subscribe("simple_coordinates/chatter", 1000, chatterCallback); 
	ros::Subscriber quaternionSub = n.subscribe("simple_coordinates/quaternionChatter", 1000, quaternionCallback);
	ros::spin();
	
	return 0; 


}
