#include <ros/ros.h>
#include <std_msgs/String.h>
#include <thread>

void talkCallback(const std_msgs::String& msg) {
    ROS_INFO("I heard: [%s]", msg.data.c_str()); 
}

void spinThread() {
    ros::spin();
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "listen");

    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("topic", 10, talkCallback);
 
    std::thread spin_thread = std::thread(std::bind(&spinThread));

    //ros::spin();
    spin_thread.join();
    return 0;


}
