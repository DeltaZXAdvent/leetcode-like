/**
 * https://leetcode.cn/problems/two-sum/description/
 */
#define MAIN main
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  vector<int> twoSum(vector<int>& nums, int target) {
    auto subs = unordered_map<int, int>();
    const auto l = nums.size();
    for (int i = 0; i < l; ++i)
      subs[nums[i]] = i;
    for (int i = 0; i < l; ++i) {
      auto j = subs.find(target - nums[i]);
      if (j != subs.end() && i != j->second)
	return vector<int>{ i, j->second };
    }
    return vector<int>();
  }
};

int MAIN() {
  auto nums = vector<int>{2, 7 ,11, 15};
  auto res = vector<int>{0, 1};
  assert(Solution().twoSum(nums, 9) == res);
  return 0;
}
