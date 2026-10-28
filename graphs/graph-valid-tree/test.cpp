#include <cassert>
#include "solution.cpp"

void check(Solution& solution, int n, vector<vector<int>> edges,
           bool expected) {
    const auto original = edges;
    assert(solution.validTree(n, edges) == expected);
    assert(edges == original);
}

int main() {
    Solution solution;
    check(solution, 1, {}, true);
    check(solution, 2, {{0, 1}}, true);
    check(solution, 2, {}, false);
    check(solution, 5, {{0, 1}, {0, 2}, {0, 3}, {1, 4}}, true);
    check(solution, 3, {{0, 1}, {1, 2}, {2, 0}}, false);
    check(solution, 4, {{0, 1}, {2, 3}}, false);
    check(solution, 4, {{1, 2}, {2, 3}, {3, 1}}, false);
    check(solution, 4, {{0, 1}, {1, 2}, {2, 3}}, true);
    check(solution, 4, {{0, 1}, {1, 2}, {2, 3}, {3, 0}}, false);
    check(solution, 5, {{0, 1}, {1, 2}, {2, 0}, {3, 4}}, false);
    check(solution, 4, {{3, 2}, {1, 0}, {2, 1}}, true);
    check(solution, 5, {}, false);

    vector<vector<int>> chain;
    for (int i = 1; i < 2000; ++i) {
        chain.push_back({i - 1, i});
    }
    check(solution, 2000, chain, true);
    chain.push_back({1999, 0});
    check(solution, 2000, chain, false);
}
