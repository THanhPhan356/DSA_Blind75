#include <algorithm>
#include <cassert>
#include "solution.cpp"

void check(Solution& solution, vector<int> candidates, int target,
           vector<vector<int>> expected) {
    const auto original = candidates;
    auto actual = solution.combinationSum(candidates, target);
    for (auto& combination : actual) {
        sort(combination.begin(), combination.end());
    }
    for (auto& combination : expected) {
        sort(combination.begin(), combination.end());
    }
    sort(actual.begin(), actual.end());
    sort(expected.begin(), expected.end());
    assert(actual == expected);
    assert(candidates == original);
}

int main() {
    Solution solution;
    check(solution, {2, 3, 6, 7}, 7, {{2, 2, 3}, {7}});
    check(solution, {2, 3, 5}, 8, {{2, 2, 2, 2}, {2, 3, 3}, {3, 5}});
    check(solution, {2}, 1, {});
    check(solution, {2}, 6, {{2, 2, 2}});
    check(solution, {7, 3, 2, 6}, 7, {{7}, {2, 2, 3}});
    check(solution, {1}, 3, {{1, 1, 1}});
    check(solution, {4, 5}, 3, {});
}
