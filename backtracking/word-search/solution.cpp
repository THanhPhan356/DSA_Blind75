#include <string>
#include <vector>

class Solution {
    bool dfs(std::vector<std::vector<char>>& board, const std::string& word,
             int r, int c, int k) {
        if (r < 0 || r >= static_cast<int>(board.size()) ||
            c < 0 || c >= static_cast<int>(board[0].size()) ||
            board[r][c] != word[k]) {
            return false;
        }

        if (k == static_cast<int>(word.size()) - 1) return true;

        char saved = board[r][c];
        board[r][c] = '#'; // Prevent reuse within the current path.

        bool found = dfs(board, word, r + 1, c, k + 1) ||
                     dfs(board, word, r - 1, c, k + 1) ||
                     dfs(board, word, r, c + 1, k + 1) ||
                     dfs(board, word, r, c - 1, k + 1);

        board[r][c] = saved;
        return found;
    }

public:
    bool exist(std::vector<std::vector<char>>& board, std::string word) {
        if (word.empty()) return true;
        if (board.empty() || board[0].empty()) return false;

        for (int r = 0; r < static_cast<int>(board.size()); ++r) {
            for (int c = 0; c < static_cast<int>(board[0].size()); ++c) {
                if (board[r][c] == word[0] && dfs(board, word, r, c, 0)) {
                    return true;
                }
            }
        }
        return false;
    }
};
