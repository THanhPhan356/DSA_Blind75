#include <algorithm>
#include <vector>

class Solution {
public:
    int eraseOverlapIntervals(std::vector<std::vector<int>>& intervals) {
        if (intervals.empty()) return 0;

        std::sort(intervals.begin(), intervals.end(),
                  [](const std::vector<int>& a, const std::vector<int>& b) {
                      return a[1] < b[1];
                  });

        int removed = 0;
        int lastEnd = intervals[0][1];
        int n = intervals.size();

        for (int i = 1; i < n; ++i) {
            if (intervals[i][0] >= lastEnd) {
                lastEnd = intervals[i][1];
            } else {
                ++removed;
            }
        }

        return removed;
    }
};
