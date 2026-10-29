#include <algorithm>
#include <string>
#include <vector>
using namespace std;

class Solution {
    int dfs(int i, int j, const string& text1, const string& text2,
            vector<vector<int>>& memo) {
        if (i == static_cast<int>(text1.size()) ||
            j == static_cast<int>(text2.size())) {
            return 0;
        }

        if (memo[i][j] != -1) return memo[i][j];

        if (text1[i] == text2[j]) {
            memo[i][j] = 1 + dfs(i + 1, j + 1, text1, text2, memo);
        } else {
            memo[i][j] = max(
                dfs(i + 1, j, text1, text2, memo),
                dfs(i, j + 1, text1, text2, memo)
            );
        }

        return memo[i][j];
    }

public:
    int longestCommonSubsequence(string text1, string text2) {
        vector<vector<int>> memo(
            text1.size(), vector<int>(text2.size(), -1)
        );
        return dfs(0, 0, text1, text2, memo);
    }
};
