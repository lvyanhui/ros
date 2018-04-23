#include <ros/ros.h>
#include <std_msgs/String.h>

void talkCallback(const std_msgs::String& msg) {
    ROS_INFO("I heard: [%s]", msg.data.c_str()); 
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "listen");

    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("topic", 10, talkCallback);

    ros::spin();
    return 0;


}
