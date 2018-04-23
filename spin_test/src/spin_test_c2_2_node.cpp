#include <ros/ros.h>
#include <std_msgs/String.h>
#include <thread>

void talkCallback(const std_msgs::String& msg) {
    ROS_INFO("I heard: [%s] in thread %d", msg.data.c_str(), std::this_thread::get_id()); 
    sleep(-1);
}

void talkCallback1(const std_msgs::String& msg) {
    ROS_INFO("I heard 1: [%s] in thread %d", msg.data.c_str(), std::this_thread::get_id()); 
    sleep(-1);
}

void talkCallback2(const std_msgs::String& msg) {
    ROS_INFO("I heard 2: [%s] in thread %d", msg.data.c_str(), std::this_thread::get_id()); 
}

void spinThread1() {
    ros::spin();
}

void spinThread2() {
    ros::Rate loop(10);
    while(ros::ok()) {
        ros::spinOnce();    
        loop.sleep();
    }
}

void spinThread() {
    ros::spin();
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "listen");

    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("topic", 10, talkCallback);
    ros::Subscriber sub1 = nh.subscribe("topic", 10, talkCallback1);
    ros::Subscriber sub2 = nh.subscribe("topic2", 10, talkCallback2);
 
    std::thread spin_thread = std::thread(std::bind(&spinThread));
    //std::thread spin_thread1 = std::thread(std::bind(&spinThread1));
    std::thread spin_thread2 = std::thread(std::bind(&spinThread2));

    //ros::spin();
    
    ros::Rate loop(10);
    while(ros::ok()) {
        ros::spinOnce();    
        loop.sleep();
    }
    
    spin_thread.join();
    //spin_thread1.join();
    spin_thread2.join();
    
    return 0;
}
