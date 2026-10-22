#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>
#include "solution.cpp"

int main() {
    Solution solution;
    const std::vector<std::pair<std::string, int>> cases = {
        {"babad", 3},
        {"cbbd", 2},
        {"a", 1},
        {"ac", 1},
        {"aa", 2},
        {"abc", 1},
        {"abba", 4},
        {"racecar", 7},
        {"aab", 2},
        {"baa", 2},
        {"abacdfgdcaba", 3},
        {"forgeeksskeegfor", 10},
        {std::string(1000, 'a'), 1000}
    };

    for (const auto& test : cases) {
        const auto result = solution.longestPalindrome(test.first);
        assert(result.size() == static_cast<std::size_t>(test.second));
        assert(test.first.find(result) != std::string::npos);
        assert(std::equal(result.begin(), result.end(), result.rbegin()));
    }
}
