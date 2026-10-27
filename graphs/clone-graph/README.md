# Clone Graph

**Problem:** [LeetCode - Clone Graph](https://leetcode.com/problems/clone-graph/)\
**Solution:** [solution.cpp](solution.cpp)\
**Tests:** [test.cpp](test.cpp)

Given a node in a connected undirected graph, return a deep copy of the graph. Each node has an integer value and a list of neighbor pointers. Every copied node must be newly allocated, and every copied edge must point to a copied node. Return `nullptr` for an empty graph.

## Approach: DFS with an original-to-copy map

Use `copies` to map each original node's address to its cloned node's address. The map serves as both a visited set and a way to reuse the same clone when several edges reach one node.

1. Return `nullptr` if the current node is null.
2. If the node is already in `copies`, return its existing clone.
3. Allocate a new node with the original value.
4. Register the clone in `copies` **before** exploring neighbors.
5. Recursively clone each neighbor and append the returned pointer to the clone's neighbor list.
6. Return the clone of the current node.

Registering before recursion handles cycles. For an edge `1 -- 2`, DFS from `2` encounters `1` again and reuses its registered clone instead of recursing forever. Every original node gets exactly one clone, and each neighbor entry is recreated between clones.

Unlike backtracking, there is no undo step: the map must retain discovered nodes for the entire traversal. The original graph is unchanged.

## How the C++ code is organized

| Part | Responsibility |
| --- | --- |
| `cloneGraph(node)` | Create a fresh map and return the copied starting node |
| `dfs(node, copies)` | Find or create the clone of one original node |
| `std::unordered_map<Node*, Node*>` | Associate original addresses with cloned addresses |
| `copies.count(node)` | Check whether the node already has a clone |
| `new Node(node->val)` | Allocate an independent node with the same value |
| `copies[node] = copy` | Register the clone before following any edges |
| `copy->neighbors.push_back(...)` | Rebuild an edge using a cloned neighbor |

## Walkthrough

```text
Original:           Clone:
1 --- 2             1' --- 2'
|     |             |      |
4 --- 3             4' --- 3'
```

For adjacency list `[[2,4],[1,3],[2,4],[1,3]]`, start from node `1`.

| Visit | Action |
| --- | --- |
| `1` | Create `1'` and record `1 -> 1'` |
| `2` from `1` | Create `2'`; its edge back to `1` reuses `1'` |
| `3` from `2` | Create `3'`; its edge back to `2` reuses `2'` |
| `4` from `3` | Create `4'`; both neighbors already have clones |
| Return to `1` | Its remaining neighbor `4` reuses `4'` |

Return `1'`. Its adjacency list has the same structure, but none of its nodes are original nodes. Each recursive call finishes filling its clone's neighbor list before returning.

## C++ notes

- LeetCode supplies the `Node` class. Submit `solution.cpp` as written, including the standard-library include; no `main()` is needed.
- `test.cpp` defines a minimal compatible `Node` class for local compilation.
- Pass the map by reference so all recursive calls share the same clones.
- Keys are node addresses, so node identity does not depend on its value.
- Copying only `val` and the original neighbor pointers would be a shallow copy.
- The map is local to each public call, so reusing one `Solution` object starts a fresh clone operation.
- Destroying the map does not delete the allocated nodes. The returned graph remains valid; local tests delete every clone once after checking it.
- DFS can reach O(V) recursive depth. The problem allows at most 100 nodes; use iterative traversal for graphs that could exceed the runtime stack limit.

## Cases to check

| Case | What it checks |
| --- | --- |
| Empty graph | Return `nullptr` |
| One node with no neighbors | Allocate a distinct node with an empty neighbor list |
| Two connected nodes | Reuse a clone for the reverse edge |
| Four-node cycle | Terminate and preserve shared neighbors |
| Triangle | Several paths reach the same cloned node |
| Chain of 100 nodes | Handle the maximum node count |
| Repeated calls on one object | Each call uses a fresh map |
| Modify the returned root | Original values and neighbor lists are unchanged |

Tests check values, adjacency, distinct cloned addresses, and the absence of any edge back into the original graph.

Run the local tests from this directory:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic test.cpp -o clone-graph-test
./clone-graph-test
```

## Complexity

Let `V` be the number of reachable nodes and `E` the number of undirected edges.

**Expected time:** O(V + E), assuming average O(1) hash-map operations. Every node is allocated once, and each edge is visited from both endpoints.\
**Auxiliary space:** O(V) for the map and recursion stack, excluding the cloned graph. The output takes O(V + E) space for nodes and neighbor lists.
