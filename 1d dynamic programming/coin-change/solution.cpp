#include <algorithm>
#include <vector>

class Solution {
public:
    int coinChange(std::vector<int>& coins, int amount) {
        std::vector<int> dp(amount + 1, amount + 1);
        dp[0] = 0;

        for (int sum = 1; sum <= amount; ++sum) {
            for (int coin : coins) {
                if (coin <= sum) {
                    dp[sum] = std::min(dp[sum], dp[sum - coin] + 1);
                }
            }
        }

        return dp[amount] > amount ? -1 : dp[amount];
    }
};
