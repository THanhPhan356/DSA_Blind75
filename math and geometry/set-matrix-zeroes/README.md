# Set Matrix Zeroes

**Problem:** [LeetCode - Set Matrix Zeroes](https://leetcode.com/problems/set-matrix-zeroes/)\
**Solution:** [solution.cpp](solution.cpp)\
**Tests:** [test.cpp](test.cpp)

Given an `m x n` integer matrix, if an element is originally zero, set its entire row and column to zero. Modify the matrix in place. Only original zeros determine which rows and columns are cleared; newly written zeros must not trigger more changes.

## Approach: use the first row and column as markers

Separate marking from clearing. Two additional arrays could record which rows and columns contain zeros, but the first row and column can store those markers directly, giving O(1) auxiliary space.

1. Before writing any markers, record whether the first row and first column originally contain a zero in `firstRowZero` and `firstColZero`.
2. Scan only the interior, where `i >= 1` and `j >= 1`. When `matrix[i][j] == 0`, set `matrix[i][0] = 0` and `matrix[0][j] = 0`.
3. Scan the interior again. Set an element to zero if its row marker or column marker is zero.
4. Clear the first row if `firstRowZero` is true, and the first column if `firstColZero` is true.

The interior stays unchanged during marking, so every zero found there is an original zero. Interior clearing does not modify the markers. Process the first row and column last so the markers remain available until all interior cells have been handled.

## How the C++ code is organized

| Part | Responsibility |
| --- | --- |
| `setZeroes(matrix)` | Modify the input directly; return no value |
| `firstRowZero` | Remember whether the first row originally needs clearing |
| `firstColZero` | Remember whether the first column originally needs clearing |
| `matrix[i][0]` | Mark whether row `i` needs clearing |
| `matrix[0][j]` | Mark whether column `j` needs clearing |
| Two interior passes | Record original zeros, then apply the markers |
| Final two loops | Clear the first row and column using their saved flags |

The two flags preserve separate information about the first row and column. Their shared corner, `matrix[0][0]`, cannot by itself represent both decisions.

## Walkthrough

Start with a zero at `(1, 2)`, using zero-based indexes:

```text
Original:             After marking:        Final:
1 2 3                 1 2 0                 1 2 0
4 5 0                 0 5 0                 0 0 0
7 8 9                 7 8 9                 7 8 0
```

Both flags are false because the first row and column originally contain no zero. The original zero marks `matrix[1][0]` to clear row `1`, and `matrix[0][2]` to clear column `2`. In the second pass, the interior cells in that row or column become zero.

The marker at `(1, 0)` must not cause the whole first column to be cleared. Likewise, the marker at `(0, 2)` must not clear the whole first row. The saved flags distinguish markers from original zeros.

## C++ notes

- Submit the `Solution` class from `solution.cpp` without `test.cpp` or a `main()` function.
- `std::vector<std::vector<int>>&` passes the matrix by reference so assignments update the caller's matrix.
- Start both interior loops at `1` to preserve the marker row and column.
- Use logical OR: a cell needs clearing when either its row or its column is marked.
- Do not clear a whole row or column immediately upon finding a zero; newly written zeros could incorrectly spread the clearing.
- No special integer sentinel is needed, so negative values and integer limits are safe.
- All state is local, allowing repeated calls on the same object.
- Empty input is handled; rows are assumed to have equal lengths, as required by the problem.

## Cases to check

| Case | What it checks |
| --- | --- |
| An interior zero | Clear its row and column without spreading further |
| Zeros only in the first row or first column | The two flags operate independently |
| Zero at `(0, 0)` | Both the first row and column are cleared |
| Several original zeros or all zeros | Combine all required rows and columns |
| No zeros, negative values, integer limits | Preserve nonzero values unless their row or column is marked |
| Single row, single column, one cell | Interior passes may be empty |
| Empty matrix or empty row | Return safely |
| Repeated calls and a `200 x 200` matrix | Local state and larger input |

Tests also enumerate every zero/nonzero pattern for matrices from `1 x 1` through `3 x 4`, comparing against an independent implementation that reads only the original matrix. Run from this directory:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic test.cpp -o set-matrix-zeroes-test
./set-matrix-zeroes-test
```

## Complexity

**Time:** O(m * n), using a constant number of passes.\
**Auxiliary space:** O(1), using two flags and a fixed number of indexes. The input matrix itself stores the markers.
