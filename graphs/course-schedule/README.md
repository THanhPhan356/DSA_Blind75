# Course Schedule

**Problem:** [LeetCode - Course Schedule](https://leetcode.com/problems/course-schedule/)\
**Solution:** [solution.cpp](solution.cpp)\
**Tests:** [test.cpp](test.cpp)

Given `numCourses` courses numbered from `0` to `numCourses - 1` and a list of prerequisite pairs, return whether all courses can be completed. A pair `[a, b]` means course `b` must be completed before course `a`. Return a boolean, not a course ordering.

## Approach: DFS with three states

Represent each prerequisite `[a, b]` as a directed edge `b -> a`. All courses can be completed exactly when this directed graph has no cycle: a cycle makes each course in it depend indirectly on itself.

1. Create an adjacency list with `numCourses` entries, including courses without edges.
2. For each pair, append `a` to `graph[b]`.
3. Initialize every course's state to `0` (unvisited).
4. Start DFS from every course that is still unvisited.
5. If DFS reaches a course in state `1` (visiting), it has returned to a course on the active recursion path. Return `false` because there is a cycle.
6. If a course is in state `2` (finished), return `true` for that branch: its outgoing paths have already been checked.
7. Otherwise, mark the course visiting, recursively check its neighbors, then mark it finished only if every branch succeeds.
8. If every component passes, return `true`.

A simple visited flag cannot distinguish a cycle from two paths reaching the same finished course. The visiting state tracks the active path; the finished state avoids checking safe paths again. The outer loop is necessary because a cycle can occur in a disconnected component.

## How the C++ code is organized

| Part | Responsibility |
| --- | --- |
| `graph[i]` | Store the courses with an outgoing edge from course `i` |
| `graph[p[1]].push_back(p[0])` | Convert `[a, b]` into `b -> a` |
| `state[node] == 0` | Course has not been visited |
| `state[node] == 1` | Course is on the active DFS path |
| `state[node] == 2` | All outgoing paths have been checked successfully |
| `dfs(node, graph, state)` | Check for a cycle reachable from one course |
| Outer loop over all courses | Include isolated courses and disconnected components |

## Walkthrough

For `numCourses = 4` and `prerequisites = [[1,0], [2,0], [3,1]]`:

```text
graph[0] = [1, 2]
graph[1] = [3]
graph[2] = []
graph[3] = []

0 -> 1 -> 3
|
`--> 2
```

| Step | Action |
| --- | --- |
| 1 | Start DFS at `0`; mark it visiting |
| 2 | Follow `0 -> 1`; mark `1` visiting |
| 3 | Follow `1 -> 3`; mark `3` visiting, then finished because it has no outgoing edges |
| 4 | Finish `1` after its only neighbor succeeds |
| 5 | Follow `0 -> 2`; visit and finish `2` |
| 6 | Finish `0`; all remaining courses are already finished, so return `true` |

For `[[1,0], [0,1]]`, DFS follows `0 -> 1 -> 0`. Course `0` is still visiting when reached again, so return `false`. In contrast, reaching a finished course through a different path is safe.

## C++ notes

- The vector index identifies a course; the vector at that index contains its outgoing neighbors.
- `graph` is passed by constant reference in DFS; `state` is passed by reference so all calls share the same marks.
- Mark a course finished after checking its neighbors, not immediately upon entering it.
- On a cycle, returning `false` immediately propagates failure through all callers. No further cleanup is needed because the entire search stops and its state is local to the method call.
- Unlike backtracking that enumerates paths, finished marks are kept permanently for this search.
- The input is unchanged, and every call creates fresh graph and state vectors.
- Inputs follow the problem's contract: course IDs are valid and each prerequisite has two entries.
- Submit the includes and `Solution` class; LeetCode supplies `main()`.

## Cases to check

| Case | What it checks |
| --- | --- |
| One prerequisite and the four-course walkthrough | Acyclic dependencies are accepted |
| Two-course cycle, longer cycle, and self-loop | Active-path detection |
| Two branches reaching the same course | A finished course is not mistaken for a cycle |
| A cycle in a separate component | The outer loop checks every component |
| No prerequisites and isolated courses | Courses without edges remain valid |
| A chain of 2,000 courses, with and without a closing edge | Deep traversal and cycle propagation |
| Repeated calls on the same object and input comparison | No stale state or input mutation |

Run the local tests from this directory:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic test.cpp -o course-schedule-test
./course-schedule-test
```

## Complexity

Let `V` be `numCourses` and `E` the number of prerequisite pairs.

**Time:** O(V + E). Each course's outgoing list is expanded at most once, and each edge is checked at most once.\
**Auxiliary space:** O(V + E) for the adjacency list, states, and recursion stack. The stack can reach O(V) depth; for inputs beyond the judge's limits or environments with a smaller stack, iterative DFS or Kahn's BFS avoids recursive stack overflow.
