#include <cassert>
#include "solution.cpp"

void check(Solution& solution, int n, vector<vector<int>> edges,
           int expected) {
    const auto original = edges;
    assert(solution.countComponents(n, edges) == expected);
    assert(edges == original);
}

int main() {
    Solution solution;
    check(solution, 1, {}, 1);
    check(solution, 5, {}, 5);
    check(solution, 2, {{0, 1}}, 1);
    check(solution, 5, {{0, 1}, {1, 2}, {3, 4}}, 2);
    check(solution, 5, {{0, 1}, {1, 2}}, 3);
    check(solution, 5, {{0, 1}, {1, 2}, {2, 3}, {3, 4}}, 1);
    check(solution, 3, {{0, 1}, {1, 2}, {2, 0}}, 1);
    check(solution, 6, {{0, 1}, {1, 2}, {2, 0}, {3, 4}}, 3);
    check(solution, 4, {{1, 2}, {2, 3}, {3, 1}}, 2);
    check(solution, 5, {{4, 3}, {2, 1}, {1, 0}}, 2);

    vector<vector<int>> chain;
    for (int i = 1; i < 2000; ++i) {
        chain.push_back({i - 1, i});
    }
    check(solution, 2000, chain, 1);
    chain.push_back({1999, 0});
    check(solution, 2000, chain, 1);
}
