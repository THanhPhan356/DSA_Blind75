#include <bitset>
#include <cassert>
#include <climits>
#include <random>
#include "solution.cpp"

int main() {
    Solution solution;
    assert(solution.hammingWeight(11) == 3);
    assert(solution.hammingWeight(128) == 1);
    assert(solution.hammingWeight(2147483645) == 30);
    assert(solution.hammingWeight(INT_MAX) == 31);
    assert(solution.hammingWeight(0) == 0);
    assert(solution.hammingWeight(0x55555555) == 16);

    for (int bit = 0; bit < 31; ++bit) {
        assert(solution.hammingWeight(1 << bit) == 1);
    }

    for (int n = 1; n <= 65535; ++n) {
        assert(solution.hammingWeight(n) ==
               static_cast<int>(std::bitset<32>(n).count()));
    }

    std::mt19937 rng(191);
    std::uniform_int_distribution<int> value(1, INT_MAX);
    for (int trial = 0; trial < 1000; ++trial) {
        int n = value(rng);
        assert(solution.hammingWeight(n) ==
               static_cast<int>(std::bitset<32>(n).count()));
    }
}
