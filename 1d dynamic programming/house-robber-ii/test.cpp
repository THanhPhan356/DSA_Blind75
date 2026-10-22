#include <cassert>
#include <utility>
#include "solution.cpp"

int main() {
    Solution solution;
    const std::vector<std::pair<std::vector<int>, int>> cases = {
        {{2, 3, 2}, 3},
        {{1, 2, 3, 1}, 4},
        {{1, 2, 3}, 3},
        {{5}, 5},
        {{0}, 0},
        {{2, 1}, 2},
        {{1, 2}, 2},
        {{0, 0, 0}, 0},
        {{2, 1, 1, 2}, 3},
        {{10, 1, 1, 10}, 11},
        {{1, 3, 1, 3, 100}, 103},
        {std::vector<int>(100, 1000), 50000}
    };

    for (const auto& test : cases) {
        auto nums = test.first;
        assert(solution.rob(nums) == test.second);
        assert(nums == test.first);
    }
}
