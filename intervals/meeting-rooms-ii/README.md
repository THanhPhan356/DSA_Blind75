# Meeting Rooms II

**Problem:** [NeetCode - Meeting Rooms II](https://neetcode.io/problems/meeting-schedule-ii)\
**Solution:** [solution.cpp](solution.cpp)\
**Tests:** [test.cpp](test.cpp)

Given meeting intervals with `start < end`, return the minimum number of rooms needed to hold every meeting. Input may be unsorted. A room can be reused when a meeting ends exactly as another begins. An empty schedule needs zero rooms.

## Approach: two pointers over sorted starts and ends

The minimum number of rooms equals the maximum number of meetings happening simultaneously. Count active meetings by processing start and end events chronologically.

1. Copy starting times into `starts` and ending times into `ends`.
2. Sort the two arrays independently in ascending order.
3. Set `i = j = 0`, `rooms = 0`, and `maxRooms = 0`.
4. If `starts[i] < ends[j]`, the next event is a start: increment `rooms` and `i`, then update the maximum.
5. Otherwise, the next event is an end: decrement `rooms` and increment `j`.
6. Stop when all starts have been processed and return `maxRooms`. Remaining end events can only decrease the count.

After sorting, `starts[i]` and `ends[i]` need not belong to the same meeting. The algorithm only needs event times to count active meetings; it does not assign individual meetings to room numbers.

### Why the event count is correct

Each start adds one active meeting and each end removes one. Processing ends before starts at equal times lets a room be reused immediately. At a peak of `k` active meetings, at least `k` rooms are necessary. Conversely, whenever a meeting starts, either a previously used room is available or another room is needed; the largest active count therefore suffices for the entire schedule.

This differs from Non-overlapping Intervals: meetings cannot be discarded. Two separate pairs of overlapping meetings can reuse two rooms, whereas three simultaneous meetings need three rooms, even though both inputs may require two removals in the other problem.

## How the C++ code is organized

| Part | Responsibility |
| --- | --- |
| `minMeetingRooms(intervals)` | Return the minimum room count |
| `starts`, `ends` | Store sorted event times separately |
| `i`, `j` | Point to the next unprocessed start and end |
| `rooms` | Count meetings currently active |
| `maxRooms` | Remember the largest active count |
| `starts[i] < ends[j]` | Process a start only if it precedes the next end |
| `while (i < n)` | Stop once no starts remain |

## Walkthrough

For `intervals = [[5,10], [0,30], [15,20]]`, the sorted arrays are `starts = [0,5,15]` and `ends = [10,20,30]`.

| Comparison | Event | `rooms` after | `maxRooms` |
| --- | --- | --- | --- |
| `0 < 10` | Start at 0; advance `i` | 1 | 1 |
| `5 < 10` | Start at 5; advance `i` | 2 | 2 |
| `15 < 10` is false | End at 10; advance `j` | 1 | 2 |
| `15 < 20` | Start at 15; advance `i` | 2 | 2 |

All starts have been processed. Return `2`; the room used for `[5,10]` can later hold `[15,20]`.

## C++ notes

- Submit the `Solution` class without a `main()` function. The judge supplies `Interval` with integer fields `start` and `end`; `test.cpp` supplies the type for local checks.
- Use `.start` and `.end` to read an `Interval` object.
- Both arrays contain integers, so the default `std::sort` ordering is sufficient. No comparator or lambda is needed.
- Strict `<` processes an end before a start at the same time. With `<=`, touching meetings would incorrectly need separate rooms.
- Update `maxRooms` after starts; ends cannot create a higher peak.
- The original input order and endpoints remain unchanged because sorting only affects the copied time arrays.
- Under the problem's `start < end` condition, an unprocessed start always has a later, unprocessed corresponding end. Thus `j < n` whenever `i < n`, making `ends[j]` safe to access.
- For empty input, the loop is skipped and the method returns zero. All working state is local for repeated calls.

## Cases to check

| Case | Expected result |
| --- | --- |
| `[[0,30], [5,10], [15,20]]` | 2 rooms |
| Unsorted disjoint meetings | 1 room |
| `[[1,5], [5,8]]` | 1 room; touching is allowed |
| Three simultaneous or identical meetings | 3 rooms |
| Two separate pairs of overlapping meetings | 2 rooms; rooms are reused |
| One long meeting covering several disjoint short ones | 2 rooms |
| Several starts and ends at the same time | Process ends first |
| One meeting / empty input | 1 room / 0 rooms |
| 10000 identical meetings | 10000 rooms |

Tests also verify unchanged input and repeated calls on one solution object. Run from this directory:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic test.cpp -o meeting-rooms-ii-test
./meeting-rooms-ii-test
```

## Complexity

**Time:** O(n log n) for sorting, followed by an O(n) event scan.\
**Auxiliary space:** O(n) for the two event arrays, including the smaller stack cost of sorting.
