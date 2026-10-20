#include <cassert>
#include "solution.cpp"

int n = 2;
std::vector<int> choices = {0, 1};
std::vector<int> path;
std::vector<std::vector<int>> results;

bool valid(int choice) {
    return path.empty() || path.back() != choice;
}

void choose(int choice) {
    path.push_back(choice);
}

void undo(int) {
    path.pop_back();
}

void save_result() {
    results.push_back(path);
}

int main() {
    backtrack(0);
    assert((results == std::vector<std::vector<int>>{{0, 1}, {1, 0}}));
    assert(path.empty());

    results.clear();
    n = 0;
    backtrack(0);
    assert((results == std::vector<std::vector<int>>{{}}));
    assert(path.empty());

    results.clear();
    n = 1;
    choices.clear();
    backtrack(0);
    assert(results.empty());
    assert(path.empty());
}
