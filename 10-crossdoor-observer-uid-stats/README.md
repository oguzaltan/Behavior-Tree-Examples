# 10 — CrossDoor with observer and UID path stats

This example extends the classic CrossDoor scenario and adds:

- A `BT::TreeObserver` to collect per-node execution statistics (transitions, successes, failures).
- A traversal that records each node's unique ID (UID) and its full human‑readable path.
- A printed tree view before execution and a per‑node stats summary after execution.

It also showcases control flow and decorators:

- `Fallback`, `RetryUntilSuccessful`, `Inverter`, and `SubTree`.

## Files

- `bt_demo.cpp` — registers `CrossDoor` nodes, loads XML with `registerBehaviorTreeFromFile("./../bt_tree.xml")`, creates `MainTree`, prints the tree, sets up an observer, records UID→path, ticks the tree, then prints per‑node statistics.
- `bt_tree.xml` — two BehaviorTrees:
  - `MainTree`: If the door is closed (detected via `Inverter(IsDoorClosed)` inside a `Fallback`), runs the `DoorClosed` subtree, then attempts to `PassThroughDoor`.
  - `DoorClosed`: tries `OpenDoor`, then `RetryUntilSuccessful` on `PickLock` (5 attempts), then `SmashDoor`.
- `crossdoor_nodes.h` / `crossdoor_nodes.cpp` — implementations and registration for `IsDoorClosed`, `PassThroughDoor`, `OpenDoor`, `PickLock`, `SmashDoor` + `BT_REGISTER_NODES` plugin entry.
- `CMakeLists.txt` — builds the executable and links BehaviorTree.CPP; includes `crossdoor_nodes.cpp` in target sources.

## Build (WSL / Bash)

```bash
# from the repository root
cmake -S 10-crossdoor-observer-uid-stats -B 10-crossdoor-observer-uid-stats/build
cmake --build 10-crossdoor-observer-uid-stats/build --parallel
```

## Run

```bash
./10-crossdoor-observer-uid-stats/build/bt_simple_pick
```

## What you’ll see

- A printed tree structure (pre‑execution).
- A list mapping each node UID to its `fullPath()`.
- After the tree finishes, a summary is like:

```text
----------------
Sequence
   Fallback
      Inverter
         IsDoorClosed
      DoorClosed
         Fallback
            OpenDoor
            RetryUntilSuccessful
               PickLock
            SmashDoor
   PassThroughDoor
----------------
1 -> Sequence::1
2 -> Fallback::2
3 -> Inverter::3
4 -> IsDoorClosed::4
5 -> DoorClosed::5
6 -> DoorClosed::5/Fallback::6
7 -> DoorClosed::5/OpenDoor::7
8 -> DoorClosed::5/RetryUntilSuccessful::8
9 -> DoorClosed::5/PickLock::9
10 -> DoorClosed::5/SmashDoor::10
11 -> PassThroughDoor::11
```

## Troubleshooting

- BehaviorTree.CPP not found: install the library or pass `-DCMAKE_PREFIX_PATH=/path/to/install` to CMake.
- Wrong working directory: the demo loads `./../bt_tree.xml`. Run from the repo root or adjust the path.
- Linker errors after adding nodes: if you add new `.cpp` files, include them in `add_executable(...)` in `CMakeLists.txt`.

## Tips

- Use `BT::printTreeRecursively(tree.rootNode())` to visualize control flow.
- `observer.getStatistics(key_or_uid)` is handy for tests to assert expected transitions/success/failure counts.
