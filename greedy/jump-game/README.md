# Jump Game

**Problem:** [LeetCode - Jump Game](https://leetcode.com/problems/jump-game/)\
**Solution:** [solution.cpp](solution.cpp)\
**Tests:** [test.cpp](test.cpp)

Given a nonempty array of nonnegative integers, start at index `0`. At index `i`, `nums[i]` is the maximum number of positions you may jump forward. Return whether the last index is reachable. You may jump fewer than `nums[i]` positions; a zero prevents forward movement from that index. The problem bounds are `1 <= nums.length <= 10000` and `0 <= nums[i] <= 100000`.

## Approach: greedy expansion of the reachable range

Keep `farthest`, the largest index reachable using jumps from the positions examined so far. This is a boundary, not the index where a simulated player currently stands. The algorithm does not choose a particular route or always take the longest jump.

1. Initialize `farthest = 0` because the starting index is reachable.
2. Visit indices `i` in increasing order.
3. If `i > farthest`, return `false` before using `nums[i]`: this index cannot be reached.
4. Otherwise, extend the boundary with `farthest = max(farthest, i + nums[i])`.
5. If `farthest >= n - 1`, return `true`: the last index is reachable.

The index `i` is a position; `nums[i]` is the jump limit; `i + nums[i]` is the farthest landing index from that position. Equality `i == farthest` is valid and may allow another extension.

### Why the greedy rule is correct

Every index from zero through the reachable boundary is reachable because jumps may be shorter than their maximum. When a reachable index extends the boundary, it also makes every intervening index reachable. Keeping the largest boundary therefore preserves all reachability information needed for future positions.

If `i > farthest`, all previous indices have already been examined, and none can reach `i` or any later index. Revisiting a different sequence of jumps cannot cross that gap. In contrast, backtracking explores individual jump sequences; this method combines their reachability into one range.

## How the C++ code is organized

| Part | Responsibility |
| --- | --- |
| `canJump(nums)` | Return whether the last index is reachable |
| `farthest` | Largest reachable index discovered so far |
| `i > farthest` | Detect a gap before reading an unreachable index's jump limit |
| `i + nums[i]` | Compute the farthest landing index from a reachable position |
| `std::max` | Preserve the boundary when a position cannot extend it |
| `farthest >= n - 1` | Stop as soon as the destination is reachable |

## Walkthrough

For `nums = [2, 3, 1, 1, 4]`:

| Index `i` | Boundary before | `i + nums[i]` | Boundary after | Result |
| --- | --- | --- | --- | --- |
| 0 | 0 | 2 | 2 | Indices 0 through 2 are reachable |
| 1 | 2 | 4 | 4 | Last index is reachable; return `true` |

One possible route is `0 -> 1 -> 4`, but the algorithm does not need to store it.

For `nums = [3, 2, 1, 0, 4]`, indices 0, 1, 2, and 3 all have farthest landing index 3. At index 4, `4 > farthest`, so return `false`. Every reachable position has already been considered; there is no alternative route to retry.

## C++ notes

- Submit the `Solution` class without a `main()` function.
- The input is passed by reference and is not modified; all state is local for repeated calls.
- A single-element array, including `[0]`, returns `true`: the starting index is already the destination.
- A zero does not always cause failure: an earlier position may jump over it, or it may be the destination.
- The boundary may exceed the last index. Shorter jumps allow landing exactly at the destination.
- `int` is sufficient for indices and their sums under the stated bounds.

## Cases to check

| Input | Expected result | What it checks |
| --- | --- | --- |
| `[2,3,1,1,4]` | `true` | A shorter first jump leads to the destination |
| `[3,2,1,0,4]` | `false` | No reachable index can cross the gap |
| `[0]` / `[0,1]` | `true` / `false` | Already at the destination versus stuck at the start |
| `[1,0]` / `[2,0,0]` | `true` / `true` | Landing on a final zero is allowed |
| `[1,0,1]` | `false` | Reachable zero blocks further progress |
| `[2,0,10000]` / `[0,10000]` | `true` / `false` | A large jump value helps only at a reachable index |
| `[10000,0,0]` | `true` | Boundary may extend beyond the destination |
| 10000 copies of `1` / `0` | `true` / `false` | Maximum input length |

Tests verify unchanged input and repeated calls, and compare 1000 deterministic random small arrays with explicit enumeration of reachable destinations. Run from this directory:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic test.cpp -o jump-game-test
./jump-game-test
```

## Complexity

**Time:** O(n) in the worst case, visiting each index at most once.\
**Auxiliary space:** O(1), keeping only indices and the reachable boundary.
