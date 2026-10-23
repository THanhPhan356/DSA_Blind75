#include <string>
#include <vector>

class Solution {
    int decode(const std::string& s, int i, std::vector<int>& memo) {
        if (memo[i] != -1) return memo[i];
        if (s[i] == '0') return memo[i] = 0;

        int count = decode(s, i + 1, memo);
        if (i + 1 < static_cast<int>(s.size()) &&
            (s[i] == '1' || (s[i] == '2' && s[i + 1] <= '6'))) {
            count += decode(s, i + 2, memo);
        }

        return memo[i] = count;
    }

public:
    int numDecodings(std::string s) {
        std::vector<int> memo(s.size() + 1, -1);
        memo[s.size()] = 1;
        return decode(s, 0, memo);
    }
};
