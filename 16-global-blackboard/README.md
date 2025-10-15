# 16 — Global blackboard (top-level @ access)

This example introduces a "global" blackboard and how to access it from anywhere in the tree using the `@` prefix.

## What it shows

- Creating a top-level (global) blackboard and a root blackboard that inherits from it.
- Using the `@` prefix in XML to refer to entries on the global blackboard (e.g., `{@value}`).
- Reading from the global blackboard in a subtree without explicit remapping.
- Writing back to the global blackboard from a `Script` node.

## Files

- `bt_demo.cpp` — registers `PrintNumber`, loads XML from file, creates a global blackboard (`BT::Blackboard::create()`), then a root blackboard whose parent is the global one. It updates `@value` in a loop and reads `@value_sqr` after each tick.
- `print_number_node.h` — a `SyncActionNode` with an input port `val`; it prints the value passed in.
- `bt_tree.xml` — uses `{@value}` in both the main tree and a subtree, and a script computes `@value_sqr := @value * @value`.
- `CMakeLists.txt` — builds the executable and links BehaviorTree.CPP.

## How it works (quick tour)

- In `main()`:
  1. Create `global_blackboard = BT::Blackboard::create()`.
  2. Create `root_blackboard = BT::Blackboard::create(global_blackboard)`; pass this when creating `MainTree`.
  3. Loop i=1..3:
     - `global_blackboard->set("value", i)`.
     - `tree.tickOnce()`.
     - `value_sqr = global_blackboard->get<int>("value_sqr")` → printed as `i*i`.

- In `bt_tree.xml`:
  - `PrintNumber` nodes read `val="{@value}"` — the `@` prefix means: look up the key on the top-level blackboard.
  - SubTree `MySub` doesn’t need any remapping; it can still read/write global keys.
  - `Script` computes and writes `@value_sqr` on the global blackboard.

## Build (WSL / Bash)

```bash
# from the repository root
cmake -S 16-global-blackboard -B 16-global-blackboard/build
cmake --build 16-global-blackboard/build --parallel
```

## Run

```bash
./16-global-blackboard/build/bt_16_global_blackboard
```

## Expected output (example)

```text
[main_print] val: 1
[sub_print] val: 1
[While loop] value: 1 value_sqr: 1

[main_print] val: 2
[sub_print] val: 2
[While loop] value: 2 value_sqr: 4

[main_print] val: 3
[sub_print] val: 3
[While loop] value: 3 value_sqr: 9
```

## Notes & troubleshooting

- `@` requires BehaviorTree.CPP ≥ 4.6 (global blackboard support).
- The global blackboard is not “owned” by a tree; you control it directly from your app.
- Prefer explicit ports and remappings for testability. Use `@` sparingly for truly global state.
- If CMake can’t find the library, set `-DCMAKE_PREFIX_PATH=/path/to/install`.
