/**
 * https://leetcode.cn/problems/move-zeroes/
 */
#include <bits/stdc++.h>
#include "print.h"
using namespace std;
#define DUMP(x) (string(#x) + ": " + to_string(x))

class Solution {
public:
  void moveZeroes(vector<int>& nums) {
    auto i = nums.begin(), j = nums.begin();
    for (; i != nums.end(); ++i)
      if (*i) swap(*i, *j++);
  }
};

int main() {
  vector<int> nums = {0,1,0,3,12};
  print(cout, nums, ' ') << '\n';
  Solution().moveZeroes(nums);
  print(cout, nums, ' ') << '\n';
  return 0;
}
