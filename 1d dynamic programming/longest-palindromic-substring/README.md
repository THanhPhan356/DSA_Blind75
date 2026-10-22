# Longest Palindromic Substring

**Problem:** [LeetCode - Longest Palindromic Substring](https://leetcode.com/problems/longest-palindromic-substring/)\
**Solution:** [solution.cpp](solution.cpp)\
**Tests:** [test.cpp](test.cpp)

Given a string `s`, return its longest palindromic substring. A palindrome reads the same forward and backward. A substring must be contiguous; characters cannot be skipped. If several longest answers exist, any one is accepted. The problem guarantees `1 <= s.length <= 1000`, with English letters and digits.

## Approach: expand around each center

Every palindrome has a center. An odd-length palindrome has a character at its center, such as `aba`. An even-length palindrome has a gap between its two middle characters, such as `abba`.

1. Visit every index as a possible center.
2. Set `offset = 0` to start with `left = right = center` for odd lengths.
3. Set `offset = 1` to start with `left = center`, `right = center + 1` for even lengths.
4. While both indexes are in bounds and their characters match, the inclusive range `[left, right]` is a palindrome.
5. Save its start and length if it is longer than the best answer so far.
6. Move `left` one position left and `right` one position right to expand again.
7. Return `s.substr(bestStart, bestLength)`.

Expansion preserves a palindrome because matching characters are added to both ends. Once a pair differs, no larger palindrome with that center can exist: it would still contain that mismatched pair. Checking both center types covers every possible palindrome.

This entry belongs to the 1-D DP topic in the study list, but this implementation uses center expansion rather than a DP table. A table-based alternative records whether `s[left..right]` is a palindrome using its inner substring; center expansion avoids storing that table.

## How the C++ code is organized

| Part | Responsibility |
| --- | --- |
| `longestPalindrome(s)` | Search all centers and return the best substring |
| `center` | Select a character center or the left index of a gap |
| `offset` | Select odd (`0`) or even (`1`) palindrome lengths |
| `left`, `right` | Inclusive boundaries of the current candidate |
| `right - left + 1` | Compute the candidate length |
| `bestStart`, `bestLength` | Remember the longest valid range |
| `s.substr(bestStart, bestLength)` | Create the returned substring once |

## Walkthrough

For `s = "cbbd"`, focus on the gap between indexes `1` and `2`:

| `left` | `right` | Characters | Action |
| --- | --- | --- | --- |
| `1` | `2` | `b`, `b` | Save `"bb"`, length `2` |
| `0` | `3` | `c`, `d` | Mismatch; stop this expansion |

No other center produces a longer palindrome. Return `"bb"`.

For `s = "babad"`, the character at index `1` expands from `"a"` to `"bab"`. Index `2` produces `"aba"`, which has the same length. Because the code updates only for a strictly longer candidate, it keeps `"bab"`; either answer is valid.

## C++ notes

- Submit the `Solution` class without a `main()` function.
- Bounds checks occur before indexing `s`; C++ short-circuits `&&` from left to right.
- Signed integer indexes allow `left` to become `-1` safely as a stopping condition.
- `substr` takes a start index and a length, not an ending index.
- Character comparisons are case-sensitive.
- All search state is local, so repeated calls on one object are independent.
- The public signature takes the string by value, matching the submission interface. The search does not modify it.

## Cases to check

| Input | Expected result | What it checks |
| --- | --- | --- |
| `"babad"` | `"bab"` or `"aba"` | Tied longest answers |
| `"cbbd"` | `"bb"` | Even-length center |
| `"a"` | `"a"` | One character |
| `"ac"` | `"a"` or `"c"` | No matching adjacent characters |
| `"aa"` | `"aa"` | Two identical characters |
| `"abba"` | `"abba"` | Entire even-length string |
| `"racecar"` | `"racecar"` | Entire odd-length string |
| `"aab"` / `"baa"` | `"aa"` | A palindrome touching either boundary |
| `"forgeeksskeegfor"` | `"geeksskeeg"` | Long internal palindrome |
| 1000 copies of `a` | Entire string | Maximum length and worst-case expansion |

Tests check the returned length, membership as a contiguous substring, and palindrome property, so tied answers are accepted. They also reuse one object across calls. Run from this directory:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic test.cpp -o longest-palindromic-substring-test
./longest-palindromic-substring-test
```

## Complexity

**Time:** O(n^2). Each of O(n) centers can expand O(n) positions. Creating the result takes O(n) at most.\
**Auxiliary space:** O(1) for the search itself, excluding the by-value input string and returned string. Including these strings takes O(n) space.
