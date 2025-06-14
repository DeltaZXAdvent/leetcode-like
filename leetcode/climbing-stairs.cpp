/**
 * https://leetcode.cn/problems/climbing-stairs/?envType=study-plan-v2&envId=top-100-liked
 */
#include <bits/stdc++.h>
#include "print.h"
static_assert(sizeof(int) * CHAR_BIT >= 32);
using namespace std;
#define DUMP(x) (string(#x) + ": " + to_string(x))
#define FOR2(i, a, b) for (int i = a; i < b; ++i)
using llong = long long;

// no long long needed? (n <= 45)
// matrix multiplication is faster
class Solution {
public:
    int climbStairs(int n) {
        assert(n >= 1);
        auto dp = vector<llong>(n + 1);
        dp[0] = dp[1] = 1;
        for (int i = 2; i < dp.size(); ++i)
            dp[i] = dp[i - 1] + dp[i - 2];
        return dp[n];
    }
};

int main() {
    return 0;
}
