#include <string>

class Solution {
public:
    int countSubstrings(std::string s) {
        int n = static_cast<int>(s.size());
        int count = 0;

        for (int center = 0; center < n; ++center) {
            for (int offset = 0; offset <= 1; ++offset) {
                int left = center, right = center + offset;

                while (left >= 0 && right < n && s[left] == s[right]) {
                    ++count;
                    --left;
                    ++right;
                }
            }
        }

        return count;
    }
};
