#include <algorithm>
#include <vector>

class Solution {
public:
    std::vector<std::vector<int>> insert(std::vector<std::vector<int>>& intervals,
                                         std::vector<int>& newInterval) {
        std::vector<std::vector<int>> result;
        int i = 0, n = intervals.size();
        int start = newInterval[0], end = newInterval[1];

        while (i < n && intervals[i][1] < start) {
            result.push_back(intervals[i++]);
        }

        while (i < n && intervals[i][0] <= end) {
            start = std::min(start, intervals[i][0]);
            end = std::max(end, intervals[i][1]);
            ++i;
        }
        result.push_back({start, end});

        while (i < n) {
            result.push_back(intervals[i++]);
        }

        return result;
    }
};
