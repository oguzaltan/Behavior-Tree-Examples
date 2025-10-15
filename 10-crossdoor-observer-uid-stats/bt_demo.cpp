#include "crossdoor_nodes.h"
#include "behaviortree_cpp/bt_factory.h"
#include "behaviortree_cpp/loggers/bt_observer.h"

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

  // Helper function to print the tree.
  BT::printTreeRecursively(tree.rootNode());

  // The purpose of the observer is to save some statistics about the number of times
  // a certain node returns SUCCESS or FAILURE.
  // This is particularly useful to create unit tests and to check if
  // a certain set of transitions happened as expected
  BT::TreeObserver observer(tree);

  std::map<int, std::string> UID_to_path;

  // Print the unique ID and the corresponding human readable path
  // Path is also expected to be unique.
  tree.applyVisitor([&UID_to_path](BT::TreeNode* node) {
    UID_to_path[node->UID()] = node->fullPath();
    std::cout << node->UID() << " -> " << node->fullPath() << std::endl;
  });

  // Tick multiple times, until either FAILURE of SUCCESS is returned
  tree.tickWhileRunning();

  // You can access a specific statistic, using is full path or the UID
  const auto& last_action_stats = observer.getStatistics("last_action");
  assert(last_action_stats.transitions_count > 0);

  std::cout << "----------------" << std::endl;
  // print all the statistics
  for(const auto& [uid, name] : UID_to_path)
  {
    const auto& stats = observer.getStatistics(uid);

    std::cout << "[" << name << "] \tT/S/F:  " << stats.transitions_count << "/"
              << stats.success_count << "/" << stats.failure_count << std::endl;
  }

  return 0;
}