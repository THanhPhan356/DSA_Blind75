#include <algorithm>
#include <string>
#include <vector>

class Solution {
private:
    struct Node {
        int next[26];
        int wordIndex = -1;

        Node() {
            std::fill(next, next + 26, -1);
        }
    };

    std::vector<Node> trie;
    std::vector<std::string> result;
    int rows = 0;
    int cols = 0;

    void dfs(std::vector<std::vector<char>>& board,
             const std::vector<std::string>& words,
             int r, int c, int parent) {
        if (r < 0 || r >= rows || c < 0 || c >= cols ||
            board[r][c] == '#') {
            return;
        }

        char ch = board[r][c];
        int letter = ch - 'a';
        int node = trie[parent].next[letter];

        if (node == -1) return;

        if (trie[node].wordIndex != -1) {
            result.push_back(words[trie[node].wordIndex]);
            trie[node].wordIndex = -1; // Report each word only once.
        }

        board[r][c] = '#';

        dfs(board, words, r - 1, c, node);
        dfs(board, words, r + 1, c, node);
        dfs(board, words, r, c - 1, node);
        dfs(board, words, r, c + 1, node);

        board[r][c] = ch; // Backtrack: make this cell available again.

        // Disconnect a branch only after all words below it are found.
        if (trie[node].wordIndex == -1) {
            bool hasChild = false;
            for (int child : trie[node].next) {
                if (child != -1) {
                    hasChild = true;
                    break;
                }
            }

            if (!hasChild) {
                trie[parent].next[letter] = -1;
            }
        }
    }

public:
    std::vector<std::string> findWords(std::vector<std::vector<char>>& board,
                                     std::vector<std::string>& words) {
        result.clear();
        trie.clear();
        trie.emplace_back(); // Root is node 0.

        if (board.empty() || board[0].empty()) return result;

        rows = static_cast<int>(board.size());
        cols = static_cast<int>(board[0].size());

        for (int i = 0; i < static_cast<int>(words.size()); ++i) {
            int node = 0;

            for (char ch : words[i]) {
                int letter = ch - 'a';

                if (trie[node].next[letter] == -1) {
                    int newNode = static_cast<int>(trie.size());
                    trie[node].next[letter] = newNode;
                    trie.emplace_back();
                }

                node = trie[node].next[letter];
            }

            trie[node].wordIndex = i;
        }

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                dfs(board, words, r, c, 0);
            }
        }

        return result;
    }
};
