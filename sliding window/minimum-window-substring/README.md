# Minimum Window Substring

**Problem:** [NeetCode – Minimum Window Substring](https://neetcode.io/problems/minimum-window-with-characters/question?list=blind75)\
**Solution:** [solution.cpp](solution.cpp)

Return the shortest contiguous substring of `s` containing every character of `t`, including repeated characters. The characters may appear in any order, and the window may contain extra characters. Matching is case-sensitive. Return an empty string if no valid window exists; the problem guarantees a unique answer.

## Approach: sliding window with frequency maps

1. Count each character of `t` in `need`. Set `required` to the number of distinct required characters.
2. Start with an empty `window` map, `left = 0`, and `have = 0`. Initialize `bestLen` to one more than the length of `s`.
3. Move `right` through `s` and increase the count of `s[right]` in `window`.
4. If the new character belongs to `need` and its count has just reached the required frequency, increase `have`.
5. While `have == required`, save the current start and length if the window is shorter than the best answer. Then remove `s[left]` from the counts and advance `left`. If a required character becomes underrepresented, decrease `have`.
6. Once the window is invalid, continue advancing `right`. After scanning `s`, return the saved substring, or an empty string if no valid window was found.

A window is valid when `window[c] >= need[c]` for every required character `c`. For each `right`, shrinking from the left examines shorter valid windows until removing a character makes the window invalid. Both pointers only move forward. The answer is saved before removing a character, so an invalid window never replaces a valid answer.

## Walkthrough

For `s = "XAAAB"` and `t = "AAB"`, `need = {A:2, B:1}` and `required = 2` throughout the trace. `have` counts distinct characters whose required frequencies are satisfied, not the total number of matched occurrences.

```text
Index: 0 1 2 3 4
s:     X A A A B
```

| Step | Action | `left` | `right` | Current window | `window` counts | `have` | `bestStart` | `bestLen` |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | Initialize | 0 | 0 | Not started | `{}` | 0 | 0 | 6 |
| 1 | Add X; it is not required | 0 | 0 | `X` | `{X:1}` | 0 | 0 | 6 |
| 2 | Add A; one occurrence is not enough | 0 | 1 | `XA` | `{X:1, A:1}` | 0 | 0 | 6 |
| 3 | Add A; its count reaches 2, so increase `have` | 0 | 2 | `XAA` | `{X:1, A:2}` | 1 | 0 | 6 |
| 4 | Add A; an extra occurrence does not increase `have` | 0 | 3 | `XAAA` | `{X:1, A:3}` | 1 | 0 | 6 |
| 5 | Add B; its required count is satisfied | 0 | 4 | `XAAAB` | `{X:1, A:3, B:1}` | 2 | 0 | 6 |
| 6 | Valid window; save its length of 5 | 0 | 4 | `XAAAB` | `{X:1, A:3, B:1}` | 2 | 0 | **5** |
| 7 | Remove X and advance `left`; the window stays valid | 1 | 4 | `AAAB` | `{X:0, A:3, B:1}` | 2 | 0 | 5 |
| 8 | Save the shorter window of length 4 | 1 | 4 | `AAAB` | `{X:0, A:3, B:1}` | 2 | **1** | **4** |
| 9 | Remove A and advance `left`; two A characters remain | 2 | 4 | `AAB` | `{X:0, A:2, B:1}` | 2 | 1 | 4 |
| 10 | Save the shorter window of length 3 | 2 | 4 | `AAB` | `{X:0, A:2, B:1}` | 2 | **2** | **3** |
| 11 | Remove A; its count falls below 2, so decrease `have` | 3 | 4 | `AB` | `{X:0, A:1, B:1}` | **1** | 2 | 3 |
| 12 | Stop shrinking; advance `right` and finish the scan | 3 | 5 | Scan finished | `{X:0, A:1, B:1}` | 1 | 2 | 3 |

`right` stays at 4 during the shrinking loop. The shorter window `"AB"` is invalid because it contains only one A, so it is not saved. The result is `s.substr(2, 3)`, which returns `"AAB"`.

## C++ notes

- `std::unordered_map<char, int> need, window` declares two separate maps. `char` is the key type and `int` is the value type; `need` and `window` are variable names.
- `map[c]` accesses the value stored under character `c`. If the key is absent, it inserts it with a zero value. Thus `++need[c]` counts an occurrence of `c`.
- `for (char c : t)` visits each character in `t`.
- `need.count(c)` returns 1 if the key exists and 0 otherwise. It checks membership, not character frequency, and does not insert a key.
- `&&` evaluates the frequency comparison only if the character is required.
- `required = need.size()` counts distinct required characters. For `t = "AAB"`, it is 2, not 3.
- Increase `have` only when a count reaches its requirement exactly. Extra occurrences must not count the same character type again.
- `char removed = s[left++]` reads the character at the old `left`, then advances `left`. Decreasing `window[removed]` removes that occurrence from the window counts.
- A count dropping below its requirement makes the window invalid and decreases `have`.
- `right - left + 1` includes both ends. `s.substr(bestStart, bestLen)` takes a starting index and a length, not an ending index.
- `bestLen = s.size() + 1` is larger than any possible window. If it remains larger than `s.size()`, no answer was found.
- The function returns the answer substring rather than its length. It also returns an empty string immediately when `t` is empty.

## Examples

| Input | Expected result | Reason |
| --- | --- | --- |
| `s = "OUZODYXAZV", t = "XYZ"` | `"YXAZ"` | The shortest contiguous window covering X, Y, and Z |
| `s = "ADOBECODEBANC", t = "ABC"` | `"BANC"` | Contains A, B, and C in a different order |
| `s = "XAAAB", t = "AAB"` | `"AAB"` | Extra characters can be removed, but two A characters are required |
| `s = "xyz", t = "xyz"` | `"xyz"` | The entire string is needed |
| `s = "x", t = "xy"` | `""` | The required character `y` is missing |
| `s = "a", t = "aa"` | `""` | One occurrence cannot satisfy two required occurrences |
| `s = "a", t = "A"` | `""` | Uppercase and lowercase characters are different |

## Complexity

**Time:** O(n + m) on average, where n is the length of `s` and m is the length of `t`, using average O(1) hash lookups. Each pointer advances at most n times.\
**Auxiliary space:** O(k) for the maps, where k is the number of distinct characters across the inputs. The English-letter alphabet bounds k by 52. Passing the strings by value can additionally copy n + m characters when called with lvalues, and constructing the returned substring requires space for the result.
