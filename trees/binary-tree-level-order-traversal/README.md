# Binary Tree Level Order Traversal

**Problem:** [NeetCode – Binary Tree Level Order Traversal](https://neetcode.io/problems/level-order-traversal-of-binary-tree/question?list=blind75)\
**Solution:** [solution.cpp](solution.cpp)

Return the node values grouped by level, from the root downward and from left to right within each level. An empty tree returns an empty list. The tree does not need to be a BST; output order depends on node positions rather than numeric values.

## Approach: breadth-first search with a queue

1. Create an empty result and return it if `root == nullptr`.
2. Push `root` into the queue.
3. At the start of each outer iteration, save `size = q.size()`. These nodes form the current level.
4. Create an empty `level` vector and process exactly `size` nodes.
5. For each node, read the front pointer, pop it, append its value to `level`, then push its non-null left child followed by its non-null right child.
6. Append `level` to `result` and repeat until the queue is empty.

The queue removes pointers in the order they were inserted. Children are added behind the remaining nodes of the current level, so they wait until those nodes have been processed. Adding the left child first preserves left-to-right order.

## Walkthrough

```text
        1
       / \
      2   3
     / \ / \
    4  5 6  7
```

| Queue at the start | Saved `size` | Collected `level` | Queue after the level |
| --- | --- | --- | --- |
| `[1]` | 1 | `[1]` | `[2,3]` |
| `[2,3]` | 2 | `[2,3]` | `[4,5,6,7]` |
| `[4,5,6,7]` | 4 | `[4,5,6,7]` | `[]` |

Return `[[1],[2,3],[4,5,6,7]]`.

## Why the saved queue size separates levels

`size` is a snapshot, not a live reference to the queue length. Calling `q.pop()` changes `q.size()` but does not change the integer already stored in `size`. The loop variable `i` counts how many current-level nodes have been processed.

For the level containing nodes 2 and 3:

| Action | Queue afterward | Current `q.size()` | Saved `size` | Processed nodes |
| --- | --- | --- | --- | --- |
| Start the level | `[2,3]` | 2 | 2 | 0 |
| Pop 2 and push 4, then 5 | `[3,4,5]` | 3 | 2 | 1 |
| Pop 3 and push 6, then 7 | `[4,5,6,7]` | 4 | 2 | 2 |

After two nodes, the `for` loop ends even though the queue is not empty. All remaining nodes belong to the next level. Using `i < q.size()` would change the boundary during processing and could mix levels or stop before finishing the current level.

## C++ notes

- `<queue>` supplies `std::queue<TreeNode*>`; it stores pointers to existing nodes.
- `q.front()` retrieves the front pointer. `q.pop()` removes it from the queue without deleting the node.
- `std::vector<int> level` stores one level, and `std::vector<std::vector<int>> result` stores all levels.
- Each outer iteration creates a new empty `level`, so previous levels are kept separate.
- A node can have zero, one, or two children. Test each child independently and skip null pointers.
- `result.push_back(level)` copies the collected values into the result.
- The method does not change the tree's values or child links.

## Cases to check

The input arrays represent trees in level order, with `null` marking a missing child.

| Input | Expected result | Reason |
| --- | --- | --- |
| `[]` | `[]` | Empty tree |
| `[1]` | `[[1]]` | One node |
| `[1,2,3,4,5,6,7]` | `[[1],[2,3],[4,5,6,7]]` | Every level is collected separately |
| `[1,2,3,4,null,null,5]` | `[[1],[2,3],[4,5]]` | Missing children do not appear in the result |
| `[1,2,null,3]` | `[[1],[2],[3]]` | Left-only chain |
| `[1,null,2,null,3]` | `[[1],[2],[3]]` | Right-only chain |
| `[0,-1,-1]` | `[[0],[-1,-1]]` | Negative and duplicate values |

## Complexity

Let `n` be the number of nodes and `w` the maximum number of nodes in any level.

**Time:** O(n). Each node is enqueued, dequeued, and added to the result once.\
**Auxiliary space:** O(w) for the queue and current level; the queue can temporarily contain nodes from two adjacent levels. The returned result stores O(n) values, so total space including output is O(n).

## Using the code

NeetCode provides `TreeNode`, so omit the `tree-node.h` include when submitting. Keep the standard-library includes and the `Solution` class. The [tree-node.h](tree-node.h) file supplies the node definition for local compilation.
