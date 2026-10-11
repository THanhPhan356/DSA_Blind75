#include <algorithm>
#include <string>

class Solution {
public:
    int characterReplacement(std::string s, int k) {
        int count[26] = {};
        int left = 0;
        int maxLen = 0;

        for (int right = 0; right < static_cast<int>(s.size()); ++right) {
            ++count[s[right] - 'A'];
            int maxCount = *std::max_element(count, count + 26);

            while (right - left + 1 - maxCount > k) {
                --count[s[left] - 'A'];
                ++left;
                maxCount = *std::max_element(count, count + 26);
            }

            maxLen = std::max(maxLen, right - left + 1);
        }

        return maxLen;
    }
};
