#include <cassert>
#include "solution.cpp"

void check(Solution& solution, int numCourses,
           vector<vector<int>> prerequisites, bool expected) {
    const auto original = prerequisites;
    assert(solution.canFinish(numCourses, prerequisites) == expected);
    assert(prerequisites == original);
}

int main() {
    Solution solution;
    check(solution, 2, {{1, 0}}, true);
    check(solution, 2, {{1, 0}, {0, 1}}, false);
    check(solution, 4, {{1, 0}, {2, 0}, {3, 1}}, true);
    check(solution, 4, {{1, 0}, {2, 0}, {3, 1}, {3, 2}}, true);
    check(solution, 4, {{1, 0}, {3, 2}, {2, 3}}, false);
    check(solution, 1, {{0, 0}}, false);
    check(solution, 1, {}, true);
    check(solution, 5, {}, true);
    check(solution, 3, {{0, 1}, {1, 2}}, true);
    check(solution, 3, {{1, 0}, {2, 1}, {0, 2}}, false);
    check(solution, 3, {{1, 0}}, true);

    vector<vector<int>> chain;
    for (int i = 1; i < 2000; ++i) {
        chain.push_back({i, i - 1});
    }
    check(solution, 2000, chain, true);
    chain.push_back({0, 1999});
    check(solution, 2000, chain, false);
}
