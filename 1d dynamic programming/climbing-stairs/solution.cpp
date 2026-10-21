#include <vector>

class Solution {
    int solve(int n, std::vector<int>& memo) {
        if (n <= 1) return 1;

        if (memo[n] != -1) return memo[n];

        memo[n] = solve(n - 1, memo) + solve(n - 2, memo);
        return memo[n];
    }

public:
    int climbStairs(int n) {
        std::vector<int> memo(n + 1, -1);
        return solve(n, memo);
    }
};
