#include <algorithm>

#include "tree-node.h"

class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }

        int leftDepth = maxDepth(root->left);
        int rightDepth = maxDepth(root->right);

        return 1 + std::max(leftDepth, rightDepth);
    }
};
