#include <cassert>
#include "solution.cpp"

void check(std::vector<std::vector<int>> heights,
           const std::vector<std::vector<int>>& expected) {
    const auto original = heights;
    Solution solution;
    assert(solution.pacificAtlantic(heights) == expected);
    assert(heights == original);
    assert(solution.pacificAtlantic(heights) == expected);
}

int main() {
    check({{1, 2, 2, 3, 5},
           {3, 2, 3, 4, 4},
           {2, 4, 5, 3, 1},
           {6, 7, 1, 4, 5},
           {5, 1, 1, 2, 4}},
          {{0, 4}, {1, 3}, {1, 4}, {2, 2}, {3, 0}, {3, 1}, {4, 0}});
    check({{7}}, {{0, 0}});
    check({{3, 1, 2}}, {{0, 0}, {0, 1}, {0, 2}});
    check({{3}, {1}, {2}}, {{0, 0}, {1, 0}, {2, 0}});
    check({{1, 2}, {3, 4}}, {{0, 1}, {1, 0}, {1, 1}});
    check({{9, 9, 9}, {9, 1, 9}, {9, 9, 9}},
          {{0, 0}, {0, 1}, {0, 2}, {1, 0}, {1, 2}, {2, 0}, {2, 1}, {2, 2}});
    check({}, {});
    check({{}}, {});

    std::vector<std::vector<int>> plateau(200, std::vector<int>(200, 5));
    std::vector<std::vector<int>> expected;
    for (int r = 0; r < 200; ++r) {
        for (int c = 0; c < 200; ++c) expected.push_back({r, c});
    }
    check(plateau, expected);
}
