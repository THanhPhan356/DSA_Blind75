#include "solution.cpp"

#include <iostream>
#include <vector>

bool sameTree(TreeNode* original, TreeNode* copy) {
    if (!original || !copy) return original == copy;
    return original != copy && original->val == copy->val &&
           sameTree(original->left, copy->left) &&
           sameTree(original->right, copy->right);
}

void destroy(TreeNode* root) {
    if (!root) return;
    destroy(root->left);
    destroy(root->right);
    delete root;
}

bool check(Codec& encoder, Codec& decoder, TreeNode* root,
           const std::string& expected) {
    const std::string data = encoder.serialize(root);
    if (data != expected) return false;
    TreeNode* copy = decoder.deserialize(data);
    const bool passed = sameTree(root, copy) && decoder.serialize(copy) == data;
    destroy(copy);
    return passed;
}

int main() {
    Codec encoder;
    Codec decoder;
    TreeNode zero(0), negative(-1000), positive(1000);
    TreeNode repeated(7), left(7, &repeated), right(7, nullptr, &repeated);
    TreeNode two(2), four(4), five(5), three(3, &four, &five);
    TreeNode sample(1, &two, &three);

    if (!check(encoder, decoder, nullptr, "# ") ||
        !check(encoder, decoder, &zero, "0 # # ") ||
        !check(encoder, decoder, &negative, "-1000 # # ") ||
        !check(encoder, decoder, &positive, "1000 # # ") ||
        !check(encoder, decoder, &left, "7 7 # # # ") ||
        !check(encoder, decoder, &right, "7 # 7 # # ") ||
        !check(encoder, decoder, &sample, "1 2 # # 3 4 # # 5 # # ")) {
        std::cerr << "Failed fixed round-trip case\n";
        return 1;
    }

    std::vector<TreeNode> balanced(10000);
    for (std::size_t i = 0; i < balanced.size(); ++i) {
        balanced[i].val = static_cast<int>(i % 2001) - 1000;
        if (2 * i + 1 < balanced.size()) balanced[i].left = &balanced[2 * i + 1];
        if (2 * i + 2 < balanced.size()) balanced[i].right = &balanced[2 * i + 2];
    }
    TreeNode* copy = decoder.deserialize(encoder.serialize(&balanced[0]));
    const bool balancedPassed = sameTree(&balanced[0], copy);
    destroy(copy);
    if (!balancedPassed) return 1;

    std::vector<TreeNode> chain(1000);
    for (std::size_t i = 1; i < chain.size(); ++i) {
        chain[i - 1].right = &chain[i];
    }
    copy = decoder.deserialize(encoder.serialize(&chain[0]));
    const bool chainPassed = sameTree(&chain[0], copy);
    destroy(copy);
    if (!chainPassed) return 1;

    std::cout << "Passed 9 round-trip cases, including 10000 nodes and a 1000-node chain\n";
}
