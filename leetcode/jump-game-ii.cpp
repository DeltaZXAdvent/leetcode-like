/**
 * https://leetcode.cn/problems/jump-game-ii/?envType=study-plan-v2&envId=top-100-liked
 */
#include <bits/stdc++.h>
#include "print.h"
static_assert(sizeof(int) * CHAR_BIT >= 32);
using namespace std;
#define DUMP(x) (string(#x) + ": " + to_string(x))
#define FOR2(i, a, b) for (int i = a; i < b; ++i)

class Solution {
public:
    int jump(vector<int>& nums) {
        int maxdist = 0;
        int n = nums.size();
        int i = 0;
        int ct = 0;
        for (; maxdist < n - 1; ++ct) {
            // cerr << DUMP(maxdist) << ' ' << DUMP(ct) << '\n';
            int newmaxdist = maxdist;
            for (; i <= maxdist && i < n; ++i) {
                newmaxdist = max(newmaxdist, i + nums[i]);
            }
            if (newmaxdist == maxdist) return -1;
            maxdist = newmaxdist;
        }
        // cerr << DUMP(maxdist) << ' ' << DUMP(ct) << '\n';
        return ct;
    }
};

int main() {
    auto nums = vector<int>{2,3,1,1,4};
    cout << DUMP(Solution().jump(nums)) << '\n';
    return 0;
}
