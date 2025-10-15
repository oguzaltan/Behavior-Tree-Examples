#include <iostream>
#include "behaviortree_cpp/action_node.h"
#include "behaviortree_cpp/bt_factory.h"

using namespace BT;

class PrintNumber : public BT::SyncActionNode
{
public:
  PrintNumber(const std::string& name, const BT::NodeConfig& config)
    : BT::SyncActionNode(name, config)
  {}

  NodeStatus tick() override
  {
    const int val = getInput<int>("val").value();
    // If you prefer not having a port and accessing the top-level blackboard
    // directly with an hardcoded address... you should question your own choices!
    // But this is the way it is done
    // val = config().blackboard-><int>("@value");
    std::cout << "[" << name() << "] val: " << val << std::endl;
    return NodeStatus::SUCCESS;
  }

  static BT::PortsList providedPorts()
  {
    return { BT::InputPort<int>("val") };
  }
};