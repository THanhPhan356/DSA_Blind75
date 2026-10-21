# 1-D Dynamic Programming Code Frame

**Solution:** [solution.cpp](solution.cpp)\
**Tests and worked example:** [test.cpp](test.cpp)

Dynamic programming (DP) solves subproblems and reuses their results. It is useful when subproblems overlap and their states contain enough information to compute the answer. In 1-D DP, one index identifies each state.

There is no single recurrence that solves every DP problem. This frame separates the reusable control flow from the base cases and transitions you must define for each problem.

## Approach: define the state before writing the code

1. **State:** What exactly does `dp[i]` represent?
2. **Transition:** Which subproblems determine its value? Why does the recurrence cover the valid possibilities?
3. **Base cases:** Which answers are known without using the recurrence?
4. **Order:** When will every dependency be available?
5. **Answer:** Which state or combination of states answers the question?

Counting often uses addition; minimum cost uses `min`; maximum value uses `max`; feasibility uses logical OR. Initial values and treatment of impossible states also depend on the problem. For counting, make sure the cases being added do not count the same answer twice.

## Top-down: recursion with memoization

1. Return the saved answer if the state has already been computed.
2. Otherwise, use its base value or recursively evaluate its dependencies.
3. Save the answer and mark the state as computed.

Allocate the cache for one problem instance, then call:

```cpp
std::vector<long long> memo(n + 1);
std::vector<bool> computed(n + 1, false);
long long answer = solveTopDown(n, memo, computed);
```

`transitionTopDown` must call `solveTopDown` for its subproblems so those calls use the cache. A separate `computed` array allows zero or negative answers without confusing them with an uncomputed state. Reset both arrays when the problem input changes.

## Bottom-up: tabulation

1. Allocate a table for states `0` through `n`.
2. Fill base cases and evaluate the remaining states in dependency order.
3. Return the state containing the answer.

```cpp
long long answer = solveBottomUp(n);
```

This frame processes indexes in increasing order, so every non-base state must depend only on smaller indexes. Change the loop order if your recurrence requires it. Some problems also need a different final answer, such as the maximum over the table rather than `dp[n]`.

## How the C++ code is organized

| Part | Responsibility |
| --- | --- |
| `isBaseCase(i)` | Identify states whose answers are known directly |
| `baseValue(i)` | Return the answer for a base state |
| `transitionTopDown(i, memo, computed)` | Apply the recurrence through recursive cached calls |
| `transitionBottomUp(i, dp)` | Apply the same recurrence using earlier table entries |
| `memo[i]`, `computed[i]` | Store a result and whether it has been evaluated |
| `dp[i]` | Store a tabulated result |

The helper declarations are placeholders. Define them for your problem before linking a program; `solution.cpp` alone is not a standalone executable. `test.cpp` supplies a complete Climbing Stairs example.

## Walkthrough: Climbing Stairs

Count ways to climb `n` steps when each move climbs one or two steps.

- **State:** `dp[i]` is the number of ways to climb exactly `i` steps.
- **Base cases:** `dp[0] = 1` and `dp[1] = 1`. There is one way to climb zero steps: take no moves.
- **Transition:** `dp[i] = dp[i - 1] + dp[i - 2]`. The final move comes from one of these two disjoint cases.
- **Order:** Increasing `i` for bottom-up; decreasing subproblem indexes for top-down.
- **Answer:** `dp[n]`.

The transition helpers in the example are:

```cpp
long long transitionTopDown(int i, std::vector<long long>& memo,
                            std::vector<bool>& computed) {
    return solveTopDown(i - 1, memo, computed)
         + solveTopDown(i - 2, memo, computed);
}

long long transitionBottomUp(int i, const std::vector<long long>& dp) {
    return dp[i - 1] + dp[i - 2];
}
```

| `i` | 0 | 1 | 2 | 3 | 4 | 5 |
| --- | --- | --- | --- | --- | --- | --- |
| `dp[i]` | 1 | 1 | 2 | 3 | 5 | 8 |

Plain recursion recomputes overlapping states; memoization computes each state once. Both DP approaches give the same answer.

## C++ notes

- Use nonnegative indexes and size both top-down arrays to cover every state you access.
- Dependencies must eventually reach a base case. This frame does not resolve cyclic dependencies.
- `long long` is a starting choice, not protection against every overflow. The Climbing Stairs example supports `0 <= n <= 91`; larger values require a different numeric representation or a modulus specified by the problem.
- Deep top-down recursion can exhaust the call stack. Bottom-up avoids recursive calls.
- The example can use O(1) auxiliary space because only two previous values are needed. Keep the full table while learning the state and recurrence; other 1-D recurrences may require many earlier states.

## Cases to check

| Case | What it checks |
| --- | --- |
| `n = 0` and `n = 1` | Both base cases |
| Known results for `n = 0` through `9` | Correct transitions and indexing |
| `n = 45` and `n = 91` | Larger results, including values beyond a signed 32-bit integer |
| Count top-down transition evaluations | Each non-base state is computed once |
| Query the same cached state twice | The second call reuses the result |
| Fresh caches for each input | Results do not leak between problem instances |

Run the assert-based checks from this directory:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic test.cpp -o dp-test
./dp-test
```

## Complexity

**Time:** Number of computed states multiplied by the work per state, including its transitions. 1-D DP is not automatically O(n): checking every earlier state can take O(n^2).

**Climbing Stairs example:** O(n) time and O(n) auxiliary space for either approach. Top-down additionally uses an O(n) recursion stack; bottom-up does not. Memory can be reduced only when the recurrence allows it.
