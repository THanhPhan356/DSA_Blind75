# Meeting Rooms

**Problem:** [NeetCode - Meeting Rooms](https://neetcode.io/problems/meeting-schedule)\
**Solution:** [solution.cpp](solution.cpp)\
**Tests:** [test.cpp](test.cpp)

Given meeting intervals with `start < end`, return whether one person can attend every meeting without a scheduling conflict. Input may be unsorted. A meeting may start exactly when another ends: `[1,5]` and `[5,8]` are compatible. An empty schedule is also valid.

## Approach: sort by start and check adjacent meetings

1. Sort meetings by starting time using the named function `compareStart`.
2. For every adjacent pair, compare the current meeting's end with the next meeting's start.
3. If `current.end > next.start`, return `false`: the meetings overlap.
4. If no adjacent pair overlaps, return `true`.

Unlike Insert Interval and Merge Intervals, this problem does not insert, merge, or remove anything. It only detects whether a conflict exists.

### Why adjacent comparisons are enough

After sorting, meetings are ordered by start time. If every meeting ends at or before the next meeting starts, it also ends before any later meeting starts. Thus no non-adjacent pair can overlap without an adjacent conflict. Conversely, any overlapping adjacent pair immediately makes full attendance impossible.

## How the C++ code is organized

| Part | Responsibility |
| --- | --- |
| `compareStart(a, b)` | Return whether `a` should appear before `b` based on starting time |
| `static` | Make the comparator callable without a `Solution` object |
| `std::sort(begin, end, compareStart)` | Sort the full vector using that comparison rule |
| `canAttendMeetings(intervals)` | Return whether the schedule has no overlaps |
| `i + 1 < n` | Ensure both meetings in each comparison exist |
| `intervals[i].end > intervals[i + 1].start` | Detect a scheduling conflict |

## Walkthrough

For `intervals = [[8,10], [1,2], [3,9]]`, sorting produces `[[1,2], [3,9], [8,10]]`.

| Current meeting | Next meeting | Check | Decision |
| --- | --- | --- | --- |
| `[1,2]` | `[3,9]` | `2 > 3` is false | Continue |
| `[3,9]` | `[8,10]` | `9 > 8` is true | Return `false` |

For `[[5,8], [1,5]]`, sorting produces `[[1,5], [5,8]]`. The comparison `5 > 5` is false, so return `true`.

## C++ notes

- Submit the `Solution` class without a `main()` function. The judge supplies `Interval` with integer fields `start` and `end`; `test.cpp` supplies the type for local checks, following the repository's judge-provided type pattern.
- Each element is an `Interval` object, so use `.start` and `.end`, not `[0]` and `[1]`.
- A custom object needs an ordering rule for `std::sort`; this code uses a named static function rather than a lambda or an overloaded operator.
- `compareStart` is a chosen name. Its body, `return a.start < b.start`, defines the actual ordering. Equal starts may appear in either order; positive-duration meetings with equal starts still conflict.
- `const Interval&` reads each compared meeting without copying or modifying it.
- `begin()` and `end()` define the half-open vector range, not meeting times. Reversing them creates an invalid range for a nonempty vector.
- Use strict `>` to detect overlap; equality is allowed.
- Sorting changes the input order. Meeting endpoints remain unchanged, and all working state is local for repeated calls.
- With zero or one meeting, the comparison loop is skipped and the answer is `true`.

## Cases to check

| Case | Expected result |
| --- | --- |
| `[[0,30], [5,10], [15,20]]` | `false`: a long meeting overlaps others |
| `[[7,10], [2,4]]` | `true`: unsorted but disjoint |
| `[[5,8], [1,5]]` | `true`: touching endpoints |
| Nested, duplicate, or equal-start meetings | `false` |
| A conflict late in the sorted schedule | `false` |
| Reverse-ordered compatible chain | `true` |
| One meeting or empty input | `true` |
| 10000 disjoint meetings in reverse order | `true` |

Tests also verify sorting by start and repeated calls on the same solution object. Run from this directory:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic test.cpp -o meeting-rooms-test
./meeting-rooms-test
```

## Complexity

**Time:** O(n log n) for sorting, followed by an O(n) scan.\
**Auxiliary space:** O(log n) for the usual `std::sort` implementation's stack; the scan uses O(1) space.
