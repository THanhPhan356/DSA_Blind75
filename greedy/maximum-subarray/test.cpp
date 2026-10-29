#include <cassert>
#include <random>
#include "solution.cpp"

int bruteForce(const std::vector<int>& nums) {
    int best = nums[0];
    for (int left = 0; left < static_cast<int>(nums.size()); ++left) {
        int sum = 0;
        for (int right = left; right < static_cast<int>(nums.size()); ++right) {
            sum += nums[right];
            best = std::max(best, sum);
        }
    }
    return best;
}

int main() {
    Solution solution;
    auto check = [&](std::vector<int> nums, int expected) {
        const auto original = nums;
        assert(solution.maxSubArray(nums) == expected);
        assert(nums == original);
    };

    check({-2, 1, -3, 4, -1, 2, 1, -5, 4}, 6);
    check({1}, 1);
    check({-5}, -5);
    check({-8, -3, -6, -2, -5, -4}, -2);
    check({0, 0, 0}, 0);
    check({5, 4, -1, 7, 8}, 23);
    check({1, 2, 3}, 6);
    check({-4, 5}, 5);
    check({5, -10}, 5);
    check(std::vector<int>(100000, 10000), 1000000000);
    check(std::vector<int>(100000, -10000), -10000);

    std::mt19937 rng(42);
    std::uniform_int_distribution<int> length(1, 20);
    std::uniform_int_distribution<int> value(-20, 20);
    for (int trial = 0; trial < 1000; ++trial) {
        std::vector<int> nums(length(rng));
        for (int& x : nums) x = value(rng);
        check(nums, bruteForce(nums));
    }
}
