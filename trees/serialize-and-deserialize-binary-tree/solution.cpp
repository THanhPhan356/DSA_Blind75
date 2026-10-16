#include <sstream>
#include <string>

#include "tree-node.h"

class Codec {
private:
    // shortcut: recursive DFS needs O(h) stack; use iterative traversal for very deep trees.
    void encode(TreeNode* node, std::ostringstream& output) {
        if (node == nullptr) {
            output << "# ";
            return;
        }

        output << node->val << ' ';
        encode(node->left, output);
        encode(node->right, output);
    }

    // shortcut: decode expects serialize's output; validate before accepting external input.
    TreeNode* decode(std::istringstream& input) {
        std::string token;
        input >> token;
        if (token == "#") {
            return nullptr;
        }

        TreeNode* node = new TreeNode(std::stoi(token));
        node->left = decode(input);
        node->right = decode(input);
        return node;
    }

public:
    std::string serialize(TreeNode* root) {
        std::ostringstream output;
        encode(root, output);
        return output.str();
    }

    TreeNode* deserialize(std::string data) {
        std::istringstream input(data);
        return decode(input);
    }
};
