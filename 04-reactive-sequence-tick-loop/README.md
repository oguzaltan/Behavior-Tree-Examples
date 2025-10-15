# 04 — Reactive sequence with custom loop

This example highlights a reactive sequence with a battery check and an explicit tick loop inside `bt_demo.cpp`. It registers a simple condition (`BatteryOK`), `MoveBase`, and `SaySomething` nodes and demonstrates how to manually tick the tree until completion.

Files of interest

- `bt_demo.cpp` — registers nodes and shows a custom ticking loop (calls `tickOnce()` and `tree.sleep(...)`).
- `bt_tree.xml` — the tree; a `ReactiveSequence` containing `BatteryOK` and a `Sequence` of `SaySomething`, `MoveBase`, `SaySomething`.
- `dummy_nodes.h` — small example node implementations used by the demo.

Build & Run

```bash
cmake -S 04-reactive-sequence-tick-loop -B 04-reactive-sequence-tick-loop/build
cmake --build 04-reactive-sequence-tick-loop/build --parallel
./04-reactive-sequence-tick-loop/build/bt_simple_pick
```

Notes

- `bt_demo.cpp` in this example prefers `tickOnce()` inside a loop and prints the status; this is useful if you want finer control over ticking and delays.
- As with the others, the XML file is loaded via `createTreeFromFile("./../bt_tree.xml")` so run from the example build folder or change the path accordingly.
