/**
 * https://leetcode.cn/problems/coin-change/?envType=study-plan-v2&envId=top-100-liked
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
    int coinChange(const vector<int>& coins, int amount) {
        auto dp = vector<int>();
        dp.reserve(amount + 1);
        dp.push_back(0);
        for (int i = 1; i <= amount; ++i) {
            int minct = INT_MAX;
            for (auto& coin: coins) {
                if (i - coin >= 0 && dp[i - coin] >= 0) {
                    // cerr << DUMP(i) << ' ' << DUMP(coin)
                    //      << ' ' << DUMP(dp[i - coin]) << '\n';
                    minct = min(minct, 1 + dp[i - coin]);
                }
            }
            dp.push_back(minct == INT_MAX ? -1 : minct);
            // cerr << DUMP(minct == INT_MAX ? -1 : minct) << '\n';
        }
        // PRINT1(cerr, dp, ' ') << '\n';
        return dp[amount];
    }
};

int main() {
    cout << DUMP(Solution().coinChange(vector<int>{1,2,5}, 11)) << '\n'
         << DUMP(Solution().coinChange(vector<int>{2}, 3)) << '\n'
         << DUMP(Solution().coinChange(vector<int>{1}, 0)) << '\n';
    return 0;
}
