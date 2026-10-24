#include <algorithm>
#include <vector>

class Solution {
public:
    int lengthOfLIS(std::vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        std::vector<int> dp(n, 1);
        int result = 1;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (nums[j] < nums[i]) {
                    dp[i] = std::max(dp[i], dp[j] + 1);
                }
            }
            result = std::max(result, dp[i]);
        }

        return result;
    }
};
