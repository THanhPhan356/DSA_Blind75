#include <algorithm>
#include <vector>

class Solution {
    int robRange(const std::vector<int>& nums, int left, int right) {
        int prev2 = 0, prev1 = 0;

        for (int i = left; i <= right; ++i) {
            int current = std::max(prev1, prev2 + nums[i]);
            prev2 = prev1;
            prev1 = current;
        }

        return prev1;
    }

public:
    int rob(std::vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        if (n == 1) return nums[0];

        return std::max(robRange(nums, 0, n - 2),
                        robRange(nums, 1, n - 1));
    }
};
