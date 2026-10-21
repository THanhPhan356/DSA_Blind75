#include <cassert>
#include "solution.cpp"

int main() {
    Solution solution;
    const std::vector<int> expected = {1, 2, 3, 5, 8, 13, 21, 34, 55, 89};

    for (int n = 1; n <= static_cast<int>(expected.size()); ++n) {
        assert(solution.climbStairs(n) == expected[n - 1]);
    }

    assert(solution.climbStairs(20) == 10946);
    assert(solution.climbStairs(30) == 1346269);
    assert(solution.climbStairs(45) == 1836311903);
    assert(solution.climbStairs(2) == 2);
    assert(solution.climbStairs(44) == 1134903170);
    assert(solution.climbStairs(1) == 1);
}
