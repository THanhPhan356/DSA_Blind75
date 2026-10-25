#include <cassert>

#include "solution.cpp"

int main() {
    Solution solution;
    std::vector<std::vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const auto original = matrix;
    solution.rotate(matrix);
    assert((matrix == std::vector<std::vector<int>>{{7, 4, 1}, {8, 5, 2}, {9, 6, 3}}));

    for (int turn = 0; turn < 3; ++turn) solution.rotate(matrix);
    assert(matrix == original);

    matrix = {{1, 2}, {3, 4}};
    solution.rotate(matrix);
    assert((matrix == std::vector<std::vector<int>>{{3, 1}, {4, 2}}));

    matrix = {{-7}};
    solution.rotate(matrix);
    assert((matrix == std::vector<std::vector<int>>{{-7}}));

    matrix = {{0, -1}, {-1, 0}};
    solution.rotate(matrix);
    assert((matrix == std::vector<std::vector<int>>{{-1, 0}, {0, -1}}));
}
