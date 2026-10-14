# Valid Binary Search Tree

**Problem:** [NeetCode – Valid Binary Search Tree](https://neetcode.io/problems/valid-binary-search-tree/question?list=blind75)\
**Solution:** [solution.cpp](solution.cpp)

Return whether a binary tree is a valid binary search tree (BST). Every value in a node's left subtree must be strictly smaller than that node's value, and every value in its right subtree must be strictly larger. The same rule applies at every node; duplicate values are not allowed.

## Approach: recursive DFS with lower and upper bounds

The helper `check(node, lower, upper)` validates a subtree whose values must lie strictly inside `(lower, upper)`. Its bounds preserve restrictions from all ancestors, not just the immediate parent.

1. If `node == nullptr`, return `true`: there is no value that can violate the bounds.
2. If `node->val <= lower` or `node->val >= upper`, return `false`.
3. Check the left subtree with `(lower, node->val)`.
4. Check the right subtree with `(node->val, upper)`.
5. Return `true` only when both subtree checks return `true`.

Start at the root with `LLONG_MIN` and `LLONG_MAX`. These are finite limits of `long long`, used as sentinels beyond the range of the node's `int` value. The tree is not modified.

## Walkthrough

Checking only a node's immediate children would miss this invalid tree:

```text
      5
     / \
    3   7
       /
      4
```

Although `4 < 7`, node 4 also belongs to the right subtree of 5, so it must be greater than 5.

| Current node | `lower` | `upper` | Result or next step |
| --- | --- | --- | --- |
| 5 | `LLONG_MIN` | `LLONG_MAX` | Check left with upper bound 5 and right with lower bound 5 |
| 3 | `LLONG_MIN` | 5 | Valid; both null children return `true` |
| 7 | 5 | `LLONG_MAX` | Its left child inherits lower bound 5 and gets upper bound 7 |
| 4 | 5 | 7 | Invalid because `4 <= 5`; return `false` |

The `false` result returns through the calls for nodes 7 and 5, so the final answer is `false`.

## How arguments move through recursion

In a call where the current node is 5 and the bounds are `(LLONG_MIN, LLONG_MAX)`:

```cpp
check(node->left, lower, node->val)
```

passes the left child's pointer, `LLONG_MIN`, and `5` immediately. If that child is 3, the new call checks node 3 inside `(LLONG_MIN, 5)`.

```cpp
check(node->right, node->val, upper)
```

passes the right child's pointer, `5`, and `LLONG_MAX`. Each call has its own parameters. Bounds are passed while descending the tree; boolean results return while unwinding the calls. Returning from the left call does not change the current call's bounds before the right call starts.

## C++ notes

- `<climits>` supplies `LLONG_MIN` and `LLONG_MAX`; these values are not mathematical infinities.
- Bounds use `long long`, so even `INT_MIN` and `INT_MAX` remain valid node values. Using those same `int` limits as exclusive bounds would incorrectly reject them.
- Use `<=` and `>=` to reject equality as well as values outside the interval.
- Preserve `lower` when descending left and preserve `upper` when descending right. Resetting either inherited bound would lose an ancestor's restriction.
- `&&` requires both subtrees to be valid. It skips the right call if the left call returns `false`.
- Check for `nullptr` before accessing `node->val`.

## Cases to check

The arrays represent trees in level order, with `null` marking a missing child.

| Input | Expected | Reason |
| --- | --- | --- |
| `[]` | `true` | Empty subtree; the helper also handles an empty root |
| `[2,1,3]` | `true` | Both sides satisfy the strict ordering |
| `[1,2,3]` | `false` | The left child exceeds the root |
| `[5,3,7,null,null,4]` | `false` | A deeper descendant violates the root's lower bound |
| `[5,3,7,null,6]` | `false` | A descendant in the root's left subtree exceeds 5 |
| `[2,2,3]` | `false` | Duplicate on the left |
| `[2,1,2]` | `false` | Duplicate on the right |
| `[0,-1,1]` | `true` | Negative values and zero |
| `[-2147483648]` | `true` | Minimum 32-bit integer is valid |
| `[2147483647]` | `true` | Maximum 32-bit integer is valid |
| `[1,null,2,null,3]` | `true` | Increasing right-only chain |

## Complexity

**Time:** O(n) in the worst case, where `n` is the number of nodes. Each node is checked at most once.\
**Auxiliary space:** O(h) for the call stack, where `h` is the tree height: O(log n) for a balanced tree and O(n) for a chain. A sufficiently deep chain can exhaust the recursion stack.

## Using the code

NeetCode provides `TreeNode`, so omit the `tree-node.h` include when submitting. Keep `<climits>` and the `Solution` class. The [tree-node.h](tree-node.h) file supplies the node definition for local compilation.
