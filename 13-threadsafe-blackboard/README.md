# 13 — Thread-safe blackboard access with getLockedPortContent

This example shows how to safely access and modify a blackboard entry by pointer while a node is ticking. It uses a mutex-protected handle so concurrent access is safe.

## What it demonstrates

- A custom action node `PushIntoVector` with:
  - An input port `value` (int)
  - A bidirectional port `vector` with type `std::vector<int>`
- Using `getLockedPortContent("vector")` to get a thread-safe pointer to the blackboard entry.
- Initializing the entry if it’s empty, or pushing values when it already contains a vector.
- Running a small tree defined inline in code that calls the action three times with values 3, 5, 7.

## Files

- `bt_demo.cpp` — registers `PushIntoVector`, builds the tree from inline XML, ticks the tree while running.
- `CMakeLists.txt` — builds the example and links BehaviorTree.CPP.

## How it works (quick tour)

- The `PushIntoVector` node:
  - Reads `value` with `getInput<int>("value")`.
  - Calls `getLockedPortContent("vector")` to get a guarded pointer to the blackboard entry.
    - While this pointer exists, access is mutex-protected and thread-safe.
  - If the entry is empty, it creates a new `std::vector<int>` with the first value.
  - If it already stores a `std::vector<int>`, it pushes the new value and reports the new size.
- The inline XML runs three `PushIntoVector` nodes in a `Sequence`:

```xml
<root BTCPP_format="4">
  <BehaviorTree ID="TreeA">
    <Sequence>
      <PushIntoVector vector="{vect}" value="3"/>
      <PushIntoVector vector="{vect}" value="5"/>
      <PushIntoVector vector="{vect}" value="7"/>
    </Sequence>
  </BehaviorTree>
</root>
```

## Build (WSL / Bash)

```bash
# from the repository root
cmake -S 13-threadsafe-blackboard -B 13-threadsafe-blackboard/build
cmake --build 13-threadsafe-blackboard/build --parallel
```

## Run

```bash
./13-threadsafe-blackboard/build/bt_13_threadsafe_blackboard
```

## Expected output (example)

```text
We created a new vector, containing value [3]
Value [5] pushed into the vector. New size: 2
Value [7] pushed into the vector. New size: 3
```

## Notes & troubleshooting

- If you see a failure status from the node, it means the `vector` entry couldn’t be accessed via `getLockedPortContent`.
- The `vector` port is bidirectional so other nodes could read it later; here we only write to it.
- Inline XML means no external file path issues in this example.
