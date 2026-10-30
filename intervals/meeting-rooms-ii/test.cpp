#include <cassert>
#include <vector>

class Interval {
public:
    int start, end;

    Interval(int s, int e) : start(s), end(e) {}
};

#include "solution.cpp"

int main() {
    Solution solution;
    auto check = [&](std::vector<Interval> intervals, int expected) {
        const auto original = intervals;
        assert(solution.minMeetingRooms(intervals) == expected);
        assert(intervals.size() == original.size());
        for (std::size_t i = 0; i < intervals.size(); ++i) {
            assert(intervals[i].start == original[i].start);
            assert(intervals[i].end == original[i].end);
        }
    };

    check({{0, 30}, {5, 10}, {15, 20}}, 2);
    check({{7, 10}, {2, 4}}, 1);
    check({{5, 8}, {1, 5}}, 1);
    check({{1, 5}, {2, 6}, {3, 7}}, 3);
    check({{1, 3}, {2, 4}, {5, 7}, {6, 8}}, 2);
    check({{1, 10}, {2, 3}, {4, 5}, {6, 7}}, 2);
    check({{1, 2}, {1, 2}, {1, 2}}, 3);
    check({{1, 3}, {2, 3}, {3, 4}, {3, 5}}, 2);
    check({{10, 12}, {1, 2}, {5, 6}}, 1);
    check({{0, 1000000}}, 1);
    check({}, 0);
    check(std::vector<Interval>(10000, Interval(1, 2)), 10000);
}
