# Binary Tree Maximum Path Sum

**Problem:** [NeetCode – Binary Tree Maximum Path Sum](https://neetcode.io/problems/binary-tree-maximum-path-sum/question?list=blind75)\
**Solution:** [solution.cpp](solution.cpp)

Find the largest sum of node values along any non-empty path in a binary tree. Adjacent nodes must share an edge, and no node can appear twice. A path can move from a child to its parent and then down another branch; it does not have to include the root or end at a leaf. Return the sum, not the sequence of nodes.

## Approach: DFS with a shared maximum and one branch returned

Process both children before combining their results at the current node. Every path has a highest node, where it can join a downward path from the left subtree and one from the right subtree. Trying this combination at every node covers every possible best path.

1. Initialize `best` to `INT_MIN` before each traversal.
2. Return 0 immediately for a null pointer.
3. Recursively get the best path starting at each child and extending downward along at most one branch.
4. Clamp each child's returned sum to 0 so a negative contribution can be skipped.
5. Update `best` with `node->val + left + right`, the best complete path through this node.
6. Return `node->val + max(left, right)` so the parent can extend one branch.
7. After DFS finishes, return the shared `best`.

The complete path may use both branches, but returning both to the parent would create three directions at the current node. Only one branch can be passed upward while preserving a single path.

## How the C++ code is organized

| Part | Responsibility |
| --- | --- |
| `maxPathSum(root)` | Create a fresh answer, run DFS, and return the maximum found anywhere |
| `dfs(node, best)` | Return the best downward path sum starting at this node |
| `TreeNode* node` | Identify the current node; `nullptr` means there is no node |
| `int& best` | Share the same answer variable across all recursive calls |
| Local `left` and `right` | Store the non-negative contributions received from the children |
| `node->val + left + right` | Consider a complete path whose highest node is the current node |
| Returned value | Extend the current node through at most one child |

Each call has its own `node`, `left`, and `right`. The caller pauses while a child call runs, then resumes with the value returned by that call. In contrast, `best` is passed by reference, so every call updates the same variable created in `maxPathSum`.

DFS calculates a path's sum without storing its nodes. The input tree's values and links remain unchanged.

## Walkthrough

For `root = [-15,10,20,null,null,15,5,-5]`:

```text
       -15
       / \
      10  20
         /  \
        15   5
       /
      -5
```

Initially, `best = INT_MIN`. The rows below show the order in which nodes finish, after their children have returned. `left` and `right` already include the clamp to 0.

| Current node | `left` | `right` | Complete path sum | `best` afterward | Returned sum |
| --- | --- | --- | --- | --- | --- |
| 10 | 0 | 0 | 10 | 10 | 10 |
| -5 | 0 | 0 | -5 | 10 | -5 |
| 15 | 0 | 0 | 15 | 15 | 15 |
| 5 | 0 | 0 | 5 | 15 | 5 |
| 20 | 15 | 5 | 40 | 40 | 35 |
| -15 | 10 | 35 | 30 | 40 | 20 |

Node -5 returns -5, but node 15 discards that contribution with `max(0, -5)`. At node 20, the complete path `15 -> 20 -> 5` has sum 40. The value returned to its parent is only `20 + 15 = 35`.

At the root, the candidate is `10 - 15 + 35 = 30`, so `best` remains 40. The root's DFS call returns 20, but `maxPathSum` returns `best`, which is 40.

## Why a leaf's `left` can be 0 while DFS returns 10

At leaf 10, both child pointers are null:

```cpp
int left = std::max(0, dfs(node->left, best));   // 0
int right = std::max(0, dfs(node->right, best)); // 0
```

Those null-child calls return 0. The call for the existing node 10 still reaches its own return statement:

```cpp
return node->val + std::max(left, right); // 10 + max(0, 0) = 10
```

The root's pending left-child call therefore receives 10. Its own `left` becomes `max(0, 10) = 10`. A child returning 0 is different from the current call returning 0; each call resumes and executes its remaining statements.

## C++ notes

- `best` starts at `INT_MIN`, not 0, because a valid path must include a node. For `[-3]`, the result must be -3.
- Clamping the child contributions to 0 does not remove the current node. A non-null DFS call always includes `node->val` and can return a negative sum.
- `left` and `right` are path sums, not counts, pointers, or just the immediate children's values.
- `std::max(a, b)` selects the larger integer. `<algorithm>` declares it, and `<climits>` supplies `INT_MIN`.
- The reference `int& best` preserves updates when recursive calls return. Passing the answer by value would create independent copies.
- The answer is local to `maxPathSum`, so repeated calls on one `Solution` object start fresh.
- A null pointer returns before any access to `node->val`, `node->left`, or `node->right`.
- The public method assumes the problem's non-empty-tree guarantee; there is no defined empty-tree answer.

## Cases to check

The arrays represent trees in level order, with `null` marking a missing child.

| Tree | Expected sum | Reason |
| --- | --- | --- |
| `[1,2,3]` | 6 | Join both branches through the root |
| `[-15,10,20,null,null,15,5,-5]` | 40 | Best path excludes the root and the negative descendant |
| `[-10,9,20,null,null,15,7]` | 42 | Path `15 -> 20 -> 7` beats the root's candidate 34 |
| `[-3]` | -3 | A single negative node is still a valid path |
| `[-8,-3,-10]` | -3 | For an entirely negative tree, choose its largest value |
| `[0]` | 0 | A single zero |
| `[2,-1]` | 2 | Skip a negative child |
| `[-2,3]` | 3 | The best path can be one child alone |
| `[1,null,2,null,3]` | 6 | A path can follow a chain |

Repeat calls on the same `Solution` object to check that the answer starts fresh each time.

## Complexity

**Time:** O(n), where `n` is the number of nodes. Each node is processed once, with constant work to combine its children.\
**Auxiliary space:** O(h) for the recursion stack, where `h` is the tree height. This is O(log n) for a balanced tree and O(n) for a chain. A sufficiently deep tree can exhaust the recursion stack.

## Using the code

NeetCode provides `TreeNode`, so omit the `tree-node.h` include when submitting. Keep the standard-library includes and the `Solution` class. The [tree-node.h](tree-node.h) file supplies the node definition for local compilation.
