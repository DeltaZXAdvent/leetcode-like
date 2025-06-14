/**
 * https://leetcode.cn/problems/subarray-sum-equals-k/?envType=study-plan-v2&envId=top-100-liked
 */
#include <bits/stdc++.h>
#include "print.h"
static_assert(sizeof(int) * CHAR_BIT >= 32);
using namespace std;
#define DUMP(x) (string(#x) + ": " + to_string(x))

class Solution {
public:
  int subarraySum(const vector<int>& nums, int k) {
    int count = 0;
    
    int n = nums.size();
    unordered_map<int, int> sumset;
    int sum = 0;
    for (auto& num: nums) {
      ++sumset[sum];
      sum += num;
      auto i = sumset.find(sum - k);
      if (i != sumset.end()) {
	// cerr << DUMP(sum) << ' ' << DUMP(i->second) << '\n';
	count += i->second;
      }
    }
    return count;
  }
};

int main() {
  cout << DUMP(Solution().subarraySum(vector<int>{1,1,1}, 2)) << '\n';
  cout << DUMP(Solution().subarraySum(vector<int>{1,2,3}, 3)) << '\n';
  cout << DUMP(Solution().subarraySum(vector<int>{-1,-1,-1}, 0)) << '\n';
  cout << DUMP(Solution().subarraySum(vector<int>{1,-1,0}, 0)) << '\n';
  return 0;
}
