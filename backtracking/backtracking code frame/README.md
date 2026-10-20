# Backtracking Code Frame

**Solution:** [solution.cpp](solution.cpp)\
**Tests:** [test.cpp](test.cpp)

A reusable C++ frame for building an answer one choice at a time. Try a valid choice, explore it recursively, then undo it before trying the next choice. Backtracking usually explores the decision tree in depth-first order (DFS).

## Approach: choose, explore, undo

1. Start with an empty state and call `backtrack(0)`.
2. If `k == n`, record the complete answer and return from this branch.
3. Loop through the candidate choices.
4. Skip a choice when `valid(choice)` is false: this branch cannot produce a valid answer.
5. Apply the choice with `choose(choice)`.
6. Call `backtrack(k + 1)` to fill the next position.
7. Call `undo(choice)` to restore the state before the next iteration.

Each call must leave the working state exactly as it found it. A `return` at the base case ends only the current call; its caller continues with undoing the choice and trying the next candidate.

## How the C++ code is organized

| Part | Responsibility |
| --- | --- |
| `n` | Number of choices needed for a complete answer; must be nonnegative |
| `k` | Number of choices already made |
| `choices` | Candidates to try at each level |
| `valid(choice)` | Check the candidate against the current partial answer |
| `choose(choice)` | Update the working state |
| `backtrack(k + 1)` | Explore answers extending that state |
| `undo(choice)` | Reverse every state change made by `choose` |
| `save_result()` | Copy or print the complete answer |

The helper declarations and `extern` variables are placeholders. Define them for your problem before linking a program; `solution.cpp` alone is not a standalone executable. This frame uses integer candidates and a fixed answer length. Adapt candidate generation and the stopping condition for problems with different requirements. Do not modify the `choices` vector during its range-based loop.

## Walkthrough

Build binary sequences of length `2`, with equal adjacent digits forbidden. Set `choices = {0, 1}`; keep selected digits in `path`. A candidate is valid when `path` is empty or its last digit differs from the candidate.

```text
[]
|-- choose 0 -> [0]
|   |-- reject 0
|   `-- choose 1 -> [0,1] -> save -> undo 1
|   undo 0 -> []
`-- choose 1 -> [1]
    |-- choose 0 -> [1,0] -> save -> undo 0
    `-- reject 1
    undo 1 -> []
```

Results: `[0,1]` and `[1,0]`. The working path is empty again after the search. If every candidate is valid, the same frame generates all four sequences: `[0,0]`, `[0,1]`, `[1,0]`, `[1,1]`.

## C++ notes

- `choose` commonly uses `push_back`; `undo` then uses `pop_back`.
- If choosing also marks an item as used, undo must clear that mark as well.
- Store a copy of the current path in `save_result`; the working path changes during backtracking.
- Keep the undo step after recursion, even when recursion found an answer.
- DFS describes the traversal order; backtracking additionally manages tentative choices and restores state.

## Cases to check

| Case | Expected result |
| --- | --- |
| Length `2`, adjacent equal digits forbidden | Exactly `[0,1]` and `[1,0]` |
| Search finishes | Working path is restored to empty |
| `n == 0` | One complete empty answer |
| No candidates and `n > 0` | No answers |

Run the assert-based checks from this directory:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic test.cpp -o backtracking-test
./backtracking-test
```

## Complexity

Let `b` be the number of candidates and `n` the answer length. The unpruned tree visits `1 + b + ... + b^n` states. For `b > 1`, traversal takes O(b^n) time if each helper takes O(1); copying each answer of length `n` can raise total time to O(n * b^n). Pruning can reduce the explored tree.

**Auxiliary space:** O(n) for recursion and the working path in the example, excluding candidates and stored results. Storing all answers can require O(n * b^n) space. Time and space depend on the actual helpers and constraints of the problem.
