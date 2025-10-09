# t09 — Scripted variables, enums and preconditions

This example demonstrates:

- Registering a custom action node (`SaySomething`) and using it from XML.
- Registering C++ enums so the tree's scripting language can use named constants (e.g., `RED`, `BLUE`).
- Using `Script` nodes to set variables on the blackboard.
- Using `Precondition` to evaluate a boolean expression and decide whether to run a subtree.
- How ports and port remapping (e.g. `message="{A}"`) pass data between Script nodes and actions.

Files

- `bt_demo.cpp` — example program. Registers nodes and enums and runs the tree.
- `bt_tree.xml` — the behavior tree. Contains `Script` nodes, a `Precondition`, and `SaySomething` actions.
- `dummy_nodes.h` — custom node implementations used by the example (`SaySomething`, `MoveBaseAction`) and a helper type `Pose2D` converter.
- `CMakeLists.txt` — builds the example executable `bt_simple_pick` (requires BehaviorTree.CPP installed).

Quick build & run (WSL / Bash)

```bash
# from the repository root
cmake -S t09 -B t09/build
cmake --build t09/build --parallel
./t09/build/bt_simple_pick
```

What to expect

- The XML first runs two `Script` nodes that set:
  - `msg` to "hello world"
  - `A` to `THE_ANSWER` (registered as 42 in the demo)
  - `B` to 3.14
  - `color` to `RED` (enum value)
- The `Precondition` checks `A>B && color != BLUE` and, if true, runs a short sequence of `SaySomething` nodes that print the values of `A`, `B`, `msg`, and `color`.

Example printed output

```
Warnings: The first tag of the XML (<root>) should contain the attribute [BTCPP_format="4"]
Please check if your XML is compatible with version 4.x of BT.CPP
----- MainTree tick ----
Robot says: 42
Robot says: 3.14
Robot says: hello world
Robot says: 1
```

Notes & troubleshooting

- If CMake cannot find BehaviorTree.CPP, install the library or set `CMAKE_PREFIX_PATH` to the install location.
- The demo uses a relative path (`./../bt_tree.xml`) in `bt_demo.cpp` — run the executable from the project root or adjust the path if you run it from elsewhere.
- The `color` value prints as a number because enums are stored as integers; if you want friendly names, convert the enum to a string before printing.
- If a node throws `missing required input`, check that the XML provides the expected port (for `SaySomething` the `message` input must be provided).
