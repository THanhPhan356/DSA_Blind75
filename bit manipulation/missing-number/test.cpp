#include <algorithm>
#include <cassert>
#include <random>
#include "solution.cpp"

int main() {
    Solution solution;
    auto check = [&](std::vector<int> nums, int expected) {
        const auto original = nums;
        assert(solution.missingNumber(nums) == expected);
        assert(nums == original);
    };

    check({3, 0, 1}, 2);
    check({0, 1}, 2);
    check({9, 6, 4, 2, 3, 5, 7, 0, 1}, 8);
    check({0}, 1);
    check({1}, 0);

    std::mt19937 rng(268);
    for (int n = 1; n <= 100; ++n) {
        for (int missing = 0; missing <= n; ++missing) {
            std::vector<int> nums;
            for (int value = 0; value <= n; ++value) {
                if (value != missing) nums.push_back(value);
            }
            std::shuffle(nums.begin(), nums.end(), rng);
            check(nums, missing);
        }
    }

    for (int missing : {0, 5000, 10000}) {
        std::vector<int> nums;
        for (int value = 0; value <= 10000; ++value) {
            if (value != missing) nums.push_back(value);
        }
        std::shuffle(nums.begin(), nums.end(), rng);
        check(nums, missing);
    }
}
