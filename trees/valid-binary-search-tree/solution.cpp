#include <climits>

#include "tree-node.h"

class Solution {
    bool check(TreeNode* node, long long lower, long long upper) {
        if (node == nullptr) {
            return true;
        }

        if (node->val <= lower || node->val >= upper) {
            return false;
        }

        return check(node->left, lower, node->val)
            && check(node->right, node->val, upper);
    }

public:
    bool isValidBST(TreeNode* root) {
        return check(root, LLONG_MIN, LLONG_MAX);
    }
};
