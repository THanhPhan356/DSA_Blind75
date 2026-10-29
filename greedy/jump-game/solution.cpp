#include <algorithm>
#include <vector>

class Solution {
public:
    bool canJump(std::vector<int>& nums) {
        int farthest = 0;
        int n = nums.size();

        for (int i = 0; i < n; ++i) {
            if (i > farthest) return false;

            farthest = std::max(farthest, i + nums[i]);

            if (farthest >= n - 1) return true;
        }

        return false;
    }
};
