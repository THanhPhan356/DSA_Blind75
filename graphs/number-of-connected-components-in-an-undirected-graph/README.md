# Number of Connected Components in an Undirected Graph

**Problem:** [LeetCode - Number of Connected Components in an Undirected Graph](https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph/)\
**Solution:** [solution.cpp](solution.cpp)\
**Tests:** [test.cpp](test.cpp)

Given `n` nodes numbered from `0` to `n - 1` and a list of undirected edges, return the number of connected components. Each pair `[a, b]` connects `a` and `b` in both directions. A connected component is a maximal group of mutually reachable nodes. An isolated node is also one component.

## Approach: DFS from every unvisited node

1. Build an adjacency list with `n` entries. Add both directions of every edge.
2. Initialize every visited mark to `false` and the component count to `0`.
3. Scan every node from `0` to `n - 1`.
4. If the node is already visited, skip it: its component has already been counted.
5. Otherwise, increment the count and start DFS from that node.
6. DFS marks its current node visited and recursively explores each unvisited neighbor.
7. Return the count after scanning all nodes.

One DFS reaches exactly one connected component. After it finishes, every node in that component is marked, so the outer loop never counts that component again. Every component eventually supplies an unvisited starting node, including isolated nodes.

Unlike Graph Valid Tree, this problem does not reject cycles. An already visited neighbor is simply skipped. No parent parameter is needed because the task does not distinguish a reverse parent edge from an edge closing a cycle.

## How the C++ code is organized

| Part | Responsibility |
| --- | --- |
| `graph[i]` | Store the nodes directly connected to node `i` |
| Two `push_back` calls per edge | Represent an undirected edge in both directions |
| `visited[node] = true` | Mark a node before exploring its neighbors |
| `if (!visited[next])` | Avoid repeated visits and infinite traversal around cycles |
| `dfs(next, graph, visited)` | Explore another node in the same component |
| Outer loop over all `n` nodes | Find components disconnected from earlier starting nodes |
| `++count` before a new DFS | Count the new component once |

## Walkthrough

For `n = 6` and `edges = [[0,1], [1,2], [3,4]]`:

```text
0 -- 1 -- 2       3 -- 4       5
```

| Node examined by the outer loop | Action | Count |
| --- | --- | --- |
| `0` | Unvisited: start DFS and mark `0`, `1`, and `2` | `1` |
| `1`, `2` | Already visited: skip | `1` |
| `3` | Unvisited: start DFS and mark `3` and `4` | `2` |
| `4` | Already visited: skip | `2` |
| `5` | Unvisited: start DFS and mark this isolated node | `3` |

Return `3`. Adding edge `[2,0]` creates a cycle inside the first component but does not change the answer.

## C++ notes

- `next` is a neighboring node ID, not an index into the neighbor list.
- Recursive calls share `visited` by reference and read `graph` through a constant reference.
- Visited marks stay `true` after returning; there is no backtracking undo step.
- `dfs` returns `void` because it only marks reachable nodes. The outer loop counts components.
- State is local to `countComponents`, so the same `Solution` object can be reused. The input edge list is unchanged.
- Inputs follow the problem's contract: `n >= 1`, each edge contains two valid node IDs, and there are no self-loops or repeated edges.
- Submit the includes and `Solution` class; the judge supplies `main()`.

## Cases to check

| Case | What it checks |
| --- | --- |
| One node or several nodes without edges | Every isolated node counts as one component |
| One edge, a chain, and multiple separate groups | Connected nodes are counted together |
| A triangle and a cycle in a disconnected component | Cycles are allowed and traversal terminates |
| An isolated node numbered `0` | The search must continue beyond the first node |
| Reordered and reversed edge pairs | Edges are undirected |
| A chain of 2,000 nodes, with and without a closing edge | Deep recursion and visited checks |
| Repeated calls and input comparison | No stale state or input mutation |

Run the local tests from this directory:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic test.cpp -o connected-components-test
./connected-components-test
```

## Complexity

Let `V = n` and `E = edges.size()`.

**Time:** O(V + E). Building the adjacency list takes O(V + E); DFS visits each node once and checks each undirected edge twice across all components. The outer scan takes O(V).\
**Auxiliary space:** O(V + E) for the adjacency list, visited marks, and recursion stack. Recursion can reach O(V) depth; iterative DFS or BFS avoids recursive stack overflow for much deeper graphs or smaller stack limits.
