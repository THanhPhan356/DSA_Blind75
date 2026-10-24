# Word Break

**Problem:** [LeetCode - Word Break](https://leetcode.com/problems/word-break/)\
**Solution:** [solution.cpp](solution.cpp)\
**Tests:** [test.cpp](test.cpp)

Given a string `s` and a dictionary `wordDict`, return whether the entire string can be split into dictionary words. Words may be reused. Characters must stay in order, with no gaps or overlaps. The input contains lowercase English letters, with `1 <= s.length <= 300`, at most `1000` unique dictionary words, and word lengths from `1` to `20`.

## Approach: bottom-up dynamic programming over prefixes

Define `dp[i]` as whether the first `i` characters of `s` can be segmented into dictionary words. Set `dp[0] = true`: an empty prefix is the starting point before choosing the first word.

For a dictionary word of length `len`, the prefix ending at `i` is valid when:

```text
i >= len
dp[i - len] == true
s[i - len ... i - 1] == word
```

1. Initialize a boolean array of size `n + 1`, with only `dp[0]` true.
2. Process prefix lengths `i` from `1` through `n`.
3. Try each dictionary word as the last word of that prefix.
4. If the earlier prefix is reachable and the ending characters match, set `dp[i] = true` and stop checking words for this prefix.
5. Return `dp[n]`, since every character must be covered.

All words are nonempty, so each transition depends on a shorter prefix that has already been processed. A valid split consists of a valid earlier prefix plus its final word; trying every final word therefore covers every possible split. Dictionary entries are never removed, allowing reuse.

## How the C++ code is organized

| Part | Responsibility |
| --- | --- |
| `wordBreak(s, wordDict)` | Decide whether the whole string can be segmented |
| `dp[i]` | Reachability of the prefix of length `i` |
| `dp[0]` | Allow the first word to start at index zero |
| `i >= len` | Avoid a negative starting position |
| `dp[i - len]` | Require the earlier prefix to have a valid split |
| `s.compare(i - len, len, word)` | Compare the ending segment without creating a substring |
| `break` | Stop after finding one valid split for this prefix |

## Walkthrough

For `s = "leetcode"` and `wordDict = ["leet", "code"]`:

| Prefix length | Prefix | Result | Reason |
| --- | --- | --- | --- |
| `0` | `""` | `true` | Starting state |
| `1`–`3` | `"l"` through `"lee"` | `false` | No word fits |
| `4` | `"leet"` | `true` | `dp[0]` and `"leet"` matches |
| `5`–`7` | `"leetc"` through `"leetcod"` | `false` | No valid final word |
| `8` | `"leetcode"` | `true` | `dp[4]` and `"code"` matches |

Return `true`. Intermediate false entries do not prevent a longer word from reaching a later prefix.

## C++ notes

- Submit the `Solution` class without a `main()` function.
- `std::vector<bool>` stores boolean states; the dictionary is passed by reference and remains unchanged.
- `std::string::compare` returns zero when the segment equals the word.
- Conditions joined by `&&` are checked left to right; the length guard protects the index access.
- Do not greedily choose the first or longest matching word: `"cars"` with `["car", "ca", "rs"]` needs `"ca" + "rs"`.
- Return a boolean, not the number of segmentations or a list of words.
- State is local to each call, so one object can process different inputs safely.

## Cases to check

| Input | Expected result | What it checks |
| --- | --- | --- |
| `"leetcode"`, `["leet","code"]` | `true` | Two-word split |
| `"applepenapple"`, `["apple","pen"]` | `true` | Reuse of a word |
| `"catsandog"`, `["cats","dog","sand","and","cat"]` | `false` | Matching pieces cannot cover the whole string |
| `"cars"`, `["car","ca","rs"]` | `true` | Greedy first match would fail |
| `"a"`, `["a"]` | `true` | One character |
| `"a"`, `["b","aa"]` | `false` | Mismatch and a word longer than the string |
| `"aaaaaaa"`, `["aaaa","aaa"]` | `true` | Different word lengths |
| `"ab"`, `["a"]` | `false` | A reachable prefix is not enough |
| 299 copies of `a` followed by `b`, `["a","aa","aaa","aaaa"]` | `false` | Many reachable prefixes before a failing suffix |

Tests also check maximum string length, unchanged dictionary contents, repeated calls, and 1000 deterministic random cases against exhaustive recursive segmentation. Run from this directory:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic test.cpp -o word-break-test
./word-break-test
```

## Complexity

Let `n` be the string length, `m` the dictionary size, and `L` the maximum word length.

**Time:** O(n * m * L), since each prefix tries at most `m` words and a comparison takes up to O(L).\
**Auxiliary space:** O(n) for the DP states. The by-value string parameter also takes O(n) space; no substring copies are created during transitions.
