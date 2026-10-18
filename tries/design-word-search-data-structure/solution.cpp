#include <string>

class WordDictionary {
private:
    struct Node {
        Node* children[26]{};
        bool isEnd = false;
    };

    Node* root;

    bool dfs(Node* node, const std::string& word, int pos) {
        if (pos == static_cast<int>(word.size())) {
            return node->isEnd;
        }

        if (word[pos] == '.') {
            for (Node* child : node->children) {
                if (child != nullptr && dfs(child, word, pos + 1)) {
                    return true;
                }
            }
            return false;
        }

        int index = word[pos] - 'a';
        Node* child = node->children[index];

        return child != nullptr && dfs(child, word, pos + 1);
    }

public:
    WordDictionary() {
        root = new Node();
    }

    void addWord(std::string word) {
        Node* current = root;

        for (char c : word) {
            int index = c - 'a';

            if (current->children[index] == nullptr) {
                current->children[index] = new Node();
            }

            current = current->children[index];
        }

        current->isEnd = true;
    }

    bool search(std::string word) {
        return dfs(root, word, 0);
    }
};
