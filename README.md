# Behavior-Tree-Examples

This repository contains small example projects that demonstrate how to use BehaviorTree.CPP (BehaviorTree.CPP v3+) with simple demo nodes and XML trees. Each example is provided in its own folder (`t01`, `t02`, etc.) and includes a `CMakeLists.txt`, `bt_demo.cpp`, `bt_tree.xml`, and `dummy_nodes.h` so you can build and run the demo easily.

These examples are intentionally small and focused on demonstrating BehaviorTree.CPP usage. Feel free to copy the example folders as a starting point for your own project.

## Contents

- `t01/` — Example 1
- `t02/` — Example 2
- `t03/` — Example 3
- `t04/` — Example 4

Each example builds an executable named `bt_simple_pick` (the project name in the `CMakeLists.txt`).

## Prerequisites

- A working C++ toolchain (g++ / clang) and CMake (>= 3.10).
- BehaviorTree.CPP library available on the system and findable by CMake. See the [BehaviorTree.CPP project](https://github.com/BehaviorTree/BehaviorTree.CPP) for installation instructions.

On Debian/Ubuntu you can often install dependencies with system packages or build BehaviorTree.CPP from source. If you're using WSL (recommended on Windows), use your distro's package manager or follow the upstream build instructions.

## Build (per example)

From the repository root you can build a specific example. The commands below are written for a Bash shell (WSL). Replace `t01` with the example folder you want to build.

```bash
# create an out-of-source build directory
cmake -S t01 -B t01/build
# build the executable
cmake --build t01/build --parallel
```

Alternative (classic):

```bash
mkdir -p t01/build
cd t01/build
cmake ..
make
```

When the build succeeds the executable will be placed in `t01/build/` and its name is `bt_simple_pick` (matching the project name in `CMakeLists.txt`).

## Run

From the repository root, run the example executable (WSL / Linux style):

```bash
./t01/build/bt_simple_pick
```

If you prefer to run from inside the build directory:

```bash
cd t01/build
./bt_simple_pick
```

Some examples may read `bt_tree.xml` from the source directory or rely on command-line arguments. Check the corresponding `bt_demo.cpp` if you need to pass a different XML file.

## Troubleshooting

- CMake cannot find BehaviorTree.CPP: Make sure the library is installed and CMake can locate it. You may need to set `CMAKE_PREFIX_PATH` to the install location of BehaviorTree.CPP, for example:

```bash
cmake -S t01 -B t01/build -DCMAKE_PREFIX_PATH=/path/to/behaviortree/install
```

- Missing compiler or wrong C++ standard: The examples require C++17. Ensure your compiler supports `-std=c++17`.

- Permission denied when running the executable: ensure the binary is executable (`chmod +x t01/build/bt_simple_pick`) or run with `./` from the build folder.
