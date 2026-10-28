#include <vector>
using namespace std;

class Solution {
    void dfs(int node, const vector<vector<int>>& graph,
             vector<bool>& visited) {
        visited[node] = true;

        for (int next : graph[node]) {
            if (!visited[next]) {
                dfs(next, graph, visited);
            }
        }
    }

public:
    int countComponents(int n, vector<vector<int>>& edges) {
        vector<vector<int>> graph(n);
        vector<bool> visited(n, false);

        for (const auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }

        int count = 0;

        for (int node = 0; node < n; ++node) {
            if (!visited[node]) {
                ++count;
                dfs(node, graph, visited);
            }
        }

        return count;
    }
};
