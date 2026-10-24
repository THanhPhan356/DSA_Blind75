# Missing Number

**Problem:** [LeetCode - Missing Number](https://leetcode.com/problems/missing-number/)\
**Solution:** [solution.cpp](solution.cpp)\
**Tests:** [test.cpp](test.cpp)

Given an array of `n` distinct integers from the inclusive range `[0, n]`, return the only missing integer. The array is not necessarily sorted. The problem guarantees `1 <= n <= 10000`, so there are `n + 1` possible values and exactly `n` values in the input.

## Approach: XOR cancellation

Use three properties of bitwise XOR:

```text
x ^ x = 0
x ^ 0 = x
XOR can be reordered and regrouped.
```

XOR every possible value from `0` through `n` with every actual array element. Each present value occurs twice and cancels out. The missing value occurs once and remains.

1. Set `result = n` to include the upper endpoint.
2. Loop over indices `i` from `0` to `n - 1`.
3. Apply `result ^= i ^ nums[i]`, adding one expected value and one actual value to the XOR.
4. Return `result` after all matching pairs have canceled.

The expected indices plus the initial `n` cover the complete range `[0, n]`. Cancellation does not require an array element to equal its corresponding index: values can pair up anywhere in the accumulated expression.

## How the C++ code is organized

| Part | Responsibility |
| --- | --- |
| `missingNumber(nums)` | Return the missing integer |
| `n = nums.size()` | Determine both the input length and the largest possible value |
| `result = n` | Include the endpoint not covered by the indices |
| `i` | Contribute expected values `0` through `n - 1` |
| `nums[i]` | Contribute the actual values |
| `result ^= i ^ nums[i]` | Accumulate XOR without sorting or extra storage |

## Walkthrough

For `nums = [3,0,1]`, initialize `result = 3`.

| Index | Array value | Update | Result |
| --- | --- | --- | --- |
| `0` | `3` | `3 ^ 0 ^ 3` | `0` |
| `1` | `0` | `0 ^ 1 ^ 0` | `1` |
| `2` | `1` | `1 ^ 2 ^ 1` | `2` |

Equivalently, the full expression is:

```text
(0 ^ 1 ^ 2 ^ 3) ^ (3 ^ 0 ^ 1) = 2
```

Return `2`.

## C++ notes

- Submit the `Solution` class without a `main()` function.
- `^` is bitwise XOR, not exponentiation and not bitwise AND (`&`).
- `result ^= i ^ nums[i]` means `result = result ^ i ^ nums[i]`.
- XOR sets a result bit to one when the two input bits differ; equal bit patterns therefore cancel.
- Starting at `n` is necessary because the loop only contributes indices through `n - 1`.
- The method also finds a missing zero: if every other value cancels, the result is zero.
- The input is passed by reference and remains unchanged; all state is local for repeated calls.
- Correctness relies on unique values in `[0, n]` with exactly one missing value. This method does not validate malformed inputs.
- No arithmetic sum is accumulated, so there is no sum-overflow issue.

## Cases to check

| Input | Expected result | What it checks |
| --- | --- | --- |
| `[3,0,1]` | `2` | Unsorted input with an interior value missing |
| `[0,1]` | `2` | Missing upper endpoint |
| `[9,6,4,2,3,5,7,0,1]` | `8` | Larger unsorted example |
| `[0]` | `1` | Minimum length, missing upper endpoint |
| `[1]` | `0` | Minimum length, missing zero |
| Every missing position for lengths `1` through `100` | The omitted value | All possible missing positions on shuffled inputs |
| Length `10000`, missing `0`, `5000`, or `10000` | The omitted value | Maximum length and boundary positions |

Tests construct valid arrays by omitting a known value, shuffle them with a fixed random seed, and verify unchanged input and repeated calls. Run from this directory:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic test.cpp -o missing-number-test
./missing-number-test
```

## Complexity

**Time:** O(n), one pass through the array.\
**Auxiliary space:** O(1), using only the length, loop index, and XOR accumulator.
