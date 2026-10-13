#pragma once

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    explicit TreeNode(int value = 0, TreeNode* leftNode = nullptr,
                      TreeNode* rightNode = nullptr)
        : val(value), left(leftNode), right(rightNode) {}
};
