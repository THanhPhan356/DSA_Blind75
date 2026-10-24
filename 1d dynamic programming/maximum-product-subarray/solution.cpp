#include <algorithm>
#include <vector>

class Solution {
public:
    int maxProduct(std::vector<int>& nums) {
        int maxEnding = nums[0];
        int minEnding = nums[0];
        int result = nums[0];

        for (int i = 1; i < static_cast<int>(nums.size()); ++i) {
            int x = nums[i];
            int fromMax = maxEnding * x;
            int fromMin = minEnding * x;

            maxEnding = std::max({x, fromMax, fromMin});
            minEnding = std::min({x, fromMax, fromMin});
            result = std::max(result, maxEnding);
        }

        return result;
    }
};
