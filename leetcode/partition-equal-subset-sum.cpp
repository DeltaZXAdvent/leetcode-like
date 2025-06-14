/**
 * https://leetcode.cn/problems/partition-equal-subset-sum/description/?envType=study-plan-v2&envId=top-100-liked
 */
#include <bits/stdc++.h>
#include "print.h"
static_assert(sizeof(int) * CHAR_BIT >= 32);
using llong = long long;
using namespace std;
#define DUMP(x) (string(#x) + ": " + to_string(x))
#define FOR2(i, a, b) for (int i = a; i < b; ++i)

// refer to the official solution
class Solution {
public:
    bool canPartition(const vector<int>& nums) {
        auto diffs = unordered_set<int>{0};
        for (auto& num: nums) {
            auto newdiffs = unordered_set<int>{};
            for (auto diff: diffs) {
                newdiffs.insert(abs(diff + num));
                newdiffs.insert(abs(diff - num));
            }
            diffs = move(newdiffs); // is this a valid use?
            // PRINT1(cerr, diffs, ' ') << ' ' << DUMP(num) << '\n';
        }
        return diffs.find(0) != diffs.end();
    }
};

int main() {
    cout << DUMP(Solution().canPartition({1,5,11,5})) << '\n'
         << DUMP(Solution().canPartition({1,2,3,5})) << '\n';
    return 0;
}
