#include <vector>

class Solution {
public:
    std::vector<int> countBits(int n) {
        std::vector<int> dp(n + 1, 0);

        for (int i = 1; i <= n; ++i) {
            dp[i] = dp[i & (i - 1)] + 1;
        }

        return dp;
    }
};
