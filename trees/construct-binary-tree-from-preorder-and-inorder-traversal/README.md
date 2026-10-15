# Construct Binary Tree from Preorder and Inorder Traversal

**Problem:** [NeetCode – Construct Binary Tree from Preorder and Inorder Traversal](https://neetcode.io/problems/binary-tree-from-preorder-and-inorder-traversal/question?list=blind75)\
**Solution:** [solution.cpp](solution.cpp)

Reconstruct a binary tree from its preorder and inorder traversals, and return its root. The inputs describe the same tree and contain unique values. The tree is not necessarily a BST.

## Approach: recursive construction with inorder boundaries

Preorder visits root, left subtree, and right subtree. Inorder visits left subtree, root, and right subtree. The next preorder value identifies a subtree's root; its position in inorder separates that subtree's left and right parts.

1. Build a map from each value to its index in the original inorder array.
2. Reset the shared preorder cursor `preIndex` to 0.
3. For an inorder interval `[left, right]`, return `nullptr` if it is empty.
4. Read the next preorder value, advance the cursor, and allocate the root node.
5. Find its inorder position `mid`.
6. Build and attach the left subtree from `[left, mid - 1]`.
7. Build and attach the right subtree from `[mid + 1, right]`.
8. Return the root of the completed subtree.

The left recursive call must finish before the right call starts because the shared cursor follows preorder. The two inorder intervals can have different sizes.

## How the C++ code is organized

Each call to `build` constructs one complete subtree and returns its root pointer. Its caller receives that pointer and assigns it to `root->left` or `root->right`.

| Part | Responsibility |
| --- | --- |
| `buildTree` | Initialize the map and cursor, then request the entire inorder interval |
| `build(preorder, left, right)` | Construct the subtree belonging to that inclusive inorder interval |
| `position[value]` | Find a value's absolute index in the original inorder array |
| `preIndex` | Track the next unused value in preorder across all recursive calls |
| `left`, `right` | Preserve the current call's own inorder boundaries |
| Local `root` pointer | Keep track of the node allocated by this particular call |

The arrays stay intact. Instead of copying smaller arrays for each call, the helper receives boundaries. The map provides the inorder information it needs, so the helper does not need an inorder parameter.

`preIndex` and `position` are shared members of the `Solution` object. Each call has its own local variables and boundaries. When a child call returns, its parent's local `root` still identifies the parent's node, while the shared cursor has advanced past every node constructed by the child.

In the expression below, the current cursor value is used for indexing before it is incremented:

```cpp
int value = preorder[preIndex++];
```

For example, with `preIndex = 0`, it reads `preorder[0]`, then changes the cursor to 1. An empty interval returns before this expression and therefore does not consume a preorder value.

## Walkthrough

```text
preorder = [3, 9, 20, 15, 7]
inorder  = [9, 3, 15, 20, 7]
index       0  1   2   3  4
```

Root 3 is at inorder index 1, so its left interval is `[0, 0]` and its right interval is `[2, 4]`. In the table, `build(left, right)` abbreviates the helper call; both bounds refer to inorder.

| Step | Current operation | Action | `preIndex` afterward |
| --- | --- | --- | --- |
| 1 | `build(0, 4)` | Read 3, allocate root 3, find `mid = 1` | 1 |
| 2 | Build 3's left child: `build(0, 0)` | Read 9, allocate root 9, find `mid = 0` | 2 |
| 3 | Build 9's left child: `build(0, -1)` | Empty interval; attach `nullptr` | 2 |
| 4 | Build 9's right child: `build(1, 0)` | Empty interval; attach `nullptr` | 2 |
| 5 | Finish root 9 | Return its pointer and attach it to `3->left` | 2 |
| 6 | Build 3's right child: `build(2, 4)` | Read 20, allocate root 20, find `mid = 3` | 3 |
| 7 | Build 20's left child: `build(2, 2)` | Read 15, allocate root 15, find `mid = 2` | 4 |
| 8 | Build 15's left child: `build(2, 1)` | Empty interval; attach `nullptr` | 4 |
| 9 | Build 15's right child: `build(3, 2)` | Empty interval; attach `nullptr` | 4 |
| 10 | Finish root 15 | Return its pointer and attach it to `20->left` | 4 |
| 11 | Build 20's right child: `build(4, 4)` | Read 7, allocate root 7, find `mid = 4` | 5 |
| 12 | Build 7's left child: `build(4, 3)` | Empty interval; attach `nullptr` | 5 |
| 13 | Build 7's right child: `build(5, 4)` | Empty interval; attach `nullptr` | 5 |
| 14 | Finish root 7 | Return its pointer and attach it to `20->right` | 5 |
| 15 | Finish root 20 | Return its pointer and attach it to `3->right` | 5 |
| 16 | Finish root 3 | Return the completed tree to `buildTree` | 5 |

```text
      3
     / \
    9   20
       /  \
      15   7
```

## C++ notes

- `left` and `right` are integer indices, not child pointers or values. A single-element interval, where `left == right`, still creates a node.
- `mid` is an absolute inorder index. The number of nodes in the left subtree is `mid - left`.
- `preorder` is passed by reference; recursive calls use the same input vector without copying or modifying it.
- Reset `preIndex` and clear `position` before each query so one `Solution` object can be reused.
- `new TreeNode(value)` creates a node that survives the return of the current function. The local pointer is returned and linked into the tree. A local caller owns the returned tree and must eventually delete its nodes.
- Returning `nullptr` from an empty interval supplies the missing child pointer naturally.
- The method assumes the problem's valid-input and unique-value guarantees; it does not validate inconsistent traversals.

## Cases to check

| Preorder | Inorder | Expected structure |
| --- | --- | --- |
| `[3,9,20,15,7]` | `[9,3,15,20,7]` | Root 3; left child 9; right child 20 with children 15 and 7 |
| `[1]` | `[1]` | A single node |
| `[1,2]` | `[2,1]` | Root 1 with only a left child |
| `[1,2]` | `[1,2]` | Root 1 with only a right child |
| `[3,2,1]` | `[1,2,3]` | Left-only chain |
| `[1,2,3]` | `[1,2,3]` | Right-only chain |
| `[0,-1,2]` | `[-1,0,2]` | Negative values and zero |
| `[]` | `[]` | The helper also handles an empty tree |

For each reconstructed tree, verify that traversing it in preorder and inorder reproduces both inputs. Also repeat calls on the same `Solution` object to check the shared-state reset.

## Complexity

**Expected time:** O(n), where `n` is the number of nodes, assuming average O(1) operations on `std::unordered_map`. Each node is allocated once. Pathological hash collisions can make the worst-case time O(n²).\
**Auxiliary space:** O(n) for the position map plus O(h) for the recursion stack, where `h` is the tree height. The output tree uses another O(n) space. A sufficiently deep tree can exhaust the recursion stack.

## Using the code

NeetCode provides `TreeNode`, so omit the `tree-node.h` include when submitting. Keep the standard-library includes and the `Solution` class. The [tree-node.h](tree-node.h) file supplies the node definition for local compilation.
