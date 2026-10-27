# Pacific Atlantic Water Flow

**Problem:** [LeetCode - Pacific Atlantic Water Flow](https://leetcode.com/problems/pacific-atlantic-water-flow/)\
**Solution:** [solution.cpp](solution.cpp)\
**Tests:** [test.cpp](test.cpp)

Given a rectangular matrix of heights, return the zero-based coordinates of every cell from which water can reach both oceans. The Pacific touches the top and left edges; the Atlantic touches the bottom and right edges. Water flows horizontally or vertically to a cell of equal or lower height. The two paths may be different, but both start at the same cell.

## Approach: reverse BFS from both oceans

Searching downhill from every cell repeats work. Instead, start from the cells beside each ocean and traverse the flow edges backward. If a neighboring cell is at least as high as the current cell, water could flow from that neighbor to the current cell and eventually to this ocean.

1. Create separate visited matrices and queues for the Pacific and Atlantic.
2. Seed the Pacific queue with every cell on the top or left edge.
3. Seed the Atlantic queue with every cell on the bottom or right edge.
4. For each ocean, repeatedly remove a cell from its queue. Skip it if already visited; otherwise mark it and examine its four neighbors.
5. Enqueue an unvisited neighbor only when `heights[nr][nc] >= heights[r][c]`.
6. Return the cells marked in both visited matrices.

A reverse path from an ocean boundary to a cell corresponds to a downhill or level path from that cell to the ocean. Therefore, the intersection of the visited matrices contains exactly the required cells.

Like Number of Islands, the grid is a graph with four possible neighbors per cell. Here, heights determine directed edges, and two searches track reachability to different destinations. Visited marks are permanent within each search; there is no backtracking undo step. BFS uses a queue to avoid deep recursive calls.

## How the C++ code is organized

| Part | Responsibility |
| --- | --- |
| `pacificAtlantic(heights)` | Seed both searches and collect the intersection |
| `pacific`, `atlantic` | Record which cells can drain into each ocean |
| `pacificQueue`, `atlanticQueue` | Hold cells pending reverse traversal |
| `bfs(heights, pending, visited)` | Traverse backward using one ocean's state |
| `directions` | Represent down, up, right, and left |
| `heights[nr][nc] >= heights[r][c]` | Reverse the normal direction of water flow |
| `pacific[r][c] && atlantic[r][c]` | Select cells that reach both oceans |

## Walkthrough

```text
heights:        Pacific visited:    Atlantic visited:
1 2             yes yes             no  yes
3 4             yes yes             yes yes
```

The Pacific starts at `(0,0)`, `(0,1)`, and `(1,0)` and reaches `(1,1)` by moving uphill. The Atlantic starts at `(0,1)`, `(1,0)`, and `(1,1)`. It cannot move backward into `(0,0)`, whose height `1` is lower than its neighbors.

Return `[[0,1], [1,0], [1,1]]`. For example, water from height `4` can flow through height `2` to the Pacific and directly off the bottom or right edge to the Atlantic. Water from height `1` cannot climb to reach the Atlantic.

## C++ notes

- `std::queue<std::pair<int, int>>` stores row and column coordinates.
- `auto [r, c]` unpacks a coordinate pair and requires C++17.
- Check bounds before accessing a neighbor's height or visited mark.
- Equal heights are allowed; using `>` instead of `>=` would lose valid paths across plateaus.
- A cell can be queued more than once before it is visited, including corner seeds. The visited check ensures its neighbors are expanded only once per ocean.
- The two oceans need separate visited matrices: reaching one does not imply reaching the other.
- The input is assumed rectangular, as required by the problem. Empty grids and empty rows return an empty result.
- The height matrix is unchanged, and each method call creates fresh search state.
- Results are collected in row-major order; the problem accepts any order.
- Submit the `Solution` class and includes; no `main()` is needed on LeetCode.

## Cases to check

| Case | What it checks |
| --- | --- |
| The standard `5 x 5` example | Two searches produce the expected seven cells |
| One cell, one row, or one column | Every cell touches both oceans |
| Increasing `2 x 2` heights | Reverse traversal moves uphill |
| A low center surrounded by high cells | The trapped center cannot climb to either ocean |
| A flat `200 x 200` grid | Equal-height cycles terminate and all cells qualify |
| Empty grid or empty row | Return an empty result |
| Repeated calls and input comparison | No stale state or input mutation |

Run the local tests from this directory:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic test.cpp -o pacific-atlantic-test
./pacific-atlantic-test
```

## Complexity

Let `M` and `N` be the number of rows and columns.

**Time:** O(M * N). Each ocean expands each cell at most once and checks at most four neighbors. Duplicate queue entries are bounded by the grid edges and boundary seeds. The final scan is also O(M * N).\
**Auxiliary space:** O(M * N) for the visited matrices and queues. The output can additionally contain O(M * N) coordinates.
