#include <vector>

class Solution {
public:
    int missingNumber(std::vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        int result = n;

        for (int i = 0; i < n; ++i) {
            result ^= i ^ nums[i];
        }

        return result;
    }
};
