#include <cassert>
#include "solution.cpp"

void check(std::vector<std::vector<char>> grid, int expected) {
    Solution solution;
    assert(solution.numIslands(grid) == expected);
    for (const auto& row : grid) {
        for (char cell : row) assert(cell == '0');
    }
    assert(solution.numIslands(grid) == 0);
}

int main() {
    check({
        {'1', '1', '1', '1', '0'},
        {'1', '1', '0', '1', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '0', '0', '0'}
    }, 1);
    check({
        {'1', '1', '0', '0', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '1', '0', '0'},
        {'0', '0', '0', '1', '1'}
    }, 3);
    check({{'1', '0'}, {'0', '1'}}, 2); // Diagonal contact is not connected.
    check({{'1', '1'}, {'1', '1'}}, 1); // A cycle must not revisit cells.
    check({{'1', '1', '0', '1'}}, 2);
    check({{'1'}, {'0'}, {'1'}, {'1'}}, 2);
    check({{'1'}}, 1);
    check({{'0'}}, 0);
    check({{'0', '0'}, {'0', '0'}}, 0);
    check({}, 0);
    check({{}}, 0);
}
