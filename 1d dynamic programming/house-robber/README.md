# House Robber

**Problem:** [LeetCode - House Robber](https://leetcode.com/problems/house-robber/)\
**Solution:** [solution.cpp](solution.cpp)\
**Tests:** [test.cpp](test.cpp)

Given a row of houses, `nums[i]` is the money in house `i`. Return the maximum amount you can rob without robbing two adjacent houses. The houses form a line, not a circle. The problem guarantees `1 <= nums.length <= 100` and `0 <= nums[i] <= 400`.

## Approach: bottom-up dynamic programming with two variables

Define `dp[i]` as the maximum money obtainable from the first `i` houses.

For the current house, either skip it and keep the best result for the previous houses, or rob it and add its money to the best result excluding its immediate neighbor:

```text
dp[0] = 0
dp[1] = nums[0]
dp[i] = max(dp[i - 1], dp[i - 2] + nums[i - 1])  for i >= 2
```

Only the previous two results are needed, so no DP array is necessary.

1. Initialize `prev2 = 0` and `prev1 = 0` for the empty prefix.
2. For each house containing `money`, compute `current = max(prev1, prev2 + money)`.
3. Set `prev2 = prev1`, then `prev1 = current`.
4. Return `prev1` after processing every house.

Before processing house index `j >= 1`, `prev1` is the best result from the first `j` houses and `prev2` is the best result from the first `j - 1` houses. The initial zero values handle the first house without a special branch. Choosing to rob the current house always excludes its neighbor.

## How the C++ code is organized

| Part | Responsibility |
| --- | --- |
| `rob(nums)` | Return the maximum total without adjacent selections |
| `prev1` | Best total for the prefix already processed |
| `prev2` | Best total before the last processed house |
| `prev1` in `std::max` | Skip the current house |
| `prev2 + money` | Rob the current house and exclude its neighbor |
| `current` | Save the new result before shifting the previous values |

## Walkthrough

For `nums = [2, 7, 9, 3, 1]`, the previous-value columns show values before each update.

| Money | `prev2` | `prev1` | Skip | Rob | `current` |
| --- | --- | --- | --- | --- | --- |
| `2` | `0` | `0` | `0` | `0 + 2` | `2` |
| `7` | `0` | `2` | `2` | `0 + 7` | `7` |
| `9` | `2` | `7` | `7` | `2 + 9` | `11` |
| `3` | `7` | `11` | `11` | `7 + 3` | `11` |
| `1` | `11` | `11` | `11` | `11 + 1` | `12` |

Return `12`, obtained from houses at indexes `0`, `2`, and `4`: `2 + 9 + 1`.

## C++ notes

- Submit the `Solution` class without a `main()` function.
- `std::vector<int>&` avoids copying the input; the function does not modify it.
- Compute `current` before changing either previous value. Update `prev2` before `prev1` so it receives the old `prev1`.
- A best prefix total does not necessarily include the last house of that prefix.
- Variables are local to each call, so the same object can handle repeated calls.
- The maximum total under the stated constraints is `20000`, which fits a signed 32-bit integer.

## Cases to check

| Input | Expected result | What it checks |
| --- | --- | --- |
| `[1,2,3,1]` | `4` | Skip adjacent houses |
| `[2,7,9,3,1]` | `12` | Combine three nonadjacent houses |
| `[5]` | `5` | One house |
| `[2,1]` / `[1,2]` | `2` | Choose the better of two houses |
| `[0,0,0]` | `0` | Zero money |
| `[2,1,1,2]` | `4` | Both ends can be robbed in a line |
| `[1,3,1,3,100]` | `103` | A large late value changes the best selection |
| 100 houses containing `400` each | `20000` | Maximum input size and values |

Tests also verify that the input is unchanged and use the same object across calls. Run from this directory:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic test.cpp -o house-robber-test
./house-robber-test
```

## Complexity

**Time:** O(n), one iteration per house.\
**Auxiliary space:** O(1), using only three totals regardless of input size.
