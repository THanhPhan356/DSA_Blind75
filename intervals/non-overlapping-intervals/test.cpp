#include <cassert>
#include "solution.cpp"

int main() {
    Solution solution;
    auto check = [&](std::vector<std::vector<int>> intervals, int expected) {
        const auto original = intervals;
        assert(solution.eraseOverlapIntervals(intervals) == expected);
        for (std::size_t i = 1; i < intervals.size(); ++i) {
            assert(intervals[i - 1][1] <= intervals[i][1]);
        }
        assert(std::is_permutation(intervals.begin(), intervals.end(),
                                   original.begin(), original.end()));
    };

    check({{1, 2}, {2, 3}, {3, 4}, {1, 3}}, 1);
    check({{1, 2}, {1, 2}, {1, 2}}, 2);
    check({{1, 2}, {2, 3}}, 0);
    check({{1, 4}, {2, 3}, {3, 5}}, 1);
    check({{1, 10}, {2, 3}, {3, 4}, {4, 5}}, 1);
    check({{3, 5}, {1, 4}, {2, 3}}, 1);
    check({{1, 3}, {2, 3}, {3, 4}}, 1);
    check({{2, 3}, {1, 3}, {3, 4}}, 1);
    check({{-5, -3}, {-3, -1}, {-4, 0}}, 1);
    check({{-50000, 50000}}, 0);
    check({}, 0);
    check(std::vector<std::vector<int>>(100000, {1, 2}), 99999);
}
