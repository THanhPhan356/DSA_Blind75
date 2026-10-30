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
    auto check = [&](std::vector<Interval> intervals, bool expected) {
        assert(solution.canAttendMeetings(intervals) == expected);
        for (std::size_t i = 1; i < intervals.size(); ++i) {
            assert(intervals[i - 1].start <= intervals[i].start);
        }
    };

    check({{0, 30}, {5, 10}, {15, 20}}, false);
    check({{7, 10}, {2, 4}}, true);
    check({{5, 8}, {1, 5}}, true);
    check({{1, 10}, {2, 3}}, false);
    check({{1, 4}, {1, 2}}, false);
    check({{1, 2}, {1, 2}}, false);
    check({{8, 10}, {1, 2}, {3, 9}}, false);
    check({{3, 4}, {1, 2}, {2, 3}}, true);
    check({{0, 1000000}}, true);
    check({}, true);

    std::vector<Interval> many;
    for (int i = 9999; i >= 0; --i) {
        many.emplace_back(2 * i, 2 * i + 1);
    }
    check(many, true);
}
