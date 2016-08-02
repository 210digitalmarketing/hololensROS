#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/Vector3.h>
#include <geometry_msgs/Twist.h> 
#include <sstream>


int main(int argc, char **argv)
{

	ros::init(argc, argv, "talker");
	ros::NodeHandle n; 
	ros::Publisher chatter_pub = n.advertise<geometry_msgs::Vector3>("simple_coordinates/chatter", 1000);	

	ros::Publisher quaternionChatter_pub = n.advertise<geometry_msgs::Twist>("simple_coordinates/quaternionChatter", 1000);
	
	

	ros::Rate loop_rate(10); 
	int count = 0; 
	while (ros::ok())
	{
	    geometry_msgs::Vector3 msg; 
	    msg.x = 0;
	    msg.y = 0;
	    msg.z = 0;
	    geometry_msgs::Twist quaternionMsg;
	   

	    geometry_msgs::Vector3 linear; 
	    linear.x = 1;
	    linear.y = 1;
	    linear.z = 1;
	    
            quaternionMsg.linear = linear;

	    geometry_msgs::Vector3 angular;
            angular.x = 1;
            angular.y = 0;
            angular.z = 0; 
		
	    quaternionMsg.angular = angular; 	


	    chatter_pub.publish(msg);
	    

	    quaternionChatter_pub.publish(quaternionMsg); 	
            ros::spinOnce();
	    loop_rate.sleep();
	    ROS_INFO_STREAM("SENDING: " << quaternionMsg.linear.x << ", " << quaternionMsg.linear.y << ", " << quaternionMsg.linear.z << ", " << quaternionMsg.angular.x); 

	    ROS_INFO_STREAM("SENDING: " <<msg.x << ", " << msg.y << ", " << msg.z); 
	}

   return 0; 

	
}

