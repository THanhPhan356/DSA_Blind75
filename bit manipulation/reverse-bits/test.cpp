#include <bitset>
#include <cassert>
#include <climits>
#include <random>
#include <string>
#include "solution.cpp"

int reference(int n) {
    std::string binary = std::bitset<32>(n).to_string();
    std::string reversed(binary.rbegin(), binary.rend());
    return static_cast<int>(std::bitset<32>(reversed).to_ulong());
}

int main() {
    Solution solution;
    assert(solution.reverseBits(43261596) == 964176192);
    assert(solution.reverseBits(2147483644) == 1073741822);
    assert(solution.reverseBits(0) == 0);
    assert(solution.reverseBits(2) == 1073741824);
    assert(solution.reverseBits(INT_MAX - 1) == INT_MAX - 1);
    assert(solution.reverseBits(0x55555554) == 0x2AAAAAAA);

    for (int bit = 1; bit <= 30; ++bit) {
        assert(solution.reverseBits(1 << bit) == (1 << (31 - bit)));
    }

    for (int n = 0; n <= 65534; n += 2) {
        int reversed = solution.reverseBits(n);
        assert(reversed == reference(n));
        assert(solution.reverseBits(reversed) == n);
    }

    std::mt19937 rng(190);
    std::uniform_int_distribution<int> half(0, (INT_MAX - 1) / 2);
    for (int trial = 0; trial < 1000; ++trial) {
        int n = half(rng) * 2;
        int reversed = solution.reverseBits(n);
        assert(reversed == reference(n));
        assert(solution.reverseBits(reversed) == n);
    }
}
