#include <cassert>
#include "solution.cpp"

int main() {
    Solution solution;
    auto check = [&](std::vector<std::vector<int>> intervals,
                     const std::vector<std::vector<int>>& expected) {
        const auto original = intervals;
        assert(solution.merge(intervals) == expected);
        assert(std::is_sorted(intervals.begin(), intervals.end()));
        assert(std::is_permutation(intervals.begin(), intervals.end(),
                                   original.begin(), original.end()));
    };

    check({{1, 3}, {2, 6}, {8, 10}, {15, 18}}, {{1, 6}, {8, 10}, {15, 18}});
    check({{1, 4}, {4, 5}}, {{1, 5}});
    check({{8, 10}, {2, 6}, {1, 4}, {1, 3}}, {{1, 6}, {8, 10}});
    check({{1, 10}, {2, 3}, {4, 5}}, {{1, 10}});
    check({{1, 2}, {2, 4}, {4, 7}}, {{1, 7}});
    check({{1, 4}, {1, 4}}, {{1, 4}});
    check({{1, 2}, {4, 5}, {7, 8}}, {{1, 2}, {4, 5}, {7, 8}});
    check({{2, 2}}, {{2, 2}});
    check({{0, 0}, {0, 1}, {2, 2}}, {{0, 1}, {2, 2}});
    check({}, {});

    std::vector<std::vector<int>> chain;
    for (int i = 9999; i >= 0; --i) {
        chain.push_back({i, i + 1});
    }
    check(chain, {{0, 10000}});
}
