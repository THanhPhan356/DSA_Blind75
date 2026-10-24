#include <cassert>
#include "solution.cpp"

int countByDivision(int value) {
    int count = 0;
    while (value > 0) {
        count += value % 2;
        value /= 2;
    }
    return count;
}

int main() {
    Solution solution;
    assert((solution.countBits(0) == std::vector<int>{0}));
    assert((solution.countBits(1) == std::vector<int>{0, 1}));
    assert((solution.countBits(2) == std::vector<int>{0, 1, 1}));
    assert((solution.countBits(5) == std::vector<int>{0, 1, 1, 2, 1, 2}));

    const auto result = solution.countBits(100000);
    assert(result.size() == 100001);
    for (int i = 0; i <= 100000; ++i) {
        assert(result[i] == countByDivision(i));
    }

    for (int bit = 0; bit <= 16; ++bit) {
        int power = 1 << bit;
        assert(result[power] == 1);
        assert(result[power - 1] == bit);
    }

    assert((solution.countBits(2) == std::vector<int>{0, 1, 1}));
}
