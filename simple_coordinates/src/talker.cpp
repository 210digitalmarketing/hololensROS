#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/Vector3.h>
#include <sstream>


int main(int argc, char **argv)
{

	ros::init(argc, argv, "talker");
	ros::NodeHandle n; 
	ros::Publisher chatter_pub = n.advertise<geometry_msgs::Vector3>("simple_coordinates/chatter", 1000);	
	ros::Rate loop_rate(10); 
	int count = 0; 
	while (ros::ok())
	{
	    geometry_msgs::Vector3 msg; 
	    msg.x = 0;
	    msg.y = 0;
	    msg.z = 0; 
	    chatter_pub.publish(msg);
            ros::spinOnce();
	    loop_rate.sleep();
	    ROS_INFO_STREAM("SENDING: " <<msg.x << ", " << msg.y << ", "
		<< msg.z); 
	}

   return 0; 

	
}

