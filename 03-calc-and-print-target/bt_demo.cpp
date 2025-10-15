#include "dummy_nodes.h"

int main()
{  
  BehaviorTreeFactory factory;
  factory.registerNodeType<CalculateGoal>("CalculateGoal");
  factory.registerNodeType<PrintTarget>("PrintTarget");

  auto tree = factory.createTreeFromFile("./../bt_tree.xml");
  tree.tickWhileRunning();
  return 0;
}