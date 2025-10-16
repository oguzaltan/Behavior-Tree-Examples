# bt_with_ros2 — BehaviorTree.CPP in a ROS 2 package

Minimal ROS 2 package showing how to:

- Build a plugin library containing BehaviorTree.CPP nodes
- Describe the plugin in `plugin_description.xml`
- Load the plugin and a BT XML model from the package share in a ROS 2 coordinator node

## Layout

- `src/print_message_node.cpp`: a plugin node `PrintMessage` with input port `msg`
- `src/bt_coordinator.cpp`: a ROS 2 node that loads the plugin and runs `behavior_trees/simple_bt.xml`
- `behavior_trees/simple_bt.xml`: uses `<PrintMessage msg="..."/>`
- `plugin_description.xml`: points to the shared library and class ID
- `CMakeLists.txt`, `package.xml`: ament_cmake package scaffolding

## Build (colcon)

Build this package alongside your ROS 2 workspace (Humbe/Iron/Jazzy):

```bash
# WSL bash, inside your ROS 2 workspace root
colcon build --packages-select bt_with_ros2
source install/setup.bash
```

If building this repo standalone with plain CMake (not recommended for ROS 2 run):

```bash
cmake -S bt_with_ros2 -B bt_with_ros2/build
cmake --build bt_with_ros2/build --parallel
```

## Run

```bash
ros2 run bt_with_ros2 bt_coordinator
```

Expected output includes lines like:

```text
[PrintMessage] Hello from ROS 2 + BT.CPP
```

## Notes & troubleshooting

- Ensure BehaviorTree.CPP is available in your ROS 2 distro (it is in recent ROS 2 releases). If not, install it via apt or from source.
- If `plugin_description.xml` can’t be found, confirm the package share path is correct and that you sourced `install/setup.bash`.
- For Groot2/ZMQ logging, ensure the ZMQ dependencies are present; otherwise the node continues without the publisher.
