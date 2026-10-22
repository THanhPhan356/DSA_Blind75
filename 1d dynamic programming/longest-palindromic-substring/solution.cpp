#include <string>

class Solution {
public:
    std::string longestPalindrome(std::string s) {
        int n = static_cast<int>(s.size());
        int bestStart = 0, bestLength = 0;

        for (int center = 0; center < n; ++center) {
            for (int offset = 0; offset <= 1; ++offset) {
                int left = center, right = center + offset;

                while (left >= 0 && right < n && s[left] == s[right]) {
                    int length = right - left + 1;
                    if (length > bestLength) {
                        bestStart = left;
                        bestLength = length;
                    }
                    --left;
                    ++right;
                }
            }
        }

        return s.substr(bestStart, bestLength);
    }
};
