# Palindromic Substrings

**Problem:** [LeetCode - Palindromic Substrings](https://leetcode.com/problems/palindromic-substrings/)\
**Solution:** [solution.cpp](solution.cpp)\
**Tests:** [test.cpp](test.cpp)

Given a string `s`, return the number of palindromic substrings. A palindrome reads the same forward and backward; a substring must be contiguous. Occurrences with different start or end indexes count separately, even when their text is identical. The problem guarantees `1 <= s.length <= 1000`, with lowercase English letters.

## Approach: expand around each center

Use the same center expansion as [Longest Palindromic Substring](../longest-palindromic-substring/README.md). Instead of keeping the longest range, count every matching range.

1. Visit every index as a possible center.
2. Use `offset = 0` for odd lengths: start with `left = right = center`.
3. Use `offset = 1` for even lengths: start with `left = center`, `right = center + 1`.
4. While both indexes are in bounds and the characters match, increment `count`.
5. Decrease `left` and increase `right` to expand the palindrome.
6. Return the total after checking every center.

Matching characters extend a palindrome by one character on each side. A mismatch ends that expansion because any larger range with the same center would include the mismatched pair. Every palindromic occurrence has exactly one center and parity, so it is counted exactly once.

This entry belongs to the 1-D DP topic in the study list, but the implementation uses center expansion rather than a DP table. A table-based solution could record whether each range is a palindrome using its inner range; center expansion avoids storing that table.

## How the C++ code is organized

| Part | Responsibility |
| --- | --- |
| `countSubstrings(s)` | Count all palindromic occurrences |
| `center` | Select the character center or left side of a gap |
| `offset` | Choose odd (`0`) or even (`1`) lengths |
| `left`, `right` | Inclusive boundaries of the current range |
| `++count` | Count the palindrome found at this expansion step |
| `--left`, `++right` | Try extending the range |

## Walkthrough

For `s = "aaa"`, indexes are zero-based:

| Center | Type | Palindromic ranges | Added |
| --- | --- | --- | --- |
| `0` | Odd | `[0,0]`: `"a"` | 1 |
| `0` | Even | `[0,1]`: `"aa"` | 1 |
| `1` | Odd | `[1,1]`: `"a"`, `[0,2]`: `"aaa"` | 2 |
| `1` | Even | `[1,2]`: `"aa"` | 1 |
| `2` | Odd | `[2,2]`: `"a"` | 1 |
| `2` | Even | Right boundary is outside the string | 0 |

Return `6`: three occurrences of `"a"`, two of `"aa"`, and one of `"aaa"`. Counting only distinct texts would incorrectly return `3`.

## C++ notes

- Submit the `Solution` class without a `main()` function.
- Bounds checks appear before indexing `s`; C++ evaluates `&&` left to right and short-circuits.
- Signed indexes allow `left` to become `-1` as a stopping condition.
- All state is local, so repeated calls on one object are independent.
- `int` holds the maximum answer: `1000 * 1001 / 2 = 500500`.
- The string is passed by value to match the submission interface; its characters are not modified.

## Cases to check

| Input | Expected result | What it checks |
| --- | --- | --- |
| `"a"` | `1` | One character |
| `"abc"` | `3` | Only single-character palindromes |
| `"aa"` | `3` | Even-length center |
| `"aaa"` | `6` | Repeated occurrences count separately |
| `"aba"` | `4` | Odd-length expansion |
| `"abba"` | `6` | Nested even-length palindromes |
| `"racecar"` | `10` | Several odd-length expansions |
| `"aab"` / `"baa"` | `4` | Palindromes touching either boundary |
| 1000 copies of `a` | `500500` | Maximum answer and worst-case expansion |

Tests reuse one object across calls and compare all 510 binary strings of lengths 1 through 8 against an independent brute-force counter. Run from this directory:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic test.cpp -o palindromic-substrings-test
./palindromic-substrings-test
```

## Complexity

**Time:** O(n^2). Each of O(n) centers can expand O(n) positions.\
**Auxiliary space:** O(1) for the search itself, excluding the by-value input string. Including that copy takes O(n) space.
