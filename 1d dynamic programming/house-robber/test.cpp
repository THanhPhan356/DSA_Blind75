#include <cassert>
#include <utility>
#include "solution.cpp"

int main() {
    Solution solution;
    const std::vector<std::pair<std::vector<int>, int>> cases = {
        {{1, 2, 3, 1}, 4},
        {{2, 7, 9, 3, 1}, 12},
        {{5}, 5},
        {{2, 1}, 2},
        {{1, 2}, 2},
        {{0, 0, 0}, 0},
        {{2, 1, 1, 2}, 4},
        {{1, 3, 1, 3, 100}, 103},
        {std::vector<int>(100, 400), 20000}
    };

    for (const auto& test : cases) {
        auto nums = test.first;
        assert(solution.rob(nums) == test.second);
        assert(nums == test.first);
    }
}
