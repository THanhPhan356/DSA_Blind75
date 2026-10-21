#include <cassert>
#include "solution.cpp"

int evaluatedStates = 0;

// Climbing Stairs: dp[i] counts ways to climb i steps using steps of size 1 or 2.
bool isBaseCase(int i) {
    return i <= 1;
}

long long baseValue(int) {
    return 1;
}

long long transitionTopDown(int i, std::vector<long long>& memo,
                            std::vector<bool>& computed) {
    ++evaluatedStates;
    return solveTopDown(i - 1, memo, computed)
         + solveTopDown(i - 2, memo, computed);
}

long long transitionBottomUp(int i, const std::vector<long long>& dp) {
    return dp[i - 1] + dp[i - 2];
}

void check(int n, long long expected) {
    std::vector<long long> memo(n + 1);
    std::vector<bool> computed(n + 1, false);
    evaluatedStates = 0;

    assert(solveTopDown(n, memo, computed) == expected);
    assert(evaluatedStates == (n > 1 ? n - 1 : 0));
    assert(solveBottomUp(n) == expected);

    const int before = evaluatedStates;
    assert(solveTopDown(n, memo, computed) == expected);
    assert(evaluatedStates == before);
}

int main() {
    const std::vector<long long> expected = {1, 1, 2, 3, 5, 8, 13, 21, 34, 55};
    for (int n = 0; n < static_cast<int>(expected.size()); ++n) {
        check(n, expected[n]);
    }
    check(45, 1836311903LL);
    check(91, 7540113804746346429LL);
}
