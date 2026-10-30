# Blind 75 - C++ Solutions and Study Notes

A completed first pass through [Blind 75](https://neetcode.io/practice/practice/blind75), with C++ implementations, explanations, worked examples, and complexity analysis organized by topic.

**75/75 Blind 75 problems** | **17 topic folders** | **45 local test files** | **2 algorithm frames**

[Problem index](#problem-index) · [Algorithm frames](#algorithm-frames) · [Run locally](#run-locally) · [Repository conventions](#repository-conventions)

## Coverage

The collection contains all 75 Blind 75 entries, one additional practice problem, and two reusable code frames. The 45 test files cover 43 problem entries and both frames; other entries have no checked-in test harness. Individual problem notes retain their learning and review context.

| Topic | Blind 75 entries | Main patterns |
| --- | ---: | --- |
| [Arrays and Hashing](#arrays-and-hashing) | 8 | Hash maps, counting, prefix and suffix products |
| [Two Pointers](#two-pointers) | 3 | Opposing pointers, sorted scans |
| [Sliding Window](#sliding-window) | 4 | Fixed and variable windows, frequency tracking |
| [Stack](#stack) | 1 | Matching delimiters |
| [Binary Search](#binary-search) | 2 | Search boundaries, rotated sorted arrays |
| [Linked List](#linked-list) | 6 | Pointer rewiring, fast and slow pointers, merging |
| [Trees](#trees) | 11 | DFS, BFS, BST properties, serialization |
| [Tries](#tries) | 3 | Prefix trees, wildcard search, board search |
| [Heap and Priority Queue](#heap-and-priority-queue) | 1 | Two heaps, streaming median |
| [Backtracking](#backtracking) | 2 | Choose, explore, undo; prune invalid paths |
| [Graphs](#graphs) | 7 | Traversal, connected components, topological sorting |
| [1-D Dynamic Programming](#1-d-dynamic-programming) | 10 | Memoization, tabulation, sequence states |
| [2-D Dynamic Programming](#2-d-dynamic-programming) | 2 | Grid states, pairs of sequence positions |
| [Greedy](#greedy) | 2 | Local decisions, reachability, running optima |
| [Intervals](#intervals) | 5 | Sorted scans, merging, scheduling, event sweeps |
| [Math and Geometry](#math-and-geometry) | 3 | Matrix traversal, rotation, in-place markers |
| [Bit Manipulation](#bit-manipulation) | 5 | XOR, masks, shifts, bit counting |

Alien Dictionary is stored under Graphs; NeetCode lists it under Advanced Graphs. Problems are grouped by the study topic, even when the implementation uses another technique: for example, the palindrome entries use center expansion.

## Problem index

Each link opens the problem README, which links to its source files and explains the implementation. Dedicated local tests are linked from the entry where provided.

### Arrays and Hashing

- [Contains Duplicate](arrays-hashing/contains-duplicate/README.md)
- [Encode and Decode Strings](arrays-hashing/encode-decode-strings/README.md)
- [Group Anagrams](arrays-hashing/group-anagrams/README.md)
- [Longest Consecutive Sequence](arrays-hashing/longest-consecutive-sequence/README.md)
- [Product of Array Except Self](arrays-hashing/product-except-self/README.md)
- [Top K Frequent Elements](arrays-hashing/top-k-frequent-elements/README.md)
- [Two Sum](arrays-hashing/two%20sum/README.md)
- [Valid Anagram](arrays-hashing/Valid%20Anagram/README.md)

### Two Pointers

- [3Sum](two%20pointer/3sum/README.md)
- [Container With Most Water](two%20pointer/container-with-most-water/README.md)
- [Valid Palindrome](two%20pointer/valid-palindrome/README.md)

### Sliding Window

- [Best Time to Buy and Sell Stock](sliding%20window/best-time-to-buy-and-sell-stock/README.md)
- [Longest Repeating Character Replacement](sliding%20window/longest-repeating-character-replacement/README.md)
- [Longest Substring Without Repeating Characters](sliding%20window/longest-substring-without-repeating-characters/README.md)
- [Minimum Window Substring](sliding%20window/minimum-window-substring/README.md)

### Stack

- [Valid Parentheses](stack/valid-parentheses/README.md)

### Binary Search

- [Find Minimum in Rotated Sorted Array](binary%20search/find-minimum-in-rotated-sorted-array/README.md)
- [Search in Rotated Sorted Array](binary%20search/search-in-rotated-sorted-array/README.md)

### Linked List

- [Linked List Cycle Detection](link%20list/linked-list-cycle-detection/README.md)
- [Merge k Sorted Lists](link%20list/merge-k-sorted-lists/README.md)
- [Merge Two Sorted Linked Lists](link%20list/merge-two-sorted-linked-lists/README.md)
- [Remove Nth Node From End of List](link%20list/remove-nth-node-from-end/README.md)
- [Reorder Linked List](link%20list/reorder-linked-list/README.md)
- [Reverse Linked List](link%20list/reverse-linked-list/README.md)

### Trees

- [Binary Tree Level Order Traversal](trees/binary-tree-level-order-traversal/README.md)
- [Binary Tree Maximum Path Sum](trees/binary-tree-maximum-path-sum/README.md)
- [Construct Binary Tree from Preorder and Inorder Traversal](trees/construct-binary-tree-from-preorder-and-inorder-traversal/README.md)
- [Invert Binary Tree](trees/invert-binary-tree/README.md)
- [Kth Smallest Integer in BST](trees/kth-smallest-integer-in-bst/README.md)
- [Lowest Common Ancestor in Binary Search Tree](trees/lowest-common-ancestor-in-binary-search-tree/README.md)
- [Maximum Depth of Binary Tree](trees/maximum-depth-of-binary-tree/README.md)
- [Same Binary Tree](trees/same-binary-tree/README.md)
- [Serialize and Deserialize Binary Tree](trees/serialize-and-deserialize-binary-tree/README.md)
- [Subtree of Another Tree](trees/subtree-of-another-tree/README.md)
- [Valid Binary Search Tree](trees/valid-binary-search-tree/README.md)

### Tries

- [Design Add and Search Word Data Structure](tries/design-word-search-data-structure/README.md)
- [Implement Trie (Prefix Tree)](tries/implement-prefix-tree/README.md)
- [Word Search II](tries/word-search-ii/README.md)

### Heap and Priority Queue

- [Find Median from Data Stream](heap%20and%20priority%20queue/find-median-from-data-stream/README.md)

### Backtracking

- [Combination Sum](backtracking/combination-sum/README.md)
- [Word Search](backtracking/word-search/README.md)

### Graphs

- [Alien Dictionary](graphs/alien-dictionary/README.md)
- [Clone Graph](graphs/clone-graph/README.md)
- [Course Schedule](graphs/course-schedule/README.md)
- [Graph Valid Tree](graphs/graph-valid-tree/README.md)
- [Number of Connected Components in an Undirected Graph](graphs/number-of-connected-components-in-an-undirected-graph/README.md)
- [Number of Islands](graphs/number-of-islands/README.md)
- [Pacific Atlantic Water Flow](graphs/pacific-atlantic-water-flow/README.md)

### 1-D Dynamic Programming

- [Climbing Stairs](1d%20dynamic%20programming/climbing-stairs/README.md)
- [Coin Change](1d%20dynamic%20programming/coin-change/README.md)
- [Decode Ways](1d%20dynamic%20programming/decode-ways/README.md)
- [House Robber](1d%20dynamic%20programming/house-robber/README.md)
- [House Robber II](1d%20dynamic%20programming/house-robber-ii/README.md)
- [Longest Increasing Subsequence](1d%20dynamic%20programming/longest-increasing-subsequence/README.md)
- [Longest Palindromic Substring](1d%20dynamic%20programming/longest-palindromic-substring/README.md)
- [Maximum Product Subarray](1d%20dynamic%20programming/maximum-product-subarray/README.md)
- [Palindromic Substrings](1d%20dynamic%20programming/palindromic-substrings/README.md)
- [Word Break](1d%20dynamic%20programming/word-break/README.md)

### 2-D Dynamic Programming

- [Longest Common Subsequence](2d%20dynamic%20programming/longest-common-subsequence/README.md)
- [Unique Paths](2d%20dynamic%20programming/unique-paths/README.md)

### Greedy

- [Jump Game](greedy/jump-game/README.md)
- [Maximum Subarray](greedy/maximum-subarray/README.md)

### Intervals

- [Insert Interval](intervals/insert-interval/README.md)
- [Meeting Rooms](intervals/meeting-rooms/README.md)
- [Meeting Rooms II](intervals/meeting-rooms-ii/README.md)
- [Merge Intervals](intervals/merge-intervals/README.md)
- [Non-overlapping Intervals](intervals/non-overlapping-intervals/README.md)

### Math and Geometry

- [Rotate Image](math%20and%20geometry/rotate-image/README.md)
- [Set Matrix Zeroes](math%20and%20geometry/set-matrix-zeroes/README.md)
- [Spiral Matrix](math%20and%20geometry/spiral-matrix/README.md)

### Bit Manipulation

- [Counting Bits](bit%20manipulation/counting-bits/README.md)
- [Missing Number](bit%20manipulation/missing-number/README.md)
- [Number of 1 Bits](bit%20manipulation/number-of-1-bits/README.md)
- [Reverse Bits](bit%20manipulation/reverse-bits/README.md)
- [Sum of Two Integers](bit%20manipulation/sum-of-two-integers/README.md)

## Additional practice

- [Largest Rectangle in Histogram](stack/largest-rectangle-in-histogram/README.md) - monotonic stack; outside the Blind 75 count.

## Algorithm frames

| Frame | What it demonstrates |
| --- | --- |
| [Backtracking](backtracking/backtracking%20code%20frame/README.md) | Choose, recurse, undo; reject invalid candidates |
| [1-D Dynamic Programming](1d%20dynamic%20programming/1d%20dp%20code%20frame/README.md) | Top-down memoization and bottom-up tabulation |

The frames contain problem-specific helper declarations. Their accompanying `test.cpp` files supply complete worked examples; fill in those helpers when adapting a frame to another problem.

## Run locally

Use a compiler with C++17 support, such as GCC or Clang. No third-party libraries are required. Compile each problem separately: solution classes and helper types are intentionally reused across directories.

### Run a checked-in test

From the repository root, this example compiles and runs the [Climbing Stairs tests](1d%20dynamic%20programming/climbing-stairs/test.cpp). Build outputs stay in `build/`, which Git ignores.

**Windows PowerShell**

```powershell
New-Item -ItemType Directory -Force build | Out-Null
g++ -std=c++17 -Wall -Wextra -pedantic "1d dynamic programming/climbing-stairs/test.cpp" -o build/climbing-stairs-test.exe
if ($LASTEXITCODE -eq 0) { .\build\climbing-stairs-test.exe }
```

**Linux / macOS shell**

```sh
mkdir -p build
g++ -std=c++17 -Wall -Wextra -pedantic "1d dynamic programming/climbing-stairs/test.cpp" -o build/climbing-stairs-test && ./build/climbing-stairs-test
```

Replace the source path and output name to run another entry with `test.cpp`. Successful assert-based tests exit with code `0` and may print nothing. Keep assertions enabled when running the tests.

### Use a solution without a local test

Most solution files define a judge-facing class and do not contain `main()`. Submit the implementation to the linked problem, or write a small local harness that supplies the expected input and helper types. Entries with several implementations document the alternatives in their README.

## Repository conventions

```text
<topic>/
  <problem>/
    README.md       # Problem link, approach, examples, complexity
    solution.cpp    # Implementation, or named alternatives
    test.cpp        # Local checks, when provided
    tree-node.h     # Shared judge type, when needed
```

- Problem READMEs document the code actually present, including tradeoffs and assumptions; implementations are not necessarily the most optimized variant.
- Multiple approaches stay together, with descriptive filenames such as `iterative.cpp` and `recursive.cpp`.
- Local headers or tests provide judge types such as `TreeNode`, `ListNode`, and `Interval` when needed.
- New entries follow the existing format: problem and source links, approach, walkthrough, C++ notes, relevant cases, and time/space complexity.
- Build artifacts belong in `build/`; source files, explanations, and test harnesses belong in the problem directory.

## Reference

The problem selection follows [NeetCode Blind 75](https://neetcode.io/practice/practice/blind75). Each entry links to its own problem statement on NeetCode or LeetCode.
