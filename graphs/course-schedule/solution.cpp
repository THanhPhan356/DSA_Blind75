#include <vector>
using namespace std;

class Solution {
    bool dfs(int node, const vector<vector<int>>& graph,
             vector<int>& state) {
        if (state[node] == 1) return false; // A node on the active path forms a cycle.
        if (state[node] == 2) return true;

        state[node] = 1;

        for (int next : graph[node]) {
            if (!dfs(next, graph, state)) return false;
        }

        state[node] = 2;
        return true;
    }

public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph(numCourses);
        vector<int> state(numCourses, 0);

        for (const auto& p : prerequisites) {
            graph[p[1]].push_back(p[0]);
        }

        for (int i = 0; i < numCourses; ++i) {
            if (state[i] == 0 && !dfs(i, graph, state)) {
                return false;
            }
        }

        return true;
    }
};
