#include <vector>

class Solution {
    void dfs(std::vector<std::vector<char>>& grid, int r, int c) {
        if (r < 0 || r >= static_cast<int>(grid.size()) ||
            c < 0 || c >= static_cast<int>(grid[0].size()) ||
            grid[r][c] != '1') {
            return;
        }

        grid[r][c] = '0'; // Mark before exploring to prevent revisiting this cell.
        dfs(grid, r + 1, c);
        dfs(grid, r - 1, c);
        dfs(grid, r, c + 1);
        dfs(grid, r, c - 1);
    }

public:
    int numIslands(std::vector<std::vector<char>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;

        int islands = 0;
        for (int r = 0; r < static_cast<int>(grid.size()); ++r) {
            for (int c = 0; c < static_cast<int>(grid[0].size()); ++c) {
                if (grid[r][c] == '1') {
                    ++islands;
                    dfs(grid, r, c);
                }
            }
        }
        return islands;
    }
};
