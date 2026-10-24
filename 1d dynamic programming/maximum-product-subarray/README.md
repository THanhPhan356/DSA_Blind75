# Maximum Product Subarray

**Problem:** [LeetCode - Maximum Product Subarray](https://leetcode.com/problems/maximum-product-subarray/)\
**Solution:** [solution.cpp](solution.cpp)\
**Tests:** [test.cpp](test.cpp)

Given an integer array, return the largest product of a nonempty contiguous subarray. You cannot skip elements inside the chosen subarray. The problem guarantees `1 <= nums.length <= 20000`, `-10 <= nums[i] <= 10`, and that the product of any subarray fits a signed 32-bit integer.

## Approach: bottom-up dynamic programming with maximum and minimum products

Track two states ending exactly at index `i`: the largest product `maxEnding` and the smallest product `minEnding`. Keep both because multiplying a negative minimum by a negative number can produce the next maximum.

Every nonempty subarray ending at `i` either starts at `i` or extends a subarray ending at `i - 1`. For `x = nums[i]`:

```text
maxEnding[i] = max(x, maxEnding[i - 1] * x, minEnding[i - 1] * x)
minEnding[i] = min(x, maxEnding[i - 1] * x, minEnding[i - 1] * x)
```

Only the previous states are needed, so use variables instead of DP arrays.

1. Initialize both states and `result` to `nums[0]`, since the answer must be nonempty.
2. For each remaining value, compute `fromMax` and `fromMin` using the previous states.
3. Update both states from the three candidates: `x`, `fromMax`, and `fromMin`.
4. Update `result` with the new `maxEnding`.
5. Return `result`, the best product across all ending positions.

A zero makes both ending products zero. At the next position, the standalone candidate `x` allows a fresh start without a separate reset branch.

## How the C++ code is organized

| Part | Responsibility |
| --- | --- |
| `maxProduct(nums)` | Return the best product of a nonempty contiguous subarray |
| `maxEnding` | Largest product ending at the current index |
| `minEnding` | Smallest product ending at the current index |
| `fromMax`, `fromMin` | Extend the previous states before overwriting them |
| `x` as a candidate | Start a new subarray at the current index |
| `result` | Largest product found at any ending index |

## Walkthrough

For `nums = [-2, 3, -4]`:

| Index | `x` | `fromMax` | `fromMin` | `maxEnding` | `minEnding` | `result` |
| --- | --- | --- | --- | --- | --- | --- |
| `0` | `-2` | — | — | `-2` | `-2` | `-2` |
| `1` | `3` | `-6` | `-6` | `3` | `-6` | `3` |
| `2` | `-4` | `-12` | `24` | `24` | `-12` | `24` |

Return `24` from the entire subarray. Keeping only the previous maximum `3` would miss the product `(-6) * (-4)`.

## C++ notes

- Submit the `Solution` class without a `main()` function.
- `std::vector<int>&` avoids copying the input; the method does not modify it.
- `std::max({a, b, c})` and `std::min({a, b, c})` compare three candidates.
- Compute both extended products before updating either state, so both use the old values.
- Initialize the answer from the first element, not zero: `[-2]` must return `-2`.
- The stated product guarantee makes `int` sufficient for all intermediate products. Inputs outside that guarantee can overflow.
- All state is local, allowing repeated calls on the same object.

## Cases to check

| Input | Expected result | What it checks |
| --- | --- | --- |
| `[2,3,-2,4]` | `6` | Best subarray ends before the last element |
| `[-2,0,-1]` | `0` | Cannot multiply across a zero while skipping it |
| `[-2,3,-4]` | `24` | A negative minimum becomes a positive maximum |
| `[-2]` / `[0]` / `[5]` | `-2` / `0` / `5` | Nonempty single-element answers |
| `[-2,-3,-4]` | `12` | Exclude one negative from an odd negative count |
| `[0,-2,-3,0,-4]` | `6` | Restart after zero |
| `[2,-5,-2,-4,3]` | `24` | Repeated changes of sign |
| Nine values of `10` | `1000000000` | Large valid products |
| 20000 values of `-1` | `1` | Maximum input length |

Tests verify unchanged input and repeated calls, and compare 1000 deterministic random small arrays against exhaustive enumeration of all subarrays. Run from this directory:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic test.cpp -o maximum-product-subarray-test
./maximum-product-subarray-test
```

## Complexity

**Time:** O(n), one pass through the array.\
**Auxiliary space:** O(1), keeping only the current maximum, minimum, and overall result.
