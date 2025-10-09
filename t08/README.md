# t08 — Custom constructor nodes (Action_A / Action_B)

This small example demonstrates how to register BehaviorTree.CPP node types that require custom constructor arguments or explicit runtime initialization.

What this example shows

- `Action_A` is a node with a non-standard constructor (it takes extra arguments).
- `Action_B` is a node that uses a separate `initialize(...)` method called before the first tick.
- How to register a node with extra constructor arguments with `BehaviorTreeFactory`.

Files to inspect

- `bt_demo.cpp` — registers `Action_A` and demonstrates the pattern.
- `dummy_nodes.h` — contains the class declarations for `Action_A` and `Action_B` (constructors, members, and `tick()` declarations).
- `CMakeLists.txt` — builds the `bt_simple_pick` executable.
- `bt_tree.xml` — (if present) example tree XML used by the demo.

Build (WSL / Bash)

From the repository root:

```bash
cmake -S t08 -B t08/build
cmake --build t08/build --parallel
```

Run

```bash
./t08/build/bt_simple_pick
```

Why you saw a linker error (vtable / undefined reference)

During a build you may have seen an error like:

  undefined reference to `vtable for Action_A`

This happens because `Action_A` declares (overrides) a virtual method (`tick()`), but there is no corresponding implementation visible to the linker. When a class has virtual methods the compiler generates a vtable and its location depends on where the out-of-line (non-inline) virtual function definitions are compiled. If you declare `tick()` in the header but never define it in any translation unit, the linker cannot find the vtable and fails.

Two ways to fix it

Option A — Quick inline implementation (fast for small demos)

Add the `tick()` implementation in the header and mark it `inline` to avoid multiple-definition issues:

```cpp
// at the end of dummy_nodes.h
inline BT::NodeStatus Action_A::tick()
{
  std::cout << "[ Action_A ] arg1=" << _arg1 << " arg2=" << _arg2 << std::endl;
  return BT::NodeStatus::SUCCESS;
}
```

Option B — Put implementations in a .cpp and add it to CMake (recommended for real projects)

1. Create `t08/dummy_nodes.cpp`:

```cpp
#include "dummy_nodes.h"

BT::NodeStatus Action_A::tick()
{
  std::cout << "[ Action_A ] arg1=" << _arg1 << " arg2=" << _arg2 << std::endl;
  return BT::NodeStatus::SUCCESS;
}

BT::NodeStatus Action_B::tick()
{
  std::cout << "[ Action_B ] arg1=" << _arg1 << " arg2=" << _arg2 << std::endl;
  return BT::NodeStatus::SUCCESS;
}
```

1. Update `t08/CMakeLists.txt` to include the new source file:

```cmake
add_executable(${PROJECT_NAME} "bt_demo.cpp" "dummy_nodes.cpp")
```

Notes about `BehaviorTreeFactory::registerNodeType` usage

- `Action_A` has a custom constructor:

```cpp
Action_A(const std::string& name, const NodeConfig& config,
         int arg_int, std::string arg_str);
```

You can register it by passing the extra arguments to the factory:

```cpp
factory.registerNodeType<Action_A>("Action_A", 42, "hello world");
```

The factory will forward the extra arguments (42, "hello world") to the node constructor when creating instances.

`Action_B` alternative initialization pattern

- `Action_B` uses an `initialize(int, string)` method to set internal parameters before the first tick. This pattern is useful when initialization is expensive or you prefer not to modify constructors. To initialize nodes in an already-created tree you can use a visitor to walk the nodes and call `initialize(...)` on instances that need it (see commented code in `bt_demo.cpp`).

Troubleshooting

- "undefined reference to vtable": see the Fix section above.
- "missing required input" runtime errors: ensure node ports are declared with `providedPorts()` and that the XML supplies required inputs or remaps ports correctly.
- CMake can't find BehaviorTree.CPP: pass `-DCMAKE_PREFIX_PATH=/path/to/behaviortree/install` to `cmake`.
