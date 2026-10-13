# Lowest Common Ancestor in Binary Search Tree

**Problem:** [NeetCode – Lowest Common Ancestor in Binary Search Tree](https://neetcode.io/problems/lowest-common-ancestor-in-binary-search-tree/question?list=blind75)

Given a binary search tree and two distinct nodes `p` and `q` from that tree, return their lowest common ancestor (LCA). A node counts as its own ancestor. The problem guarantees unique values and that both target nodes exist.

## Shared idea: follow the path until it splits

At every node in a BST, all values in the left subtree are smaller and all values in the right subtree are larger.

- If both target values are smaller than the current value, continue left.
- If both target values are larger, continue right.
- Otherwise, return the current node: the targets lie on different sides, or one target is the current node itself.

When both targets lie in the same child subtree, their LCA must also lie there. The first node where their paths split is the deepest common ancestor, because no child subtree contains both targets. If the current node is `p` or `q`, it is already an ancestor of the other target and therefore is the LCA.

## 1. Iterative — using a loop

**Code:** [iterative.cpp](iterative.cpp)

1. Start at `root`.
2. While the current pointer is non-null, compare both target values with its value.
3. Update `root` to `root->left` if both are smaller, or `root->right` if both are larger.
4. Return `root` in all other cases.

Only one pointer moves down the tree. No stack or queue is needed. The final `nullptr` return handles reaching an empty path; valid inputs are guaranteed to reach an LCA first.

## 2. Recursive — following one child at a time

**Code:** [recursive.cpp](recursive.cpp)

1. If `root == nullptr`, return `nullptr`.
2. If both targets are smaller, return `lowestCommonAncestor(root->left, p, q)`.
3. If both are larger, return `lowestCommonAncestor(root->right, p, q)`.
4. Otherwise, return `root`.

Each call makes the same decision as one loop iteration. Returning the recursive result passes the LCA pointer back through the earlier calls. Both implementations use the BST ordering and inspect only one path.

## Walkthrough

```text
        5
       / \
      3   8
     / \ / \
    1  4 7  9
```

For `p = 1` and `q = 4`:

| Current node | Comparison | Action |
| --- | --- | --- |
| 5 | Both 1 and 4 are smaller than 5 | Continue to the left child, 3 |
| 3 | 1 is smaller and 4 is larger than 3 | Return node 3 |

For `p = 5` and `q = 3`, neither the both-smaller condition nor the both-larger condition holds, because `p->val == root->val`. Return node 5 immediately: `p` is an ancestor of `q`. This also handles a three-node tree `[5,3,8]` without any recursive call.

## C++ notes

- Compare `p->val`, `q->val`, and `root->val`, rather than ordering the pointer addresses.
- The comparisons are strict. Equality with either target falls through to `return root`.
- `&&` requires both targets to lie on the same side before choosing that side.
- Keep `p` and `q` fixed; only the current subtree root changes.
- Return the existing `TreeNode*`, not its integer value or a newly allocated node.
- Both methods preserve all node values and child links.
- These methods rely on the BST property and the guarantee that both targets exist; they do not validate those assumptions.

## Complexity comparison

Let `h` be the tree height and `n` the number of nodes.

| Approach | Time | Auxiliary space |
| --- | --- | --- |
| Iterative | O(h) | O(1) |
| Recursive | O(h) | O(h) for the call stack |

A balanced BST has height O(log n), while a chain can have height O(n). The recursive version can exhaust the call stack on a very deep chain; the iterative version avoids that limit.

## Cases to check

For the tree `[5,3,8,1,4,7,9]` shown above:

| `p` | `q` | Expected LCA value | Reason |
| --- | --- | --- | --- |
| 1 | 4 | 3 | Both go left, then their paths split |
| 7 | 9 | 8 | Both go right, then their paths split |
| 4 | 7 | 5 | Targets lie on opposite sides of the root |
| 5 | 3 | 5 | One target is the root |
| 3 | 4 | 3 | One target is an ancestor of the other |
| 4 | 3 | 3 | Swapping the target order does not change the result |

Also check a two-node tree, a chain, and a BST containing negative values. Verify that the returned pointer identifies the original LCA node.

## Using the code

The two C++ files are independent alternatives, each defining a `Solution` class. Choose one approach for submission. NeetCode provides `TreeNode`, so copy only the `Solution` class. The [tree-node.h](tree-node.h) file supplies the node definition for local compilation.
