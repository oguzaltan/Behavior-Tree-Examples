# 02 — Say / Think / Say example

This example demonstrates composition of simple custom nodes: `SaySomething` and `ThinkWhatToSay`. It's useful to see how blackboard variables can be written and then used by later nodes.

Files of interest

- `bt_demo.cpp` — registers `SaySomething` and `ThinkWhatToSay`.
- `bt_tree.xml` — the tree; Sequence: `SaySomething(message="hello")` -> `ThinkWhatToSay(text="{the_answer}")` -> `SaySomething(message="{the_answer}")`.
- `dummy_nodes.h` — small example node implementations used by the demo.

Build & Run

```bash
cmake -S 02-say-think-blackboard -B 02-say-think-blackboard/build
cmake --build 02-say-think-blackboard/build --parallel
./02-say-think-blackboard/build/bt_02_say_think_blackboard
```

Notes

- The tree uses blackboard placeholders like `{the_answer}`; `ThinkWhatToSay` sets that blackboard entry for the later `SaySomething`.
- XML is loaded with `createTreeFromFile("./../bt_tree.xml")` so run from the example build folder or adjust the path in `bt_demo.cpp`.
