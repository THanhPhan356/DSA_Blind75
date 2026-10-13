# Subtree of Another Tree

**Problem:** [NeetCode – Subtree of Another Tree](https://neetcode.io/problems/subtree-of-a-binary-tree/question?list=blind75)\
**Solution:** [solution.cpp](solution.cpp)

Given `root` and `subRoot`, return `true` if any subtree of `root` has exactly the same structure and node values as `subRoot`. A subtree includes its root and all descendants; the entire tree can also be a subtree of itself. The solution does not modify either tree.

## Approach: search recursively and compare each candidate

Reuse the recursive comparison from [Same Binary Tree](../same-binary-tree/README.md).

1. If `subRoot == nullptr`, return `true`: the implementation treats an empty tree as a subtree of any tree.
2. If `root == nullptr` while `subRoot` is nonempty, return `false`.
3. Call `isSameTree(root, subRoot)` to check whether the current node starts an exact match.
4. If it does not match, search the left subtree with `isSubtree(root->left, subRoot)`.
5. If that search fails, search the right subtree with `isSubtree(root->right, subRoot)`.
6. Return `true` if any of the three checks succeeds; otherwise, return `false`.

`isSameTree` compares two fixed roots. It returns `true` for two null pointers, `false` for one null pointer or different values, and otherwise requires both corresponding child pairs to match. `isSubtree` searches for the root at which that comparison succeeds.

The search covers every possible subtree root. At each candidate, the helper checks the full structure and all corresponding values, so a successful comparison establishes an exact subtree match.

## Walkthrough

For `root = [1,2,3,4,5]` and `subRoot = [2,4,5]`:

```text
root:       1           subRoot:      2
           / \                      / \
          2   3                    4   5
         / \
        4   5
```

| Step | Candidate | Result |
| --- | --- | --- |
| Compare at node 1 | `isSameTree(1, 2)` | `false`: root values differ |
| Search the left subtree | Candidate root is node 2 | Compare the two trees rooted at 2 |
| Compare at node 2 | Both values are 2 | Check both child pairs |
| Compare children | 4 matches 4 and 5 matches 5; their children are null | Both comparisons return `true` |
| Return to the search | The candidate rooted at 2 matches | Return `true`; skip the right subtree |

If the node 4 in `root` had an additional child, the comparison would return `false`, even though the values 2, 4, and 5 are present. The candidate contains extra descendants and is not identical to `subRoot`.

## C++ notes

- `TreeNode*` arguments refer to existing nodes; passing the pointers does not copy the trees.
- Check null pointers before accessing their values or children.
- `&&` in `isSameTree` requires both corresponding subtrees to match.
- `||` in `isSubtree` requires only one candidate search to succeed. It short-circuits, so later checks are skipped once a match is found.
- Keep `subRoot` fixed during the search. Only the candidate pointer into `root` moves.
- A failed comparison at one node does not finish the search: another node with the same value may start an exact match.
- The problem supplies nonempty trees; the null checks also allow empty inputs during local testing.

## Cases to check

The arrays represent trees in level order, with `null` marking a missing child.

| `root` | `subRoot` | Expected result | Reason |
| --- | --- | --- | --- |
| `[1,2,3,4,5]` | `[2,4,5]` | `true` | Match in the left subtree |
| `[1,2,3,4,5,null,null,6]` | `[2,4,5]` | `false` | Candidate has an extra descendant |
| `[1,2,3]` | `[3]` | `true` | Match in the right subtree |
| `[1,2,3]` | `[1,2,3]` | `true` | The entire tree matches |
| `[1,2]` | `[1,null,2]` | `false` | Same values, different child positions |
| `[1,1]` | `[1]` | `true` | The first candidate fails, but a later node matches |
| `[1]` | `[2]` | `false` | No matching value |
| `[1]` | `[1,2]` | `false` | The requested subtree is larger |
| `[]` | `[1]` | `false` | No candidate exists |
| `[1]` | `[]` | `true` | Empty subtree convention |
| `[]` | `[]` | `true` | Both inputs are empty |

## Complexity

Let `n` be the number of nodes in `root`, `m` the number in `subRoot`, and `h` the height of `root`.

**Time:** O(n × m) in the worst case. The search can try up to `n` candidate roots, and each comparison can inspect up to `m` nodes. Repeated values and late mismatches can cause overlapping comparisons.\
**Auxiliary space:** O(h) for the recursive call stack. During a comparison, the outer search is paused; the combined active calls still follow a path through `root`. This is O(log n) for a balanced main tree and O(n) for a chain.

## Using the code

NeetCode provides `TreeNode`, so copy the full `Solution` class when submitting, including both methods. The [tree-node.h](tree-node.h) file supplies the node definition for local compilation.
