#include <ros/ros.h>
#include <std_msgs/String.h>
#include <thread>
#include <ros/callback_queue.h>

/*READ ME
   if we start a ros::spin in the main thread, 
   then start another ros::spin int sub thread,
   the two spin is really one same spin.
*/

void talkCallback(const std_msgs::String& msg) {
    ROS_INFO("I heard: [%s] in thread %d", msg.data.c_str(), std::this_thread::get_id());
    sleep(-1); //
}

void talkCallback2(const std_msgs::String::ConstPtr& msg) {
    ROS_INFO("I also heard: [%s] in thread %d", msg->data.c_str(), std::this_thread::get_id()); 
}

/*void talkCallback2(const std_msgs::String& msg) {
    ROS_INFO("I also heard: [%s]", msg.data.c_str()); 
}*/

ros::CallbackQueue g_custom_queue;
void customThread() {
    ros::NodeHandle n;
    while(n.ok()) {
        g_custom_queue.callAvailable(ros::WallDuration(0.01));
    }
}

void spinThread() {
    ros::spin();
}

void traceThread() {
    
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("topic2", 10, talkCallback2);
    
    std::thread spin_thread = std::thread(std::bind(&spinThread));
    /*ros::SubscribeOptions ops = ros::SubscribeOptions::create<std_msgs::String>("topic2", 10, &talkCallback2, ros::VoidPtr(), &g_custom_queue);
    ros::Subscriber sub2 = nh.subscribe(ops);
   
    std::thread custom_thread = std::thread(std::bind(&customThread));
    */ 

    ros::Rate loop(10);
    while(ros::ok()) {
        
        loop.sleep();
    }
    
    spin_thread.join();
    //custom_thread.join();
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "listen");

    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("topic", 10, talkCallback);
 
   
    std::thread trace_thread = std::thread(std::bind(&traceThread));

    ros::spin();

    trace_thread.join();
    return 0;
}
