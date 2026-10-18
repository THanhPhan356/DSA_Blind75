#include <cassert>
#include <iostream>
#include <iterator>
#include <random>
#include <set>
#include <string>

#include "solution.cpp"

bool expectedMatch(const std::set<std::string>& words,
                   const std::string& pattern) {
    for (const std::string& word : words) {
        if (word.size() != pattern.size()) {
            continue;
        }

        bool matches = true;
        for (std::size_t i = 0; i < word.size(); ++i) {
            if (pattern[i] != '.' && pattern[i] != word[i]) {
                matches = false;
                break;
            }
        }

        if (matches) {
            return true;
        }
    }
    return false;
}

int main() {
    WordDictionary dictionary;
    assert(!dictionary.search("cat"));
    assert(!dictionary.search("."));

    dictionary.addWord("bad");
    dictionary.addWord("dad");
    dictionary.addWord("mad");
    assert(!dictionary.search("pad"));
    assert(dictionary.search("bad"));
    assert(dictionary.search(".ad"));
    assert(dictionary.search("b.."));
    assert(dictionary.search("..d"));
    assert(!dictionary.search("ba"));
    assert(!dictionary.search("b."));
    assert(!dictionary.search("bad."));
    assert(!dictionary.search(".az"));

    WordDictionary branching;
    branching.addWord("cap");
    branching.addWord("cut");
    assert(branching.search("c.t"));
    assert(branching.search(".ap"));
    assert(branching.search("c.."));
    assert(!branching.search("c.z"));
    assert(!branching.search("c."));
    assert(!branching.search("c.t."));
    assert(branching.search("cap"));

    branching.addWord("care");
    assert(!branching.search("car"));
    assert(branching.search("ca."));  // "cap" is already stored.
    branching.addWord("car");
    branching.addWord("car");
    assert(branching.search("car"));
    assert(branching.search("ca."));
    assert(branching.search("care"));
    assert(branching.search("ca.."));
    assert(!branching.search("cart"));

    WordDictionary alphabet;
    for (char c = 'a'; c <= 'z'; ++c) {
        alphabet.addWord(std::string(1, c));
        assert(alphabet.search(std::string(1, c)));
    }
    assert(alphabet.search("."));
    assert(!alphabet.search(".."));

    const std::string longest(25, 'z');
    alphabet.addWord(longest);
    assert(alphabet.search(longest));
    std::string pattern = longest;
    pattern.front() = '.';
    pattern.back() = '.';
    assert(alphabet.search(pattern));
    assert(!alphabet.search(std::string(24, 'z')));
    assert(!alphabet.search("bad"));
    assert(!dictionary.search("z"));

    WordDictionary randomDictionary;
    std::set<std::string> words;
    std::mt19937 random(211);
    for (int step = 0; step < 1200; ++step) {
        std::string word(1 + random() % 25, 'a');
        for (char& c : word) {
            c = static_cast<char>('a' + random() % 5);
        }

        if (step % 3 == 0) {
            randomDictionary.addWord(word);
            words.insert(word);
        }

        assert(randomDictionary.search(word) == expectedMatch(words, word));

        std::string query = word;
        const unsigned int dots = random() % 3;
        for (unsigned int i = 0; i < dots; ++i) {
            query[random() % query.size()] = '.';
        }
        assert(randomDictionary.search(query) == expectedMatch(words, query));

        if (!words.empty()) {
            auto it = words.begin();
            std::advance(it, random() % words.size());
            query = *it;
            query[random() % query.size()] = '.';
            query[random() % query.size()] = '.';
            assert(randomDictionary.search(query));
        }
    }

    std::cout << "All WordDictionary tests passed (including 1200 randomized operations).\n";
}
