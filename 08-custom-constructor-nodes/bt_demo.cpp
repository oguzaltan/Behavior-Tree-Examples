#include "dummy_nodes.h"

int main()
{  

  /* Node Action A has a custom constructor
  The additional arguments must be passed at registration time
  */

  BT::BehaviorTreeFactory factory;
  factory.registerNodeType<Action_A>("Action_A", 42, "hello world");

  // If you prefer to specify the template parameters
  // factory.registerNodeType<Action_A, int, std::string>("Action_A", 42, "hello world");

  auto tree = factory.createTreeFromFile("./../bt_tree.xml");
  tree.tickWhileRunning();



  /*Node Action B has a default constructor and an initialize() method
  The initialize() method must be called before the first tick()
  */

  // BT::BehaviorTreeFactory factory;

  // // Register as usual, but we still need to initialize
  // factory.registerNodeType<Action_B>("Action_B");

  // // Create the whole tree. Instances of Action_B are not initialized yet
  // auto tree = factory.createTreeFromFile("./../bt_tree.xml");

  // // visitor will initialize the instances of 
  // auto visitor = [](TreeNode* node)
  // {
  //   if (auto action_B_node = dynamic_cast<Action_B*>(node))
  //   {
  //     action_B_node->initialize(69, "interesting_value");
  //   }
  // };

  // // Apply the visitor to ALL the nodes of the tree
  // tree.applyVisitor(visitor);
  // tree.tickWhileRunning();

  return 0;
}