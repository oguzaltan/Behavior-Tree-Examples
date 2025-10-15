# 12 — Default port values (including JSON)

This example shows multiple ways to provide default values for input ports, including parsing JSON into a custom type.

## Highlights

- Custom type (`Point2D`) with JSON (de)serialization via `BT_JSON_CONVERTER`.
- `convertFromString<Point2D>` extended to support both `x,y` strings and `json:{...}`.
- Default input values demonstrated using:
  - typed C++ default (`Point2D{1,2}`),
  - blackboard key default (`{point}`),
  - string default (`"5,6"`),
  - same-name blackboard default (`{=}`),
  - JSON default (`json:{"x":9,"y":10}`).

## Files

- `bt_demo.cpp` — defines `Point2D`, registers a JSON converter, registers `NodeWithDefaultPoints`, builds a tiny XML in code, sets blackboard defaults, and ticks once.
- `CMakeLists.txt` — builds the example and links BehaviorTree.CPP.

## How it works

- Custom type and JSON
  - `struct Point2D { int x; int y; }` with equality operators.
  - `BT_JSON_CONVERTER(Point2D, point)` maps `x` and `y` to JSON.
  - `convertFromString<Point2D>`:
    - if the string starts with `json:`, parse with `convertFromJSON<Point2D>`;
    - else parse `x,y` using `splitString` + `convertFromString<int>`.

- NodeWithDefaultPoints
  - Ports: `input`, `pointA`, `pointB`, `pointC`, `pointD`, `pointE`.
  - Defaults set in `providedPorts()`:
    - `input`: none (must be provided by XML; given as `-1,-2`).
    - `pointA`: `Point2D{1,2}`.
    - `pointB`: `{point}` (from blackboard key `point`).
    - `pointC`: `"5,6"` (parsed string).
    - `pointD`: `{=}` (from blackboard key with same name `pointD`).
    - `pointE`: `json:{"x":9,"y":10}`.
  - In `tick()`, the node reads each port and asserts the expected values; returns SUCCESS when all match.

- Inline XML

```xml
<root BTCPP_format="4">
  <BehaviorTree>
    <NodeWithDefaultPoints input="-1,-2"/>
  </BehaviorTree>
</root>
```

- Blackboard setup
  - Before ticking, code sets:
    - `point` → `{3,4}` (used by `pointB`)
    - `pointD` → `{7,8}` (used by `pointD` with `{=}`)

## Build (WSL / Bash)

```bash
# from the repository root
cmake -S 12-default-port-values-json -B 12-default-port-values-json/build
cmake --build 12-default-port-values-json/build --parallel
```

## Run

```bash
./12-default-port-values-json/build/bt_12_default_port_values_json
```

## Expected output

```text
Result: SUCCESS
```

## Troubleshooting

- BehaviorTree.CPP not found: install the library or pass `-DCMAKE_PREFIX_PATH=/path/to/install` to CMake.
- If you see a runtime exception like `failed pointA` (or B/C/D/E/input), check that:
  - blackboard values were set before ticking,
  - the XML provided `input`,
  - the `convertFromString<Point2D>` logic and JSON converter are present.
