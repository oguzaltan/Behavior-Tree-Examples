# t02 — Say / Think / Say example

This example demonstrates composition of simple custom nodes: `SaySomething` and `ThinkWhatToSay`. It's useful to see how blackboard variables can be written and then used by later nodes.

Files of interest

- `bt_demo.cpp` — registers `SaySomething` and `ThinkWhatToSay`.
- `bt_tree.xml` — the tree; Sequence: `SaySomething(message="hello")` -> `ThinkWhatToSay(text="{the_answer}")` -> `SaySomething(message="{the_answer}")`.
- `dummy_nodes.h` — small example node implementations used by the demo.

Build & Run

```bash
cmake -S t02 -B t02/build
cmake --build t02/build --parallel
./t02/build/bt_simple_pick
```

Notes

- The tree uses blackboard placeholders like `{the_answer}`; `ThinkWhatToSay` sets that blackboard entry for the later `SaySomething`.
- XML is loaded with `createTreeFromFile("./../bt_tree.xml")` so run from the example build folder or adjust the path in `bt_demo.cpp`.
