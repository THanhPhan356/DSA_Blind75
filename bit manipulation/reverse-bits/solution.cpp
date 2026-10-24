#include <cstdint>

class Solution {
public:
    int reverseBits(int n) {
        std::uint32_t bits = static_cast<std::uint32_t>(n);
        std::uint32_t result = 0;

        for (int i = 0; i < 32; ++i) {
            result = (result << 1) | (bits & 1u);
            bits >>= 1;
        }

        return static_cast<int>(result);
    }
};
