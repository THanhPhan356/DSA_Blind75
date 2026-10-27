#include <unordered_map>

// Node is provided by the judge; test.cpp defines it for local checks.
class Solution {
private:
    Node* dfs(Node* node, std::unordered_map<Node*, Node*>& copies) {
        if (node == nullptr) return nullptr;
        if (copies.count(node)) return copies[node];

        Node* copy = new Node(node->val);
        copies[node] = copy;
        for (Node* neighbor : node->neighbors) {
            copy->neighbors.push_back(dfs(neighbor, copies));
        }
        return copy;
    }

public:
    Node* cloneGraph(Node* node) {
        std::unordered_map<Node*, Node*> copies;
        return dfs(node, copies);
    }
};
