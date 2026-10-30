# Non-overlapping Intervals

**Problem:** [LeetCode - Non-overlapping Intervals](https://leetcode.com/problems/non-overlapping-intervals/)\
**Solution:** [solution.cpp](solution.cpp)\
**Tests:** [test.cpp](test.cpp)

Given intervals `[start, end]` with `start < end`, return the minimum number of intervals to remove so the remaining intervals do not overlap. Intervals may be unsorted. Sharing an endpoint is allowed: `[1,2]` and `[2,3]` do not overlap for this problem.

## Approach: greedy selection by earliest ending point

Removing as few intervals as possible is equivalent to keeping as many compatible intervals as possible. Prefer the interval ending earliest to leave the most room for later intervals.

1. Sort intervals by ending point in ascending order.
2. Keep the first interval and initialize `lastEnd` to its end.
3. For each remaining interval, compare its start with `lastEnd`.
4. If `start >= lastEnd`, keep it and update `lastEnd` to its end.
5. Otherwise, count one removal and leave `lastEnd` unchanged.

`lastEnd` belongs to the last interval **kept**, not necessarily the previous interval in the input. Overlapping intervals are counted as removed but are not physically erased from the vector.

### Why the greedy rule is correct

An optimal compatible selection can start with the earliest-ending interval: replace its first interval with the earliest-ending one. This replacement ends no later, so every later selected interval still fits. Apply the same argument to intervals starting at or after that end. Choosing the earliest available end repeatedly therefore keeps the maximum number of intervals and minimizes removals. Equal ending points may be processed in either order.

Sorting by start alone does not justify this scan. For `[[1,4], [2,3], [3,5]]`, keeping `[1,4]` first would reject both others. Sorting by end lets us keep `[2,3]` and `[3,5]`, removing only one interval.

## How the C++ code is organized

| Part | Responsibility |
| --- | --- |
| `eraseOverlapIntervals(intervals)` | Return the number of removals |
| `intervals.empty()` | Return zero before accessing the first interval |
| Comparator `a[1] < b[1]` | Put smaller ending points first |
| `lastEnd` | Track the end of the last kept interval |
| `start >= lastEnd` | Accept a compatible interval, including a touching endpoint |
| `++removed` | Reject an overlapping interval without moving the boundary |

## Walkthrough

For `intervals = [[1,4], [2,3], [3,5]]`, sorting by end produces `[[2,3], [1,4], [3,5]]`.

| Interval | Decision | `lastEnd` after | Removed |
| --- | --- | --- | --- |
| `[2,3]` | Keep the first interval | 3 | 0 |
| `[1,4]` | `1 < 3`: remove | 3 | 1 |
| `[3,5]` | `3 >= 3`: keep | 5 | 1 |

Return `1`. The kept intervals are `[2,3]` and `[3,5]`.

## C++ notes

- Submit the `Solution` class without a `main()` function.
- `std::sort(begin, end, comparator)` takes the range first and the ordering rule last.
- `begin()` is the first vector position; `end()` is just past the last. These positions are unrelated to an interval's numeric endpoints.
- The lambda `[](const std::vector<int>& a, const std::vector<int>& b)` is an unnamed comparison function. `const` references avoid copying or changing the compared intervals.
- Returning `a[1] < b[1]` means `a` must appear before `b` when its end is smaller. Use strict `<`, not `<=`.
- Without a comparator, vector sorting compares starts first, then ends. Reversing `begin()` and `end()` does not sort by ending point; it creates an invalid range for nonempty input.
- Sorting changes input order but preserves the original interval endpoints. All working state is local for repeated calls.
- Unlike Merge Intervals, this problem allows touching endpoints and counts removals rather than merging ranges.

## Cases to check

| Case | Expected behavior |
| --- | --- |
| `[[1,2], [2,3], [3,4], [1,3]]` | Remove one interval |
| Three copies of `[1,2]` | Remove two duplicates |
| `[[1,2], [2,3]]` | Remove none; touching is allowed |
| `[[1,4], [2,3], [3,5]]` | Earliest-ending choice avoids an extra removal |
| One long interval surrounding a compatible chain | Remove the long interval |
| Unsorted input, negative endpoints, or equal ends | Apply the same selection rule |
| One interval or empty input | Return zero |
| 100000 identical intervals | Keep one and remove 99999 |

Tests also verify ending-point order, preservation of original intervals, and repeated calls on one solution object. Run from this directory:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic test.cpp -o non-overlapping-intervals-test
./non-overlapping-intervals-test
```

## Complexity

**Time:** O(n log n) for sorting, followed by an O(n) scan.\
**Auxiliary space:** O(log n) for the usual `std::sort` implementation's stack; the scan uses O(1) space.
