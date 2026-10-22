#include <algorithm>
#include <vector>

class Solution {
public:
    int rob(std::vector<int>& nums) {
        int prev2 = 0, prev1 = 0;

        for (int money : nums) {
            int current = std::max(prev1, prev2 + money);
            prev2 = prev1;
            prev1 = current;
        }

        return prev1;
    }
};
