#include <ros/ros.h>
#include <std_msgs/String.h>

#include <iostream>
#include <string.h>

int main(int argc, char** argv) {
    ros::init(argc,argv,"talker");
 
    ros::NodeHandle nh;

    ros::Publisher pub = nh.advertise<std_msgs::String>("topic", 1);
 
    ros::Rate loop(5);

    int count = 0;
    while(ros::ok()) {
        std_msgs::String msg;
        msg.data = "hello" + std::to_string(count);
        ROS_INFO_STREAM(msg.data);
        pub.publish(msg);


        ros::spinOnce();
        loop.sleep();
        count++;
    }

    return 0;
}
