#include <cassert>
#include "solution.cpp"

int main() {
    Solution solution;
    auto check = [&](std::vector<std::vector<int>> intervals,
                     std::vector<int> added,
                     const std::vector<std::vector<int>>& expected) {
        const auto original = intervals;
        const auto originalAdded = added;
        assert(solution.insert(intervals, added) == expected);
        assert(intervals == original);
        assert(added == originalAdded);
    };

    check({{1, 3}, {6, 9}}, {2, 5}, {{1, 5}, {6, 9}});
    check({{1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16}}, {4, 8},
          {{1, 2}, {3, 10}, {12, 16}});
    check({}, {2, 5}, {{2, 5}});
    check({{3, 5}}, {0, 1}, {{0, 1}, {3, 5}});
    check({{1, 3}}, {5, 7}, {{1, 3}, {5, 7}});
    check({{1, 2}, {6, 8}}, {3, 4}, {{1, 2}, {3, 4}, {6, 8}});
    check({{1, 10}}, {3, 5}, {{1, 10}});
    check({{3, 4}, {6, 7}}, {2, 8}, {{2, 8}});
    check({{1, 3}, {5, 7}}, {3, 5}, {{1, 7}});
    check({{1, 3}}, {1, 3}, {{1, 3}});
    check({{0, 0}, {2, 2}}, {1, 1}, {{0, 0}, {1, 1}, {2, 2}});
    check({{0, 100000}}, {100000, 100000}, {{0, 100000}});

    std::vector<std::vector<int>> many;
    for (int i = 0; i < 10000; ++i) {
        many.push_back({3 * i, 3 * i + 1});
    }
    check(many, {0, 100000}, {{0, 100000}});
}
