# 07 — Auto-registering subtrees from XML files

This example demonstrates scanning a directory for BehaviorTree XML files, registering them with the factory, and running the main tree or individual subtrees.

Files of interest

- `bt_demo.cpp` — registers the `SaySomething` node and registers any `.xml` trees found in the current folder.
- `bt_tree.xml` — the main tree that references `SubTreeA` and `SubTreeB`.
- `subtree_A.xml`, `subtree_B.xml` — the subtree definitions.
- `dummy_nodes.h` — contains the `SaySomething` node implementation used by the trees.
- `CMakeLists.txt` — builds the example executable `bt_07_autoregister_xml_subtrees`.

Build (WSL / Bash)

```bash
cmake -S 07-autoregister-xml-subtrees -B 07-autoregister-xml-subtrees/build
cmake --build 07-autoregister-xml-subtrees/build --parallel
```

Run

```bash
./07-autoregister-xml-subtrees/build/bt_07_autoregister_xml_subtrees
```

Expected output

When you run the example you should see a small warning (if your XML files don't include the BTCPP format attribute) and the example `SaySomething` outputs:

```bash
Warnings: The first tag of the XML (<root>) should contain the attribute [BTCPP_format="4"]
Please check if your XML is compatible with version 4.x of BT.CPP
----- MainTree tick ----
Robot says: starting MainTree
Robot says: Executing Sub_A
Robot says: Executing Sub_B
----- SubA tick ----
Robot says: Executing Sub_A
```

Notes and troubleshooting

- XML format warning: Add `BTCPP_format="4"` to the `<root>` element to silence the warning:

```xml
<root BTCPP_format="4">
  ...
</root>
```

- If `std::filesystem::directory_iterator` is not available on your compiler/libstdc++, use a fixed list of filenames or upgrade your toolchain (GCC 9+ / clang with C++17 support).

- If you add new node implementations in separate `.cpp` files, remember to add them to `CMakeLists.txt` so they are compiled and linked.
