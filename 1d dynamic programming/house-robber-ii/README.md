# House Robber II

**Problem:** [LeetCode - House Robber II](https://leetcode.com/problems/house-robber-ii/)\
**Solution:** [solution.cpp](solution.cpp)\
**Tests:** [test.cpp](test.cpp)

Given houses arranged in a circle, `nums[i]` is the money in house `i`. Return the maximum amount you can rob without robbing adjacent houses. The first and last houses are adjacent. The problem guarantees `1 <= nums.length <= 100` and `0 <= nums[i] <= 1000`.

## Approach: two linear ranges with bottom-up dynamic programming

The first and last houses cannot both be robbed. Every valid selection therefore excludes at least one of them. Solve two ordinary House Robber problems and take the larger result:

```text
Exclude the last house:  indexes [0, n - 2]
Exclude the first house: indexes [1, n - 1]
answer = max(best of the first range, best of the second range)
```

These cases may overlap: a selection excluding both ends is valid in both. Each range is a line, so neither allows an invalid selection containing both ends of the original circle. Taking the maximum covers all valid selections.

1. If there is only one house, return its money directly.
2. Run `robRange(nums, 0, n - 2)` to exclude the last house.
3. Run `robRange(nums, 1, n - 1)` to exclude the first house.
4. Return the larger total.

Within each range, define `dp[t]` as the best total from its first `t` houses:

```text
dp[0] = 0
dp[1] = nums[left]
dp[t] = max(dp[t - 1], dp[t - 2] + nums[left + t - 1])  for t >= 2
```

Keep only two previous totals. At each house, `prev1` represents skipping it, while `prev2 + nums[i]` represents robbing it and excluding its neighbor. Both variables start at zero, which also handles the first house of each range.

## How the C++ code is organized

| Part | Responsibility |
| --- | --- |
| `rob(nums)` | Handle one house and compare the two linear ranges |
| `robRange(nums, left, right)` | Solve one inclusive range without copying it |
| `prev1` | Best total for the processed prefix of the range |
| `prev2` | Best total before the last processed house |
| `current` | Save the new best total before updating previous values |
| `std::max` in `robRange` | Choose between skipping and robbing the current house |
| `std::max` in `rob` | Choose which endpoint to exclude |

## Walkthrough

For `nums = [2, 3, 2]`:

| Range | Houses | Best total |
| --- | --- | --- |
| `[0, 1]` | `[2, 3]` | `3` |
| `[1, 2]` | `[3, 2]` | `3` |

Return `3`. Taking both houses containing `2` would be invalid because they are neighbors in the circle.

For `nums = [1, 2, 3, 1]`:

| Range | Houses | Best total |
| --- | --- | --- |
| `[0, 2]` | `[1, 2, 3]` | `4` from `1 + 3` |
| `[1, 3]` | `[2, 3, 1]` | `3` |

Return `4`.

## C++ notes

- Submit the `Solution` class without a `main()` function.
- The helper is private by default and receives a const reference; neither range copies or modifies the array.
- `left` and `right` are inclusive, so the helper uses `i <= right`.
- The single-house case is necessary because excluding either endpoint would exclude the only house.
- With two houses, each range contains exactly one house, so the larger amount wins.
- Compute `current` before shifting `prev2` and `prev1`. Each range starts with fresh local totals.
- The maximum total under the stated constraints is `50000`, which fits a signed 32-bit integer.

## Cases to check

| Input | Expected result | What it checks |
| --- | --- | --- |
| `[2,3,2]` | `3` | First and last houses cannot both be robbed |
| `[1,2,3,1]` | `4` | Excluding the last house gives the better total |
| `[1,2,3]` | `3` | Excluding the first house gives the better total |
| `[5]` / `[0]` | `5` / `0` | Single-house base case |
| `[2,1]` / `[1,2]` | `2` | Two adjacent houses |
| `[0,0,0]` | `0` | Zero money |
| `[2,1,1,2]` | `3` | Unlike House Robber I, both ends cannot be selected |
| `[10,1,1,10]` | `11` | Large amounts at both ends |
| 100 houses containing `1000` each | `50000` | Maximum input size and values |

Tests also check a large late value, input preservation, and repeated calls on one object. Run from this directory:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic test.cpp -o house-robber-ii-test
./house-robber-ii-test
```

## Complexity

**Time:** O(n), two linear passes.\
**Auxiliary space:** O(1), with no array copies or recursion.
