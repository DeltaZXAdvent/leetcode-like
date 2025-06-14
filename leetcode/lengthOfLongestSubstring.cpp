/**
 * https://leetcode.cn/problems/longest-substring-without-repeating-characters/?envType=study-plan-v2&envId=top-100-liked
 */
#include <bits/stdc++.h>
#include "print.h"
static_assert(sizeof(int) * CHAR_BIT >= 32);
using namespace std;
#define DUMP(x) (string(#x) + ": " + to_string(x))

class Solution {
public:
  int lengthOfLongestSubstring(string s) {
    unordered_map<char, int> indices;
    int i = 0, j = 0, n = s.length(), maxLen = 0;
    while (j < n) {
      auto rep = indices.find(s[j]);
      if (rep != indices.end()) {
	maxLen = max(maxLen, j - i);
	// cerr << DUMP(i) << ' ' << DUMP(j) << ' '
	//      << DUMP(rep->first) << ' '
	//      << DUMP(rep->second) << '\n';
	auto reppos = rep->second;
	while (i <= reppos) {
	  indices.erase(s[i]);
	  ++i;
	}
      }
      indices.insert({s[j], j});
      ++j;
    }
    // cerr << DUMP(i) << ' ' << DUMP(j) << '\n';
    maxLen = max(maxLen, j - i);
    return maxLen;
  }
};

int main() {
  cout << DUMP(Solution().lengthOfLongestSubstring("abcabcbb")) << '\n';
  cout << DUMP(Solution().lengthOfLongestSubstring("bbbbb")) << '\n';
  cout << DUMP(Solution().lengthOfLongestSubstring("pwwkew")) << '\n';
  return 0;
}
