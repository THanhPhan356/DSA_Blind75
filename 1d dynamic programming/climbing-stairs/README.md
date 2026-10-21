# Climbing Stairs

**Problem:** [LeetCode - Climbing Stairs](https://leetcode.com/problems/climbing-stairs/)\
**Solution:** [solution.cpp](solution.cpp)\
**Tests:** [test.cpp](test.cpp)

Given a staircase with `n` steps, count the distinct ways to reach the top when each move climbs either one or two steps. The order of moves matters: `1 + 2` and `2 + 1` are different ways. Return the count, not the sequences. The problem guarantees `1 <= n <= 45`.

## Approach: top-down dynamic programming with memoization

Define `solve(n, memo)` as the number of ways to climb exactly `n` steps.

The final move reaches step `n` from either step `n - 1` with a one-step move or step `n - 2` with a two-step move. These cases are disjoint and cover every valid way, so:

```text
ways(n) = ways(n - 1) + ways(n - 2)
ways(0) = 1
ways(1) = 1
```

There is one way to climb zero steps: take no moves. Although the public input starts at one, recursion needs the zero-step base case.

1. Create a `memo` vector with `n + 1` entries, all initialized to `-1`.
2. Return `1` immediately when `n` is zero or one.
3. If `memo[n]` is not `-1`, return the saved answer.
4. Otherwise, recursively compute the counts for `n - 1` and `n - 2`.
5. Add those counts, save the result in `memo[n]`, and return it.

Plain recursion repeatedly solves the same subproblems. Memoization computes each non-base state once and reuses its answer on later calls.

## How the C++ code is organized

| Part | Responsibility |
| --- | --- |
| `climbStairs(n)` | Create a fresh cache and return the answer for the input |
| `solve(n, memo)` | Return the number of ways to climb `n` steps |
| `n` | Pass the subproblem size by value; each call has its own copy |
| `std::vector<int>& memo` | Share one cache across recursive calls without copying it |
| `memo[i]` | Store the number of ways to climb `i` steps, not the index `i` itself |
| `-1` | Mark an answer that has not been computed |
| `if (n <= 1) return 1` | Stop recursion at the two base cases |
| `return memo[n]` | Send the saved or newly computed count back to the caller |

## Walkthrough

For `n = 3`, the valid sequences are `1 + 1 + 1`, `1 + 2`, and `2 + 1`. Return `3`.

For `n = 4`, assuming the `n - 1` branch is evaluated first:

| Call | Action | Returned value |
| --- | --- | --- |
| `solve(1)` and `solve(0)` | Base cases | `1` each |
| `solve(2)` | Save `memo[2] = 1 + 1` | `2` |
| `solve(3)` | Save `memo[3] = memo[2] + 1` | `3` |
| `solve(2)` again | Reuse `memo[2]` without recursion | `2` |
| `solve(4)` | Save `memo[4] = 3 + 2` | `5` |

The final cache is `[-1, -1, 2, 3, 5]`. Entries zero and one stay `-1` because the base cases return directly. Evaluating the other branch first changes the call order but not the result.

## C++ notes

- Submit the `Solution` class without a `main()` function.
- The helper is private by default because it appears before `public:` in a class.
- Check the cache before expanding another pair of recursive calls.
- Each recursive dependency has a smaller nonnegative index, so it eventually reaches a base case.
- `-1` is a safe marker because every valid count is positive.
- The maximum result is `1836311903` for `n = 45`, which fits a signed 32-bit integer. Do not assume `int` remains sufficient for larger inputs.
- The cache is local to `climbStairs`, so repeated calls on the same object do not share stale results.
- Bottom-up DP can reduce auxiliary space to O(1) for this recurrence. This implementation keeps the recursive memoized approach.

## Cases to check

| Input | Expected result | What it checks |
| --- | --- | --- |
| `1` | `1` | Smallest valid input |
| `2` | `2` | Both one-step and two-step moves |
| `3` | `3` | Different move orders count separately |
| `4` | `5` | Repeated subproblems |
| `20` | `10946` | A larger count |
| `45` | `1836311903` | Maximum valid input |

Tests also cover all inputs from one through ten and repeated calls on one object. Run from this directory:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic test.cpp -o climbing-stairs-test
./climbing-stairs-test
```

## Complexity

**Time:** O(n). Each non-base state is computed once, with constant work per state.\
**Auxiliary space:** O(n) for the memo vector and an O(n) recursion stack.
