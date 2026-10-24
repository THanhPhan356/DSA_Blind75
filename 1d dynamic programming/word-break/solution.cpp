#include <string>
#include <vector>

class Solution {
public:
    bool wordBreak(std::string s, std::vector<std::string>& wordDict) {
        int n = static_cast<int>(s.size());
        std::vector<bool> dp(n + 1, false);
        dp[0] = true;

        for (int i = 1; i <= n; ++i) {
            for (const auto& word : wordDict) {
                int len = static_cast<int>(word.size());
                if (i >= len && dp[i - len] &&
                    s.compare(i - len, len, word) == 0) {
                    dp[i] = true;
                    break;
                }
            }
        }

        return dp[n];
    }
};
