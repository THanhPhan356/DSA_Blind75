#include <cassert>
#include <random>
#include "solution.cpp"

int bruteForce(const std::vector<int>& nums) {
    int best = 0;
    for (unsigned mask = 1; mask < (1u << nums.size()); ++mask) {
        int length = 0;
        int previous = 0;
        bool increasing = true;
        for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
            if ((mask & (1u << i)) == 0) continue;
            if (length > 0 && nums[i] <= previous) {
                increasing = false;
                break;
            }
            previous = nums[i];
            ++length;
        }
        if (increasing) best = std::max(best, length);
    }
    return best;
}

int main() {
    Solution solution;
    auto check = [&](std::vector<int> nums, int expected) {
        const auto original = nums;
        assert(solution.lengthOfLIS(nums) == expected);
        assert(nums == original);
    };

    check({10, 9, 2, 5, 3, 7, 101, 18}, 4);
    check({0, 1, 0, 3, 2, 3}, 4);
    check({7, 7, 7, 7, 7, 7, 7}, 1);
    check({5}, 1);
    check({5, 4, 3, 2, 1}, 1);
    check({1, 2, 3, 0}, 3);
    check({-3, -2, -1, 0}, 4);
    check({1, 2, 2, 3}, 3);
    check({-10000, 10000}, 2);

    std::vector<int> ascending(2500);
    for (int i = 0; i < 2500; ++i) ascending[i] = i;
    check(ascending, 2500);
    std::reverse(ascending.begin(), ascending.end());
    check(ascending, 1);
    check(std::vector<int>(2500, 7), 1);

    std::mt19937 rng(300);
    std::uniform_int_distribution<int> length(1, 10);
    std::uniform_int_distribution<int> value(-5, 5);
    for (int trial = 0; trial < 1000; ++trial) {
        std::vector<int> nums(length(rng));
        for (int& x : nums) x = value(rng);
        check(nums, bruteForce(nums));
    }
}
