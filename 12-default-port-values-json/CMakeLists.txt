cmake_minimum_required(VERSION 3.10.2)

project(bt_12_default_port_values_json)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find BehaviorTree.CPP (REQUIRED so configuration stops early if not found)
find_package(behaviortree_cpp REQUIRED)

add_executable(${PROJECT_NAME} "bt_demo.cpp")
target_link_libraries(${PROJECT_NAME} behaviortree_cpp::behaviortree_cpp)