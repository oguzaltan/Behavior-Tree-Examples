# Behavior-Tree-Examples

This repository contains small example projects that demonstrate how to use BehaviorTree.CPP (BehaviorTree.CPP v3+) with simple demo nodes and XML trees. Each example is provided in its own folder (now renamed with descriptive names like `01-simple-pick-sequence`, `02-say-think-blackboard`, etc.) and includes a `CMakeLists.txt`, `bt_demo.cpp`, `bt_tree.xml`, and `dummy_nodes.h` so you can build and run the demo easily.

These examples are intentionally small and focused on demonstrating BehaviorTree.CPP usage. Feel free to copy the example folders as a starting point for your own project.

## Contents (examples)

- `01-simple-pick-sequence/` — Simple pick sequence
- `02-say-think-blackboard/` — Say/Think with blackboard
- `03-calc-and-print-target/` — Calculate and print target
- `04-reactive-sequence-tick-loop/` — Reactive sequence and custom tick loop
- `05-crossdoor-fallback-retry/` — CrossDoor with Fallback/Retry/SubTree
- `06-subtree-script-ports/` — SubTree, Script nodes, and port remapping
- `07-autoregister-xml-subtrees/` — Auto-register XML subtrees from files
- `08-custom-constructor-nodes/` — Custom constructor nodes
- `09-scripting-enums-precondition/` — Scripted variables, enums, Precondition
- `10-crossdoor-observer-uid-stats/` — CrossDoor with observer and UID stats
- `11-groot2-logging-custom-types/` — Groot2 streaming, file logs, custom types
- `12-default-port-values-json/` — Default port values, JSON converters
- `13-threadsafe-blackboard/` — Thread-safe blackboard access
- `14-subtree-model-default-remap/` — SubTree Model with default remaps
- `15-substitution-rules-mocking/` — Substitution rules / mocking nodes
- `16-global-blackboard/` — Global blackboard with @ prefix

Each example builds a uniquely named executable matching the folder's topic (e.g., `bt_01_simple_pick_sequence`).

## Prerequisites

- A working C++ toolchain (g++ / clang) and CMake (>= 3.10).
- BehaviorTree.CPP library available on the system and findable by CMake. See the [BehaviorTree.CPP project](https://github.com/BehaviorTree/BehaviorTree.CPP) for installation instructions.

On Debian/Ubuntu you can often install dependencies with system packages or build BehaviorTree.CPP from source. If you're using WSL (recommended on Windows), use your distro's package manager or follow the upstream build instructions.

## Build (per example)

From the repository root you can build a specific example. The commands below are written for a Bash shell (WSL). Replace the path with the example folder you want to build.

```bash
# create an out-of-source build directory
cmake -S 01-simple-pick-sequence -B 01-simple-pick-sequence/build
# build the executable
cmake --build 01-simple-pick-sequence/build --parallel
```

Alternative (classic):

```bash
mkdir -p 01-simple-pick-sequence/build
cd 01-simple-pick-sequence/build
cmake ..
make
```

When the build succeeds the executable will be placed in `01-simple-pick-sequence/build/` and its name is `bt_01_simple_pick_sequence` (matching the project name in `CMakeLists.txt`).

## Run

From the repository root, run the example executable (WSL / Linux style):

```bash
./01-simple-pick-sequence/build/bt_01_simple_pick_sequence
```

If you prefer to run from inside the build directory:

```bash
cd 01-simple-pick-sequence/build
./bt_01_simple_pick_sequence
```

Some examples may read `bt_tree.xml` from the source directory or rely on command-line arguments. Check the corresponding `bt_demo.cpp` if you need to pass a different XML file.

## Troubleshooting

- CMake cannot find BehaviorTree.CPP: Make sure the library is installed and CMake can locate it. You may need to set `CMAKE_PREFIX_PATH` to the install location of BehaviorTree.CPP, for example:

```bash
cmake -S 01-simple-pick-sequence -B 01-simple-pick-sequence/build -DCMAKE_PREFIX_PATH=/path/to/behaviortree/install
```

## Build all examples

Use the helper script to build every example folder that contains a `CMakeLists.txt` (name-agnostic):

```bash
./build_all.sh -j $(nproc)
```

On Windows PowerShell, you can run it under WSL or use the same commands in a Bash shell.

- Missing compiler or wrong C++ standard: The examples require C++17. Ensure your compiler supports `-std=c++17`.

- Permission denied when running the executable: ensure the binary is executable (`chmod +x 01-simple-pick-sequence/build/bt_01_simple_pick_sequence`) or run with `./` from the build folder.
