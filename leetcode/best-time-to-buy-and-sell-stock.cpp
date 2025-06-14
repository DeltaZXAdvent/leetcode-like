/**
 * https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/?envType=study-plan-v2&envId=top-100-liked
 */
#include <bits/stdc++.h>
#include "print.h"
static_assert(sizeof(int) * CHAR_BIT >= 32);
using namespace std;
#define DUMP(x) (string(#x) + ": " + to_string(x))
#define FOR2(i, a, b) for (int i = a; i < b; ++i)

class Solution {
public:
    int maxProfit(const vector<int>& prices) {
        int n = prices.size(), maxsell = 0, best = 0;
        for (int buy = n - 2; buy >= 0; --buy) {
            maxsell = max(maxsell, prices[buy + 1]);
            best = max(best, maxsell - prices[buy]);
        }
        return best;
    }
};

int main() {
    cout << DUMP(Solution().maxProfit(vector<int>{7,1,5,3,6,4})) << '\n'
         << DUMP(Solution().maxProfit(vector<int>{7,6,4,3,1})) << '\n';
    return 0;
}
