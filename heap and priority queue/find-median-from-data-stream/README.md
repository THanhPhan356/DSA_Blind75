# Find Median from Data Stream

**Problem:** [LeetCode - Find Median from Data Stream](https://leetcode.com/problems/find-median-from-data-stream/)\
**Solution:** [solution.cpp](solution.cpp)\
**Tests:** [test.cpp](test.cpp)

Design a `MedianFinder` that supports adding integers with `addNum(num)` and returning the median of all received values with `findMedian()`. For an odd count, the median is the middle value in sorted order. For an even count, it is the average of the two middle values. At least one number is present before `findMedian()` is called.

## Approach: two heaps with balanced sizes

Keep the smaller half in a max-heap named `lower` and the larger half in a min-heap named `upper`. Their roots expose the two values nearest the middle without sorting the entire stream.

Maintain two conditions:

1. Every value in `lower` is less than or equal to every value in `upper`.
2. The heap sizes differ by at most one.

### Add a number

1. If `lower` is empty or `num <= lower.top()`, push the number into `lower`. Otherwise, push it into `upper`.
2. If `lower` has two more elements than `upper`, move `lower.top()` to `upper` and pop it from `lower`.
3. Otherwise, if `upper` has two more elements than `lower`, move `upper.top()` to `lower` and pop it from `upper`.

Comparing against the maximum of the smaller half places the number on the correct side of the existing boundary. Moving the maximum from `lower`, or the minimum from `upper`, preserves that boundary. Before insertion the sizes differ by at most one; one insertion can make the difference at most two, so a single transfer is sufficient.

The empty heaps satisfy both conditions initially. Applying these rules after every insertion keeps them true even when numbers arrive in arbitrary order. Two individually valid heaps alone do not guarantee a valid split: `lower = {1,3,7}` and `upper = {5,8,9}` would violate the boundary because `7 > 5`.

### Find the median

- If the sizes are equal, average `lower.top()` and `upper.top()`.
- If `lower` is larger, return `lower.top()`.
- If `upper` is larger, return `upper.top()`.

Reading the median does not remove any values.

## How the C++ code is organized

| Part | Responsibility |
| --- | --- |
| `MedianFinder()` | Construct two empty heaps |
| `std::priority_queue<int> lower` | Store the smaller half with its maximum at the root |
| `std::greater<int>` in `upper` | Make a min-heap holding the larger half |
| `top()` | Read the root without removing it |
| `push(num)` | Insert a value and restore heap order |
| `pop()` | Remove the root and restore heap order; it returns no value |
| Size comparisons in `addNum` | Rebalance the halves with at most one transfer |
| `static_cast<double>` | Convert before addition to avoid integer overflow |

## Walkthrough

For the stream `7, 1, 3, 5`, the half contents below are sorted only for readability; a heap's internal array is not fully sorted.

| Added number | Placement and rebalance | Smaller half | Larger half | Median |
| --- | --- | --- | --- | --- |
| `7` | `lower` is empty: push into `lower` | `[7]` | `[]` | `7.0` |
| `1` | Push into `lower`; move its maximum `7` to `upper` | `[1]` | `[7]` | `4.0` |
| `3` | `3 > 1`: push into `upper` | `[1]` | `[3,7]` | `3.0` |
| `5` | `5 > 1`: push into `upper`; move its minimum `3` to `lower` | `[1,3]` | `[5,7]` | `4.0` |

## C++ notes

- Submit the `MedianFinder` class without a `main()` function.
- Standard priority queues maintain heap order automatically; manual heapify code is unnecessary here.
- Duplicates and negative values follow the same placement rules.
- Either heap may hold the extra element, so `findMedian()` handles both cases.
- Use `/ 2.0` to preserve fractional medians. Converting before the addition also supports pairs such as `INT_MAX, INT_MAX` without overflowing an `int`.
- The problem guarantees a nonempty stream when querying the median; calling `top()` on an empty heap is invalid.

## Cases to check

| Input stream | What it checks |
| --- | --- |
| `[1,2,3]` | Medians `1.0`, `1.5`, `2.0` after successive insertions |
| `[7,1,3,5]` | Transfers in both directions and the walkthrough |
| Increasing and decreasing sequences | Repeated balancing |
| `[4,4,4,4]` | Duplicate values |
| `[-5,-1,-3,0,2]` | Negative values, zero, and mixed signs |
| Repeated `INT_MAX` and `INT_MIN` | Averaging without integer overflow |
| 1000 deterministic random numbers | Every prefix agrees with a sorted-vector reference |

Tests query each median twice to check that reading it leaves the data intact. Each test stream uses a fresh object. Run from this directory:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic test.cpp -o median-finder-test
./median-finder-test
```

## Complexity

Let `n` be the number of received values.

**Time:** O(log n) per `addNum`, with a constant number of heap insertions/removals; O(1) per `findMedian`.\
**Space:** O(n) to retain all values across the two heaps.
