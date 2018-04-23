#include <ros/ros.h>
#include <std_msgs/String.h>
#include <thread>

void talkCallback(const std_msgs::String& msg) {
    ROS_INFO("I heard: [%s]", msg.data.c_str()); 
}

void talkCallback2(const std_msgs::String& msg) {
    ROS_INFO("I also heard: [%s]", msg.data.c_str()); 
}

void traceThread() {
    
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("topic2", 10, talkCallback2);
    
    ros::Rate loop(10);
    while(ros::ok()) {
        
        loop.sleep();
    }
}

void spinThread() {
    //ros::spin();
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "listen");

    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("topic", 10, talkCallback);
 
    //std::thread spin_thread = std::thread(std::bind(&spinThread));
    std::thread trace_thread = std::thread(std::bind(&traceThread));

    ros::spin();
    //spin_thread.join();
    trace_thread.join();
    return 0;
}
