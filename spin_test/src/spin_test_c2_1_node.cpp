#include <ros/ros.h>
#include <std_msgs/String.h>
#include <thread>

void talkCallback(const std_msgs::String& msg) {
    ROS_INFO("I heard: [%s] in thread %d", msg.data.c_str(), std::this_thread::get_id()); 
    sleep(-1);
}

void talkCallback2(const std_msgs::String& msg) {
    ROS_INFO("I also heard: [%s] in thread %d", msg.data.c_str(), std::this_thread::get_id()); 
}

void spinThread() {
    ros::spin();
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "listen");

    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("topic", 10, talkCallback);
    ros::Subscriber sub2 = nh.subscribe("topic2", 10, talkCallback2);
 
    std::thread spin_thread = std::thread(std::bind(&spinThread));

    //ros::spin();
    
    ros::Rate loop(10);
    while(ros::ok()) {
        ros::spinOnce();    
        loop.sleep();
    }
    
    spin_thread.join();
    
    return 0;
}
