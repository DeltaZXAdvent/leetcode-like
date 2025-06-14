/**
 * https://leetcode.cn/problems/jump-game/description/?envType=study-plan-v2&envId=top-100-liked
 */
#include <bits/stdc++.h>
#include "print.h"
static_assert(sizeof(int) * CHAR_BIT >= 32);
using namespace std;
#define DUMP(x) (string(#x) + ": " + to_string(x))
#define FOR2(i, a, b) for (int i = a; i < b; ++i)

class Solution {
public:
    bool canJump(const vector<int>& nums) {
        int maxdist = 0;
        int n = nums.size();
        for (int i = 0; i <= maxdist; ++i) {
            maxdist = max(maxdist, i + nums[i]);
            if (maxdist >= n - 1) return true;
        }
        return false;
    }
};

int main() {
    
    cout << DUMP(Solution().canJump(vector<int>{2,3,1,1,4})) << '\n'
         << DUMP(Solution().canJump(vector<int>{3,2,1,0,4})) << '\n';
    return 0;
}
