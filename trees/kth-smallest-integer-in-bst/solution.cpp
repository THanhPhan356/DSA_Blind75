#include "tree-node.h"

class Solution {
    int count = 0;
    int answer = 0;

    void inorder(TreeNode* node, int k) {
        if (node == nullptr || count == k) {
            return;
        }

        inorder(node->left, k);
        if (count == k) {
            return;
        }

        ++count;
        if (count == k) {
            answer = node->val;
            return;
        }

        inorder(node->right, k);
    }

public:
    int kthSmallest(TreeNode* root, int k) {
        count = 0;
        answer = 0;
        inorder(root, k);
        return answer;
    }
};
