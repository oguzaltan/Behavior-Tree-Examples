#include "dummy_nodes.h"

int main()
{  
  BehaviorTreeFactory factory;
  factory.registerNodeType<SaySomething>("SaySomething");
  factory.registerNodeType<ThinkWhatToSay>("ThinkWhatToSay");

  auto tree = factory.createTreeFromFile("./../bt_tree.xml");
  tree.tickWhileRunning();
  return 0;
}