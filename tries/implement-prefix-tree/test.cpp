#include <cassert>
#include <iostream>
#include <random>
#include <set>
#include <string>

#include "solution.cpp"

int main() {
    PrefixTree trie;
    assert(!trie.search("car"));
    assert(!trie.startsWith("c"));

    trie.insert("care");
    assert(trie.search("care"));
    assert(!trie.search("car"));
    assert(trie.startsWith("car"));
    assert(!trie.startsWith("careful"));

    trie.insert("car");
    trie.insert("cat");
    trie.insert("car");
    assert(trie.search("car"));
    assert(trie.search("care"));
    assert(trie.search("cat"));
    assert(!trie.search("ca"));
    assert(trie.startsWith("ca"));
    assert(!trie.search("cart"));

    for (char c = 'a'; c <= 'z'; ++c) {
        const std::string word(1, c);
        trie.insert(word);
        assert(trie.search(word));
        assert(trie.startsWith(word));
    }

    const std::string longest(1000, 'z');
    const std::string shorter(999, 'z');
    trie.insert(longest);
    assert(trie.search(longest));
    assert(trie.startsWith(shorter));
    assert(!trie.search(shorter));
    trie.insert(shorter);
    assert(trie.search(shorter));
    assert(trie.search(longest));

    PrefixTree other;
    assert(!other.search("car"));
    assert(!other.startsWith("c"));
    other.insert("dog");
    assert(other.search("dog"));
    assert(!trie.search("dog"));

    PrefixTree randomTrie;
    std::set<std::string> words;
    std::mt19937 random(208);
    for (int step = 0; step < 1200; ++step) {
        std::string word(1 + random() % 10, 'a');
        for (char& c : word) {
            c = static_cast<char>('a' + random() % 5);
        }

        if (step % 3 == 0) {
            randomTrie.insert(word);
            words.insert(word);
        }

        assert(randomTrie.search(word) == (words.count(word) != 0));
        const std::string prefix = word.substr(0, 1 + random() % word.size());
        bool expectedPrefix = false;
        for (const std::string& stored : words) {
            if (stored.compare(0, prefix.size(), prefix) == 0) {
                expectedPrefix = true;
                break;
            }
        }
        assert(randomTrie.startsWith(prefix) == expectedPrefix);
    }

    std::cout << "All Trie tests passed (including 1200 randomized operations).\n";
}
