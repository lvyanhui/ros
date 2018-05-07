#include <ros/ros.h>
#include <service_test/Add.h>


int main(int argc, char** argv) {
    ros::init(argc, argv, "add");

    ros::NodeHandle nh;

    ros::ServiceClient client = nh.serviceClient<service_test::Add> ("add");
    service_test::Add service;
     service.request.a = 1;
     service.request.b = 2;
     if(client.call(service)) {
         ROS_INFO("Sum:%d", service.response.sum);
     } else {
         ROS_INFO("service call error");
     }

}

