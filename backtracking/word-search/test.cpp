#include <cassert>
#include "solution.cpp"

void check(std::vector<std::vector<char>> board, const std::string& word,
           bool expected) {
    const auto original = board;
    Solution solution;
    assert(solution.exist(board, word) == expected);
    assert(board == original);
    assert(solution.exist(board, word) == expected);
    assert(board == original);
}

int main() {
    const std::vector<std::vector<char>> board = {
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'}
    };
    check(board, "ABCCED", true);
    check(board, "SEE", true);
    check(board, "ABCB", false); // Would reuse B.
    check(board, "Z", false);
    check({{'A', 'B'}, {'C', 'D'}}, "AD", false); // Diagonal.
    check({{'A', 'B'}, {'A', 'C'}}, "AC", true); // Later starting A.
    check({{'A', 'A', 'A'}, {'A', 'B', 'B'}}, "AAABB", true); // Retry a branch.
    check({{'A', 'B', 'C'}}, "CBA", true);
    check({{'A'}, {'B'}, {'C'}}, "ABC", true);
    check({{'A'}}, "A", true);
    check({{'A'}}, "AA", false);
    check({{'a'}}, "A", false);
    check({}, "A", false);
    check({{}}, "A", false);
    check({}, "", true);
}
