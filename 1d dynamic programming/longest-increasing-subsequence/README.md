# Longest Increasing Subsequence

**Problem:** [LeetCode - Longest Increasing Subsequence](https://leetcode.com/problems/longest-increasing-subsequence/)\
**Solution:** [solution.cpp](solution.cpp)\
**Tests:** [test.cpp](test.cpp)

Return the length of the longest strictly increasing subsequence of `nums`. A subsequence keeps the original order but may skip elements; its elements do not need to be contiguous. Equal values do not extend a strictly increasing subsequence. The input guarantees `1 <= nums.length <= 2500` and `-10000 <= nums[i] <= 10000`.

## Approach: bottom-up dynamic programming over ending positions

Define `dp[i]` as the length of the longest increasing subsequence ending exactly at index `i`. Initialize every state to `1`, since each element forms a subsequence by itself.

```text
dp[i] = 1 initially
dp[i] = max(dp[i], dp[j] + 1) for each j < i with nums[j] < nums[i]
answer = max(dp[i]) across all i
```

1. Process each ending index `i` from left to right.
2. Check every earlier index `j` as the previous element.
3. If `nums[j] < nums[i]`, extend the best subsequence ending at `j`.
4. Keep the largest candidate in `dp[i]` and update the overall result.
5. Return the overall result, since the longest subsequence need not end at the last index.

Every increasing subsequence ending at `i` either contains only `nums[i]` or has an earlier final index `j` with a smaller value. Trying all such indices covers every possible predecessor. Each `dp[j]` has already been computed, so the transition gives the best length ending at `i`.

## How the C++ code is organized

| Part | Responsibility |
| --- | --- |
| `lengthOfLIS(nums)` | Return the length, without reconstructing a subsequence |
| `dp[i]` | Best length ending exactly at index `i` |
| Initial value `1` | Count the current element itself |
| `j < i` | Preserve the original index order |
| `nums[j] < nums[i]` | Require a strictly increasing value |
| `dp[j] + 1` | Append the current value to a valid earlier subsequence |
| `result` | Best length across all ending positions |

## Walkthrough

For `nums = [10,9,2,5,3,7,101,18]`:

| Index | Value | `dp[i]` | One subsequence ending here |
| --- | --- | --- | --- |
| `0` | `10` | `1` | `[10]` |
| `1` | `9` | `1` | `[9]` |
| `2` | `2` | `1` | `[2]` |
| `3` | `5` | `2` | `[2,5]` |
| `4` | `3` | `2` | `[2,3]` |
| `5` | `7` | `3` | `[2,5,7]` |
| `6` | `101` | `4` | `[2,5,7,101]` |
| `7` | `18` | `4` | `[2,5,7,18]` |

Return `4`. Several different subsequences can have the same maximum length; the method only stores lengths.

## C++ notes

- Submit the `Solution` class without a `main()` function.
- The input is passed by reference and remains unchanged.
- Use `<`, not `<=`, so duplicates cannot extend a subsequence.
- `dp[i]` is not the best answer for the entire prefix: it must include the element at `i`.
- Do not sort the input, since that would change the required order.
- Return `result`, not `dp[n - 1]`: `[1,2,3,0]` has answer `3`, while its final DP state is `1`.
- The nonempty input guarantee makes `result = 1` valid; all state is local for repeated calls.
- This implementation uses the direct O(n^2) DP recurrence. The optional O(n log n) follow-up uses minimum tails and binary search.

## Cases to check

| Input | Expected result | What it checks |
| --- | --- | --- |
| `[10,9,2,5,3,7,101,18]` | `4` | Skip elements while preserving order |
| `[0,1,0,3,2,3]` | `4` | Multiple competing subsequences |
| `[7,7,7,7,7,7,7]` | `1` | Strict inequality |
| `[5]` | `1` | Single element |
| `[5,4,3,2,1]` | `1` | Decreasing input |
| `[1,2,3,0]` | `3` | Best answer ends before the last element |
| `[-3,-2,-1,0]` | `4` | Negative values |
| `[1,2,2,3]` | `3` | Duplicate inside an increasing sequence |
| `[-10000,10000]` | `2` | Value boundaries |
| 2500 increasing / decreasing / equal values | `2500` / `1` / `1` | Maximum input length |

Tests also verify unchanged input and repeated calls, and compare 1000 deterministic random small arrays against exhaustive enumeration of subsequences. Run from this directory:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic test.cpp -o longest-increasing-subsequence-test
./longest-increasing-subsequence-test
```

## Complexity

**Time:** O(n^2), checking all earlier indices for every ending position.\
**Auxiliary space:** O(n), storing one length per index.
