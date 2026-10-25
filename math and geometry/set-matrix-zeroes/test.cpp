#include <cassert>
#include <climits>
#include "solution.cpp"

using Matrix = std::vector<std::vector<int>>;

// Read zeros only from the original matrix to avoid spreading new zeros.
Matrix expectedResult(const Matrix& original) {
    Matrix expected = original;
    int rows = static_cast<int>(original.size());
    int cols = rows == 0 ? 0 : static_cast<int>(original[0].size());
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (original[i][j] != 0) continue;
            for (int c = 0; c < cols; ++c) expected[i][c] = 0;
            for (int r = 0; r < rows; ++r) expected[r][j] = 0;
        }
    }
    return expected;
}

int main() {
    Solution solution;
    auto check = [&](Matrix matrix, const Matrix& expected) {
        solution.setZeroes(matrix);
        assert(matrix == expected);
    };

    check({{1, 1, 1}, {1, 0, 1}, {1, 1, 1}},
          {{1, 0, 1}, {0, 0, 0}, {1, 0, 1}});
    check({{0, 1, 2, 0}, {3, 4, 5, 2}, {1, 3, 1, 5}},
          {{0, 0, 0, 0}, {0, 4, 5, 0}, {0, 3, 1, 0}});
    check({{1, 0}, {3, 4}}, {{0, 0}, {3, 0}});
    check({{1, 2}, {0, 4}}, {{0, 2}, {0, 0}});
    check({{0, 2}, {3, 4}}, {{0, 0}, {0, 4}});
    check({{INT_MIN, 1}, {-1, INT_MAX}},
          {{INT_MIN, 1}, {-1, INT_MAX}});
    check({{1, 0, 3}}, {{0, 0, 0}});
    check({{1}, {0}, {3}}, {{0}, {0}, {0}});
    check({{0}}, {{0}});
    check({{7}}, {{7}});
    check({}, {});
    check({{}}, {{}});

    for (int rows = 1; rows <= 3; ++rows) {
        for (int cols = 1; cols <= 4; ++cols) {
            for (int mask = 0; mask < (1 << (rows * cols)); ++mask) {
                Matrix matrix(rows, std::vector<int>(cols, 1));
                for (int i = 0; i < rows; ++i) {
                    for (int j = 0; j < cols; ++j) {
                        if (mask & (1 << (i * cols + j))) matrix[i][j] = 0;
                    }
                }
                check(matrix, expectedResult(matrix));
            }
        }
    }

    Matrix large(200, std::vector<int>(200, 1));
    large[100][150] = 0;
    check(large, expectedResult(large));
}
