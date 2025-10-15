#include "print_number_node.h"  

/**
 * This example introduces the concept of a "global blackboard",
 * and the syntax to use it.
 *
 * As you know know from previous tutorials, blackboard are "scoped",
 * i.e. each SubTree (including the one in the root) has its own
 * Blackboard, isolated by default, unless we do remapping.
 *
 * It is possible (since version 4.6) to create a global BB,
 * accessible from everywhere without remapping.
 *
 * In the example below we can access the entry "value" and
 * "value_sqr" from everywhere, as long as we use the pregix "@".
 *
 * Note as <SubTree ID="MySub"/> doesn't have any remapping
 *
 * In other words, the prefix "@" means: "search the entry in the top-level
 * blackboard of the hierarchy".
 *
 * In this case, the top-level blackboard will be [global_blackboard].
 */

//---------------------------------------------------
int main()
{
  BehaviorTreeFactory factory;

  factory.registerNodeType<PrintNumber>("PrintNumber");
  factory.registerBehaviorTreeFromFile("./../bt_tree.xml");

  // No one "own" this blackboard
  auto global_blackboard = BT::Blackboard::create();
  // This blackboard will be owned by "MainTree". Its parent is global_blackboard
  auto root_blackboard = BT::Blackboard::create(global_blackboard);

  auto tree = factory.createTree("MainTree", root_blackboard);

  // we can interact directly with global_blackboard
  for(int i = 1; i <= 3; i++)
  {
    global_blackboard->set("value", i);
    tree.tickOnce();
    int value_sqr = global_blackboard->get<int>("value_sqr");
    std::cout << "[While loop] value: " << i << " value_sqr: " << value_sqr << "\n\n";
  }

  return 0;
}