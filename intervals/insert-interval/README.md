# Insert Interval

**Problem:** [LeetCode - Insert Interval](https://leetcode.com/problems/insert-interval/)\
**Solution:** [solution.cpp](solution.cpp)\
**Tests:** [test.cpp](test.cpp)

Given a list of non-overlapping closed intervals sorted by starting point and one new interval, insert the new interval and merge any overlaps. Return intervals that remain sorted and non-overlapping. The original list may be empty. Intervals sharing an endpoint overlap: `[1,3]` and `[3,5]` merge into `[1,5]`.

## Approach: scan before, overlapping, and after

Keep a local copy `[start, end]` of the new interval and scan the existing intervals once.

1. Copy every interval whose end is strictly less than `start`. These intervals lie entirely before the new interval.
2. While the next interval starts at or before `end`, merge it by setting `start = min(start, interval[0])` and `end = max(end, interval[1])`.
3. Append the merged interval `[start, end]` once.
4. Copy all remaining intervals, which lie entirely after it.

Compare against the updated `end` after every merge. Neither endpoint of the new interval needs to lie inside an existing interval: `[2,8]` also merges `[3,4]` and `[6,7]` because it covers them.

### Why the scan is correct

Sorted, non-overlapping input places intervals into three consecutive groups: before the new interval, overlapping its expanding range, and after that range. The first group cannot overlap it. Each merge preserves the union of the new interval and all intervals consumed in the second group. Once an interval starts beyond the merged end, every later interval does too, so the final group can be copied unchanged. The result therefore preserves all covered points, remains sorted, and has no overlapping intervals.

## How the C++ code is organized

| Part | Responsibility |
| --- | --- |
| `insert(intervals, newInterval)` | Return the updated interval list |
| `i` | Index of the next interval to process |
| `start`, `end` | Boundaries of the expanding merged interval |
| First `while` loop | Copy intervals entirely before it |
| Second `while` loop | Consume and merge overlapping intervals |
| `result.push_back({start, end})` | Insert the merged interval exactly once |
| Last `while` loop | Copy intervals entirely after it |

## Walkthrough

For `intervals = [[1,2], [3,5], [6,7], [8,10], [12,16]]` and `newInterval = [4,8]`:

| Existing interval | Action | Merged interval | Result so far |
| --- | --- | --- | --- |
| `[1,2]` | `2 < 4`: copy before | `[4,8]` | `[[1,2]]` |
| `[3,5]` | `3 <= 8`: merge | `[3,8]` | `[[1,2]]` |
| `[6,7]` | `6 <= 8`: merge | `[3,8]` | `[[1,2]]` |
| `[8,10]` | `8 <= 8`: merge at shared endpoint | `[3,10]` | `[[1,2]]` |
| `[12,16]` | `12 > 10`: append merged interval, then copy remaining | `[3,10]` | `[[1,2], [3,10], [12,16]]` |

## C++ notes

- Submit the `Solution` class without a `main()` function.
- `interval[0]` is the starting point and `interval[1]` is the ending point.
- The first loop uses `<`, while the merging loop uses `<=`, because touching endpoints count as overlap.
- Input is already sorted and non-overlapping; no sorting is needed.
- Both inputs are passed by reference and remain unchanged. All working state is local for repeated calls.
- Check `i < n` before indexing `intervals[i]`; an empty input still returns the new interval.

## Cases to check

| Case | Expected behavior |
| --- | --- |
| `[[1,3], [6,9]]`, insert `[2,5]` | `[[1,5], [6,9]]` |
| Walkthrough above | Merge several intervals |
| Empty list | Return only the new interval |
| Insert before, between, or after existing intervals | Preserve sorted order without unnecessary merging |
| New interval is contained in an existing interval | Keep the existing covered range |
| New interval covers all existing intervals | Return one merged interval |
| Shared endpoints | Merge touching intervals |
| Identical intervals or single-point intervals | Preserve coverage correctly |
| 10000 intervals covered by the new interval | Merge the full list |

Tests also verify unchanged inputs and repeated calls. Run from this directory:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic test.cpp -o insert-interval-test
./insert-interval-test
```

## Complexity

**Time:** O(n), processing each existing interval once.\
**Auxiliary space:** O(1), excluding the returned list.\
**Output space:** O(n + 1), including the new interval; O(n) for nonempty input.
