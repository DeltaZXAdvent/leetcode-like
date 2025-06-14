/**
 * https://leetcode.cn/problems/combination-sum/?envType=study-plan-v2&envId=top-100-liked
 */
#include <bits/stdc++.h>
#include "print.h"
static_assert(sizeof(int) * CHAR_BIT >= 32);
using namespace std;
#define DUMP(x) (string(#x) + ": " + to_string(x))
#define FOR2(i, a, b) for (int i = a; i < b; ++i)

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> out;
        vector<int> cur;
        backtrack(candidates, target, 0, cur, out);
        return out;
    }
    void backtrack(vector<int>& candidates, int target, int from, vector<int>& cur, vector<vector<int>>& out) {
        // PRINT1(cout, cur, ' ') << '\n';
        if (target == 0) {
            out.push_back(cur);
            return;
        }
        if (from == candidates.size()) return;
        if (candidates[from] <= target) {
            cur.push_back(candidates[from]);
            backtrack(candidates, target - candidates[from], from, cur, out);
            cur.pop_back();
        }
        backtrack(candidates, target, from + 1, cur, out);
    }
};

int main() {
    auto v = vector<int>{2,3,6,7};
    print(cout, Solution().combinationSum(v, 7), '\n', ' ') << '\n';
    return 0;
}
