#include <vector>

class Solution {
public:
    std::vector<int> spiralOrder(std::vector<std::vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return {};

        int top = 0, bottom = static_cast<int>(matrix.size()) - 1;
        int left = 0, right = static_cast<int>(matrix[0].size()) - 1;
        std::vector<int> result;

        while (top <= bottom && left <= right) {
            for (int col = left; col <= right; ++col) result.push_back(matrix[top][col]);
            ++top;

            for (int row = top; row <= bottom; ++row) result.push_back(matrix[row][right]);
            --right;

            if (top <= bottom) {
                for (int col = right; col >= left; --col) result.push_back(matrix[bottom][col]);
                --bottom;
            }

            if (left <= right) {
                for (int row = bottom; row >= top; --row) result.push_back(matrix[row][left]);
                ++left;
            }
        }

        return result;
    }
};
