# Graph Valid Tree

**Problem:** [LeetCode - Graph Valid Tree](https://leetcode.com/problems/graph-valid-tree/)\
**Solution:** [solution.cpp](solution.cpp)\
**Tests:** [test.cpp](test.cpp)

Given `n` nodes numbered from `0` to `n - 1` and a list of undirected edges, return whether the graph is a tree. A valid tree is connected and has no cycle. Each pair `[a, b]` connects `a` and `b` in both directions.

## Approach: DFS with a parent and visited marks

1. Build an adjacency list with `n` entries. For every edge, add each endpoint to the other endpoint's list.
2. Initialize every visited mark to `false`.
3. Call `dfs(0, -1, graph, visited)`. The root has no parent, represented by `-1`.
4. Mark the current node visited and examine each neighbor.
5. Skip a neighbor equal to the parent: this is the same undirected edge in reverse, not a cycle.
6. If another neighbor is already visited, return `false` because the edge closes a cycle.
7. Otherwise, recurse into that neighbor, passing the current node as its parent. Propagate any `false` result immediately.
8. If DFS succeeds, check that every node was visited. An unvisited node means the graph is disconnected, so return `false`. Otherwise return `true`.

DFS explores the component containing node `0`. If that component has no cycle and includes every node, the whole graph is a tree. A cycle in another component does not need a separate DFS: the connectivity check already rejects the graph.

Unlike Course Schedule, edges here are undirected. A single visited flag is sufficient when the parent edge is skipped; the three states used for directed cycle detection are unnecessary.

## How the C++ code is organized

| Part | Responsibility |
| --- | --- |
| `graph[i]` | Store the nodes directly connected to node `i` |
| Two `push_back` calls per edge | Represent both directions of an undirected edge |
| `visited[node] = true` | Record that DFS has reached this node |
| `parent` | Identify the node from which this DFS call arrived |
| `next == parent` | Skip traversing the same edge backward |
| `visited[next]` after the parent check | Detect a cycle |
| `dfs(next, node, graph, visited)` | Explore a neighbor with the correct parent |
| Final loop over `visited` | Reject disconnected graphs |

## Walkthrough

For `n = 5` and `edges = [[0,1], [0,2], [0,3], [1,4]]`:

```text
    0
   /|\
  1 2 3
  |
  4
```

| Step | Action |
| --- | --- |
| 1 | Visit `0` with parent `-1`; its neighbors are `1`, `2`, and `3` |
| 2 | Visit `1` with parent `0`; skip neighbor `0` because it is the parent |
| 3 | Visit `4` with parent `1`; skip neighbor `1` and return `true` |
| 4 | Return from `1` to the suspended call for `0`; its loop continues with `2` |
| 5 | Visit `2`, skip parent `0`, and return; then do the same for `3` |
| 6 | DFS succeeds and all five nodes are visited, so return `true` |

For a triangle `[[0,1], [1,2], [2,0]]`, DFS follows `0 -> 1 -> 2`. At node `2`, neighbor `1` is the parent and is skipped. Neighbor `0` is already visited and is not the parent, so `2 -> 0` closes a cycle and the method returns `false`.

For `n = 4` and `edges = [[0,1], [2,3]]`, DFS finds no cycle in `0`'s component, but nodes `2` and `3` remain unvisited. The final check returns `false`.

## C++ notes

- `next` is a neighboring node ID, not its position in the adjacency list.
- Recursive calls share `visited` by reference, while `graph` is read through a constant reference.
- Marks stay `true` after returning from DFS; there is no backtracking undo step.
- Returning from a child resumes the parent's loop; it does not require a graph edge pointing back to the parent.
- Each call to `validTree` creates fresh state, so the same `Solution` object can be reused. The input edge list is unchanged.
- Inputs follow the problem's contract: `n >= 1`, each edge has two valid node IDs, and there are no self-loops or repeated edges.
- Submit the includes and `Solution` class; the judge supplies `main()`.

## Cases to check

| Case | What it checks |
| --- | --- |
| One node without edges | A single node is a valid tree |
| Two nodes with one edge | The reverse parent edge is not a cycle |
| A branching tree and a chain | DFS explores all neighbors |
| A triangle or a longer cycle | A visited non-parent neighbor is rejected |
| Disconnected components or an isolated root | Connectivity is required |
| `n - 1` edges but a disconnected graph containing a cycle | Edge count alone is insufficient |
| Reordered or reversed edge pairs | Edges are undirected |
| A chain of 2,000 nodes, with and without a closing edge | Deep recursion and cycle propagation |
| Repeated calls and input comparison | No stale state or input mutation |

Run the local tests from this directory:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic test.cpp -o graph-valid-tree-test
./graph-valid-tree-test
```

## Complexity

Let `V = n` and `E = edges.size()`.

**Time:** O(V + E). Building the graph takes O(V + E); DFS visits each reached node once and checks each undirected edge at most twice, and the final scan takes O(V).\
**Auxiliary space:** O(V + E) for the adjacency list, visited marks, and recursion stack. Recursion can reach O(V) depth; iterative DFS or BFS avoids recursive stack overflow for much deeper graphs or smaller stack limits.
