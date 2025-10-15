# 11 — CrossDoor with Groot2, file logging, and custom types

This example revisits the CrossDoor scenario and shows how to:

- Stream your tree to Groot2 (visual editor) and see live status updates.
- Export a model of your registered nodes for Groot2 automatically.
- Log execution to files (two formats) compatible with Groot2.
- Visualize a custom type in Groot2 by registering a JSON schema.

## What’s new vs t05/t10

- `BT::Groot2Publisher` publishes the tree and node states over a TCP port.
- `BT::FileLogger2` and `BT::MinitraceLogger` write execution traces to disk.
- `BT_JSON_CONVERTER(Position2D, pos)` + `BT::RegisterJsonDefinition<Position2D>()` let Groot2 understand your custom `Position2D` type.
- A simple action `UpdatePosition` writes a `Position2D` to the blackboard via an output port.

## Files

- `bt_demo.cpp` — registers nodes, writes the node model XML for Groot2, creates the tree from inline XML, registers the custom `Position2D` type, starts the Groot2 publisher, and logs to files while repeatedly ticking the tree.
- `bt_tree.xml` — classic CrossDoor trees (MainTree and DoorClosed) — not used directly by the program (we use inline XML), but provided for reference.
- `crossdoor_nodes.h` / `crossdoor_nodes.cpp` — CrossDoor node implementations and registration.
- `CMakeLists.txt` — includes `crossdoor_nodes.cpp` and links BehaviorTree.CPP.

## Build (WSL / Bash)

```bash
# from the repository root
cmake -S 11-groot2-logging-custom-types -B 11-groot2-logging-custom-types/build
cmake --build 11-groot2-logging-custom-types/build --parallel
```

## Run

```bash
./11-groot2-logging-custom-types/build/bt_simple_pick
```

You should see:

- The XML of the instantiated tree printed to stdout.
- Publisher listening on port 1667 (Groot2 can connect to it).
- Two log files generated in `t11/`:
  - `t11_groot_howto.btlog` (lightweight BT log)
  - `minitrace.json` (minitrace format)

## Connecting Groot2

- Start Groot2 and choose “Connect to running application”.
- Host: `localhost` — Port: `1667` — The tree model is provided via `writeTreeNodesModelXML(factory)`.
- You’ll see live status updates as the example ticks the tree in a loop.

## Notes and troubleshooting

- Firewall/port busy: if port 1667 is in use, pick another port in the code (`BT::Groot2Publisher publisher(tree, <port>)`).
- Long‑running loop: the example runs forever (tick loop + sleep). Stop it with Ctrl‑C.
- If you change or add nodes, re‑run to regenerate the node model XML for Groot2.
- If BehaviorTree.CPP isn’t found at configure time, pass `-DCMAKE_PREFIX_PATH=/path/to/install` to CMake.
