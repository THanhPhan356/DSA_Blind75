#include <unordered_map>
#include <vector>

#include "tree-node.h"

class Solution {
    std::unordered_map<int, int> position;
    int preIndex = 0;

    TreeNode* build(std::vector<int>& preorder, int left, int right) {
        if (left > right) {
            return nullptr;
        }

        int value = preorder[preIndex++];
        TreeNode* root = new TreeNode(value);
        int mid = position[value];

        root->left = build(preorder, left, mid - 1);
        root->right = build(preorder, mid + 1, right);

        return root;
    }

public:
    TreeNode* buildTree(std::vector<int>& preorder, std::vector<int>& inorder) {
        preIndex = 0;
        position.clear();

        for (int i = 0; i < static_cast<int>(inorder.size()); ++i) {
            position[inorder[i]] = i;
        }

        return build(preorder, 0, static_cast<int>(inorder.size()) - 1);
    }
};
