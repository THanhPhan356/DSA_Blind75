#include <queue>
#include <utility>
#include <vector>

class Solution {
    void bfs(const std::vector<std::vector<int>>& heights,
             std::queue<std::pair<int, int>>& pending,
             std::vector<std::vector<bool>>& visited) {
        int rows = static_cast<int>(heights.size());
        int cols = static_cast<int>(heights[0].size());
        const int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        while (!pending.empty()) {
            auto [r, c] = pending.front();
            pending.pop();
            if (visited[r][c]) continue;
            visited[r][c] = true;

            for (const auto& direction : directions) {
                int nr = r + direction[0];
                int nc = c + direction[1];
                if (nr >= 0 && nr < rows && nc >= 0 && nc < cols &&
                    !visited[nr][nc] && heights[nr][nc] >= heights[r][c]) {
                    pending.push({nr, nc});
                }
            }
        }
    }

public:
    std::vector<std::vector<int>> pacificAtlantic(std::vector<std::vector<int>>& heights) {
        if (heights.empty() || heights[0].empty()) return {};

        int rows = static_cast<int>(heights.size());
        int cols = static_cast<int>(heights[0].size());
        std::vector<std::vector<bool>> pacific(rows, std::vector<bool>(cols, false));
        std::vector<std::vector<bool>> atlantic(rows, std::vector<bool>(cols, false));
        std::queue<std::pair<int, int>> pacificQueue, atlanticQueue;

        for (int r = 0; r < rows; ++r) {
            pacificQueue.push({r, 0});
            atlanticQueue.push({r, cols - 1});
        }
        for (int c = 0; c < cols; ++c) {
            pacificQueue.push({0, c});
            atlanticQueue.push({rows - 1, c});
        }

        bfs(heights, pacificQueue, pacific);
        bfs(heights, atlanticQueue, atlantic);

        std::vector<std::vector<int>> result;
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (pacific[r][c] && atlantic[r][c]) result.push_back({r, c});
            }
        }
        return result;
    }
};
