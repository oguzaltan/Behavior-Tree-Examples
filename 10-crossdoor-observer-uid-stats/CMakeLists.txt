cmake_minimum_required(VERSION 3.10.2)

project(bt_10_crossdoor_observer_uid_stats)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find BehaviorTree.CPP (REQUIRED so configuration stops early if not found)
find_package(behaviortree_cpp REQUIRED)

add_executable(${PROJECT_NAME} "bt_demo.cpp" "crossdoor_nodes.cpp")
target_link_libraries(${PROJECT_NAME} behaviortree_cpp::behaviortree_cpp)