# t01 — Simple pick sequence

This example shows a straightforward sequence: a battery check, opening a gripper, approaching an object, and closing the gripper.

Files of interest

- `bt_demo.cpp` — registers the demo nodes and builds the tree from `bt_tree.xml`.
- `bt_tree.xml` — the tree; Sequence: `CheckBattery` -> `OpenGripper` -> `ApproachObject` -> `CloseGripper`.
- `dummy_nodes.h` — small example node implementations used by the demo.

Build

From the repository root (WSL / Bash):

```bash
cmake -S t01 -B t01/build
cmake --build t01/build --parallel
```

Run

```bash
./t01/build/bt_simple_pick
```

Notes

- `bt_demo.cpp` loads the XML with `createTreeFromFile("./../bt_tree.xml")` so when running from `t01/build` the tree file is expected at `../bt_tree.xml` (i.e., `t01/bt_tree.xml`).
- Make sure BehaviorTree.CPP is available to CMake. If CMake cannot find it, pass `-DCMAKE_PREFIX_PATH=/path/to/behaviortree/install` to `cmake`.
