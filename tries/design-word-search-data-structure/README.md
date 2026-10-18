# Design Add and Search Word Data Structure

**Problem:** [NeetCode – Design Add and Search Word Data Structure](https://neetcode.io/problems/design-word-search-data-structure/question?list=blind75)\
**Solution:** [solution.cpp](solution.cpp)

Build a dictionary with `addWord(word)` and `search(word)`. A search pattern matches a complete stored word of the same length. Each `.` matches exactly one letter. Added words contain lowercase English letters; queries may also contain dots. The problem limits word length to 25 and each query to at most two dots.

## Approach: trie with recursive wildcard search

Reuse the nodes and insertion logic from [Implement Trie](../implement-prefix-tree/README.md). Each node has 26 child pointers and an `isEnd` flag. The new part is searching multiple branches when a pattern contains a dot.

### Add word

1. Start at the root.
2. Map each letter to its child slot with `c - 'a'`.
3. Create a missing child, then move to it.
4. Mark the last node with `isEnd = true`.

### Search

The helper `dfs(node, word, pos)` asks whether a complete stored word below `node` matches the pattern starting at `pos`.

1. When `pos` reaches the pattern length, return `node->isEnd`.
2. For a normal letter, follow its child. A missing child means failure.
3. For `.`, try every existing child with `pos + 1`.
4. Return `true` as soon as one branch matches the entire remaining pattern.
5. Return `false` only after every candidate branch fails.

A dot consumes one edge. It cannot skip a letter, match several letters, or match an empty string.

## How the C++ code is organized

| Part | Responsibility |
| --- | --- |
| `WordDictionary` | Expose the constructor, `addWord`, and `search` |
| Nested `Node` | Store child pointers and the end-of-word marker |
| `Node* children[26]{}` | Initialize all child pointers to `nullptr` |
| `Node* root` | Keep the starting node across operations |
| `dfs(node, word, pos)` | Match the suffix beginning at `pos` below the current node |
| `const std::string& word` | Share the pattern across recursive calls without copying it |
| `pos + 1` | Consume exactly one pattern character and one trie edge |
| `child != nullptr && dfs(...)` | Avoid recursion through a missing child |
| `node->isEnd` | Distinguish a complete word from a prefix |

Every recursive call gets its own node pointer and position. If one branch fails, the caller continues its loop with the next child. There is no shared traversal pointer to restore.

## Walkthrough

Add `"cap"` and `"cut"`:

```text
(root) -> c
          |-> a -> p*
          |-> u -> t*
```

The `*` marks `isEnd = true`; it is not a stored character.

Search for `"c.t"`:

1. Follow `c` from the root.
2. The dot tries `a` first.
3. From `a`, there is no `t` child, so that recursive call returns `false`.
4. Continue with `u`, the next existing child of `c`.
5. From `u`, follow `t`. The pattern is consumed and `t` is marked, so return `true`.

Finding a `t` somewhere in the trie is insufficient: it must follow a valid path with exactly one letter between `c` and `t`.

| Query | Result | Reason |
| --- | --- | --- |
| `"cap"` | `true` | Exact stored word |
| `"c.t"` | `true` | The dot matches `u` in `cut` |
| `".ap"` | `true` | The dot matches `c` in `cap` |
| `"c.."` | `true` | Two dots match the last two letters |
| `"c."` | `false` | A two-letter prefix is not a stored word |
| `"c.z"` | `false` | Neither branch ends with `z` |
| `"c.t."` | `false` | A dot cannot match zero letters |

## C++ notes

- Insertion is the previous trie's `insert` operation renamed to `addWord`; this problem does not require `startsWith`.
- Repeated insertion reuses the existing path.
- Searches only read nodes and markers; a failed query does not change the dictionary.
- Handle `.` before calculating `word[pos] - 'a'`, since a dot is not a valid child-array index.
- This preserves the submit version's raw-pointer allocation and has no custom destructor. A long-lived application needs node cleanup and an explicit copying policy.

## Cases to check

| Case | What it checks |
| --- | --- |
| Search before adding a word | An empty dictionary never matches |
| Exact matches and missing words | Ordinary trie lookup |
| Leading, middle, trailing, and two dots | Each wildcard consumes one letter |
| First candidate fails, later candidate succeeds | Search explores all necessary branches |
| Shared prefixes and words of different lengths | End markers enforce whole-word matching |
| Duplicate additions and separate instances | Insertions are harmless and roots stay independent |
| One-letter words and length-25 words | Boundary lengths and child indexes |
| Deterministic random operations | Results agree with a direct scan of stored words |

## Complexity

Let `L` be the argument length, `D` the number of dots, and `T` the total number of allocated nodes.

**Add time:** O(L).\
**Search time:** O(L · 26^D) as a worst-case upper bound; missing branches and successful matches can stop exploration early. Without dots it is O(L). With the problem's fixed limit D ≤ 2 and alphabet size 26, the bound is also O(L) with a potentially large constant.\
**Stored space:** O(T), with at most O(L) new nodes per addition.\
**Auxiliary space:** O(L) for the recursive call stack during search. The public by-value string arguments can also require O(L) space when copied; recursive calls share the pattern by reference.

## Using the code

Submit the `<string>` include and the `WordDictionary` class from `solution.cpp`. No `main` function is needed.

Run the local [test.cpp](test.cpp) from this folder:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic test.cpp -o test
./test
```
