# Search in Rotated Sorted Array

**Problem:** [NeetCode – Search in Rotated Sorted Array](https://neetcode.io/problems/find-target-in-rotated-sorted-array/question?list=blind75)\
**Solution:** [solution.cpp](solution.cpp)

Given a nonempty array that was originally sorted in ascending order and then rotated, return the zero-based index of `target` in the current array. Return `-1` if it is absent. Every value is unique, and the array may still be in its original sorted order. The solution must run in O(log n) time.

## Approach: find the pivot, then search a sorted segment

1. Set `left = 0` and `right = n - 1`. Use the binary search from Find Minimum in Rotated Sorted Array to locate the smallest element.
2. While `left < right`, compute `mid`. If `nums[mid] > nums[right]`, set `left = mid + 1`; otherwise, set `right = mid`. When the boundaries meet, save their index as `pivot`.
3. The array has two increasing segments: indices `[0, pivot - 1]` and `[pivot, n - 1]`. The first segment is empty when `pivot = 0`.
4. If `nums[pivot] <= target && target <= nums[n - 1]`, search the second segment by setting `left = pivot` and `right = n - 1`. Otherwise, search the first segment with `left = 0` and `right = pivot - 1`.
5. While `left <= right`, perform ordinary binary search. Return `mid` if its value equals `target`; move `left` to `mid + 1` if its value is smaller, or `right` to `mid - 1` if its value is larger.
6. Return `-1` if the selected range becomes empty without finding the target.

Finding the pivot separates the array into increasing segments. Every value before the pivot is larger than every value from the pivot onward, so the second segment's endpoints determine whether a present target belongs there. The range check selects a segment but does not guarantee that the target exists. Both searches retain original array indices; no new arrays or sorting are needed.

## Walkthrough

For `nums = [4,5,6,7,0,1,2]` and `target = 0`, the first search finds `pivot = 4`. The boundary columns below show values before each action.

```text
Index: 0 1 2 3 4 5 6
nums:  4 5 6 7 0 1 2
               ^
           pivot = 4
```

| Phase | `left` | `right` | `mid` | Comparison | Action |
| --- | --- | --- | --- | --- | --- |
| Find pivot | 0 | 6 | 3 | `nums[3] = 7 > nums[6] = 2` | Set `left = 4` |
| Find pivot | 4 | 6 | 5 | `nums[5] = 1 < nums[6] = 2` | Set `right = 5` |
| Find pivot | 4 | 5 | 4 | `nums[4] = 0 < nums[5] = 1` | Set `right = 4`; save `pivot = 4` |
| Select segment | 4 | 4 | — | `0 <= target = 0 <= 2` | Set `left = 4`, `right = 6`; search `[0,1,2]` |
| Search target | 4 | 6 | 5 | `nums[5] = 1 > target = 0` | Set `right = 4` |
| Search target | 4 | 4 | 4 | `nums[4] = target = 0` | Return index **4** |

For the same array with `target = 6`, the segment condition is false because 6 is greater than the second segment's largest value, 2. Search indices 0–3 instead, covering `[4,5,6,7]`, and return index 2. A target such as 3 is absent even though a segment is selected; the target-search loop returns `-1` after exhausting that range.

## C++ notes

- `std::vector<int>& nums` passes the array by reference without copying it. The function does not modify its elements.
- `static_cast<int>(nums.size())` stores the array length as a signed integer, allowing `right` to become `-1` when a selected segment is empty.
- `left` and `right` are inclusive bounds. `left + (right - left) / 2` computes the midpoint safely.
- `pivot` is the index of the minimum, not the minimum value itself.
- The pivot-search loop uses `left < right` and keeps `mid` with `right = mid` because it may be the minimum.
- The target-search loop uses `left <= right` so it examines the final remaining candidate. After a failed comparison, it discards `mid` with `mid + 1` or `mid - 1`.
- `&&` means that both segment-boundary comparisons must hold. The inclusive comparisons allow the target to equal either endpoint.
- When `pivot = 0`, the entire array is increasing. An in-range target selects the whole array; an out-of-range target selects the empty range `[0, -1]` and returns `-1`.
- Return `mid`, the original array index, when the target is found. Reusing only the minimum value from the previous problem would lose the segment boundary needed here.

## Examples

| Input | Expected result | Reason |
| --- | --- | --- |
| `nums = [4,5,6,7,0,1,2], target = 0` | `4` | Target is at the rotation point |
| `nums = [4,5,6,7,0,1,2], target = 6` | `2` | Target belongs to the first increasing segment |
| `nums = [4,5,6,7,0,1,2], target = 3` | `-1` | Target is absent |
| `nums = [1,3,8,20], target = 8` | `2` | The array is already sorted and has unequal gaps |
| `nums = [2,1], target = 1` | `1` | A rotated two-element array |
| `nums = [7], target = 7` | `0` | The only element matches |
| `nums = [7], target = 8` | `-1` | The only element does not match |
| `nums = [0,2,-5,-1], target = -5` | `2` | Negative values are supported |

## Complexity

**Time:** O(log n), where n is the array length. Finding the pivot takes O(log n), choosing a segment takes O(1), and searching it takes O(log n); their sum remains O(log n).\
**Auxiliary space:** O(1) for the indices and midpoint variables; the input is passed by reference.
