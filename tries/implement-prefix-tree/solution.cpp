#include <string>

class PrefixTree {
private:
    struct Node {
        Node* children[26]{};
        bool isEnd = false;
    };

    Node* root;

public:
    PrefixTree() {
        root = new Node();
    }

    void insert(std::string word) {
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
        Node* current = root;

        for (char c : word) {
            int index = c - 'a';

            if (current->children[index] == nullptr) {
                return false;
            }

            current = current->children[index];
        }

        return current->isEnd;
    }

    bool startsWith(std::string prefix) {
        Node* current = root;

        for (char c : prefix) {
            int index = c - 'a';

            if (current->children[index] == nullptr) {
                return false;
            }

            current = current->children[index];
        }

        return true;
    }
};
