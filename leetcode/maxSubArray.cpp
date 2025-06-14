/**
 * https://leetcode.cn/problems/maximum-subarray/?envType=study-plan-v2&envId=top-100-liked
 */
#include <bits/stdc++.h>
static_assert(sizeof(int) * CHAR_BIT >= 32);
using namespace std;
#define DUMP(x) (string(#x) + ": " + to_string(x))

class Solution {
public:
  int maxSubArray(const vector<int>& nums) {
    int minsum = 0, sum = 0, maxsubsum = INT_MIN;
    for (auto& num: nums) {
      sum += num;
      maxsubsum = max(maxsubsum, sum - minsum);
      minsum = min(minsum, sum);
    }
    return maxsubsum;
  }
};

int main() {
  cout << DUMP(Solution().maxSubArray(vector<int>{-2,1,-3,4,-1,2,1,-5,4})) << '\n'
       << DUMP(Solution().maxSubArray(vector<int>{1})) << '\n'
       << DUMP(Solution().maxSubArray(vector<int>{5,4,-1,7,8})) << '\n';
  return 0;
}
