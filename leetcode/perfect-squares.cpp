/**
 * https://leetcode.cn/problems/perfect-squares/description/?envType=study-plan-v2&envId=top-100-liked
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
    int numSquares(int n) {
        auto dp = vector<int>(n + 1);
        dp[0] = 0;
        for (int i = 1; i < n + 1; ++i) {
            int minct = i;      // i is an upper bound
            for (int j = 1; j * j <= i; ++j) {
                minct = min(minct, 1 + dp[i - j * j]);
            }
            dp[i] = minct;
        }
        return dp[n];
    }
};

int main() {
    cout << DUMP(Solution().numSquares(12)) << '\n'
         << DUMP(Solution().numSquares(13)) << '\n';
    return 0;
}
