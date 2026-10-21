# Word Search

**Problem:** [LeetCode - Word Search](https://leetcode.com/problems/word-search/)\
**Solution:** [solution.cpp](solution.cpp)

Given a rectangular character grid and a word, return whether the word can be formed by moving between horizontally or vertically neighboring cells. A cell cannot be used twice in the same path. Matching is case-sensitive.

## Approach: DFS with backtracking

1. Scan every cell of the board. A cell matching `word[0]` is a possible starting point.
2. Call `dfs(board, word, r, c, k)` to match character `word[k]` at cell `(r, c)`.
3. Reject the branch if the cell is outside the board or its character does not match.
4. If this is the final character, return `true`.
5. Save the cell's character and replace it with `'#'` to mark it as used.
6. Search the four neighboring cells for `word[k + 1]`.
7. Restore the saved character before returning, whether the search succeeds or fails.
8. If every starting point fails, return `false`.

The marked cells belong only to the current path. Restoring them lets other paths and starting points use them again. Unlike Word Search II, this problem has only one target word: an index `k` tracks progress directly, so a trie is unnecessary.

## How the C++ code is organized

| Part | Responsibility |
| --- | --- |
| Outer two loops | Try every possible starting cell |
| `r`, `c` | Identify the current board cell |
| `k` | Identify the character currently being matched |
| Boundary and character checks | Reject invalid paths before accessing or using a cell |
| Final-character check | Recognize a complete match |
| `saved` and `'#'` | Preserve the character and temporarily prevent reuse |
| Four recursive calls | Try down, up, right, and left |
| `board[r][c] = saved` | Undo the mark even when a recursive call succeeds |

## Walkthrough

```text
board:
A B E
C D F

word = "ABD"
```

| Step | Cell | Character index | Action |
| --- | --- | --- | --- |
| 1 | `(0,0)` = A | `0` | Match A, mark the cell |
| 2 | `(1,0)` = C | `1` | Reject: expected B |
| 3 | `(0,1)` = B | `1` | Match B, mark the cell |
| 4 | `(1,1)` = D | `2` | Match the final character; return `true` |
| Return | B, then A | — | Restore marked cells before returning `true` |

Coordinates are zero-based. The path is A → B → D. Out-of-bounds neighbor attempts return `false` immediately.

## C++ notes

- The problem's board and word contain English letters, so `'#'` cannot match a target character.
- `word` is passed by constant reference within DFS to avoid copying it at each recursive call.
- `||` short-circuits: once one neighbor succeeds, the remaining neighbors are skipped.
- Store the combined result in `found`, restore the cell, then return. Returning directly from a successful neighbor would leave marks on the board.
- The public method takes `word` by value to match the submission interface.
- The board is restored after both successful and unsuccessful searches; the same object can be called repeatedly.
- Empty words return `true`; empty boards return `false` for nonempty words. The problem itself guarantees nonempty inputs.
- No `main` function is needed when submitting the `Solution` class.

## Cases to check

| Case | What it checks |
| --- | --- |
| `ABCCED` and `SEE` on the standard example | Paths with turns |
| `ABCB` on the standard example | A cell cannot be reused |
| A diagonal-only match | Diagonal moves are rejected |
| Several cells matching the first character | Later starting points are tried |
| A failed branch before a successful one | Backtracking restores cells for another branch |
| Single row, column, and cell | Boundary checks |
| Repeated calls | Input board is restored after success and failure |
| Empty word or board | Defensive input handling |

## Complexity

Let `M` and `N` be the board dimensions and `L` the word length.

**Time:** O(M * N * 4^L), a simple worst-case upper bound. There are `M * N` starting points and at most four recursive calls at each level. Marking cells and rejecting mismatches reduce the actual search.\
**Auxiliary search space:** O(min(L, M * N)) for recursion. Cell marking uses no separate visited grid. The public method also holds a copy of the word using O(L) space, making total auxiliary space O(L).

## Using the code

Submit the includes and the `Solution` class from `solution.cpp`.

Run the local [test.cpp](test.cpp) from this folder:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic test.cpp -o test
./test
```
