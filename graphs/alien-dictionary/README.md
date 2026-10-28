# Alien Dictionary

**Problem:** [LeetCode - Alien Dictionary](https://leetcode.com/problems/alien-dictionary/)\
**Solution:** [solution.cpp](solution.cpp)\
**Tests:** [test.cpp](test.cpp)

Given a list of words already sorted lexicographically in an unknown language, infer an ordering of its lowercase English letters. Return every distinct character appearing in the input exactly once in any valid order. Return an empty string if no ordering can explain the dictionary.

## Approach: directed constraints and DFS topological sort

1. Register every character, including characters that never occur in an ordering constraint.
2. Compare each adjacent pair of words from left to right.
3. At the first differing character, add an edge from the earlier word's character to the later word's character. This edge means the first letter must precede the second. Later characters in this pair impose no constraints.
4. If no character differs within the shorter word, reject the input when the earlier word is longer. For example, `"abc"` cannot precede its prefix `"ab"`. Equal words and a shorter prefix appearing first are valid.
5. Start DFS from each present, unvisited character. Use state `0` for unvisited, `1` for visiting, and `2` for finished. State `-1` represents a character absent from the input.
6. Reaching a visiting character reveals a directed cycle: return an empty string. Reaching a finished character is safe and does not repeat its outgoing traversal.
7. After all outgoing neighbors finish, mark the current character finished and append it to the result.
8. Reverse the result to get a topological ordering.

For each edge `a -> b`, DFS finishes `b` before appending `a` if `b` is unvisited, or finds `b` already finished. Reversing the finish order places `a` before `b`. A visiting neighbor instead closes a cycle, making the required ordering impossible.

The dictionary is already sorted; the task is to recover the alphabet, not to sort the words. Constraints from adjacent words are sufficient to preserve the whole list's lexicographic order.

## How the C++ code is organized

| Part | Responsibility |
| --- | --- |
| `graph[c - 'a']` | Store letters that must follow character `c` |
| Initial scan of all words | Include isolated letters in the result |
| `j` and `limit` | Find the first mismatch without exceeding either word |
| Prefix check | Reject a longer word placed before its exact prefix |
| `state[node] == 1` | Detect a cycle on the active recursion path |
| `state[node] == 2` | Reuse a completed traversal without appending the letter again |
| `order.push_back('a' + node)` | Record a letter after its outgoing neighbors finish |
| `reverse(order.begin(), order.end())` | Convert finish order into the required letter order |

## Walkthrough

For `words = ["ab", "ac", "bc"]`:

| Adjacent words | First mismatch | Constraint |
| --- | --- | --- |
| `"ab"`, `"ac"` | `b` and `c` | `b -> c` |
| `"ac"`, `"bc"` | `a` and `b` | `a -> b` |

```text
a -> b -> c
```

DFS starts at `a`, follows `b`, then follows `c`. It finishes and appends letters in the order `c`, `b`, `a`. Reversing `"cba"` produces `"abc"`.

For `["z", "x", "z"]`, the constraints are `z -> x` and `x -> z`. DFS encounters a visiting letter, so return `""`.

For `["abc", "ab"]`, no mismatch exists before the shorter word ends, but the longer word appears first. Return `""` before DFS.

## C++ notes

- `node` is a letter index from `0` to `25`; convert with `c - 'a'` and `'a' + node`.
- `graph` is read through a constant reference; DFS shares `state` and `order` by reference.
- A letter is marked finished only after all outgoing neighbors succeed. A single visited flag cannot distinguish an active-path cycle from a shared finished neighbor.
- Repeated constraints may create duplicate edges; finished-state checks keep them safe. The implementation retains these edges rather than deduplicating them.
- When multiple alphabets are valid, any is accepted. Isolated letters need not appear in ordinary alphabetical order.
- Every call creates fresh state, and the input words remain unchanged.
- Inputs follow the problem's contract: a nonempty list of nonempty words containing only `a` through `z`.
- Submit the includes and `Solution` class; the judge supplies `main()`.

## Cases to check

| Case | What it checks |
| --- | --- |
| The walkthrough and the standard five-word example | Constraints produce a valid alphabet |
| Two-letter cycle or a cycle reached from another letter | Visiting-state detection and failure propagation |
| Longer word before its prefix | Invalid dictionary without needing a cycle |
| Valid prefix order and repeated identical words | No extra constraint or false rejection |
| One word and all 26 letters | Include characters without edges |
| `["ab", "ba"]` | Only the first mismatch constrains a pair |
| `["za", "zb", "ca", "cb"]` | Separate components and repeated constraints |
| Repeated calls and input comparison | No stale state or input mutation |

Tests validate character coverage, uniqueness, and the original dictionary under the returned alphabet instead of requiring one arbitrary order.

Run the local tests from this directory:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic test.cpp -o alien-dictionary-test
./alien-dictionary-test
```

## Complexity

Let `S` be the total number of input characters, `V` the alphabet capacity (`26`), and `E` the number of stored constraints, including duplicates. There is at most one constraint per adjacent word pair.

**Time:** O(S + V + E). Registering letters and comparing neighboring words takes O(S) overall; DFS processes each present letter once and each stored edge once.\
**Auxiliary space:** O(V + E) for the graph, states, result, and recursion stack. DFS depth is at most `26` for this alphabet. Duplicate constraints mean stored graph space can still grow with the number of words.
