#include <algorithm>
#include <vector>

class Solution {
public:
    int maxSubArray(std::vector<int>& nums) {
        int prefix = 0;
        int minPrefix = 0;
        int best = nums[0];

        for (int x : nums) {
            prefix += x;
            best = std::max(best, prefix - minPrefix);
            minPrefix = std::min(minPrefix, prefix);
        }

        return best;
    }
};
