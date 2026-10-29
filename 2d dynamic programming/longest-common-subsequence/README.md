# Longest Common Subsequence

**Problem:** [LeetCode - Longest Common Subsequence](https://leetcode.com/problems/longest-common-subsequence/)\
**Solution:** [solution.cpp](solution.cpp)\
**Tests:** [test.cpp](test.cpp)

Given two strings, return the length of their longest common subsequence (LCS). A subsequence can skip characters but must preserve their original order; its characters do not need to be adjacent. Return `0` when the strings have no common characters. Return the length, not the subsequence itself.

## Approach: top-down dynamic programming with memoization

Define `dfs(i, j, text1, text2, memo)` as the LCS length of the suffixes `text1[i...]` and `text2[j...]`.

```text
dfs(i, j) = 0                                      if either suffix is empty
dfs(i, j) = 1 + dfs(i + 1, j + 1)                   if text1[i] == text2[j]
dfs(i, j) = max(dfs(i + 1, j), dfs(i, j + 1))        otherwise
```

When the leading characters match, an optimal subsequence can include that character and continue after both positions. Any common subsequence omitting it can be matched within the remaining suffixes, possibly after removing its first character, so taking the match does not lose a better solution.

When the leading characters differ, they cannot match each other. At least one must be skipped. Explore both possibilities and take the larger length; adding the lengths would combine alternative answers instead of finding the longest one.

1. Create a cache with one row per character of `text1` and one column per character of `text2`, initialized to `-1`.
2. Start at `dfs(0, 0)` to compare the entire strings.
3. If either index reaches its string length, return `0` before accessing a character or cache entry.
4. Return `memo[i][j]` immediately if this state has already been computed.
5. Apply the matching or skipping rule, save the resulting length, and return it.

Different sequences of skips can reach the same pair of positions. Memoization computes each such state once. The remaining answer depends only on `(i, j)` for these fixed strings, so no earlier path needs to be stored.

## How the C++ code is organized

| Part | Responsibility |
| --- | --- |
| `longestCommonSubsequence(text1, text2)` | Create a fresh cache and start at `(0, 0)` |
| `i`, `j` | Identify the next character in each string |
| `const string& text1`, `const string& text2` | Share the strings without copying or modifying them during recursion |
| `vector<vector<int>>& memo` | Share one cache across all recursive calls |
| `memo[i][j]` | Store an LCS length, not a character or a subsequence |
| `-1` | Mark an uncomputed state; `0` is a valid computed answer |
| `1 + dfs(i + 1, j + 1, ...)` | Include a matching character and advance both positions |
| `max(...)` | Choose the better result after skipping one character |

## Walkthrough

For `text1 = "abc"` and `text2 = "ac"`:

| State `(i, j)` | Comparison | Action | Returned length |
| --- | --- | --- | --- |
| `(0, 0)` | `a == a` | Include `a`; compute `1 + dfs(1, 1)` | `2` |
| `(1, 1)` | `b != c` | Compare skipping `b` with skipping `c` | `1` |
| `(2, 1)` | `c == c` | Include `c`; compute `1 + dfs(3, 2)` | `1` |
| `(1, 2)` | Second string exhausted | Return `0` | `0` |
| `(3, 2)` | Strings exhausted | Return `0` | `0` |

The longest common subsequence is `"ac"`, so return `2`. The table describes dependencies, not a guaranteed order of evaluating the two arguments to `max`.

## C++ notes

- Submit the `Solution` class without a `main()` function.
- The helper is private by default because it appears before `public:`.
- Increasing an index skips a character without deleting it from the string.
- Check the base case before accessing `memo[i][j]`; the cache has no extra row or column for exhausted suffixes.
- `static_cast<int>` converts the string length to the index type used here.
- Each call returns a length to its caller, which then adds `1` or compares alternatives.
- Base cases return directly without writing to the cache.
- A local cache prevents stale results when the same object is reused.
- Bottom-up DP can reduce cache storage to one row; this implementation preserves the recursive approach.

## Cases to check

| Input `(text1, text2)` | Expected result | What it checks |
| --- | --- | --- |
| `("abcde", "ace")` | `3` | Characters can be separated by gaps |
| `("abc", "abc")` | `3` | All characters match |
| `("abc", "def")` | `0` | No common characters |
| `("ab", "ba")` | `1` | Original order must be preserved |
| `("abc", "ac")` or reversed inputs | `2` | Both skip directions |
| `("aaaa", "aa")` | `2` | Repeated characters cannot be reused |
| `("a", "a")` or `("a", "b")` | `1` or `0` | Single-character inputs |

Tests also check empty strings, strings of length `1000` with all matching or all differing characters, and repeated calls on the same object. Run from this directory:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic test.cpp -o longest-common-subsequence-test
./longest-common-subsequence-test
```

## Complexity

Let `m` and `n` be the lengths of the two strings.

**Time:** O(m * n) for nonempty inputs. Each state performs constant work and is computed once.\
**Auxiliary space:** O(m * n) for the cache plus O(m + n) for the recursion stack. The public method also takes its input strings by value, while recursive calls share them by reference.
