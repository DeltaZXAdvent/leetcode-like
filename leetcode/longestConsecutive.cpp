/**
 * https://leetcode.cn/problems/longest-consecutive-sequence/
 */
#include <bits/stdc++.h>
using namespace std;
#define DUMP(x) (string(#x) + ": " + to_string(x))

// TODO numeric_limits for int? insert({}) or insert(make_pair)?

class Solution {
public:
  int longestConsecutive(vector<int>& nums) {
    return longestConsecutiveHash(nums);
  }
  int longestConsecutiveMine(vector<int>& nums) {
    unordered_map<int, int> mates;
    int maxLen = 0;
    for (auto& key: nums)
      if (mates.find(key) == mates.end()) {
	int left = key, right = key;
	if (key > INT_MIN) {
	  auto i = mates.find(key - 1);
	  if (i != mates.end() && i->second <= i->first) {
	    left = i->second;
	    mates.erase(i);
	  }
	}
	if (key < INT_MAX) {
	  auto i = mates.find(key + 1);
	  if (i != mates.end() && i->first <= i->second) {
	    right = i->second;
	    mates.erase(i);
	  }
	}
	// cerr << DUMP(key) << ' '
	//      << DUMP(left) << ' '
	//      << DUMP(right) << '\n';
	mates[left] = right;
	mates[right] = left;
	maxLen = max(maxLen, right - left + 1);
      }
    return maxLen;
  }
  int longestConsecutiveHash(vector<int>& nums) {
    unordered_set<int> numset;
    for (auto& num: nums)
      numset.insert(num);
    int maxLen = 0;
    for (auto& num: numset)
      if (numset.find(num - 1) == numset.end()) {
	int len;
	for (len = 1;
	     numset.find(num + len) != numset.end();
	     ++len);
	maxLen = max(maxLen, len);
      }
    return maxLen;
  }
  int longestConsecutiveSort(vector<int>& nums) {
    if (nums.empty()) return 0;
    sort(nums.begin(), nums.end());
    auto l = nums.size();
    int len = 1, maxLen = 0;
    int pred = nums[0];
    for (auto& num: nums) {
      if (num != pred + 1) {
	if (num != pred)
	  len = 1;
      } else {
	++len;
      }
      pred = num;
      maxLen = max(maxLen, len);
      // cerr << DUMP(pred) << ' ' << DUMP(len) << '\n';
    }
    return maxLen;
  }
};

int main() {
  auto nums = vector<int>{100,4,200,1,3,2};
  cout << Solution().longestConsecutive(nums) << '\n';
  auto nums2 = vector<int>{0,3,7,2,5,8,4,6,0,1};
  cout << Solution().longestConsecutive(nums2) << '\n';
  auto nums3 = vector<int>{1,0,1,2};
  cout << Solution().longestConsecutive(nums3) << '\n';
  return 0;
}
