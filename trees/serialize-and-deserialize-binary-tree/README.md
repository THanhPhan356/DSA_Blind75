# Serialize and Deserialize Binary Tree

**Problem:** [NeetCode – Serialize and Deserialize Binary Tree](https://neetcode.io/problems/serialize-and-deserialize-binary-tree/question?list=blind75)\
**Solution:** [solution.cpp](solution.cpp)

Convert a binary tree into a string, then reconstruct a tree with the same values and child positions from that string. The string format is your choice; it does not have to match the level-order arrays shown in the examples. Empty trees, negative values, and repeated values are allowed.

## Approach: preorder DFS with null markers

Preorder visits the current node, its left subtree, and then its right subtree. Recording a `#` for every missing child preserves the structure, even when values repeat. Spaces separate tokens so multi-digit and negative integers remain unambiguous.

### Serialize

1. Create a fresh output stream.
2. For a null pointer, write `# ` and return.
3. Otherwise, write the node's integer value followed by a space.
4. Encode the left subtree, then the right subtree into the same stream.
5. Return the stream's string.

### Deserialize

1. Create a fresh input stream from the serialized string.
2. Read the next token.
3. If it is `#`, return `nullptr` for that child position.
4. Otherwise, convert the token to an integer and allocate a node.
5. Decode and attach its left subtree, then its right subtree.
6. Return the node pointer to the caller.

Each token describes either one node followed by two subtree encodings, or a missing child. This rule lets the decoder determine exactly where each subtree ends without an inorder array or unique node values.

## How the C++ code is organized

| Part | Responsibility |
| --- | --- |
| `Codec` | Expose the two methods required by the judge |
| `serialize(root)` | Create an output stream and return the completed string |
| `encode(node, output)` | Append one subtree in preorder |
| `deserialize(data)` | Create an input stream and return the rebuilt root |
| `decode(input)` | Consume one subtree's tokens and return its root pointer |
| `std::ostringstream& output` | Share the same growing output across recursive calls |
| `std::istringstream& input` | Share the reading position across recursive calls |
| Local `token` | Hold the next value or null marker read by this call |
| Local `node` | Hold the newly allocated node belonging to this call |

`output << node->val << ' '` appends a value and a separator. `output.str()` retrieves the accumulated text. `input >> token` skips whitespace, reads one token, and advances the stream. `std::stoi(token)` converts a numeric token, including a minus sign, to an integer.

When `node->left = decode(input)` runs, the parent waits for the entire left subtree to finish. The returned pointer becomes its left child. The next call starts at the stream's updated position and builds the right subtree. These calls are separate statements to guarantee left-before-right processing.

Both public methods create fresh streams, and the class stores no traversal state. The encoder and decoder can be different `Codec` objects, and repeated calls do not carry over earlier positions or output.

## Walkthrough

For `root = [1,2,3,null,null,4,5]`:

```text
      1
     / \
    2   3
       / \
      4   5
```

Serialization produces the following string, including one trailing space:

```text
"1 2 # # 3 4 # # 5 # # "
```

The decoder consumes tokens in this order:

| Token position | Token | Action |
| --- | --- | --- |
| 1 | `1` | Create root 1 |
| 2 | `2` | Create 1's left child 2 |
| 3 | `#` | Set 2's left child to null |
| 4 | `#` | Set 2's right child to null; finish subtree 2 |
| 5 | `3` | Create 1's right child 3 |
| 6 | `4` | Create 3's left child 4 |
| 7 | `#` | Set 4's left child to null |
| 8 | `#` | Set 4's right child to null; finish subtree 4 |
| 9 | `5` | Create 3's right child 5 |
| 10 | `#` | Set 5's left child to null |
| 11 | `#` | Set 5's right child to null; finish subtrees 5, 3, and 1 |

The result is a newly allocated copy with the original structure. For an empty tree, the string is `"# "`, which decodes to `nullptr`.

## Why null markers matter

Both of these trees have preorder values `7, 7`, but different structures:

```text
    7          7
   /            \
  7              7
```

Their encodings are `"7 7 # # # "` and `"7 # 7 # # "`. The null positions distinguish them. A tree with `n` nodes has `n + 1` missing child pointers, so this format writes `2n + 1` tokens.

## C++ notes

- The interface is named `Codec`, with `serialize` and `deserialize`, rather than the `Solution` class used by many other problems.
- Streams are passed by reference so every recursive call appends to the same output or advances the same input.
- Serialization reads the tree without changing its values or links. Deserialization allocates new nodes; a local caller must eventually delete them.
- This decoder expects a complete string produced by this codec, as in the judge's round-trip use. Malformed external strings are outside its contract and need validation before reuse in an application.
- The trailing space is intentional and harmless: token extraction skips whitespace.

## Cases to check

The tests compare values and left/right structure after a round trip, check that reconstructed nodes have new addresses, and reuse separate encoder and decoder objects.

| Case | What it checks |
| --- | --- |
| Empty tree | Null root marker |
| A single zero | Zero is a value, not a null marker |
| Single nodes -1000 and 1000 | Negative and multi-digit values |
| Equal values with only a left or right child | Structural information from null markers |
| `[1,2,3,null,null,4,5]` | Both branches and missing children |
| A 10,000-node balanced tree | Maximum node count |
| A 1,000-node right chain | Deep recursion and repeated values |

## Complexity

Let `L` be the serialized string length, `n` the number of nodes, and `h` the tree height.

**Time:** O(L) for each operation, which is O(n) under the problem's bounded integer values. Each node and null marker is processed once.\
**Space:** O(L + h) for the stream/string buffers and recursive calls. Deserialization additionally allocates O(n) space for the output tree. The recursion stack alone is O(h), and a sufficiently deep tree can exhaust it.

## Using the code

NeetCode provides `TreeNode`, so omit the `tree-node.h` include when submitting. Keep the standard-library includes and the `Codec` class. The [tree-node.h](tree-node.h) file supplies the node definition for local compilation.

Run the local [test.cpp](test.cpp) from this folder:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic test.cpp -o test
./test
```
