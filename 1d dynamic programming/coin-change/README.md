# Coin Change

**Problem:** [LeetCode - Coin Change](https://leetcode.com/problems/coin-change/)\
**Solution:** [solution.cpp](solution.cpp)\
**Tests:** [test.cpp](test.cpp)

Given coin denominations `coins` and a target `amount`, return the fewest coins needed to make that amount. Each denomination can be used any number of times. Return `-1` if the amount cannot be formed. The problem guarantees positive coin values, at most 12 denominations, and `0 <= amount <= 10000`.

## Approach: bottom-up dynamic programming

Define `dp[x]` as the minimum number of coins needed to form total `x`.

```text
dp[0] = 0
dp[x] = min(dp[x - coin] + 1) over coins <= x
```

Initialize other entries to `amount + 1`, a sentinel for an unreachable total. Any reachable total up to `amount` needs at most `amount` coins because every coin is worth at least one.

1. Start with `dp[0] = 0`: making zero requires no coins.
2. Process totals from `1` through `amount`.
3. Try each coin no larger than the current total.
4. Use that coin as the last coin: the remaining total is `sum - coin`, costing `dp[sum - coin] + 1` coins.
5. Keep the smallest count across all choices.
6. Return `-1` if `dp[amount]` still exceeds `amount`; otherwise return it.

Every valid combination has a last coin. Trying each possible last coin covers all combinations, and using the minimum for its remainder gives the minimum total count. Since coins are positive, each remainder is smaller than the current total and has already been computed. Reusing a denomination is allowed.

Greedy selection of the largest coin can fail: with `[1,3,4]` and amount `6`, greedy chooses `4+1+1` (three coins), while DP finds `3+3` (two coins).

## How the C++ code is organized

| Part | Responsibility |
| --- | --- |
| `coinChange(coins, amount)` | Return the minimum count using the judge's required signature |
| `vector<int> dp(amount + 1, amount + 1)` | Allocate totals `0..amount`, initially unreachable |
| `dp[0] = 0` | Initialize the empty combination |
| Outer loop over `sum` | Compute smaller totals before larger totals |
| Inner loop over `coins` | Try each possible last coin |
| `coin <= sum` | Avoid negative indexes and ignore oversized coins |
| `min(dp[sum], dp[sum - coin] + 1)` | Keep the best combination found so far |
| Final conditional | Convert an unreachable target to `-1` |

## Walkthrough

For `coins = [1,3,4]` and `amount = 6`, the sentinel is `7`.

| Total | Minimum coins | One optimal combination |
| --- | --- | --- |
| `0` | `0` | Empty |
| `1` | `1` | `1` |
| `2` | `2` | `1+1` |
| `3` | `1` | `3` |
| `4` | `1` | `4` |
| `5` | `2` | `4+1` |
| `6` | `2` | `3+3` |

At total `6`, compare `dp[5]+1 = 3`, `dp[3]+1 = 2`, and `dp[2]+1 = 3`. Return `2`.

## C++ notes

- Submit the `Solution` class without a `main()` function.
- Coins need not be sorted, and the input vector is not modified.
- The sentinel stays small even if a denomination is `INT_MAX`; the code checks `coin <= sum` before subtracting it.
- An unreachable remainder gives `amount + 2` after adding one, so it cannot improve an entry initialized to `amount + 1`.
- All arithmetic is safe within the problem's constraints.
- The DP array is local, so repeated calls on one object are independent.

## Cases to check

| Input | Expected result | What it checks |
| --- | --- | --- |
| `[1,2,5]`, `11` | `3` | Reusing coins |
| `[2]`, `3` | `-1` | Unreachable amount |
| `[1]`, `0` | `0` | Empty combination |
| `[1,3,4]`, `6` | `2` | Greedy fails |
| `[5,2,1]`, `11` | `3` | Unsorted denominations |
| `[7]`, `7` | `1` | Exact match |
| `[2147483647]`, `1` | `-1` | Large denomination |
| `[1]`, `10000` | `10000` | Maximum amount |

Tests also compare all 127 nonempty subsets of denominations `1..7`, for amounts `0..30`, with an independent breadth-first search. They reuse one object and verify the input remains unchanged. Run from this directory:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic test.cpp -o coin-change-test
./coin-change-test
```

## Complexity

**Time:** O(amount * coins.size()), with each denomination tried for each positive total.\
**Auxiliary space:** O(amount) for the DP array.
