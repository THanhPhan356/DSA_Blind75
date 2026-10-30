#include <algorithm>
#include <vector>

// Interval is provided by the judge; test.cpp defines it for local checks.
class Solution {
public:
    static bool compareStart(const Interval& a, const Interval& b) {
        return a.start < b.start;
    }

    bool canAttendMeetings(std::vector<Interval>& intervals) {
        std::sort(intervals.begin(), intervals.end(), compareStart);
        int n = intervals.size();

        for (int i = 0; i + 1 < n; ++i) {
            if (intervals[i].end > intervals[i + 1].start) {
                return false;
            }
        }

        return true;
    }
};
