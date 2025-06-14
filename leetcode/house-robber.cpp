/**
 * https://leetcode.cn/problems/house-robber/description/?envType=study-plan-v2&envId=top-100-liked
 */
#include <bits/stdc++.h>
#include "print.h"
static_assert(sizeof(int) * CHAR_BIT >= 32);
using llong = long long;
using namespace std;
#define DUMP(x) (string(#x) + ": " + to_string(x))
#define FOR2(i, a, b) for (int i = a; i < b; ++i)

class Solution {
public:
    int rob(const vector<int>& nums) {
        int n = nums.size();
        int p = 0, q = 0;
        int r;
        for (int i = 0; i < n; ++i) {
            r = max(q, p + nums[i]);
            p = q;
            q = r;
        }
        return r;
    }
};

int main() {
    cout << DUMP(Solution().rob(vector<int>{1,2,3,1})) << '\n'
         << DUMP(Solution().rob(vector<int>{2,7,9,3,1})) << '\n';
    return 0;
}
