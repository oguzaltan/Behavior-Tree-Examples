cmake_minimum_required(VERSION 3.8)
project(bt_with_ros2)

# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
	set(CMAKE_CXX_STANDARD 17)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(ament_index_cpp REQUIRED)
find_package(behaviortree_cpp REQUIRED)

add_library(bt_with_ros2_nodes SHARED
	src/print_message_node.cpp
)
target_compile_definitions(bt_with_ros2_nodes PRIVATE BT_PLUGIN_EXPORT)
target_link_libraries(bt_with_ros2_nodes
	behaviortree_cpp::behaviortree_cpp
)
ament_target_dependencies(bt_with_ros2_nodes rclcpp ament_index_cpp behaviortree_cpp)

add_executable(bt_coordinator
	src/bt_coordinator.cpp
)
target_link_libraries(bt_coordinator
	behaviortree_cpp::behaviortree_cpp
)
ament_target_dependencies(bt_coordinator rclcpp ament_index_cpp behaviortree_cpp)

install(TARGETS
	bt_with_ros2_nodes
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	RUNTIME DESTINATION bin
)

install(TARGETS
	bt_coordinator
	RUNTIME DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY behavior_trees/
	DESTINATION share/${PROJECT_NAME}/behavior_trees
)

install(FILES plugin_description.xml
	DESTINATION share/${PROJECT_NAME}
)

ament_package()
