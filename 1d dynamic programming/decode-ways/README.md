# Decode Ways

**Problem:** [LeetCode - Decode Ways](https://leetcode.com/problems/decode-ways/)\
**Solution:** [solution.cpp](solution.cpp)\
**Tests:** [test.cpp](test.cpp)

Given a string of digits `s`, count the ways to decode it using `1 -> A`, `2 -> B`, ..., `26 -> Z`. Every digit must belong to exactly one valid code. Codes cannot start with zero: `"06"` is invalid, while `"10"` and `"20"` are valid. Return `0` if no complete decoding exists. The problem guarantees `1 <= s.length <= 100` and an answer that fits a signed 32-bit integer.

## Approach: top-down dynamic programming with memoization

Define `dp[i]` as the number of ways to decode the suffix starting at index `i`.

```text
dp[n] = 1
dp[i] = 0                                          if s[i] == '0'
dp[i] = dp[i + 1] + (dp[i + 2] if pair is 10..26)   otherwise
```

The empty suffix contributes one way: all previous digits have been decoded successfully. It does not represent an extra letter.

1. Initialize `memo` with `-1` for unknown results and `memo[n] = 1`.
2. Start with `decode(s, 0, memo)`.
3. Return a cached result immediately when available.
4. If the current digit is zero, cache and return `0`.
5. Decode the current nonzero digit alone, adding the ways from `i + 1`.
6. If the next digit exists and the pair is between `10` and `26`, also add the ways from `i + 2`.
7. Cache and return the sum.

The two branches partition decodings by the length of their first code, so their counts can be added without duplicates. Different branches may reach the same suffix; memoization computes that suffix only once. Unlike plain backtracking, this code counts completions without constructing each decoded string.

## How the C++ code is organized

| Part | Responsibility |
| --- | --- |
| `numDecodings(s)` | Create a fresh cache and start the search |
| `decode(s, i, memo)` | Count complete decodings of the suffix at `i` |
| `memo[i] == -1` | Mark a state that has not been computed |
| `memo[n] = 1` | Count a successfully consumed string |
| `s[i] == '0'` | Reject a zero as the start of a code |
| `decode(s, i + 1, memo)` | Consume one digit |
| `s[i] == '1'` | Accept any second digit for codes `10` through `19` |
| `s[i] == '2' && s[i + 1] <= '6'` | Accept codes `20` through `26` |
| `decode(s, i + 2, memo)` | Consume a valid pair |

## Walkthrough

For `s = "226"`, the recurrence gives:

| Index | Suffix | Calculation | Ways |
| --- | --- | --- | --- |
| `3` | Empty | Base case | `1` |
| `2` | `"6"` | `dp[3]` | `1` |
| `1` | `"26"` | `dp[2] + dp[3]` | `2` |
| `0` | `"226"` | `dp[1] + dp[2]` | `3` |

Return `3`: `2|2|6` (`BBF`), `22|6` (`VF`), and `2|26` (`BZ`). The table shows dependencies; the implementation evaluates them recursively and reuses cached results.

For `"10"`, taking `1` alone leaves an invalid `0`, contributing zero ways. Taking `10` together reaches the empty suffix, contributing one way. For `"06"`, the first digit is zero, so the answer is immediately `0`.

## C++ notes

- Submit the `Solution` class without a `main()` function.
- The memo lookup precedes `s[i]`, so index `n` returns its base value without accessing a character.
- The next-index check precedes `s[i + 1]`; C++ short-circuits `&&` left to right.
- The helper passes the string and cache by reference to avoid copies during recursion.
- A fresh cache on every public call makes repeated calls independent.
- The input is guaranteed to contain digits, so the character checks are sufficient.
- Only suffixes reachable through valid prefixes are evaluated. Their counts cannot exceed the total answer, so `int` is safe under the problem's answer guarantee. Arbitrary unreachable suffixes or prefixes need not have small counts.

## Cases to check

| Input | Expected result | What it checks |
| --- | --- | --- |
| `"12"` | `2` | One digit or a pair |
| `"226"` | `3` | Overlapping subproblems |
| `"0"` / `"06"` | `0` | Leading zero |
| `"10"` / `"20"` | `1` | Zero consumed in a valid pair |
| `"30"` / `"100"` | `0` | Zero with no valid grouping |
| `"101"` | `1` | Valid pair followed by a single digit |
| `"26"` / `"27"` | `2` / `1` | Upper boundary for two-digit codes |
| `"11106"` | `2` | Zero eliminates some branches |
| 45 copies of `1` | `1836311903` | Large result within the integer limit |
| 100 copies of `3` | `1` | Maximum input length |
| `"30"` followed by 98 copies of `1` | `0` | Huge unreachable suffix is skipped |
| 98 copies of `1` followed by `"00"` | `0` | Many choices but no complete decoding |

Tests reuse one object and compare all 10,000 four-digit strings, including leading zeros, with an independent counter that tries codes `1` through `26`. Run from this directory:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic test.cpp -o decode-ways-test
./decode-ways-test
```

## Complexity

**Time:** O(n). Each suffix is evaluated at most once with at most two transitions.\
**Auxiliary space:** O(n) for the memo and recursion stack. The by-value input copy also takes O(n) space.
