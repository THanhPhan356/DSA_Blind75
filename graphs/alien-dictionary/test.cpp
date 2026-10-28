#include <cassert>
#include "solution.cpp"

void check(Solution& solution, vector<string> words, bool possible) {
    const auto original = words;
    const string order = solution.alienOrder(words);
    assert(words == original);

    if (!possible) {
        assert(order.empty());
        return;
    }

    vector<bool> present(26, false);
    for (const string& word : words) {
        for (char c : word) present[c - 'a'] = true;
    }

    vector<int> rank(26, -1);
    for (int i = 0; i < static_cast<int>(order.size()); ++i) {
        const char c = order[i];
        assert(c >= 'a' && c <= 'z');
        assert(present[c - 'a'] && rank[c - 'a'] == -1);
        rank[c - 'a'] = i;
    }
    for (int i = 0; i < 26; ++i) {
        assert(present[i] == (rank[i] != -1));
    }

    // Validate the original dictionary under the returned alphabet, not one fixed order.
    for (size_t i = 1; i < words.size(); ++i) {
        assert(!lexicographical_compare(
            words[i].begin(), words[i].end(),
            words[i - 1].begin(), words[i - 1].end(),
            [&](char a, char b) { return rank[a - 'a'] < rank[b - 'a']; }));
    }
}

int main() {
    Solution solution;
    check(solution, {"wrt", "wrf", "er", "ett", "rftt"}, true);
    check(solution, {"ab", "ac", "bc"}, true);
    check(solution, {"z", "x"}, true);
    check(solution, {"z", "x", "z"}, false);
    check(solution, {"abc", "ab"}, false);
    check(solution, {"ab", "abc"}, true);
    check(solution, {"abc", "abc"}, true);
    check(solution, {"abc"}, true);
    check(solution, {"z"}, true);
    check(solution, {"ab", "ba"}, true);
    check(solution, {"za", "zb", "ca", "cb"}, true);
    check(solution, {"aa", "ab", "ba", "bc", "bd", "bc"}, false);
    check(solution, {"abcdefghijklmnopqrstuvwxyz"}, true);
    check(solution, {"a", "b", "c"}, true);
}
