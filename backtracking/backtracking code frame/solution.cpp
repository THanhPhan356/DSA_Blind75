#include <vector>

// Define these variables and helpers for the problem being solved.
extern int n;
extern std::vector<int> choices;
bool valid(int choice);
void choose(int choice);
void undo(int choice);
void save_result();

void backtrack(int k) {
    if (k == n) {
        save_result();
        return;
    }

    for (auto choice : choices) {
        if (valid(choice)) {
            choose(choice);
            backtrack(k + 1);
            undo(choice);
        }
    }
}
