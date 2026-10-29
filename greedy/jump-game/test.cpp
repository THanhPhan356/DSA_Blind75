#include <cassert>
#include <random>
#include "solution.cpp"

bool reachableByEnumeration(const std::vector<int>& nums) {
    const int n = nums.size();
    std::vector<bool> reachable(n, false);
    reachable[0] = true;
    for (int i = 0; i < n; ++i) {
        if (!reachable[i]) continue;
        for (int step = 1; step <= nums[i] && i + step < n; ++step) {
            reachable[i + step] = true;
        }
    }
    return reachable[n - 1];
}

int main() {
    Solution solution;
    auto check = [&](std::vector<int> nums, bool expected) {
        const auto original = nums;
        assert(solution.canJump(nums) == expected);
        assert(nums == original);
    };

    check({2, 3, 1, 1, 4}, true);
    check({3, 2, 1, 0, 4}, false);
    check({0}, true);
    check({0, 1}, false);
    check({1, 0}, true);
    check({2, 0, 0}, true);
    check({1, 0, 1}, false);
    check({2, 3, 0, 0, 0}, true);
    check({2, 0, 10000}, true);
    check({0, 10000}, false);
    check({10000, 0, 0}, true);
    check(std::vector<int>(10000, 1), true);
    check(std::vector<int>(10000, 0), false);

    std::mt19937 rng(42);
    std::uniform_int_distribution<int> length(1, 20);
    std::uniform_int_distribution<int> jump(0, 6);
    for (int trial = 0; trial < 1000; ++trial) {
        std::vector<int> nums(length(rng));
        for (int& x : nums) x = jump(rng);
        check(nums, reachableByEnumeration(nums));
    }
}
