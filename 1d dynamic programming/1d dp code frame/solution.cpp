#include <vector>

// Define these helpers for the problem being solved.
bool isBaseCase(int i);
long long baseValue(int i);
long long transitionTopDown(int i, std::vector<long long>& memo,
                            std::vector<bool>& computed);
long long transitionBottomUp(int i, const std::vector<long long>& dp);

long long solveTopDown(int i, std::vector<long long>& memo,
                       std::vector<bool>& computed) {
    if (computed[i]) {
        return memo[i];
    }

    if (isBaseCase(i)) {
        memo[i] = baseValue(i);
    } else {
        memo[i] = transitionTopDown(i, memo, computed);
    }

    computed[i] = true;
    return memo[i];
}

long long solveBottomUp(int n) {
    std::vector<long long> dp(n + 1);

    for (int i = 0; i <= n; ++i) {
        if (isBaseCase(i)) {
            dp[i] = baseValue(i);
        } else {
            dp[i] = transitionBottomUp(i, dp);
        }
    }

    return dp[n];
}
