#include <vector>

class Solution {
public:
    int search(std::vector<int>& nums, int target) {
        int n = static_cast<int>(nums.size());
        int left = 0, right = n - 1;

        // Find the rotation point.
        while (left < right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] > nums[right]) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }

        int pivot = left;

        // Select the sorted segment containing the target, if present.
        if (nums[pivot] <= target && target <= nums[n - 1]) {
            left = pivot;
            right = n - 1;
        } else {
            left = 0;
            right = pivot - 1;
        }

        // Standard binary search.
        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] == target) {
                return mid;
            } else if (nums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return -1;
    }
};
