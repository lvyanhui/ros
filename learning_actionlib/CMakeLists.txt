cmake_minimum_required(VERSION 2.8.3)
project(learning_actionlib)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS roscpp genmsg actionlib actionlib_msgs)
find_package(Boost REQUIRED COMPONENTS system)

add_action_files(
  DIRECTORY action
  FILES Fibonacci.action
)

add_message_files(
  DIRECTORY msg
  FILES
  beaconSetting.msg
  beaconSettings.msg
)

generate_messages(
  DEPENDENCIES actionlib_msgs std_msgs
)

catkin_package(
  CATKIN_DEPENDS actionlib_msgs
  message_runtime
)

include_directories(include ${catkin_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})

add_executable( fibonacci_server src/fibonacci_server.cpp)
target_link_libraries( fibonacci_server  ${catkin_LIBRARIES})
add_dependencies(  fibonacci_server  ${learning_actionlib_EXPORTED_TARGETS})

add_executable( fibonacci_client src/fibonacci_client.cpp)
target_link_libraries(  fibonacci_client  ${catkin_LIBRARIES})
add_dependencies(  fibonacci_client  ${learning_actionlib_EXPORTED_TARGETS})

add_executable(fibonacci_client_0 src/fibonacci_client_0.cpp)
target_link_libraries(  fibonacci_client_0  ${catkin_LIBRARIES})
add_dependencies(  fibonacci_client_0  ${learning_actionlib_EXPORTED_TARGETS})

add_executable(averaging_client src/averaging_client.cpp)
target_link_libraries( averaging_client ${catkin_LIBRARIES})
add_dependencies(  averaging_client  ${learning_actionlib_EXPORTED_TARGETS})

add_executable(averaging_client_0 src/averaging_client_0.cpp)
target_link_libraries( averaging_client_0 ${catkin_LIBRARIES})
add_dependencies(  averaging_client_0  ${learning_actionlib_EXPORTED_TARGETS})

add_executable(averaging_server src/averaging_server.cpp)
target_link_libraries( averaging_server ${catkin_LIBRARIES})
add_dependencies(  averaging_server  ${learning_actionlib_EXPORTED_TARGETS})

