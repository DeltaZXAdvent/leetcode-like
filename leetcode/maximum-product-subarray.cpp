/**
 * https://leetcode.cn/problems/maximum-product-subarray/description/?envType=study-plan-v2&envId=top-100-liked
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
    int maxProduct(const vector<int>& nums) {
        int n = nums.size();
        auto dp = vector<pair<int, int>>();
        dp.reserve(n);
        dp.push_back(make_pair(nums[0], nums[0]));
        int res = nums[0];
        // dp can be omitted
        for (int i = 1; i < n; ++i) {
            auto p = dp[i - 1].first * nums[i];
            auto q = dp[i - 1].second * nums[i];
            dp.push_back(make_pair(min(min(p, q), nums[i]), max(max(p, q), nums[i])));
            res = max(res, max(max(p, q), nums[i]));
        }
        return res;
    }
};

int main() {
    cout << DUMP(Solution().maxProduct({2,3,-2,4})) << '\n'
         << DUMP(Solution().maxProduct({-2,0,-1})) << '\n';
    return 0;
}
