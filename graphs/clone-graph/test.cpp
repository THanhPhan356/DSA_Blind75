#include <cassert>
#include <unordered_set>
#include <vector>

class Node {
public:
    int val;
    std::vector<Node*> neighbors;

    explicit Node(int value) : val(value) {}
};

#include "solution.cpp"

void check(Solution& solution, const std::vector<std::vector<int>>& adjacency) {
    std::vector<Node*> original;
    for (int i = 0; i < static_cast<int>(adjacency.size()); ++i) {
        original.push_back(new Node(i + 1));
    }
    for (int i = 0; i < static_cast<int>(adjacency.size()); ++i) {
        for (int neighbor : adjacency[i]) {
            original[i]->neighbors.push_back(original[neighbor - 1]);
        }
    }

    Node* root = solution.cloneGraph(original.empty() ? nullptr : original[0]);
    if (original.empty()) {
        assert(root == nullptr);
        return;
    }

    std::unordered_set<Node*> source(original.begin(), original.end());
    std::unordered_set<Node*> unique;
    std::vector<Node*> copies(original.size(), nullptr);
    std::vector<int> pending = {0};
    copies[0] = root;
    for (std::size_t i = 0; i < pending.size(); ++i) {
        int index = pending[i];
        Node* copy = copies[index];
        assert(copy != nullptr && source.count(copy) == 0);
        assert(unique.insert(copy).second);
        assert(copy->val == original[index]->val);
        assert(copy->neighbors.size() == adjacency[index].size());
        assert(original[index]->neighbors.size() == adjacency[index].size());
        for (std::size_t j = 0; j < adjacency[index].size(); ++j) {
            int next = adjacency[index][j] - 1;
            assert(original[index]->neighbors[j] == original[next]);
            Node* neighbor = copy->neighbors[j];
            assert(neighbor != nullptr && source.count(neighbor) == 0);
            if (copies[next] == nullptr) {
                copies[next] = neighbor;
                pending.push_back(next);
            }
            assert(copies[next] == neighbor);
        }
    }
    assert(unique.size() == original.size());
    root->val = -1;
    root->neighbors.clear();
    assert(original[0]->val == 1);
    assert(original[0]->neighbors.size() == adjacency[0].size());

    for (Node* node : copies) delete node;
    for (Node* node : original) delete node;
}

int main() {
    Solution solution;
    check(solution, {});
    check(solution, {{}});
    check(solution, {{2}, {1}});
    check(solution, {{2, 4}, {1, 3}, {2, 4}, {1, 3}});
    check(solution, {{2, 3}, {1, 3}, {1, 2}});

    std::vector<std::vector<int>> chain(100);
    for (int i = 0; i < 99; ++i) {
        chain[i].push_back(i + 2);
        chain[i + 1].push_back(i + 1);
    }
    check(solution, chain);
}
