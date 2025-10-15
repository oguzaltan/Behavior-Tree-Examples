#include "crossdoor_nodes.h"
#include "behaviortree_cpp/bt_factory.h"

/** This is a more complex example that uses Fallback,
 * Decorators and Subtrees
 *
 * For the sake of simplicity, we aren't focusing on ports remapping to the time being.
 */

int main()
{
  BT::BehaviorTreeFactory factory;

  CrossDoor cross_door;
  cross_door.registerNodes(factory);

  // In this example a single XML contains multiple <BehaviorTree>
  // To determine which one is the "main one", we should first register
  // the XML and then allocate a specific tree, using its ID

  // factory.registerBehaviorTreeFromText(xml_text);
  factory.registerBehaviorTreeFromFile("./../bt_tree.xml");

  auto tree = factory.createTree("MainTree");

  // helper function to print the tree
  BT::printTreeRecursively(tree.rootNode());

  // Tick multiple times, until either FAILURE of SUCCESS is returned
  tree.tickWhileRunning();

  return 0;
}