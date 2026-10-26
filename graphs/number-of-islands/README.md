# Number of Islands

**Problem:** [LeetCode - Number of Islands](https://leetcode.com/problems/number-of-islands/)\
**Solution:** [solution.cpp](solution.cpp)\
**Tests:** [test.cpp](test.cpp)

Given a rectangular grid containing `'1'` (land) and `'0'` (water), return the number of islands. An island consists of land cells connected horizontally or vertically. Diagonal contact does not connect islands. The area outside the grid is water.

## Approach: DFS and connected components

Treat each land cell as a graph vertex. Edges connect horizontally or vertically adjacent land cells. Each island is one connected component; there is no need to build a separate adjacency list.

1. Scan every cell with two loops.
2. Skip water and previously visited land.
3. On finding `'1'`, increment the island count and start DFS from that cell.
4. DFS returns immediately for an out-of-bounds cell or any cell other than `'1'`.
5. Replace the current land cell with `'0'` before visiting its four neighbors.
6. Continue scanning after DFS finishes. Every cell in that island is now marked, so it cannot be counted again.

Each DFS reaches exactly the land connected to its starting cell. Therefore, the first scanned cell of each island increments the count once, and the remaining cells of that island never increment it.

Unlike backtracking in Word Search, these visited marks are permanent. The task counts components, so there is no reason to restore a cell for another path. This implementation modifies the input grid: all land becomes water.

## How the C++ code is organized

| Part | Responsibility |
| --- | --- |
| `numIslands(grid)` | Scan the grid and return the number of islands |
| `r`, `c` | Identify a cell by row and column |
| `islands` | Count DFS searches started from unvisited land |
| `dfs(grid, r, c)` | Mark every land cell connected to the starting cell |
| Boundary checks | Reject invalid coordinates before accessing a cell |
| `grid[r][c] = '0'` | Mark land as visited without a separate visited matrix |
| Four recursive calls | Explore down, up, right, and left |

## Walkthrough

```text
Before:          Labels for explanation:
1 1 0 0 0        A A 0 0 0
1 1 0 0 0        A A 0 0 0
0 0 1 0 0        0 0 B 0 0
0 0 0 1 1        0 0 0 C C
```

| First unvisited land | Action | Island count |
| --- | --- | --- |
| `(0,0)` | DFS marks all four cells of A as water | `1` |
| `(2,2)` | DFS marks the single cell of B as water | `2` |
| `(3,3)` | DFS marks both cells of C as water | `3` |

Coordinates are zero-based. B touches A and C only diagonally, so it is a separate island. Return `3`; the modified grid contains only `'0'`.

## C++ notes

- Cells contain characters: compare against `'1'` and `'0'`, not integers `1` and `0`.
- Pass the grid by reference so recursive calls share the visited marks.
- Mark a cell before exploring neighbors; otherwise adjacent land cells can recurse back into each other indefinitely.
- `||` evaluates left to right and short-circuits, so invalid coordinates return before `grid[r][c]` is accessed.
- The input is assumed rectangular, as required by the problem. Empty grids and empty rows return `0`.
- Calling the method again on the same modified grid returns `0`. Copy the grid before calling if its original contents must be retained.
- Recursive DFS can use one stack frame per land cell in the worst case. Use an explicit stack or BFS when recursion depth can exceed the runtime stack limit.
- Submit the `Solution` class and includes; no `main()` is needed on LeetCode.

## Cases to check

| Case | What it checks |
| --- | --- |
| One connected island | Several rows belong to the same component |
| The three-island walkthrough | Separate components and diagonal contact |
| Diagonally adjacent land | Diagonal moves are excluded |
| A solid `2 x 2` island | Cycles do not revisit marked cells |
| Single row, column, and cell | Boundary checks |
| All water or an empty grid | Return `0` |
| A second call on the consumed grid | Permanent marks prevent recounting |

Run the local tests from this directory:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic test.cpp -o number-of-islands-test
./number-of-islands-test
```

## Complexity

Let `M` and `N` be the number of rows and columns.

**Time:** O(M * N). The outer loops scan every cell, and each land cell is marked once with at most four neighbor checks.\
**Auxiliary space:** O(M * N) in the worst case for the recursion stack. Reusing the grid avoids a separate visited matrix but does not eliminate recursion space.
