#include <cassert>
#include "solution.cpp"

int main() {
    Solution solution;
    assert(solution.uniquePaths(1, 1) == 1);
    assert(solution.uniquePaths(1, 100) == 1);
    assert(solution.uniquePaths(100, 1) == 1);
    assert(solution.uniquePaths(2, 3) == 3);
    assert(solution.uniquePaths(3, 2) == 3);
    assert(solution.uniquePaths(3, 3) == 6);
    assert(solution.uniquePaths(3, 7) == 28);
    assert(solution.uniquePaths(10, 10) == 48620);
    assert(solution.uniquePaths(17, 18) == 1166803110);
    assert(solution.uniquePaths(2, 3) == 3);
}
