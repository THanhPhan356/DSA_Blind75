#include <algorithm>
#include <string>
#include <vector>
using namespace std;

class Solution {
    bool dfs(int node, const vector<vector<int>>& graph,
             vector<int>& state, string& order) {
        if (state[node] == 1) return false;
        if (state[node] == 2) return true;

        state[node] = 1;

        for (int next : graph[node]) {
            if (!dfs(next, graph, state, order)) {
                return false;
            }
        }

        state[node] = 2;
        order.push_back('a' + node);
        return true;
    }

public:
    string alienOrder(vector<string>& words) {
        vector<vector<int>> graph(26);
        vector<int> state(26, -1); // -1: character is absent from the input.

        for (const string& word : words) {
            for (char c : word) {
                state[c - 'a'] = 0;
            }
        }

        for (int i = 1; i < static_cast<int>(words.size()); ++i) {
            const string& previous = words[i - 1];
            const string& current = words[i];

            size_t j = 0;
            size_t limit = min(previous.size(), current.size());

            while (j < limit && previous[j] == current[j]) {
                ++j;
            }

            if (j == limit) {
                if (previous.size() > current.size()) return "";
                continue;
            }

            graph[previous[j] - 'a'].push_back(current[j] - 'a');
        }

        string order;

        for (int node = 0; node < 26; ++node) {
            if (state[node] == 0) {
                if (!dfs(node, graph, state, order)) return "";
            }
        }

        reverse(order.begin(), order.end());
        return order;
    }
};
