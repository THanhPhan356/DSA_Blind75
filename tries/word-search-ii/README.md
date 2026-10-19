# Word Search II

**Problem:** [LeetCode - Word Search II](https://leetcode.com/problems/word-search-ii/)\
**Solution:** [solution.cpp](solution.cpp)

Given a character grid and a list of words, return the listed words that can be formed by a path on the grid. A path can start anywhere and move up, down, left, or right. It cannot use the same cell twice for one word. Different words can reuse cells. Report each found word once.

**Study status:** Saved as a reference implementation. Revisit and implement independently after learning backtracking; this entry does not mark backtracking as mastered.

## Approach: trie with DFS and backtracking

Build a trie containing all target words, then start a depth-first search (DFS) from every board cell. A search follows a board path and a trie path together. Stop immediately when the next board character has no matching trie edge: no target word has that prefix.

The trie shares work between words with the same prefix. Backtracking makes board cells available again when a search returns.

### Build the trie

1. Start at root index `0` for each word.
2. Map each letter to a child slot with `ch - 'a'`.
3. Append a node when that child is missing.
4. Store the word's index at its terminal node. `-1` means no unreported word ends there.

### Search the board

The helper `dfs(board, words, r, c, parent)` tries to consume cell `(r, c)` from trie node `parent`.

1. Return if the cell is outside the grid or already marked `'#'`.
2. Return if its letter has no child below `parent`.
3. Follow that child. If it ends a word, append the word and reset its index to `-1` to avoid duplicate results.
4. Temporarily replace the cell with `'#'` to prevent reuse in the current path.
5. Search the four neighboring cells from the new trie node.
6. Restore the cell's original character before returning. This is the backtracking step.
7. If the node has no remaining terminal word or children, disconnect it from its parent. That branch cannot produce any new answer.

Finding a word does not end the search: `back` can extend to `backend`. Resetting a terminal marker must not remove its children. Nodes disconnected during pruning remain allocated until the trie is cleared or destroyed.

## How the C++ code is organized

| Part | Responsibility |
| --- | --- |
| `std::vector<Node> trie` | Own all nodes and identify them by integer indexes |
| `int next[26]` | Store child indexes; `-1` represents a missing edge |
| `wordIndex` | Identify a complete word without rebuilding its string along the path |
| `board[r][c]` | Access row `r`, column `c`, with indexes starting at zero |
| `rows`, `cols` | Check boundaries before accessing a cell |
| `'#'` | Mark a cell used by the current path |
| `board[r][c] = ch` | Restore the cell when returning from recursion |
| Outer two loops | Try every cell as a starting point |
| `result.clear()`, `trie.clear()` | Reset state when the same `Solution` object is reused |

Insertion uses indexes rather than references to nodes: appending to a vector can invalidate references when it reallocates.

## Walkthrough

```text
board:
a b c d
s a a t
a c k e
a c d n

words = ["bat", "cat", "back", "backend", "stack"]
```

Coordinates below are zero-based `(row, column)`.

| Word | Path or reason |
| --- | --- |
| `cat` | `(0,2) -> (1,2) -> (1,3)` |
| `back` | `(0,1) -> (1,1) -> (2,1) -> (2,2)` |
| `backend` | Continue the `back` path through `(2,3) -> (3,3) -> (3,2)` |
| `bat` | Neither `a` beside the only `b` has a neighboring `t` |
| `stack` | The only `s` has no neighboring `t` |

Return `cat`, `back`, and `backend`; result order is irrelevant.

## C++ notes

- The grid and word list contain lowercase English letters, so `'#'` is a safe temporary marker.
- A board path cannot move diagonally, jump over a cell, or revisit an earlier cell in that path.
- Restore cells even after finding a word so that other words can use them.
- The caller's board is restored, and the input word list is unchanged after the function returns.
- The trie is rebuilt on each call because reporting words and pruning modify it.
- No `main` function is needed when submitting the `Solution` class.

## Cases to check

| Case | What it checks |
| --- | --- |
| The example above | Turning paths and a word that extends another word |
| One word with several possible paths | Each word appears only once |
| A word requiring cell reuse or a diagonal move | Invalid paths are rejected |
| Shared prefixes and early failed paths | Trie pruning preserves words that are still needed |
| Single row, single column, and one cell | Boundary checks |
| Repeated calls on one object | State is reset and board contents are restored |
| Deterministic random small boards | Results agree with an independent per-word search |

## Complexity

Let `S` be the sum of input word lengths, `M` and `N` the board dimensions, and `L` the smaller of the longest word length and `M * N`.

**Time:** O(S + M * N * 4 * 3^(L - 1)) as a worst-case upper bound for non-empty inputs. Building the trie takes O(S). From each start, the first move has at most four options and later moves at most three because the previous cell is marked. Prefix checks and exhausted-branch pruning often reduce the search substantially. The 26-child scan is constant work per visited trie node.\
**Stored space:** O(S) for the trie, excluding returned strings.\
**Auxiliary search space:** O(L) for the recursion stack; cell marking does not require a separate visited grid.\
**Output space:** O(F), where `F` is the total length of returned words.

## Using the code

Submit the includes and the `Solution` class from `solution.cpp`.

Run the local [test.cpp](test.cpp) from this folder:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic test.cpp -o test
./test
```
