#include "solution.cpp"
#include <cassert>

int main() {
    Solution solution;
    assert(solution.lengthOfLongestSubstring("") == 0);
    assert(solution.lengthOfLongestSubstring("abcabcbb") == 3);
    assert(solution.lengthOfLongestSubstring("bbbbb") == 1);
    assert(solution.lengthOfLongestSubstring("pwwkew") == 3);
    assert(solution.lengthOfLongestSubstring("abba") == 2);
    assert(solution.lengthOfLongestSubstring("dvdf") == 3);
    assert(solution.lengthOfLongestSubstring("tmmzuxt") == 5);
    assert(solution.lengthOfLongestSubstring(" ") == 1);
}
