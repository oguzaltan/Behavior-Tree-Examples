#include "dummy_nodes.h"

int main()
{
  BehaviorTreeFactory factory;
  factory.registerNodeType<SaySomething>("SaySomething");

  // We can add these enums to the scripting language.
  // Check the limits of magic_enum
  factory.registerScriptingEnums<Color>();

  // Or we can manually assign a number to the label "THE_ANSWER".
  // This is not affected by any range limitation
  factory.registerScriptingEnum("THE_ANSWER", 42);

  auto tree = factory.createTreeFromFile("./../bt_tree.xml");
  tree.tickWhileRunning();

  return 0;
}