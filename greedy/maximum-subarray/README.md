# Maximum Subarray

**Problem:** [LeetCode - Maximum Subarray](https://leetcode.com/problems/maximum-subarray/)\
**Solution:** [solution.cpp](solution.cpp)\
**Tests:** [test.cpp](test.cpp)

Given a nonempty integer array, return the largest sum of a nonempty contiguous subarray. Elements cannot be skipped inside the chosen subarray. The problem bounds are `1 <= nums.length <= 100000` and `-10000 <= nums[i] <= 10000`.

## Approach: running prefix sum with the smallest previous prefix

Let `prefix[i]` be the sum of the first `i` elements, with `prefix[0] = 0`. The sum of a subarray from index `l` through index `r` is:

```text
sum(l, r) = prefix[r + 1] - prefix[l]
```

For a fixed right endpoint, maximize this difference by subtracting the smallest earlier prefix. Once a smaller prefix appears, larger earlier prefixes cannot produce a better sum for any future endpoint, so retaining just the minimum is safe.

1. Initialize `prefix = 0`, `minPrefix = 0`, and `best = nums[0]`.
2. Add each value `x` to the running prefix.
3. Update `best` using `prefix - minPrefix`, the best nonempty subarray ending here.
4. Update `minPrefix` to include the current prefix for future endpoints.
5. Return `best` after visiting all elements.

Update `best` before `minPrefix`. Otherwise, subtracting the current prefix from itself would allow an empty subarray with sum zero, which is wrong for an all-negative array. A full prefix array is unnecessary because only the running sum and the smallest earlier sum are needed.

## How the C++ code is organized

| Part | Responsibility |
| --- | --- |
| `maxSubArray(nums)` | Return the maximum sum without modifying the input |
| `prefix` | Sum of all elements visited so far |
| `minPrefix` | Smallest prefix strictly before the current endpoint when updating `best` |
| `prefix - minPrefix` | Best nonempty subarray sum ending at the current element |
| `best` | Largest subarray sum across all endpoints visited |

## Walkthrough

For `nums = [-2, 1, -3, 4, -1, 2, 1, -5, 4]`, initially `best = -2`. The minimum-prefix column shows the value before each iteration's update.

| Index | `x` | `prefix` | Earlier `minPrefix` | Candidate sum | `best` |
| --- | --- | --- | --- | --- | --- |
| 0 | -2 | -2 | 0 | -2 | -2 |
| 1 | 1 | -1 | -2 | 1 | 1 |
| 2 | -3 | -4 | -2 | -2 | 1 |
| 3 | 4 | 0 | -4 | 4 | 4 |
| 4 | -1 | -1 | -4 | 3 | 4 |
| 5 | 2 | 1 | -4 | 5 | 5 |
| 6 | 1 | 2 | -4 | 6 | 6 |
| 7 | -5 | -3 | -4 | 1 | 6 |
| 8 | 4 | 1 | -4 | 5 | 6 |

Return `6`, from `[4, -1, 2, 1]`.

## C++ notes

- Submit the `Solution` class without a `main()` function.
- `std::vector<int>&` avoids copying the input; this method leaves it unchanged.
- Initialize `best` from the first element, not zero, because the answer must be nonempty.
- All state is local, allowing repeated calls on one object.
- Under the stated bounds, every prefix and subarray sum fits in a signed 32-bit `int`. Larger inputs may require a wider integer type.
- Kadane's algorithm reaches the same O(n) time and O(1) space by keeping the best sum ending at the current position; this implementation keeps prefix sums instead.

## Cases to check

| Input | Expected result | What it checks |
| --- | --- | --- |
| `[-2,1,-3,4,-1,2,1,-5,4]` | `6` | Best subarray lies inside the array |
| `[1]` / `[-5]` | `1` / `-5` | Single-element answers |
| `[-8,-3,-6,-2,-5,-4]` | `-2` | All-negative input cannot return an empty subarray |
| `[0,0,0]` | `0` | Repeated equal prefixes |
| `[5,4,-1,7,8]` | `23` | Best subarray includes a negative value |
| `[1,2,3]` | `6` | Entire array is optimal |
| `[-4,5]` / `[5,-10]` | `5` / `5` | Best subarray starts late or ends early |
| 100000 copies of `10000` / `-10000` | `1000000000` / `-10000` | Maximum length and value bounds |

Tests verify unchanged input and repeated calls, and compare 1000 deterministic random small arrays with exhaustive enumeration of all subarrays. Run from this directory:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic test.cpp -o maximum-subarray-test
./maximum-subarray-test
```

## Complexity

**Time:** O(n), one pass through the input. Every element must be examined in the general case.\
**Auxiliary space:** O(1), storing three integers without a prefix array.
