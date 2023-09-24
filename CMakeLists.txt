cmake_minimum_required(VERSION 2.8.3)
project(joy_to_cmd_vel)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  geometry_msgs
  sensor_msgs
  message_generation
)

add_message_files(FILES JOY2RPM.msg)
generate_messages(DEPENDENCIES std_msgs)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS roscpp geometry_msgs sensor_msgs
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(joy_to_cmd_vel_node src/joy_to_cmd_vel.cpp)
target_link_libraries(joy_to_cmd_vel_node ${catkin_LIBRARIES})
