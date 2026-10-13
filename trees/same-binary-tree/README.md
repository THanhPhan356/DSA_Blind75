# Same Binary Tree

**Problem:** [NeetCode – Same Binary Tree](https://neetcode.io/problems/same-binary-tree/question?list=blind75)\
**Solution:** [solution.cpp](solution.cpp)

Given the roots `p` and `q` of two binary trees, return `true` only when their structures match and every pair of corresponding nodes has the same value. The solution compares the existing nodes without modifying either tree.

## Approach: recursive depth-first comparison

1. If both pointers are `nullptr`, return `true`: both subtrees are empty.
2. If only one pointer is `nullptr`, return `false`: the structures differ.
3. If `p->val != q->val`, return `false`: the corresponding values differ.
4. Compare `p->left` with `q->left` recursively.
5. Compare `p->right` with `q->right` recursively.
6. Return the logical AND of the two comparisons.

Every call answers the same question for two smaller subtrees. Matching the current values is only the first step: the left subtrees and the right subtrees must also match. The null checks preserve structural information, including which side contains a child.

## Walkthrough

For `p = [1,2,3]` and `q = [1,2,3]`:

```text
p:       1           q:       1
        / \                 / \
       2   3               2   3
```

| Comparison | Action | Returned result |
| --- | --- | --- |
| Roots 1 and 1 | Values match; compare both child pairs | `true && true` → `true` |
| Left children 2 and 2 | Values match; both have empty children | `true && true` → `true` |
| Right children 3 and 3 | Values match; both have empty children | `true && true` → `true` |
| Each pair of null children | Both pointers are `nullptr` | `true` |

The null-child calls return first, allowing their parents to return `true`. The root then returns the combined result. If node 3 in `q` were changed to 4, that pair would return `false`, and the root would return `true && false`, which is `false`.

Matching values alone are insufficient. For `p = [1,2]` and `q = [1,null,2]`, the roots match, but the next comparison pairs `p->left` (node 2) with `q->left` (`nullptr`). The result is `false` because the child occupies a different position.

## C++ notes

- `TreeNode* p` and `TreeNode* q` point to the current pair of nodes.
- Check the null cases before accessing `p->val`, `q->val`, or their child pointers.
- After the first condition rules out two null pointers, `p == nullptr || q == nullptr` identifies exactly one missing node.
- `&&` requires both recursive results to be `true`. It short-circuits: if the left comparison returns `false`, the right comparison is skipped.
- Pair left with left and right with right. Cross-comparing children would test a different relationship between the trees.
- Each call returns a Boolean result to its caller; no shared flag or counter is needed.
- Pointer addresses may differ: separately allocated trees can still have identical structures and values.

## Cases to check

The arrays represent trees in level order, with `null` marking a missing child.

| `p` | `q` | Expected result | Reason |
| --- | --- | --- | --- |
| `[]` | `[]` | `true` | Both trees are empty |
| `[]` | `[1]` | `false` | Only one tree is empty |
| `[1]` | `[]` | `false` | Only one tree is empty |
| `[1]` | `[1]` | `true` | Identical single nodes |
| `[1]` | `[2]` | `false` | Different root values |
| `[1,2,3]` | `[1,2,3]` | `true` | Matching structure and values |
| `[1,2,3]` | `[1,2,4]` | `false` | A deeper value differs |
| `[1,2]` | `[1,null,2]` | `false` | Same values in different positions |
| `[1,2,2,3]` | `[1,2,2,null,3]` | `false` | Duplicate values do not hide structural differences |

## Complexity

**Time:** O(n) in the worst case, where `n` is the combined number of nodes in the two trees. Each comparison performs constant work; the search can stop early at a mismatch.\
**Auxiliary space:** O(h) for the recursive call stack, where `h` is the greater tree height. This is O(log n) for balanced trees and O(n) in the worst case of a chain.

## Using the code

NeetCode provides `TreeNode`, so copy the `Solution` class when submitting. The [tree-node.h](tree-node.h) file supplies the node definition for local compilation.
