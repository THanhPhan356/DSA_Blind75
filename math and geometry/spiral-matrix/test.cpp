#include <cassert>
#include <vector>

#include "solution.cpp"
#define Solution BoundarySolution
#include "solution-boundaries.cpp"
#undef Solution

void check(std::vector<std::vector<int>> matrix, const std::vector<int>& expected) {
    const auto original = matrix;
    Solution visited;
    BoundarySolution boundaries;

    assert(visited.spiralOrder(matrix) == expected);
    assert(matrix == original);
    assert(boundaries.spiralOrder(matrix) == expected);
    assert(matrix == original);
    assert(visited.spiralOrder(matrix) == expected);
    assert(boundaries.spiralOrder(matrix) == expected);
}

int main() {
    check({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}, {1, 2, 3, 6, 9, 8, 7, 4, 5});
    check({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}},
          {1, 2, 3, 4, 8, 12, 11, 10, 9, 5, 6, 7});
    check({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}},
          {1, 2, 3, 4, 8, 12, 16, 15, 14, 13, 9, 5, 6, 7, 11, 10});
    check({{1, 2}, {3, 4}, {5, 6}}, {1, 2, 4, 6, 5, 3});
    check({{1, 2, 3, 4}}, {1, 2, 3, 4});
    check({{1}, {2}, {3}, {4}}, {1, 2, 3, 4});
    check({{-7}}, {-7});
    check({{0, -1}, {-1, 0}}, {0, -1, 0, -1});
    check({}, {});
    check({{}}, {});
}
