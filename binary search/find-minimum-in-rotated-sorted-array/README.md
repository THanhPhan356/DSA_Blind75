# Find Minimum in Rotated Sorted Array

**Problem:** [NeetCode – Find Minimum in Rotated Sorted Array](https://neetcode.io/problems/find-minimum-in-rotated-sorted-array/question?list=blind75)\
**Solution:** [solution.cpp](solution.cpp)

Return the smallest value in a nonempty array that was originally sorted in ascending order and then rotated. Every value is unique. The number of rotations is not provided, and the values do not need to be evenly spaced. The solution must run in O(log n) time.

One rotation moves the last element to the front: `[1,2,3,4,5]` becomes `[5,1,2,3,4]`. Rotating again gives `[4,5,1,2,3]`. Rotating n times restores the original order, so an already sorted array is valid input.

## Approach: binary search with the right boundary

1. Set `L = 0` and `R = nums.size() - 1`. The minimum must lie within this inclusive range.
2. While `L < R`, compute `mid = L + (R - L) / 2`.
3. If `nums[mid] > nums[R]`, the rotation point and the minimum lie strictly to the right of `mid`. Set `L = mid + 1`.
4. Otherwise, the segment from `mid` to `R` is increasing. The minimum lies at `mid` or somewhere to its left within the current range. Set `R = mid` to keep `mid` as a candidate.
5. When `L == R`, only one candidate remains. Return `nums[L]`.

The minimum stays inside `[L, R]` after each update. Comparing the midpoint with the right boundary identifies which half can be discarded. While `L < R`, `mid < R`, so the compared values are different because the input has no duplicates. Each update reduces the range by approximately half, and the same rules also work for an already sorted array.

Scanning for the first value smaller than its predecessor would find the rotation point, but it takes O(n) time. Binary search finds the minimum without examining every element.

## Walkthrough

For `nums = [4,5,6,7,0,1,2]`, start with `L = 0` and `R = 6`. The boundary columns show values before each iteration; the remaining range shows the result of the update.

```text
Index: 0 1 2 3 4 5 6
nums:  4 5 6 7 0 1 2
```

| Iteration | `L` | `R` | `mid` | `nums[mid]` | `nums[R]` | Update | Remaining range |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 1 | 0 | 6 | 3 | 7 | 2 | `7 > 2`: set `L = 4` | Indices 4–6: `[0,1,2]` |
| 2 | 4 | 6 | 5 | 1 | 2 | `1 < 2`: set `R = 5` | Indices 4–5: `[0,1]` |
| 3 | 4 | 5 | 4 | 0 | 1 | `0 < 1`: set `R = 4` | Index 4: `[0]` |
| Finish | 4 | 4 | — | — | 0 | `L == R`: return `nums[L]` | Minimum value: `0` |

In the last iteration, `mid` points to the minimum itself. Setting `R = mid - 1` would discard the answer; keeping `R = mid` preserves it.

## C++ notes

- `std::vector<int>& nums` passes the input array by reference without copying it. The function does not modify its elements.
- `L` and `R` are inclusive indices delimiting the remaining search range.
- `static_cast<int>(nums.size())` converts the array length to the integer type used by the indices. The input is guaranteed to be nonempty.
- `L + (R - L) / 2` computes the midpoint without adding both boundaries together. Integer division rounds down here because the difference is nonnegative.
- Compare `nums[mid]` with `nums[R]`, the value at the current right boundary, rather than comparing the indices themselves.
- `L = mid + 1` discards `mid` because it cannot be the minimum in that branch.
- `R = mid` retains `mid` because it may be the minimum.
- The loop uses `L < R`; once the boundaries meet, the remaining value is the answer.
- Return `nums[L]`, the minimum value, rather than `L`, its index.
- The input contains no duplicates, so equality between the midpoint and right-boundary values cannot occur during the loop. The `else` branch therefore handles the less-than case.

## Examples

| Input | Expected result | Reason |
| --- | --- | --- |
| `[3,4,5,6,1,2]` | `1` | The minimum occurs after the descending transition |
| `[4,5,0,1,2,3]` | `0` | The minimum lies inside the rotated array |
| `[4,5,6,7]` | `4` | The array is already increasing |
| `[1,3,8,20]` | `1` | Values do not need equal gaps |
| `[2,1]` | `1` | A rotated two-element array |
| `[7]` | `7` | A single element is already the minimum |
| `[0,2,-5,-1]` | `-5` | Negative values are supported |

## Complexity

**Time:** O(log n), where n is the array length. Each iteration discards approximately half of the remaining candidates.\
**Auxiliary space:** O(1) for the boundary and midpoint variables; the input is passed by reference.
