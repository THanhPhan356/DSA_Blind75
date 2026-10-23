#include <cassert>
#include <utility>
#include <vector>
#include "solution.cpp"

int bruteCount(const std::string& s, int i = 0) {
    if (i == static_cast<int>(s.size())) return 1;
    int count = 0;
    for (int code = 1; code <= 26; ++code) {
        std::string token = std::to_string(code);
        if (s.compare(i, token.size(), token) == 0) {
            count += bruteCount(s, i + static_cast<int>(token.size()));
        }
    }
    return count;
}

int main() {
    Solution solution;
    const std::vector<std::pair<std::string, int>> cases = {
        {"12", 2}, {"226", 3}, {"06", 0}, {"0", 0},
        {"10", 1}, {"20", 1}, {"30", 0}, {"100", 0},
        {"101", 1}, {"27", 1}, {"26", 2}, {"11106", 2},
        {std::string(45, '1'), 1836311903},
        {std::string(100, '3'), 1},
        {"0" + std::string(99, '1'), 0},
        {"30" + std::string(98, '1'), 0},
        {std::string(98, '1') + "00", 0}
    };
    for (const auto& test : cases) {
        assert(solution.numDecodings(test.first) == test.second);
    }

    for (int value = 0; value < 10000; ++value) {
        std::string s = std::to_string(value);
        s.insert(0, 4 - s.size(), '0');
        assert(solution.numDecodings(s) == bruteCount(s));
    }
}
