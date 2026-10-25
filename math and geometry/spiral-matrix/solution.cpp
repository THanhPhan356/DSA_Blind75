#include <vector>

class Solution {
public:
    std::vector<int> spiralOrder(std::vector<std::vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return {};

        int rows = static_cast<int>(matrix.size());
        int cols = static_cast<int>(matrix[0].size());
        std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
        std::vector<int> result;
        const int dr[] = {0, 1, 0, -1};
        const int dc[] = {1, 0, -1, 0};
        int row = 0, col = 0, direction = 0;

        for (int step = 0; step < rows * cols; ++step) {
            result.push_back(matrix[row][col]);
            visited[row][col] = true;

            int nextRow = row + dr[direction];
            int nextCol = col + dc[direction];
            if (nextRow < 0 || nextRow >= rows || nextCol < 0 || nextCol >= cols ||
                visited[nextRow][nextCol]) {
                direction = (direction + 1) % 4;
            }

            row += dr[direction];
            col += dc[direction];
        }

        return result;
    }
};
