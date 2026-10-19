#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <set>
#include <string>
#include <vector>

#include "solution.cpp"

using Board = std::vector<std::vector<char>>;

// Independent oracle: find each word using a separate visited grid, no trie.
bool follows(const Board& board, const std::string& word, int r, int c,
             int pos, std::vector<std::vector<bool>>& used) {
    if (r < 0 || r >= static_cast<int>(board.size()) || c < 0 ||
        c >= static_cast<int>(board[0].size()) || used[r][c] ||
        board[r][c] != word[pos]) {
        return false;
    }
    if (pos + 1 == static_cast<int>(word.size())) return true;

    used[r][c] = true;
    bool found = follows(board, word, r - 1, c, pos + 1, used) ||
                 follows(board, word, r + 1, c, pos + 1, used) ||
                 follows(board, word, r, c - 1, pos + 1, used) ||
                 follows(board, word, r, c + 1, pos + 1, used);
    used[r][c] = false;
    return found;
}

std::vector<std::string> expectedWords(
    const Board& board, const std::vector<std::string>& words) {
    std::vector<std::string> expected;
    for (const auto& word : words) {
        bool found = false;
        std::vector<std::vector<bool>> used(
            board.size(), std::vector<bool>(board[0].size(), false));
        for (int r = 0; r < static_cast<int>(board.size()) && !found; ++r) {
            for (int c = 0; c < static_cast<int>(board[0].size()) && !found; ++c) {
                found = follows(board, word, r, c, 0, used);
            }
        }
        if (found) expected.push_back(word);
    }
    std::sort(expected.begin(), expected.end());
    return expected;
}

void check(Solution& solution, Board board, std::vector<std::string> words,
           std::vector<std::string> expected) {
    const Board originalBoard = board;
    const auto originalWords = words;
    auto actual = solution.findWords(board, words);
    std::sort(actual.begin(), actual.end());
    std::sort(expected.begin(), expected.end());
    assert(actual == expected); // Also catches duplicate answers.
    assert(board == originalBoard);
    assert(words == originalWords);
}

int main() {
    Solution solution;
    check(solution,
          {{'a', 'b', 'c', 'd'}, {'s', 'a', 'a', 't'},
           {'a', 'c', 'k', 'e'}, {'a', 'c', 'd', 'n'}},
          {"bat", "cat", "back", "backend", "stack"},
          {"cat", "back", "backend"});
    check(solution,
          {{'o', 'a', 'a', 'n'}, {'e', 't', 'a', 'e'},
           {'i', 'h', 'k', 'r'}, {'i', 'f', 'l', 'v'}},
          {"oath", "pea", "eat", "rain"}, {"oath", "eat"});
    check(solution, {{'a', 'b'}, {'c', 'd'}},
          {"abcb", "ad", "abdc"}, {"abdc"});
    check(solution, {{'a', 'a'}, {'a', 'a'}},
          {"a", "aa", "aaa", "aaaa", "aaaaa"},
          {"a", "aa", "aaa", "aaaa"});
    check(solution, {{'a'}}, {"a", "b", "aa"}, {"a"});
    check(solution, {{'a', 'b', 'c'}},
          {"a", "ab", "abc", "cba", "aba", "ac"},
          {"a", "ab", "abc", "cba"});
    check(solution, {{'a'}, {'b'}, {'c'}}, {"abc", "cba", "ac"},
          {"abc", "cba"});
    check(solution, {{'a', 'b'}, {'a', 'c'}},
          {"acb", "abc", "aba", "aac", "aab"}, {"acb", "abc", "aac", "aab"});
    check(solution, {{'z'}}, {"a", "cat"}, {});
    check(solution, {}, {"a"}, {});
    check(solution, {{'a'}}, {}, {});

    std::mt19937 random(212);
    for (int trial = 0; trial < 300; ++trial) {
        int rows = 1 + random() % 4;
        int cols = 1 + random() % 4;
        Board board(rows, std::vector<char>(cols));
        for (auto& row : board) {
            for (char& ch : row) ch = static_cast<char>('a' + random() % 3);
        }

        std::set<std::string> uniqueWords;
        for (int i = 0; i < 30; ++i) {
            std::string word(1 + random() % 6, 'a');
            for (char& ch : word) ch = static_cast<char>('a' + random() % 4);
            uniqueWords.insert(word);
        }
        std::vector<std::string> words(uniqueWords.begin(), uniqueWords.end());
        check(solution, board, words, expectedWords(board, words));
    }

    std::cout << "All Word Search II tests passed (including 300 random boards).\n";
}
