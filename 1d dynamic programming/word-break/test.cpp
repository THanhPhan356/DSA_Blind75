#include <cassert>
#include <random>
#include "solution.cpp"

bool bruteForce(const std::string& s, const std::vector<std::string>& words,
                int start = 0) {
    if (start == static_cast<int>(s.size())) return true;
    for (const auto& word : words) {
        if (s.compare(start, word.size(), word) == 0 &&
            bruteForce(s, words, start + static_cast<int>(word.size()))) {
            return true;
        }
    }
    return false;
}

int main() {
    Solution solution;
    auto check = [&](std::string s, std::vector<std::string> words, bool expected) {
        const auto original = words;
        assert(solution.wordBreak(s, words) == expected);
        assert(words == original);
    };

    check("leetcode", {"leet", "code"}, true);
    check("applepenapple", {"apple", "pen"}, true);
    check("catsandog", {"cats", "dog", "sand", "and", "cat"}, false);
    check("cars", {"car", "ca", "rs"}, true);
    check("a", {"a"}, true);
    check("a", {"b", "aa"}, false);
    check("aaaaaaa", {"aaaa", "aaa"}, true);
    check("ab", {"a"}, false);
    check(std::string(300, 'a'), {"a", "aa", "aaa"}, true);
    check(std::string(299, 'a') + "b", {"a", "aa", "aaa", "aaaa"}, false);

    std::mt19937 rng(139);
    const std::vector<std::string> pool = {"a", "b", "aa", "ab", "ba", "bb", "aba"};
    for (int trial = 0; trial < 1000; ++trial) {
        std::string s(1 + rng() % 9, 'a');
        for (char& ch : s) ch = static_cast<char>('a' + rng() % 2);
        std::vector<std::string> words;
        for (const auto& word : pool) {
            if (rng() % 2) words.push_back(word);
        }
        if (words.empty()) words.push_back("a");
        check(s, words, bruteForce(s, words));
    }
}
