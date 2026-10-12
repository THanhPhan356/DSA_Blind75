#include <vector>

class Solution {
public:
    int findMin(std::vector<int>& nums) {
        int L = 0;
        int R = static_cast<int>(nums.size()) - 1;

        while (L < R) {
            int mid = L + (R - L) / 2;

            if (nums[mid] > nums[R]) {
                L = mid + 1;
            } else {
                R = mid;
            }
        }

        return nums[L];
    }
};
