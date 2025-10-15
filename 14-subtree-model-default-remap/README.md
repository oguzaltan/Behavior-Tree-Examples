# 14 — SubTree Model and default remapping (BT.CPP ≥ 4.4)

This example demonstrates SubTree Models: defining a subtree’s interface once (inputs/outputs) with optional default values and default remappings, so parent trees only remap what’s necessary.

## What it shows

- Declaring a SubTree model (`MySub`) with input and output ports.
- Using default input values and default output remappings.
- Calling that subtree from a parent tree (`MainTree`) while remapping only the required ports.

## Files

- `bt_demo.cpp` — registers two XML snippets from text:
  - A model + subtree (`MySub`) that checks inputs and sets outputs.
  - `MainTree` that sets an input, calls `MySub`, and validates outputs.
- `CMakeLists.txt` — builds the example and links BehaviorTree.CPP.

## The model and subtree (xml_subtree)

Model declares `SubTree ID="MySub"` with ports:

- Inputs:
  - `sub_in_value` with default `42`
  - `sub_in_name` with no default (must be provided by caller)
- Outputs:
  - `sub_out_result` default‑remapped to `{out_result}`
  - `sub_out_state` with no default (must be provided by caller)

The `BehaviorTree ID="MySub"` does:

- `ScriptCondition`: `sub_in_value==42 && sub_in_name=='john'`
- `Script`: `sub_out_result:=69; sub_out_state:='ACTIVE'`

## The parent (xml_maintree)

`BehaviorTree ID="MainTree"`:

1. `Script`: `in_name:='john'`
2. `SubTree ID="MySub"` with only:
   - `sub_in_name="{in_name}"` (explicit input remap)
   - `sub_out_state="{out_state}"` (explicit output remap)
   - `sub_in_value` uses its default `42`
   - `sub_out_result` uses default remap to `{out_result}`
3. `ScriptCondition`: `out_result==69 && out_state=='ACTIVE'`

## Build (WSL / Bash)

```bash
# from the repository root
cmake -S 14-subtree-model-default-remap -B 14-subtree-model-default-remap/build
cmake --build 14-subtree-model-default-remap/build --parallel
```

## Run

```bash
./14-subtree-model-default-remap/build/bt_14_subtree_model_default_remap
```

## Expected behavior

- The `MainTree` sequence succeeds:
  - `MySub` sees inputs (42, 'john'), sets outputs (69, 'ACTIVE').
  - Parent’s condition validates `out_result==69 && out_state=='ACTIVE'`.

## Notes

- SubTree Models require BehaviorTree.CPP ≥ 4.4.
- Defaults in the model reduce repetition at callsites and prevent wiring mistakes.
