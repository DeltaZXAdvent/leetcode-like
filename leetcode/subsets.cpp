/**
 * https://leetcode.cn/problems/subsets/description/?envType=study-plan-v2&envId=top-100-liked
 */
#include <bits/stdc++.h>
#include "print.h"
static_assert(sizeof(int) * CHAR_BIT >= 32);
using namespace std;
#define DUMP(x) (string(#x) + ": " + to_string(x))
#define FOR2(i, a, b) for (int i = a; i < b; ++i)

class Solution {
public:
    vector<vector<int>> subsets(const vector<int>& nums) {
        const int n = nums.size();
        vector<vector<int>> out;
        out.reserve(2 << n);
        vector<int> cur;
        int first = 0;
        cur.reserve(n);
        backtrack(nums, first, cur, out);
        return out;
    }
private:
    void backtrack(const vector<int>& nums, int& first, vector<int>& cur, vector<vector<int>>& out) {
        int n = nums.size();
        if (first == n) {
            out.push_back(cur);
            return;
        }
        ++first;
        backtrack(nums, first, cur, out);
        --first;
        cur.push_back(nums[first]);
        ++first;
        backtrack(nums, first, cur, out);
        cur.pop_back();
        --first;
    }
};

int main() {
    auto res = Solution().subsets(vector<int>{1,2,3});
    print(cout, res, '\n', ' ')
        << '\n'
        << DUMP(res.size()) << '\n';
    return 0;
}
