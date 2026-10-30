# Merge Intervals

**Problem:** [LeetCode - Merge Intervals](https://leetcode.com/problems/merge-intervals/)\
**Solution:** [solution.cpp](solution.cpp)\
**Tests:** [test.cpp](test.cpp)

Given a list of closed intervals `[start, end]`, merge every group of overlapping intervals. Return non-overlapping intervals covering exactly the same points. Input may be unsorted. Intervals sharing an endpoint overlap: `[1,4]` and `[4,5]` merge into `[1,5]`.

## Approach: sort and merge into the last result

1. Sort intervals by starting point. With the default C++ ordering, equal starts are ordered by ending point.
2. Visit each interval in sorted order.
3. If the result is empty, or the current start is greater than the last result's end, append the interval separately.
4. Otherwise, merge it into the last result by keeping the larger ending point.

Compare with the last **merged** interval, not just the previous input interval. For `[[1,10], [2,3], [4,5]]`, the merged end remains `10`, so all three intervals belong to `[1,10]`.

### Why the scan is correct

After sorting, intervals arrive in nondecreasing starting order. If the current start lies beyond the last merged end, there is a gap that no later interval can fill, so a new result interval is needed. Otherwise, the current interval overlaps the last merged interval; extending its end preserves their union. Earlier result intervals are already separated from the last one and cannot overlap the current interval. Each step therefore preserves sorted, non-overlapping coverage of the processed input.

Unlike Insert Interval, the input is not already guaranteed to be sorted and non-overlapping, and there is no separate new interval to insert.

## How the C++ code is organized

| Part | Responsibility |
| --- | --- |
| `merge(intervals)` | Return the merged interval list |
| `std::sort(intervals.begin(), intervals.end())` | Sort the entire input vector in place |
| `const auto& interval` | Read each interval without copying or modifying its endpoints |
| `result.empty()` | Handle the first interval without accessing an empty result |
| `result.back()` | Access the last merged interval by reference |
| `result.push_back(interval)` | Add a separate interval |
| `result.back()[1] = std::max(...)` | Extend the last merged end without shrinking it |

## Walkthrough

For `intervals = [[8,10], [2,6], [1,4], [1,3]]`, sorting produces `[[1,3], [1,4], [2,6], [8,10]]`.

| Current interval | Decision | Result so far |
| --- | --- | --- |
| `[1,3]` | Empty result: append | `[[1,3]]` |
| `[1,4]` | `1 <= 3`: extend end to `4` | `[[1,4]]` |
| `[2,6]` | `2 <= 4`: extend end to `6` | `[[1,6]]` |
| `[8,10]` | `8 > 6`: append separately | `[[1,6], [8,10]]` |

## C++ notes

- Submit the `Solution` class without a `main()` function.
- `begin()` points to the first element; `end()` points just past the last element. Sorting covers this half-open range.
- Vector comparisons are lexicographic: compare `start` first, then `end` if starts are equal.
- `result.back()[0]` is the last merged start; `result.back()[1]` is its end. Assigning to the latter changes the stored interval directly.
- `||` short-circuits: when `result.empty()` is true, C++ does not evaluate `result.back()`, avoiding access to an empty vector.
- Use `>` to detect a gap; equality counts as overlap.
- Sorting changes the input order, but the original interval endpoints are not changed. The returned list holds the merged endpoints.
- All working state is local, so the same `Solution` object can handle repeated calls. Empty input returns an empty result as well.

## Cases to check

| Case | Expected behavior |
| --- | --- |
| `[[1,3], [2,6], [8,10], [15,18]]` | `[[1,6], [8,10], [15,18]]` |
| `[[1,4], [4,5]]` | Merge touching endpoints into `[1,5]` |
| Unsorted intervals and equal starting points | Sort before merging |
| `[[1,10], [2,3], [4,5]]` | Preserve the outer end instead of shrinking it |
| A chain of overlaps | Merge the entire chain |
| Duplicate intervals | Return their covered range once |
| Disjoint intervals | Keep separate intervals |
| One interval, single-point intervals, or empty input | Handle boundaries safely |
| 10000 intervals in reverse order | Sort and merge a long chain |

Tests also check that input is sorted without changing its original intervals and reuse the same solution object. Run from this directory:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic test.cpp -o merge-intervals-test
./merge-intervals-test
```

## Complexity

**Time:** O(n log n) for sorting, followed by an O(n) scan.\
**Auxiliary space:** O(log n) for the usual `std::sort` implementation's stack.\
**Output space:** O(n) when no intervals overlap.
