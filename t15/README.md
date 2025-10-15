# t15 — Substituting/mocking nodes (factory substitution rules)

This example shows how to replace parts of a behavior tree without touching the XML, using factory substitution rules. It’s handy for tests, demos, or temporarily bypassing slow/external actions.

## What it demonstrates

- Three ways to provide substitutes:
  1. Register a custom dummy node (here via `registerSimpleAction`).
  2. Use `BT::TestNode` with a configuration (status, async delay, post-script).
  3. Load substitution rules from JSON.
- Substitutions must be defined before `createTree()` so the factory uses them when instantiating nodes.

## Files

- `bt_demo.cpp` — registers `SaySomething`, loads `bt_tree.xml`, runs the original tree, defines substitution rules (either manually or from JSON), then rebuilds and runs the substituted tree.
- `bt_tree.xml` — defines `MainTree` and `MySub` with a few named nodes used by the rules.
- `dummy_nodes.h` — contains `SaySomething` and other sample nodes used by the examples.
- `CMakeLists.txt` — builds the example and links BehaviorTree.CPP.

## Original tree (summary)

- `MainTree` sequence:
  - `SaySomething` name="talk" message="hello world"
  - `Fallback` with `AlwaysFailure` and `SubTree` ID="MySub" name="mysub"
  - `SaySomething` message="before last_action"
  - `Script` sets `msg := 'after last_action'`
  - `AlwaysSuccess` name="last_action"
  - `SaySomething` message="{msg}"
- `MySub`:
  - `AlwaysSuccess` name="action_subA"
  - `AlwaysSuccess` name="action_subB"

## Substitutions used here

- Manually (commented in code) or via JSON (default on in the demo):
  - `"mysub/action_*"` → `DummyAction` (custom dummy; prints its `fullPath()` and returns `SUCCESS`).
  - `"talk"` → `DummySaySomething` (prints the input `message` directly; returns `SUCCESS`).
  - `"set_message"` → `TestNode` configured as `NewMessage`:
    - `return_status: SUCCESS`
    - `async_delay: 2000ms`
    - `post_script: msg = 'message SUBSTITUTED'`
  - `"counting"` → `TestNode` configured as `NoCounting` (returns `SUCCESS` synchronously), demonstrating branch substitution.

Equivalent JSON (snippet from the code)

```json
{
  "TestNodeConfigs": {
    "NewMessage": {
      "async_delay": 2000,
      "return_status": "SUCCESS",
      "post_script": "msg ='message SUBSTITUTED'"
    },
    "NoCounting": {
      "return_status": "SUCCESS"
    }
  },
  "SubstitutionRules": {
    "mysub/action_*": "DummyAction",
    "talk": "DummySaySomething",
    "set_message": "NewMessage",
    "counting": "NoCounting"
  }
}
```

## Build (WSL / Bash)

```bash
# from the repository root
cmake -S t15 -B t15/build
cmake --build t15/build --parallel
```

## Run

```bash
./t15/build/bt_simple_pick
```

## What you’ll see

- First run (original): prints each node’s `fullPath()` and the natural outputs, like:

```text
Robot says: hello world
Robot says: the original message
Robot says: 1
Robot says: 2
Robot says: 3
```

- Second run (substituted): shows dummy and test nodes in action, e.g.:

```text
DummySaySomething: hello world
DummyAction substituting node with fullPath(): mysub/action_subA
DummyAction substituting node with fullPath(): mysub/action_subB
Robot says: message SUBSTITUTED
```

## Tips & troubleshooting

- Ensure substitutions are declared before `createTree()`.
- Match node names/paths correctly; wildcards like `mysub/action_*` are supported.
- Use `post_script` to tweak blackboard values (like `msg`) after a test node completes.
- If BehaviorTree.CPP cannot be found by CMake, set `-DCMAKE_PREFIX_PATH=/path/to/install`.
