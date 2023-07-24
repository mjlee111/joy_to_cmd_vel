cmake_minimum_required(VERSION 3.5)
project(joy_to_cmd_vel)

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(std_msgs REQUIRED)  # Add this line
find_package(rosgraph_msgs REQUIRED)  # Add this line

# Add executable
add_executable(joy_to_cmd_vel
  src/joy_to_cmd_vel.cpp
)

# Link against dependencies
ament_target_dependencies(joy_to_cmd_vel
  rclcpp
  sensor_msgs
  geometry_msgs
  std_msgs  # Add this line
  rosgraph_msgs  # Add this line
)

# Install executable
install(TARGETS joy_to_cmd_vel
  DESTINATION lib/${PROJECT_NAME}
)

# # Install launch files
# install(DIRECTORY
#   launch
#   DESTINATION share/${PROJECT_NAME}
# )

ament_package()
