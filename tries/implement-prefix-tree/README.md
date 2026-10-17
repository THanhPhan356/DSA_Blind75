# Implement Trie (Prefix Tree)

**Problem:** [NeetCode – Implement Trie (Prefix Tree)](https://neetcode.io/problems/implement-prefix-tree/question?list=blind75)\
**Solution:** [solution.cpp](solution.cpp)

Implement a prefix tree with `insert(word)`, `search(word)`, and `startsWith(prefix)`. Search succeeds only for a complete word previously inserted; a prefix query succeeds when any inserted word begins with that prefix. Inputs are non-empty strings of lowercase English letters, with length at most 1,000.

## Approach: shared prefixes with 26 child pointers

Each node has one child slot for each letter from `a` to `z`, plus an `isEnd` flag. An edge's array index identifies its letter, so a node does not need a separate character field. Words with the same prefix follow the same nodes. The root represents the empty prefix.

### Insert

1. Start at the root.
2. Convert each character to an index using `c - 'a'`.
3. If the corresponding child is missing, allocate a node.
4. Move to that child and continue with the next character.
5. Mark the final node with `isEnd = true`.

### Search

1. Follow the word's characters from the root.
2. Return `false` immediately if a required child is missing.
3. After consuming every character, return the final node's `isEnd` value.

### Starts with

Follow the same path checks as search, then return `true` when every prefix character has been consumed. The final node does not need to mark the end of a word.

## How the C++ code is organized

| Part | Responsibility |
| --- | --- |
| `PrefixTree` | Expose the constructor and three operations required by NeetCode |
| Nested `Node` | Store the children and the end-of-word flag |
| `Node* children[26]{}` | Initialize all 26 child pointers to `nullptr` |
| `bool isEnd = false` | Record whether a complete inserted word ends here |
| `Node* root` | Keep the starting node across calls |
| Local `current` | Walk the tree without moving the root pointer |
| `c - 'a'` | Map `a` to index 0, `c` to index 2, and `z` to index 25 |
| `new Node()` | Allocate a node that remains available to later operations |

`current = current->children[index]` changes the local traversal pointer. `current->children[index] = new Node()` changes the tree by attaching a missing child. Only insertion creates nodes; queries read the existing structure.

## Walkthrough

Insert `"care"` first:

```text
(root) -> c -> a -> r -> e*
```

The `*` represents `isEnd = true`; it is not an actual stored character. `search("car")` returns `false`, because the `r` node is not marked. `startsWith("car")` returns `true`, because the path exists.

Now insert `"car"`. Its entire path already exists, so only the flag on `r` changes:

```text
(root) -> c -> a -> r* -> e*
```

Both words can end on the same path. An end-of-word marker does not prevent further children. Adding `"cat"` creates a separate branch after `a`:

```text
(root) -> c -> a
               |-> r* -> e*
               |-> t*
```

| Operation | Result | Reason |
| --- | --- | --- |
| `search("care")` | `true` | The full path exists and `e` is marked |
| `search("car")` | `true` | Inserting `car` marked `r` |
| `search("ca")` | `false` | The path exists, but `a` is not marked |
| `startsWith("ca")` | `true` | At least one stored word starts with `ca` |
| `search("cart")` | `false` | There is no `t` child after `r` |

## C++ notes

- The class name for NeetCode is `PrefixTree`. LeetCode's equivalent problem uses the name `Trie`.
- Repeated insertion reuses existing nodes and leaves the final marker true.
- Each object creates its own root, so inserting into one object does not change another.
- Array indexing assumes the problem's lowercase `a`–`z` input contract.
- This keeps the submit version's raw-pointer allocation: it has no custom destructor, so allocated nodes remain until process exit. A long-lived application needs node cleanup and an explicit copying policy.

## Cases to check

| Case | What it checks |
| --- | --- |
| Queries before any insertion | Missing children return `false` |
| Insert `care`, then query `car` | A prefix is not automatically a stored word |
| Insert both `car` and `care` | Multiple end markers can share one path |
| Insert `cat` and repeat `car` | Branches coexist and duplicate insertion is harmless |
| One-letter words from `a` through `z` | Every child index works |
| A 1,000-character word | Maximum input length and proper-prefix behavior |
| Separate trie instances | Roots and inserted words stay independent |
| Deterministic random operations | Queries agree with a set of inserted words |

## Complexity

Let `L` be the argument length and `T` the total number of allocated nodes.

**Time:** O(L) per operation. Each character selects one child in constant time.\
**Stored space:** O(T), since each node contains a fixed array of 26 pointers. An insertion creates at most O(L) new nodes.\
**Auxiliary space:** Traversal uses O(1); the by-value `std::string` arguments additionally require O(L) space when copied.

## Using the code

Submit the `<string>` include and the `PrefixTree` class from `solution.cpp`. No `main` function or separate node definition is needed.

Run the local [test.cpp](test.cpp) from this folder:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic test.cpp -o test
./test
```
