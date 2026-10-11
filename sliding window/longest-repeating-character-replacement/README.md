# Longest Repeating Character Replacement

**Problem:** [NeetCode – Longest Repeating Character Replacement](https://neetcode.io/problems/longest-repeating-substring-with-replacement/question?list=neetcode150)\
**Solution:** [solution.cpp](solution.cpp)

Given an uppercase English string `s` and an integer `k`, return the length of the longest contiguous substring that can become a single repeated character after at most `k` replacements. Using all `k` replacements is optional.

## Approach: sliding window with character counts

1. Initialize a zero-filled array `count[26]`, `left = 0`, and `maxLen = 0`.
2. Move `right` through the string and increase the count of the new character.
3. Find `maxCount`, the highest character frequency in the current window.
4. While `right - left + 1 - maxCount > k`, decrease the count of `s[left]`, advance `left`, and recompute `maxCount`.
5. Once the window is valid, update `maxLen` with its length.

Keeping the most frequent character minimizes the replacements: every other character must change. Therefore, a window is valid exactly when its length minus `maxCount` is at most `k`. Both pointers move forward; for each `right`, removing characters from the left finds the longest valid window ending there.

## Walkthrough

For `"AAAABB"` with `k = 1`, start with `left = 0` and `maxLen = 0`. Counts below apply only to the current window.

| Action | `left` | Window | Count A | Count B | `maxCount` | Replacements needed | `maxLen` |
| --- | --- | --- | --- | --- | --- | --- | --- |
| Add A at `right = 0` | 0 | `A` | 1 | 0 | 1 | `1 - 1 = 0` | 1 |
| Add A at `right = 1` | 0 | `AA` | 2 | 0 | 2 | `2 - 2 = 0` | 2 |
| Add A at `right = 2` | 0 | `AAA` | 3 | 0 | 3 | `3 - 3 = 0` | 3 |
| Add A at `right = 3` | 0 | `AAAA` | 4 | 0 | 4 | `4 - 4 = 0` | 4 |
| Add B at `right = 4` | 0 | `AAAAB` | 4 | 1 | 4 | `5 - 4 = 1` | 5 |
| Add B at `right = 5` | 0 | `AAAABB` | 4 | 2 | 4 | `6 - 4 = 2`; shrink | 5 |
| Remove A at index 0 | 1 | `AAABB` | 3 | 2 | 3 | `5 - 3 = 2`; shrink | 5 |
| Remove A at index 1 | 2 | `AABB` | 2 | 2 | 2 | `4 - 2 = 2`; shrink | 5 |
| Remove A at index 2 | 3 | `ABB` | 1 | 2 | 2 | `3 - 2 = 1`; valid | 5 |

During the `while` loop, `right` stays at 5. After shrinking, the update is `maxLen = max(5, 3) = 5`: the earlier valid window `"AAAAB"` remains the best answer. Replacing its B with A gives five consecutive A characters.

## C++ notes

- `count[26] = {}` initializes every count to zero.
- `s[right] - 'A'` maps uppercase letters to indices 0 through 25.
- `++count[...]` adds a character to the window; `--count[...]` removes one.
- `std::max_element(count, count + 26)` returns a pointer to a largest count; `*` reads that count.
- Recompute `maxCount` after removing a character because the true highest frequency may change.
- The `while` body runs only when more than `k` replacements are needed and can run several times per `right`.
- The `maxLen` update is outside `while`, so it runs on every iteration of `for`, including when no shrinking is needed.
- `maxLen` is declared before `for`, preserving the best length across iterations.
- The function tracks possible replacements without modifying the input characters.

## Examples

| Input | Expected result | Reason |
| --- | --- | --- |
| `s = "ABAB", k = 2` | `4` | Replace both B characters with A |
| `s = "AABABBA", k = 1` | `4` | Turn `AABA` into `AAAA` |
| `s = "AAAABB", k = 1` | `5` | Turn the first five characters into `AAAAA` |
| `s = "ABCDE", k = 0` | `1` | No replacements are allowed |
| `s = "AAAA", k = 0` | `4` | The entire string already has one distinct character |
| `s = "ABCDE", k = 5` | `5` | Four replacements suffice to unify the string |

## Complexity

**Time:** O(26n), which is O(n) for the fixed uppercase English alphabet. Each pointer advances at most n times, and each frequency scan examines 26 counts.\
**Auxiliary space:** O(1) for the 26 counts and integer variables. Passing the string by value can additionally copy n characters when called with an lvalue, making the total extra space O(n) in that case.
