#include <iostream>
#include <chrono>
#include <thread>
#include "behaviortree_cpp/action_node.h"
#include "behaviortree_cpp/bt_factory.h"
#include "dummy_nodes.h"

int main()
{
  BT::BehaviorTreeFactory factory;

  factory.registerNodeType<ApproachObject>("ApproachObject");

  // Register condition as a simple callable.
  factory.registerSimpleCondition("CheckBattery", [](BT::TreeNode &){ return CheckBattery(); });

  GripperInterface gripper;

  // Register gripper actions using lambdas capturing 'gripper'.
  factory.registerSimpleAction("OpenGripper",  [&gripper](BT::TreeNode &){ return gripper.open(); });
  factory.registerSimpleAction("CloseGripper", [&gripper](BT::TreeNode &){ return gripper.close(); });

  //Create Tree
  auto tree = factory.createTreeFromFile("./../bt_tree.xml");

  //execute the tree
  tree.tickWhileRunning();

  return 0;
}