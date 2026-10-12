#include <string>
#include <unordered_map>

class Solution {
public:
    std::string minWindow(std::string s, std::string t) {
        if (t.empty()) return "";

        std::unordered_map<char, int> need, window;
        for (char c : t) ++need[c];

        int left = 0, have = 0;
        int required = static_cast<int>(need.size());
        int bestStart = 0;
        int bestLen = static_cast<int>(s.size()) + 1;

        for (int right = 0; right < static_cast<int>(s.size()); ++right) {
            char c = s[right];
            ++window[c];

            if (need.count(c) && window[c] == need[c]) {
                ++have;
            }

            while (have == required) {
                int length = right - left + 1;
                if (length < bestLen) {
                    bestLen = length;
                    bestStart = left;
                }

                char removed = s[left++];
                --window[removed];

                if (need.count(removed) && window[removed] < need[removed]) {
                    --have;
                }
            }
        }

        return bestLen > static_cast<int>(s.size())
            ? ""
            : s.substr(bestStart, bestLen);
    }
};
