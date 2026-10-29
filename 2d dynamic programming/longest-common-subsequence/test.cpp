#include <cassert>
#include "solution.cpp"

int main() {
    Solution solution;
    assert(solution.longestCommonSubsequence("abcde", "ace") == 3);
    assert(solution.longestCommonSubsequence("abc", "abc") == 3);
    assert(solution.longestCommonSubsequence("abc", "def") == 0);
    assert(solution.longestCommonSubsequence("ab", "ba") == 1);
    assert(solution.longestCommonSubsequence("abc", "ac") == 2);
    assert(solution.longestCommonSubsequence("ac", "abc") == 2);
    assert(solution.longestCommonSubsequence("aaaa", "aa") == 2);
    assert(solution.longestCommonSubsequence("a", "a") == 1);
    assert(solution.longestCommonSubsequence("a", "b") == 0);
    assert(solution.longestCommonSubsequence("", "abc") == 0);
    assert(solution.longestCommonSubsequence("abc", "") == 0);
    assert(solution.longestCommonSubsequence("", "") == 0);
    assert(solution.longestCommonSubsequence(string(1000, 'a'), string(1000, 'a')) == 1000);
    assert(solution.longestCommonSubsequence(string(1000, 'a'), string(1000, 'b')) == 0);
    assert(solution.longestCommonSubsequence("abcde", "ace") == 3);
}
