# Kth Smallest Integer in BST

**Problem:** [NeetCode – Kth Smallest Integer in BST](https://neetcode.io/problems/kth-smallest-integer-in-bst/question?list=blind75)\
**Solution:** [solution.cpp](solution.cpp)

Find the value at position `k` when the values of a valid binary search tree are ordered from smallest to largest. Positions start at 1. The input guarantees that `k` is between 1 and the number of nodes.

## Approach: recursive inorder traversal

Inorder visits the left subtree, the current node, and then the right subtree. In a BST, this visits values in increasing order, so the kth visited node contains the answer.

1. Reset the shared `count` and `answer` for each call to `kthSmallest`.
2. Return immediately if the current pointer is null or `count == k`.
3. Recursively process the left subtree.
4. If the left subtree already found the answer, return before counting the current node.
5. Increment `count` to visit the current node. If it reaches `k`, save `node->val` and return.
6. Otherwise, recursively process the right subtree.

The BST's ordering gives the traversal its sorted order; no sorting or result array is needed. The node values and child links remain unchanged.

## Walkthrough

For this tree and `k = 3`, the sorted values are `1, 3, 4, 5, 7`, so the answer is 4.

```text
      5
     / \
    3   7
   / \
  1   4
```

Initially, `count = 0` and `answer = 0`.

| Step | Current node | Action | `count` | `answer` |
| --- | --- | --- | --- | --- |
| 1 | 5 | Recurse left to 3 | 0 | 0 |
| 2 | 3 | Recurse left to 1 | 0 | 0 |
| 3 | 1 | Its left child is null; that call returns | 0 | 0 |
| 4 | 1 | Visit 1 and increment the counter | 1 | 0 |
| 5 | 1 | Its right child is null; finish the call for 1 | 1 | 0 |
| 6 | 3 | Resume after the left call; the counter is still below `k` | 1 | 0 |
| 7 | 3 | Visit 3 and increment the counter | 2 | 0 |
| 8 | 3 | Recurse right to 4 | 2 | 0 |
| 9 | 4 | Its left child is null; that call returns | 2 | 0 |
| 10 | 4 | Visit 4, reach `k`, save the value, and return | 3 | 4 |
| 11 | 3 | Its right call has finished; return | 3 | 4 |
| 12 | 5 | Resume after the left call; `count == k`, so return | 3 | 4 |

Entering `inorder(5, k)` is not the same as visiting node 5. A node is counted only when execution reaches `++count`. Nodes 5 and 7 are never counted in this example.

## Why the counter is shared

`count` and `answer` are members of the `Solution` object, so all recursive calls use the same two variables. Declaring `int count = 0` inside the helper would instead create a separate counter for every call.

Each call has its own `node` and `k` parameters. The helper returns no value because its return type is `void`; it records the result in the shared `answer`. After the traversal, `kthSmallest` returns that stored value.

## Why check again after the left call?

The left subtree may find the kth node. The second `count == k` check prevents an ancestor from incrementing the counter or starting its right subtree after that happens.

A `return` exits only the current call. Earlier calls resume where they paused; the checks make them stop as they unwind.

## C++ notes

- Check `node == nullptr` before accessing either child or `node->val`.
- The entry condition uses `||`: either an empty subtree or an already-found answer is enough to stop.
- `answer = 0` is an initial value, not a failure indicator. Zero can be a valid answer; `count == k` controls stopping.
- Reset the member variables in `kthSmallest` so reusing one `Solution` object works for another query.
- This method assumes a valid BST and valid `k`; it does not validate those input guarantees.
- An ordinary BFS queue visits nodes by level, which does not produce the sorted order required here.

## Cases to check

The arrays represent trees in level order, with `null` marking a missing child.

| Tree | `k` | Expected value | Reason |
| --- | --- | --- | --- |
| `[5,3,7,1,4]` | 1 | 1 | Smallest value lies below the left child |
| `[5,3,7,1,4]` | 3 | 4 | Stop inside the root's left subtree |
| `[5,3,7,1,4]` | 4 | 5 | The root is fourth in sorted order |
| `[5,3,7,1,4]` | 5 | 7 | Largest valid rank |
| `[0]` | 1 | 0 | One node, with value zero |
| `[3,2,null,1]` | 2 | 2 | Left-only chain |
| `[1,null,2,null,3]` | 3 | 3 | Right-only chain |

Also call `kthSmallest` several times with different ranks on the same `Solution` object to verify that the counter and answer reset.

## Complexity

**Time:** O(h + k), where `h` is the tree height. The traversal descends toward the smallest values, counts at most `k` nodes, and stops after finding the answer. This is O(n) in the worst case.\
**Auxiliary space:** O(h) for the recursion stack, which is O(log n) for a balanced tree and O(n) for a chain. A sufficiently deep tree can exhaust the recursion stack.

## Using the code

NeetCode provides `TreeNode`, so omit the `tree-node.h` include when submitting and copy the `Solution` class. The [tree-node.h](tree-node.h) file supplies the node definition for local compilation.
