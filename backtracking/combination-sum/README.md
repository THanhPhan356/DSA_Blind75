# Combination Sum

**Problem:** [LeetCode - Combination Sum](https://leetcode.com/problems/combination-sum/)\
**Solution:** [solution.cpp](solution.cpp)\
**Tests:** [test.cpp](test.cpp)

Given distinct positive integers `candidates` and a positive integer `target`, return all unique combinations whose sum equals `target`. Each candidate may be used any number of times. The order of numbers within a combination does not create a different answer.

## Approach: backtracking with a starting index

1. Start with an empty `path`, `start = 0`, and `remaining = target`.
2. If `remaining == 0`, copy `path` into `res` and return from this branch.
3. Try each candidate at index `i` from `start` to the end of the array.
4. If `arr[i] > remaining`, use `continue` to skip it and try the next candidate.
5. Append `arr[i]` to `path`, then recurse with `start = i` and `remaining - arr[i]`.
6. Remove the last number from `path` after recursion returns.

Passing `i` allows the same number to be selected again. Passing `i + 1` would prevent reuse. Never moving to an earlier index ensures every combination is generated in only one index order: after selecting `3` from `[2,3,6,7]`, later choices cannot include `2`.

The array does not need sorting. Selected indices are nondecreasing, even if the values are not sorted. Because candidates are distinct, this avoids duplicate combinations without a set. Use `continue`, not `break`, when a candidate is too large: a later candidate may be smaller.

## How the C++ code is organized

| Part | Responsibility |
| --- | --- |
| `arr` | Read the available candidates by const reference |
| `start` | First index allowed in the current recursive call |
| `remaining` | Amount still needed to reach the target |
| `path` | Share the current partial combination across calls |
| `res` | Collect copies of complete combinations |
| `path.push_back(arr[i])` | Choose a candidate |
| `backtrack(arr, i, remaining - arr[i], path, res)` | Explore using this candidate, allowing reuse |
| `path.pop_back()` | Undo the choice before trying another candidate |
| `combinationSum` | Create fresh state and return the completed result |

`start` and `remaining` are passed by value, so each call has its own values. `path` and `res` are passed by reference. Undoing a choice changes the working path without changing the copies already stored in `res`.

## Walkthrough

For `candidates = [2,3,6,7]` and `target = 7`:

| Path | Remaining | Action |
| --- | --- | --- |
| `[]` | `7` | Choose `2` |
| `[2]` | `5` | Choose `2` again |
| `[2,2]` | `3` | Choose `2` again |
| `[2,2,2]` | `1` | All candidates are too large; return |
| `[2,2]` | `3` | Undo the last `2`, then choose `3` |
| `[2,2,3]` | `0` | Save a copy, then return and undo `3` |
| Other branches beginning with `2`, `3`, or `6` | Varies | Find no additional answers |
| `[7]` | `0` | Save a copy |

Return `[[2,2,3],[7]]`. Returning from a recursive call goes back to its immediate caller; it does not search for the path closest to the target. Oversized choices are skipped before being appended.

## C++ notes

- No `main()` is required when submitting the `Solution` class to LeetCode.
- Candidates are positive, so every recursive choice strictly decreases `remaining`; recursion eventually stops.
- Zero or negative candidates are outside the problem's contract and could prevent termination.
- The input array is not modified, and repeated calls on the same object start with fresh results.
- The `return` after saving an answer ends the current call; its caller still performs `pop_back()`.

## Cases to check

| Input | Expected result |
| --- | --- |
| `[2,3,6,7]`, target `7` | `[[2,2,3],[7]]` |
| `[2,3,5]`, target `8` | `[[2,2,2,2],[2,3,3],[3,5]]` |
| `[2]`, target `1` | `[]` |
| `[2]`, target `6` | `[[2,2,2]]` |
| `[7,3,2,6]`, target `7` | Combinations `[7]` and `[3,2,2]`; ordering is irrelevant |
| `[1]`, target `3` | `[[1,1,1]]` |

The tests also check input preservation and repeated calls on one object. Run from this directory:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic test.cpp -o combination-sum-test
./combination-sum-test
```

## Complexity

Let `N` be the number of candidates, `T` the target, `m` the smallest candidate, and `D = floor(T / m)` the maximum path length. Let `V` be the number of recursive calls and `S` the total number of integers copied into the output.

**Time:** O(N * V + S), since each call scans at most `N` candidates. A loose worst-case bound is O(N * (N + 1)^D + S); the starting-index rule and sum checks reduce the explored tree.\
**Auxiliary space:** O(D) for recursion and the working path, excluding O(S) output storage.
