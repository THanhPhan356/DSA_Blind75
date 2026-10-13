# Invert Binary Tree

**Problem:** [NeetCode – Invert Binary Tree](https://neetcode.io/problems/invert-a-binary-tree/question?list=blind75)

Mirror a binary tree by swapping the left and right children of every node, then return its root. Both approaches reuse the existing nodes and preserve their values.

```text
Before:                 After:
       4                       4
      / \                     / \
     2   7                   7   2
    / \ / \                 / \ / \
   1  3 6  9               9  6 3  1
```

## 1. Recursive — using depth-first search

**Code:** [recursive.cpp](recursive.cpp)

1. If `root == nullptr`, return `nullptr`: an empty subtree needs no changes.
2. Save `root->left` in `temp`, assign `root->right` to `root->left`, then assign `temp` to `root->right`.
3. Call `invertTree(root->left)` to mirror the new left subtree.
4. Call `invertTree(root->right)` to mirror the new right subtree.
5. Return `root`.

Swapping the pointers at the root exchanges the entire subtrees, but their internal links still need to be mirrored. Each recursive call applies the same operation to a smaller subtree. A leaf has two null children, so swapping them leaves the leaf unchanged and both recursive calls stop immediately.

## 2. Iterative — using an explicit stack

**Code:** [iterative.cpp](iterative.cpp)

1. If the tree is empty, return `nullptr`.
2. Push `root` onto `nodes`, a stack of pointers to nodes awaiting processing.
3. While the stack is not empty, take its top node and pop it.
4. Swap that node's left and right child pointers.
5. Push each non-null child onto the stack.
6. Return `root` after every node has been processed.

The stack records the nodes that recursion would otherwise arrange through function calls. Each node is pushed once, popped once, and has its children swapped once. Because the code pushes the new left child before the new right child, the right child is processed first: a stack removes the most recently added item.

## Walkthrough

For the tree shown above, both approaches exchange these child pointers:

| Node | Children before (`left`, `right`) | Children after (`left`, `right`) |
| --- | --- | --- |
| 4 | 2, 7 | 7, 2 |
| 7 | 6, 9 | 9, 6 |
| 2 | 1, 3 | 3, 1 |
| 1, 3, 6, 9 | `nullptr`, `nullptr` | `nullptr`, `nullptr` |

The recursive code visits nodes in the order `4, 7, 9, 6, 2, 3, 1`. The iterative code visits them in the order `4, 2, 1, 3, 7, 6, 9`. The order differs, but both produce the same mirrored tree.

## C++ notes

- `TreeNode*` is a pointer to a tree node; `root->left` accesses that node's left-child pointer.
- `temp` preserves the original left child while the two pointers are exchanged. Assigning `left = right` and then `right = left` without saving the original would lose a subtree.
- `std::swap` exchanges the two pointers; it does not copy the nodes or swap their stored values.
- `nodes.top()` accesses the next node; `nodes.pop()` removes its pointer from the stack without deleting the node.
- Null children are not pushed onto the stack, so every popped pointer can be safely dereferenced.
- The recursive calls modify existing nodes directly. Their returned pointers need not be assigned because each subtree keeps the same root node.
- Return the original root pointer; only the child links change.

## Complexity comparison

Let `n` be the number of nodes and `h` the tree height.

| Approach | Time | Auxiliary space |
| --- | --- | --- |
| Recursive | O(n) | O(h) for the call stack |
| Iterative DFS | O(n) | O(h) as an upper bound for the explicit stack |

For a balanced tree, `h` is O(log n); in the worst case, `h` is O(n). The iterative approach avoids recursive calls, and its actual stack usage depends on the shape: a chain keeps only one pending node at a time.

## Cases to check

The arrays below represent trees in level order, with `null` marking a missing child.

| Input | Expected output | Reason |
| --- | --- | --- |
| `[]` | `[]` | Empty tree |
| `[4]` | `[4]` | One node |
| `[4,2,7,1,3,6,9]` | `[4,7,2,9,6,3,1]` | Mirror all levels |
| `[1,2]` | `[1,null,2]` | Only a left child |
| `[1,null,2]` | `[1,2]` | Only a right child |
| `[1,2,3,null,4]` | `[1,3,2,null,null,4]` | An asymmetric tree |
| `[1,2,2,3,null,null,4]` | `[1,2,2,4,null,null,3]` | Equal values do not determine node identity |

Inverting a tree twice must restore its original links. Preserve all node addresses and values, including in trees with duplicate values.

## Using the code

The two C++ files are independent alternatives, each defining a `Solution` class. Choose one approach for submission. NeetCode provides `TreeNode`, so omit the `tree-node.h` include when submitting. Keep the standard-library includes used by the iterative approach. The [tree-node.h](tree-node.h) file supplies the node definition for local compilation.
