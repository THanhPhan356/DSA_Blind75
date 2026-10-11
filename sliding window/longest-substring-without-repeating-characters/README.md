# Longest Substring Without Repeating Characters

**Problem:** [NeetCode – Longest Substring Without Repeating Characters](https://neetcode.io/problems/longest-substring-without-duplicates/question?list=neetcode150)\
**Solution:** [solution.cpp](solution.cpp)

Return the length of the longest contiguous substring whose characters are all different. Characters cannot be skipped to form the substring. An empty string returns zero.

## Approach: sliding window with last seen positions

1. Start with `left = 0`, `maxLen = 0`, and an empty `lastSeen` map.
2. Move `right` through the string, starting at index 0.
3. Look up the previous position of `s[right]`. If it exists and is at least `left`, move `left` to one position after it.
4. Store the current position with `lastSeen[s[right]] = right`.
5. Update `maxLen` with the window length `right - left + 1`.

The window always contains distinct characters after updating `left`. Moving just past the previous occurrence removes the duplicate while keeping the longest valid window ending at `right`. `left` never moves backward.

## Walkthrough

For `"abba"`, start with `left = 0`, `maxLen = 0`, and an empty map.

| `right` | Character | Previous position | `left` after checking | Window | `maxLen` |
| --- | --- | --- | --- | --- | --- |
| 0 | `a` | Not found | 0 | `a` | 1 |
| 1 | `b` | Not found | 0 | `ab` | 2 |
| 2 | `b` | 1, inside the window | 2 | `b` | 2 |
| 3 | `a` | 0, outside the window | 2 | `ba` | 2 |

At the last character, moving `left` back to 1 would produce `"bba"`, which is invalid. The answer remains 2.

## C++ notes

- `lastSeen` maps each character to its most recent index. It is filled as `right` advances.
- `find` looks up a key without inserting it. `it != lastSeen.end()` means the character was found; `it->second` is its stored index.
- `it->second >= left` checks whether that occurrence is still in the current window.
- Look up the old position before overwriting it with the current position.
- `right - left + 1` counts both ends of the window.
- The input uses printable ASCII characters, including spaces and punctuation.

## Examples

| Input | Expected result | Reason |
| --- | --- | --- |
| `"abcabcbb"` | `3` | `abc` is a longest valid substring |
| `"bbbbb"` | `1` | A valid window contains only one `b` |
| `"pwwkew"` | `3` | `wke` is contiguous; `pwke` is not |
| `"abba"` | `2` | An old occurrence outside the window must not move `left` backward |
| `""` | `0` | No characters |

## Complexity

**Time:** O(n) on average, using average O(1) hash lookups.\
**Auxiliary space:** O(m) for the map, where m is the number of distinct characters in the input. Passing the string by value can additionally copy n characters when called with an lvalue, making the total extra space O(n) in that case.

