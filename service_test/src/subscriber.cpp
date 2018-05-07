#include <ros/ros.h>
#include <std_msgs/String.h>
#include <service_test/Add.h>

void talkCallback(const std_msgs::String& msg) {
    ROS_INFO("I heard: [%s]", msg.data.c_str()); 
}

bool add(service_test::Add::Request &req, service_test::Add::Response &res){
    ros::Rate loop(1);
    int count = 10;
    while(count--) {
        ros::spinOnce();
        loop.sleep();
    }

    ROS_INFO("service_test: add...");
    res.sum = req.a + req.b;
    ROS_INFO("%d+%d = %d", req.a, req.b, res.sum);
    return true;
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "listen");

    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe("topic", 100, talkCallback);
    ros::ServiceServer service = nh.advertiseService("add", add);


    ros::Rate loop(1);
    while(ros::ok()) {
        ros::spinOnce();
        loop.sleep();
    }

    //ros::spin();
    return 0;


}
