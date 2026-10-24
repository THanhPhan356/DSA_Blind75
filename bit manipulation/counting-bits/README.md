# Counting Bits

**Problem:** [LeetCode - Counting Bits](https://leetcode.com/problems/counting-bits/)\
**Solution:** [solution.cpp](solution.cpp)\
**Tests:** [test.cpp](test.cpp)

Given `n`, return an array of length `n + 1` whose entry at index `i` is the number of set bits in `i`, for every integer from `0` through `n`. The input guarantees `0 <= n <= 100000`. Do not use a built-in population-count function.

## Approach: dynamic programming by removing one set bit

The expression `i & (i - 1)` removes exactly the lowest set bit from a positive integer. Its result therefore has one fewer set bit than `i`.

Define `dp[i]` as the number of set bits in `i`:

```text
dp[0] = 0
dp[i] = dp[i & (i - 1)] + 1   for i >= 1
```

1. Create `n + 1` entries initialized to zero.
2. Process integers `i` from `1` through `n`.
3. Remove one set bit to obtain a smaller integer whose count is already stored.
4. Add one to that stored count for the removed bit.
5. Return the entire array, including the entry for zero.

Unlike repeatedly clearing bits to count each integer independently, this method performs one transition per integer and reuses previous results. The array is both the DP table and the required output.

## How the C++ code is organized

| Part | Responsibility |
| --- | --- |
| `countBits(n)` | Return all counts from `0` through `n` |
| `std::vector<int> dp(n + 1, 0)` | Allocate the result and initialize `dp[0]` |
| `i & (i - 1)` | Find a smaller integer with one fewer set bit |
| `dp[i & (i - 1)] + 1` | Reuse its count and restore the removed bit |
| `i <= n` | Include the requested upper endpoint |

## Walkthrough

For `n = 5`:

| `i` | Binary | `i & (i - 1)` | Computation | `dp[i]` |
| --- | --- | --- | --- | --- |
| `0` | `0` | — | Initial state | `0` |
| `1` | `1` | `0` | `dp[0] + 1` | `1` |
| `2` | `10` | `0` | `dp[0] + 1` | `1` |
| `3` | `11` | `2` | `dp[2] + 1` | `2` |
| `4` | `100` | `0` | `dp[0] + 1` | `1` |
| `5` | `101` | `4` | `dp[4] + 1` | `2` |

Return `[0,1,1,2,1,2]`. For example, `5 & 4` is `4`; since `4` has one set bit, `5` has two.

## C++ notes

- Submit the `Solution` class without a `main()` function.
- `&` is bitwise AND, not logical AND (`&&`).
- Parentheses around `i & (i - 1)` keep the index expression clear.
- The loop starts at `1`, so the recurrence never subtracts one from zero.
- For positive `i`, removing a set bit produces a value smaller than `i`; its table entry has already been calculated.
- `n == 0` skips the loop and returns `[0]`.
- The method returns counts for all integers, not only the count for `n`.
- The input is passed by value and all state is local, allowing repeated calls.

## Cases to check

| Input | Expected result | What it checks |
| --- | --- | --- |
| `0` | `[0]` | Lower boundary |
| `1` | `[0,1]` | First nonzero entry |
| `2` | `[0,1,1]` | Power of two |
| `5` | `[0,1,1,2,1,2]` | Reuse earlier counts |
| A power of two `2^k` | Entry at `2^k` equals `1` | Single set bit |
| `2^k - 1` | Entry equals `k` | All lower bits set |
| `100000` | `100001` correct entries | Maximum input |

Tests compare every entry from `0` through `100000` against an independent counter using division and remainder, and check repeated calls. Run from this directory:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic test.cpp -o counting-bits-test
./counting-bits-test
```

## Complexity

**Time:** O(n), one constant-time transition per positive integer.\
**Space:** O(n) for the returned DP array; O(1) auxiliary space excluding that output.
