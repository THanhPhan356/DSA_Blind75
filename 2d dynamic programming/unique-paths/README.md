# Unique Paths

**Problem:** [LeetCode - Unique Paths](https://leetcode.com/problems/unique-paths/)\
**Solution:** [solution.cpp](solution.cpp)\
**Tests:** [test.cpp](test.cpp)

Given a grid with `m` rows and `n` columns, count the distinct paths from the top-left cell to the bottom-right cell. Each move goes one cell right or down. There are no obstacles. Return the number of paths, not the paths themselves. Dimensions are positive; the problem guarantees the answer fits within `2 * 10^9`.

## Approach: top-down dynamic programming with memoization

Define `dfs(r, c, m, n, memo)` as the number of paths from cell `(r, c)` to the destination.

Every path starts by moving down or right. These two cases are disjoint and cover all possible first moves, so:

```text
dfs(r, c) = dfs(r + 1, c) + dfs(r, c + 1)
dfs(m - 1, n - 1) = 1
dfs(r, c) = 0 when r >= m or c >= n
```

Reaching the destination counts as one completed path; leaving the grid cannot produce a valid path.

1. Create an `m` by `n` cache initialized to `-1` and start at `(0, 0)`.
2. Check boundaries before accessing the cache.
3. Return `1` at the destination.
4. Return a cached count if the current cell was already computed.
5. Otherwise, add the counts from the down and right neighbors, save the sum, and return it.

Different prefixes can reach the same cell. The remaining number of paths depends only on that cell, so reuse its count instead of exploring the same suffixes again. No path list, visited array, or undo step is needed: every move increases a coordinate, so recursion cannot revisit an earlier cell on the same path.

## How the C++ code is organized

| Part | Responsibility |
| --- | --- |
| `uniquePaths(m, n)` | Create a fresh cache and start the search |
| `r`, `c` | Zero-based row and column of the current cell |
| `m`, `n` | Number of rows and columns |
| `vector<vector<int>>& memo` | Share the cache without copying it |
| `memo[r][c]` | Store the number of paths from this cell to the destination |
| `-1` | Mark a count that has not been computed |
| `dfs(r + 1, c, ...)` | Count paths whose next move is down |
| `dfs(r, c + 1, ...)` | Count paths whose next move is right |

## Walkthrough

For `m = 2`, `n = 3`, there are three paths: right-right-down, right-down-right, and down-right-right.

The number of remaining paths from each cell is:

```text
3  2  1
1  1  1
```

At `(0, 1)`, moving down gives one path and moving right gives one path, for a total of two. At the start, moving down gives one path and moving right gives two, so return `3`.

For a `3` by `3` grid, both right-down and down-right reach `(1, 1)`. The count from `(1, 1)` is `2` regardless of the earlier moves; compute it once and reuse it. This implementation counts paths from a cell to the destination, rather than paths from the start to a cell.

## C++ notes

- Submit the `Solution` class without a `main()` function.
- The helper is private by default because it appears before `public:`.
- Check out-of-bounds coordinates before indexing `memo`.
- The destination returns directly, so its cache entry remains `-1`.
- `int` is sufficient under the problem's answer bound. Larger unrestricted grids can overflow it.
- A local cache keeps repeated calls on the same object independent.
- Bottom-up DP can reduce memory to one row. This version preserves the recursive approach.

## Cases to check

| Input `(m, n)` | Expected result | What it checks |
| --- | --- | --- |
| `(1, 1)` | `1` | Start is already the destination |
| `(1, 100)` or `(100, 1)` | `1` | Only one direction is available |
| `(2, 3)` or `(3, 2)` | `3` | Rectangular grids and symmetry |
| `(3, 3)` | `6` | Shared subproblems |
| `(3, 7)` | `28` | A wider grid |
| `(10, 10)` | `48620` | A larger square grid |
| `(17, 18)` | `1166803110` | A large count within the answer bound |

Tests also repeat an earlier input on the same object. Run from this directory:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic test.cpp -o unique-paths-test
./unique-paths-test
```

## Complexity

**Time:** O(m * n). Each non-base cell is computed once, with constant work per state.\
**Auxiliary space:** O(m * n) for the cache plus O(m + n) for the recursion stack, totaling O(m * n) for positive dimensions.
