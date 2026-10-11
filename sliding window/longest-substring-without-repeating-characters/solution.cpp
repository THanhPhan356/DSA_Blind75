#include <algorithm>
#include <string>
#include <unordered_map>

class Solution {
public:
    int lengthOfLongestSubstring(std::string s) {
        std::unordered_map<char, int> lastSeen;
        int left = 0;
        int maxLen = 0;

        for (int right = 0; right < static_cast<int>(s.size()); ++right) {
            auto it = lastSeen.find(s[right]);

            if (it != lastSeen.end() && it->second >= left) {
                left = it->second + 1;
            }

            lastSeen[s[right]] = right;
            maxLen = std::max(maxLen, right - left + 1);
        }

        return maxLen;
    }
};
