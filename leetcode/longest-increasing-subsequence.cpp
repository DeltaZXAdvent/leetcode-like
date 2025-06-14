/**
 * https://leetcode.cn/problems/longest-increasing-subsequence/?envType=study-plan-v2&envId=top-100-liked
 */
#include <bits/stdc++.h>
#include "print.h"
static_assert(sizeof(int) * CHAR_BIT >= 32);
using llong = long long;
using namespace std;
#define DUMP(x) (string(#x) + ": " + to_string(x))
#define FOR2(i, a, b) for (int i = a; i < b; ++i)

// better use greedy(?) + binary search
class Solution {
public:
    int lengthOfLIS(const vector<int>& nums) {
        int n = nums.size();
        auto dp = vector<int>();
        dp.reserve(n);
        int maxlen = 1;
        for (int i = 0; i < n; ++i) {
            int len = 1;
            for (int j = 0; j < i; ++j) {
                if (nums[j] < nums[i])
                    len = max(len, 1 + dp[j]);
            }
            dp[i] = len;
            maxlen = max(maxlen, len);
        }
        return maxlen;
    }
};

int main() {
    cout << DUMP(Solution().lengthOfLIS(vector<int>{10,9,2,5,3,7,101,18})) << '\n'
         << DUMP(Solution().lengthOfLIS(vector<int>{0,1,0,3,2,3})) << '\n'
         << DUMP(Solution().lengthOfLIS(vector<int>{7,7,7,7,7,7,7})) << '\n';
    return 0;
}
