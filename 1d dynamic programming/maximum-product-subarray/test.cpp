#include <cassert>
#include <random>
#include "solution.cpp"

int bruteForce(const std::vector<int>& nums) {
    int best = nums[0];
    for (int left = 0; left < static_cast<int>(nums.size()); ++left) {
        int product = 1;
        for (int right = left; right < static_cast<int>(nums.size()); ++right) {
            product *= nums[right];
            best = std::max(best, product);
        }
    }
    return best;
}

int main() {
    Solution solution;
    auto check = [&](std::vector<int> nums, int expected) {
        const auto original = nums;
        assert(solution.maxProduct(nums) == expected);
        assert(nums == original);
    };

    check({2, 3, -2, 4}, 6);
    check({-2, 0, -1}, 0);
    check({-2, 3, -4}, 24);
    check({-2}, -2);
    check({0}, 0);
    check({5}, 5);
    check({-2, -3, -4}, 12);
    check({0, -2, -3, 0, -4}, 6);
    check({2, -5, -2, -4, 3}, 24);
    check({10, 10, 10, 10, 10, 10, 10, 10, 10}, 1000000000);
    check({-10, 10, 10, 10, 10, 10, 10, 10, 10}, 100000000);
    check(std::vector<int>(20000, -1), 1);

    std::mt19937 rng(152);
    std::uniform_int_distribution<int> length(1, 9);
    std::uniform_int_distribution<int> value(-3, 3);
    for (int trial = 0; trial < 1000; ++trial) {
        std::vector<int> nums(length(rng));
        for (int& x : nums) x = value(rng);
        check(nums, bruteForce(nums));
    }
}
