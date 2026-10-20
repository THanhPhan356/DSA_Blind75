#include <vector>
using namespace std;

class Solution {
    void backtrack(const vector<int>& arr, int start, int remaining,
                   vector<int>& path, vector<vector<int>>& res) {
        if (remaining == 0) {
            res.push_back(path);
            return;
        }

        for (int i = start; i < static_cast<int>(arr.size()); ++i) {
            if (arr[i] > remaining) {
                continue;
            }

            path.push_back(arr[i]);
            backtrack(arr, i, remaining - arr[i], path, res);
            path.pop_back();
        }
    }

public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        vector<int> path;

        backtrack(candidates, 0, target, path, res);
        return res;
    }
};
