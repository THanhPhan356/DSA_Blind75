#include <cassert>
#include <utility>
#include <vector>
#include "solution.cpp"

int bruteCount(const std::string& s) {
    int count = 0;
    int n = static_cast<int>(s.size());
    for (int start = 0; start < n; ++start) {
        for (int end = start; end < n; ++end) {
            int left = start, right = end;
            while (left < right && s[left] == s[right]) {
                ++left;
                --right;
            }
            if (left >= right) ++count;
        }
    }
    return count;
}

int main() {
    Solution solution;
    const std::vector<std::pair<std::string, int>> cases = {
        {"a", 1}, {"abc", 3}, {"aa", 3}, {"aaa", 6},
        {"aba", 4}, {"abba", 6}, {"racecar", 10},
        {"aab", 4}, {"baa", 4}, {std::string(1000, 'a'), 500500}
    };
    for (const auto& test : cases) {
        assert(solution.countSubstrings(test.first) == test.second);
    }

    for (int length = 1; length <= 8; ++length) {
        for (int mask = 0; mask < (1 << length); ++mask) {
            std::string s(length, 'a');
            for (int i = 0; i < length; ++i) {
                if (mask & (1 << i)) s[i] = 'b';
            }
            assert(solution.countSubstrings(s) == bruteCount(s));
        }
    }
}
