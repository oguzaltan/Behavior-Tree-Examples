#include <iostream>
#include <chrono>
#include <thread>
#include "behaviortree_cpp/action_node.h"
#include "behaviortree_cpp/bt_factory.h"

using namespace std::chrono_literals;

class ApproachObject : public BT::SyncActionNode
{
public:
  explicit ApproachObject(const std::string &name) : BT::SyncActionNode(name, {})
  {
  }

  BT::NodeStatus tick() override
  {
    std::cout << "Approach Object: " << this->name() << std::endl;

    std::this_thread::sleep_for(5s);
    return BT::NodeStatus::SUCCESS;
  }
};

BT::NodeStatus CheckBattery()
{
  std::cout << "Battery OK" << std::endl;
  return BT::NodeStatus::SUCCESS;
}

class GripperInterface
{
public:
  GripperInterface() : _open(true) {}

  BT::NodeStatus open()
  {
    _open = true;
    std::cout << "Gripper open" << std::endl;
    return BT::NodeStatus::SUCCESS;
  }

  BT::NodeStatus close()
  {
    _open = false;
    std::cout << "Gripper close" << std::endl;
    return BT::NodeStatus::SUCCESS;
  }

private:
  bool _open;
};