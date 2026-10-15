#include <algorithm>
#include <climits>

#include "tree-node.h"

class Solution {
private:
    int dfs(TreeNode* node, int& best) {
        if (node == nullptr) {
            return 0;
        }

        int left = std::max(0, dfs(node->left, best));
        int right = std::max(0, dfs(node->right, best));

        // A complete path can join both branches through this node.
        best = std::max(best, node->val + left + right);

        // Only one branch can be extended through the parent.
        return node->val + std::max(left, right);
    }

public:
    int maxPathSum(TreeNode* root) {
        int best = INT_MIN;
        dfs(root, best);
        return best;
    }
};
