# Maximum Depth of Binary Tree

**Problem:** [NeetCode – Maximum Depth of Binary Tree](https://neetcode.io/problems/depth-of-binary-tree/question?list=blind75)\
**Solution:** [solution.cpp](solution.cpp)

Return the number of nodes on the longest path from the root to a leaf. An empty tree has depth 0, and a single-node tree has depth 1.

## Approach: recursive depth-first search

1. If `root == nullptr`, return `0`.
2. Compute `leftDepth = maxDepth(root->left)`.
3. Compute `rightDepth = maxDepth(root->right)`.
4. Return `1 + std::max(leftDepth, rightDepth)`.

Each call returns the depth of the subtree rooted at its argument. The deeper child determines the longest path, and adding 1 includes the current node. The tree's values and links remain unchanged.

## Walkthrough

For `root = [8,3,10,1,null,null,14]`, the longest paths contain three nodes:

```text
        8
       / \
      3   10
     /      \
    1        14
```

The calls return their results from the leaves upward:

| Node | `leftDepth` | `rightDepth` | Returned result |
| --- | --- | --- | --- |
| 1 | 0 | 0 | `1 + max(0, 0) = 1` |
| 3 | 1 | 0 | `1 + max(1, 0) = 2` |
| 14 | 0 | 0 | `1 + max(0, 0) = 1` |
| 10 | 0 | 1 | `1 + max(0, 1) = 2` |
| 8 | 2 | 2 | `1 + max(2, 2) = 3` |

## Why no shared counter is needed

The `+1` counts the current node. Every recursive call has its own `leftDepth` and `rightDepth` variables, which receive the results returned by its child calls.

For a chain `1 → 2 → 3`, the null child returns 0, node 3 returns 1, node 2 returns 2, and node 1 returns 3. The final depth is built through these return values.

## C++ notes

- `TreeNode* root` points to the current node; `root->left` and `root->right` identify its children.
- Check `root` before dereferencing it.
- `<algorithm>` supplies `std::max`.
- Use the maximum child depth, not their sum. Adding both would count nodes across different branches.
- Node values do not affect depth. Only the tree's structure matters.

## Cases to check

The arrays represent trees in level order, with `null` marking a missing child.

| Input | Expected depth | Reason |
| --- | --- | --- |
| `[]` | `0` | Empty tree |
| `[8]` | `1` | One node |
| `[8,3]` | `2` | Only a left child |
| `[8,null,10]` | `2` | Only a right child |
| `[8,3,10,1,null,null,14]` | `3` | Two longest paths of equal length |
| `[1,2,3,4,5,6,7]` | `3` | Seven nodes, but only three on a longest path |
| `[1,null,2,null,3,null,4]` | `4` | A right-only chain |
| `[0,-1,-1]` | `2` | Negative and duplicate values |

## Complexity

**Time:** O(n), where `n` is the number of nodes. Each node is visited once.\
**Auxiliary space:** O(h) for the call stack, where `h` is the tree height. This is O(log n) for a balanced tree and O(n) for a chain.

## Using the code

NeetCode provides `TreeNode`, so omit the `tree-node.h` include when submitting. Keep `<algorithm>` and the `Solution` class. The [tree-node.h](tree-node.h) file supplies the node definition for local compilation.
