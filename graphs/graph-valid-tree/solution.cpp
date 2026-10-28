#include <vector>
using namespace std;

class Solution {
    bool dfs(int node, int parent,
             const vector<vector<int>>& graph,
             vector<bool>& visited) {
        visited[node] = true;

        for (int next : graph[node]) {
            if (next == parent) continue;

            if (visited[next]) return false;

            if (!dfs(next, node, graph, visited)) {
                return false;
            }
        }

        return true;
    }

public:
    bool validTree(int n, vector<vector<int>>& edges) {
        vector<vector<int>> graph(n);
        vector<bool> visited(n, false);

        for (const auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }

        if (!dfs(0, -1, graph, visited)) return false;

        for (bool seen : visited) {
            if (!seen) return false;
        }

        return true;
    }
};
