#include <cassert>
#include "solution.cpp"

int main() {
    Solution solution;
    assert(solution.getSum(1, 2) == 3);
    assert(solution.getSum(2, 3) == 5);
    assert(solution.getSum(0, 0) == 0);
    assert(solution.getSum(-1, 1) == 0);
    assert(solution.getSum(-2, -3) == -5);
    assert(solution.getSum(7, 1) == 8);
    assert(solution.getSum(-1000, -1000) == -2000);
    assert(solution.getSum(1000, 1000) == 2000);

    for (int a = -1000; a <= 1000; ++a) {
        for (int b = -1000; b <= 1000; ++b) {
            assert(solution.getSum(a, b) == a + b);
        }
    }
}
