# 05 — CrossDoor (Fallback, Retry, SubTree)

This example implements a small cross-door scenario that demonstrates:

- Using `Fallback`, `RetryUntilSuccessful`, `Inverter`, and `SubTree` nodes.
- Registering C++ actions/conditions with a `BehaviorTreeFactory`.
- Loading an XML file that contains multiple `<BehaviorTree>` definitions and selecting the one to run.

Files of interest

- `bt_demo.cpp` — creates a `BehaviorTreeFactory`, registers the `CrossDoor` nodes and loads `bt_tree.xml` with `registerBehaviorTreeFromFile("./../bt_tree.xml")`, then creates and runs the tree with `createTree("MainTree")`.
- `bt_tree.xml` — contains two BehaviorTrees: `MainTree` (top-level behavior) and `DoorClosed` (a subtree used by `MainTree`).
- `crossdoor_nodes.h` / `crossdoor_nodes.cpp` — the C++ node implementations for `IsDoorClosed`, `PassThroughDoor`, `OpenDoor`, `PickLock`, and `SmashDoor`. The class also exposes `registerNodes(...)` that registers these with the factory.
- `CMakeLists.txt` — builds the executable and links against BehaviorTree.CPP. Note the add_executable includes `crossdoor_nodes.cpp` so the implementation is compiled into the binary.

What the demo does (expected behavior)

1. The program registers the `CrossDoor` nodes and reads `bt_tree.xml`.
2. It creates the `MainTree` and prints the tree structure to stdout.
3. The tree first checks if the door is closed; if so it runs the `DoorClosed` subtree which attempts to open the door by:
   - trying `OpenDoor`, then `RetryUntilSuccessful` on `PickLock` (up to a number of attempts), then `SmashDoor` as a last resort.
4. Once the door is open, the `PassThroughDoor` action runs.

Build (WSL / Bash)

From the repository root (or from inside `05-crossdoor-fallback-retry`):

```bash
# configure & build (out-of-source)
cmake -S 05-crossdoor-fallback-retry -B 05-crossdoor-fallback-retry/build
cmake --build 05-crossdoor-fallback-retry/build --parallel
```

Run

```bash
./05-crossdoor-fallback-retry/build/bt_05_crossdoor_fallback_retry
```

Notes and troubleshooting

- XML parsing error: If you see "Error parsing the XML" with `registerBehaviorTreeFromText`, that means the code attempted to parse a filename as XML content. This repository's `bt_demo.cpp` uses `registerBehaviorTreeFromFile("./../bt_tree.xml")`, which is correct. If you edited the code, make sure you didn't accidentally switch to the `registerBehaviorTreeFromText` overload.

- Missing BehaviorTree.CPP: If CMake cannot find the library, pass its install location to CMake:

```bash
cmake -S 05-crossdoor-fallback-retry -B 05-crossdoor-fallback-retry/build -DCMAKE_PREFIX_PATH=/path/to/behaviortree/install
```

- Permission / pkgRedirects error during reconfigure: When running `cmake` repeatedly on a Windows-mounted directory from WSL you might see errors like:

  CMake Error: Unable to (re)create the private pkgRedirects directory

  This is a filesystem/permission issue with the mounted Windows path. Common fixes:

  - Remove the `build/` directory and reconfigure from scratch:

```bash
cd 05-crossdoor-fallback-retry
rm -rf build
cmake -S . -B build
cmake --build build --parallel
```

If `rm -rf build` fails due to ownership, inspect and (carefully) change ownership:

```bash
ls -la
sudo chown -R $(id -u):$(id -g) build
rm -rf build
```

- Linker errors (undefined references): If you add new node implementations in `.cpp` files, be sure to include them in `CMakeLists.txt` (the example already lists `crossdoor_nodes.cpp` in `add_executable(...)`).

- Runtime behavior: The example prints the tree with `BT::printTreeRecursively(...)` before executing. Use that to verify which nodes will run.
