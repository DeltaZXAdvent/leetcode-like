/**
 * https://leetcode.cn/problems/3sum/description/?envType=study-plan-v2&envId=top-100-liked
 */
#include <bits/stdc++.h>
#include "print.h"
using namespace std;
#define DUMP(x) (string(#x) + ": " + to_string(x))

class Solution {
public:
  vector<vector<int>> threeSumCubic(vector<int>& nums) {
    vector<vector<int>> res;
    int n = nums.size();
    sort(nums.begin(), nums.end());
    int i = 0;
    while (i < n) {
      int j = i + 1;
      while (j < n) {
	int k = j + 1;
	while (k < n) {
	  if (nums[i] + nums[j] + nums[k] == 0)
	    res.push_back({nums[i], nums[j], nums[k]});
	  while (++k < n && nums[k] == nums[k - 1]);
	}
	while (++j < n && nums[j] == nums[j - 1]);
      }
      while (++i < n && nums[i] == nums[i - 1]);
    }
    return res;
  }

  vector<vector<int>> threeSumHash(vector<int>& nums) {
    vector<vector<int>> res;
    unordered_set<int> is;
    sort(nums.begin(), nums.end());
    // print(cerr << "nums: ", nums, ' ') << '\n';
    int n = nums.size();
    int j = 0;
    while (j < n) {
      // cerr << DUMP(j) << '\n';
      int k = j + 1;
      while (k < n) {
	if (is.find(0 - (nums[j] + nums[k])) != is.end())
	  res.push_back({0 - (nums[j] + nums[k]), nums[j], nums[k]});
	while (++k < n && nums[k] == nums[k - 1]);
      }
      is.insert(nums[j]);
      if (++j < n) {
	if (nums[j] == nums[j - 1]) {
	  // cerr << DUMP(j) << " nums[j] == nums[j - 1]" << '\n';
	  for (int k = j + 1; k < n; ++k)
	    if (2 * nums[j] + nums[k] == 0) {
	      res.push_back({nums[j], nums[j], nums[k]});
	      break;
	    }
	  while (++j < n && nums[j] == nums[j - 1]);
	}
      }
    }
    // print(cerr << "is: ", is, ' ') << '\n';
    return res;
  }

  vector<vector<int>> threeSumTwoPointers(vector<int>& nums) {
    vector<vector<int>> res;
    sort(nums.begin(), nums.end());
    // print(cerr << "nums: ", nums, ' ') << '\n';
    int n = nums.size();
    for (int i = 0; i < n - 2;) {
      // cerr << DUMP(i) << '\n';
      int j = i + 1, k = n - 1;
      while (j < k) {
	// cerr << DUMP(j) << ' ' << DUMP(k)
	//      << DUMP(nums[j]) << ' ' << DUMP(nums[k]) << '\n';
	int sum = nums[i] + nums[j] + nums[k];
	if (sum == 0) {
	  res.push_back({nums[i], nums[j], nums[k]});
	  while (++j < n && nums[j] == nums[j - 1]);
	} else if (sum > 0) {
	  --k;
	} else {
	  ++j;
	}
      }
      while (++i < n && nums[i] == nums[i - 1]);
    }
    return res;
  }

  vector<vector<int>> threeSum(vector<int>& nums) {
    return threeSumTwoPointers(nums);
  }
};

int main() {
  vector<int> nums1 = {-1,0,1,2,-1,-4},
    nums2 = {0, 1, 1},
    nums3 = {0, 0, 0},
    nums4 = {2,-3,0,-2,-5,-5,-4,1,2,-2,2,0,2,-4,5,5,-10};
  print(cout, Solution().threeSum(nums1), ';', ' ') << '\n';
  print(cout, Solution().threeSum(nums2), ';', ' ') << '\n';
  print(cout, Solution().threeSum(nums3), ';', ' ') << '\n';
  print(cout, Solution().threeSum(nums4), ';', ' ') << '\n';
  return 0;
}
