#include <algorithm>
#include <vector>

// Interval is provided by the judge; test.cpp defines it for local checks.
class Solution {
public:
    int minMeetingRooms(std::vector<Interval>& intervals) {
        std::vector<int> starts, ends;

        for (const Interval& interval : intervals) {
            starts.push_back(interval.start);
            ends.push_back(interval.end);
        }

        std::sort(starts.begin(), starts.end());
        std::sort(ends.begin(), ends.end());

        int n = intervals.size();
        int i = 0, j = 0;
        int rooms = 0, maxRooms = 0;

        while (i < n) {
            if (starts[i] < ends[j]) {
                ++rooms;
                ++i;
                maxRooms = std::max(maxRooms, rooms);
            } else {
                --rooms;
                ++j;
            }
        }

        return maxRooms;
    }
};
