# t03 — Calculate and print target

This example shows how to pass data via the blackboard between nodes and how to use the `Script` node to set literal values.

Files of interest

- `bt_demo.cpp` — registers `CalculateGoal` and `PrintTarget` nodes.
- `bt_tree.xml` — the tree; Sequence: `CalculateGoal goal="{GoalPosition}"` -> `PrintTarget target="{GoalPosition}"` -> `Script code=" OtherGoal:='-1;3' "` -> `PrintTarget target="{OtherGoal}"`.
- `dummy_nodes.h` — small example node implementations used by the demo.

Build & Run

```bash
cmake -S t03 -B t03/build
cmake --build t03/build --parallel
./t03/build/bt_simple_pick
```

Notes

- The example demonstrates writing to and reading from the blackboard using placeholder syntax.
- Make sure the `Script` node is supported by your BehaviorTree.CPP build (some builds may require enabling script support).
