#include <algorithm>
#include <vector>

class Solution {
public:
    std::vector<std::vector<int>> merge(std::vector<std::vector<int>>& intervals) {
        std::sort(intervals.begin(), intervals.end());
        std::vector<std::vector<int>> result;

        for (const auto& interval : intervals) {
            if (result.empty() || interval[0] > result.back()[1]) {
                result.push_back(interval);
            } else {
                result.back()[1] = std::max(result.back()[1], interval[1]);
            }
        }

        return result;
    }
};
