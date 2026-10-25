# Spiral Matrix

**Problem:** [LeetCode - Spiral Matrix](https://leetcode.com/problems/spiral-matrix/)\
**Solution:** [solution.cpp](solution.cpp) (position and visited cells)\
**Alternative:** [solution-boundaries.cpp](solution-boundaries.cpp) (four boundaries)

Given an `m x n` integer matrix, return its elements in clockwise spiral order, starting at the top-left corner. The matrix can be rectangular. Both implementations leave the input unchanged.

## Approach 1: move a position and track visited cells

1. Start at `(row, col) = (0, 0)`, facing right.
2. Append the current value and mark its cell as visited.
3. Compute the next position. If it is outside the matrix or already visited, turn clockwise.
4. Move one cell in the current direction.
5. Repeat exactly `m * n` times.

The direction arrays encode right, down, left, and up. `(direction + 1) % 4` selects the next direction and wraps from up back to right. Checking only the outer edge is insufficient: after completing the outer layer, visited cells force the path into the next layer.

The position update after the final element is unused because the loop ends before accessing another cell.

## Approach 2: shrink four boundaries

Keep `top`, `bottom`, `left`, and `right` as inclusive row and column indexes of the unvisited region. Indexes start at zero: for a `4 x 4` matrix, the initial boundaries are `0`, `3`, `0`, and `3`.

| Direction | Cells to append | Boundary update |
| --- | --- | --- |
| Right | Row `top`, columns `left` through `right` | `++top` |
| Down | Column `right`, rows `top` through `bottom` | `--right` |
| Left | Row `bottom`, columns `right` down to `left` | `--bottom` |
| Up | Column `left`, rows `bottom` down to `top` | `++left` |

Repeat while `top <= bottom && left <= right`. Check `top <= bottom` before the leftward pass and `left <= right` before the upward pass. These checks prevent revisiting elements when the remaining region is a single row or column; loop bounds also skip empty ranges.

Update each boundary immediately after its pass. For example, the top-right corner is already included in the top row, so the right-column pass starts at the new `top` and does not append that corner twice.

## Walkthrough

```text
 1   2   3   4
 5   6   7   8
 9  10  11  12
13  14  15  16
```

| Layer | Right | Down | Left | Up |
| --- | --- | --- | --- | --- |
| Outer | `1, 2, 3, 4` | `8, 12, 16` | `15, 14, 13` | `9, 5` |
| Inner | `6, 7` | `11` | `10` | No cells remain |

Result: `[1,2,3,4,8,12,16,15,14,13,9,5,6,7,11,10]`.

With visited cells, the upward path reaches `5`, detects that `1` is visited, and turns right toward `6`. With boundaries, completing the outer layer leaves rows `1..2` and columns `1..2` for the next iteration.

## C++ notes

- Both files define the submission signature `std::vector<int> spiralOrder(std::vector<std::vector<int>>& matrix)` inside `class Solution`. Submit one file at a time, without `test.cpp`.
- `dr` and `dc` store the row and column changes for each direction.
- The bounds checks appear before `visited[nextRow][nextCol]`. C++ short-circuit evaluation prevents indexing outside the visited matrix.
- Signed indexes let a boundary become `-1` without unsigned underflow.
- All traversal state is local, so repeated calls do not retain visited cells or old results.
- Both implementations handle an empty matrix and an empty row. Like the problem, they assume rectangular rows with equal lengths.

## Cases to check

[test.cpp](test.cpp) checks both implementations against explicit expected sequences.

| Case | What it checks |
| --- | --- |
| `3 x 3` and `4 x 4` | Multiple layers and the center of an odd-sized matrix |
| Wide and tall rectangles | Row and column counts are independent |
| Single row, single column, one cell | No duplicated values when a boundary collapses |
| Negative values, zeros, duplicates | Visitation depends on positions, not element values |
| Empty matrix or empty row | Return an empty result safely |
| Repeated calls and unchanged input | State is reset and the input is preserved |

Run from this directory:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic test.cpp -o spiral-matrix-test
./spiral-matrix-test
```

## Complexity

| Approach | Time | Auxiliary space, excluding the result |
| --- | --- | --- |
| Position and visited cells | O(m * n) | O(m * n) |
| Four boundaries | O(m * n) | O(1) |

Each cell is appended exactly once. Both result vectors require O(m * n) space.
