# t06 — SubTree, Script and Ports example

This example demonstrates how to use subtrees, script nodes and ports/blackboards to pass data between trees.

Highlights

- Using a `SubTree` with port remapping (`target` / `result`).
- Using `Script` nodes to set blackboard values.
- Implementing custom node types with input ports (`MoveBase` and `SaySomething`).
- Demonstrates automatic conversion from string to a custom type (`Pose2D`).

Files of interest

- `bt_demo.cpp` — registers the example nodes, loads `bt_tree.xml` (contains `MainTree` and `MoveRobot` subtree), runs the tree and prints the blackboards of the subtrees.
- `bt_tree.xml` — the XML tree with `MainTree` that sets `move_goal`, calls the `MoveRobot` subtree and says the result; `MoveRobot` contains a `MoveBase` action and fallback/force-failure handling.
- `dummy_nodes.h` — contains `SaySomething`, `MoveBaseAction`, a `Pose2D` converter and helper functions used by the example.
- `CMakeLists.txt` — builds the `bt_simple_pick` executable and links to BehaviorTree.CPP.

Build (WSL / Bash)

From the repository root:

```bash
cmake -S t06 -B t06/build
cmake --build t06/build --parallel
```

Run

```bash
./t06/build/bt_simple_pick
```

Expected output (approximate)

When the program runs it prints action progress and the state of the two subtree blackboards. The `bt_demo.cpp` file contains an example expected output comment; the important lines look like:

```bash
[ MoveBase: SEND REQUEST ]. goal: x=1.000000 y=2.000000 theta=3.000000
[ MoveBase: FINISHED ]
Robot says: goal reached

------ First BB ------
move_result (std::string)
move_goal (Pose2D)

------ Second BB------
[result] remapped to port of parent tree [move_result]
[target] remapped to port of parent tree [move_goal]
```

Troubleshooting

- If CMake cannot find BehaviorTree.CPP, pass the install location:

```bash
cmake -S t06 -B t06/build -DCMAKE_PREFIX_PATH=/path/to/behaviortree/install
```

- If you edited `dummy_nodes.h` and added new `.cpp` files, make sure to add them to `CMakeLists.txt` so they are compiled and linked.

- If you run into XML parsing errors, confirm the demo uses `registerBehaviorTreeFromFile("./../bt_tree.xml")` (the code loads a file path, not raw XML text).

Notes

- The example includes a template specialization that converts a semicolon-separated string into a `Pose2D` value so that the `MoveBase` node can accept `goal="1;2;3"` in the XML.
- The subtree mechanism demonstrates port remapping: `SubTree ID="MoveRobot" target="{move_goal}" result="{move_result}"` maps parent / child ports.
