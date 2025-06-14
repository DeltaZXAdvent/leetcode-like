/**
 * https://leetcode.cn/problems/permutations/description/?envType=study-plan-v2&envId=top-100-liked
 */
#include <bits/stdc++.h>
#include "print.h"
static_assert(sizeof(int) * CHAR_BIT >= 32);
using namespace std;
#define DUMP(x) (string(#x) + ": " + to_string(x))
#define FOR2(i, a, b) for (int i = a; i < b; ++i)

/**
 * Using C++'s next permutation and flags both lead to O(n!) complexity
 * (not much verified)
 */

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        do
            res.push_back(nums);
        while (next_permutation(nums.begin(), nums.end()));
        return res;
    }
};

int main() {
    vector<int> v{1,2,3,4,5,6};
    print(cout, Solution().permute(v), '\n', ' ') << '\n';
    return 0;
}
