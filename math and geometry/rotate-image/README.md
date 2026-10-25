# Rotate Image

**Problem:** [LeetCode - Rotate Image](https://leetcode.com/problems/rotate-image/)\
**Solution:** [solution.cpp](solution.cpp)

Given an `n x n` integer matrix, rotate it 90 degrees clockwise. Modify the input matrix in place without allocating another matrix for the result.

## Approach: transpose, then reverse each row

1. Transpose the matrix by swapping `matrix[i][j]` with `matrix[j][i]` for every `j > i`.
2. Reverse each row with `std::reverse`.

Transposing moves an element from `(i, j)` to `(j, i)`. Reversing each row then moves it to `(j, n - 1 - i)`, which is exactly its position after a 90-degree clockwise rotation.

Only visit entries above the main diagonal during transposition. Visiting both halves would swap every pair twice and restore the original matrix. Diagonal entries already have the correct position for the transpose.

## Walkthrough

```text
Original:       Transpose:      Reverse each row:
1 2 3           1 4 7           7 4 1
4 5 6     ->    2 5 8     ->    8 5 2
7 8 9           3 6 9           9 6 3
```

For example, `3` starts at `(0, 2)`, moves to `(2, 0)` after transposition, then to `(2, 2)` after row reversal. The original top row becomes the rightmost column, read from top to bottom.

## C++ notes

- `std::vector<std::vector<int>>& matrix` passes the matrix by reference so changes affect the caller's matrix.
- `j = i + 1` visits each off-diagonal pair exactly once.
- `std::swap` exchanges two entries without copying the matrix.
- `auto& row` accesses each original row by reference; omitting `&` would reverse a copy.
- `std::reverse(row.begin(), row.end())` reverses the complete row in place.
- The input is guaranteed to be square. This transpose loop does not support rectangular matrices.
- The function returns `void` because the result is stored in the input matrix. No `main` function is needed when submitting the `Solution` class.

## Examples

| Input | Expected result | Reason |
| --- | --- | --- |
| `[[1,2,3],[4,5,6],[7,8,9]]` | `[[7,4,1],[8,5,2],[9,6,3]]` | Odd-sized matrix; center stays fixed |
| `[[1,2],[3,4]]` | `[[3,1],[4,2]]` | Even-sized matrix |
| `[[-7]]` | `[[-7]]` | One entry remains unchanged |
| `[[0,-1],[-1,0]]` | `[[-1,0],[0,-1]]` | Zero, negative values, and duplicates |

## Cases to check

[test.cpp](test.cpp) uses assertions for the examples above and verifies that four consecutive rotations restore the original matrix.

Run from this directory:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic test.cpp -o rotate-image-test
./rotate-image-test
```

## Complexity

**Time:** O(n²), where `n` is the side length. Transposition swaps `n * (n - 1) / 2` pairs, and reversing every row also takes O(n²) time.\
**Auxiliary space:** O(1). Both operations modify the existing matrix with no extra matrix or recursion.
