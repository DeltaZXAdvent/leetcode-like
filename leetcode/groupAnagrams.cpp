/**
 * https://leetcode.cn/problems/group-anagrams/
 */
#include <bits/stdc++.h>
#include "print.h"
using namespace std;

class Solution {
public:
  vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string, vector<string>> groups;
    for (auto& str: strs) {
      auto canonical = str;
      sort(canonical.begin(), canonical.end());
      groups[move(canonical)].push_back(str);
    }
    vector<vector<string>> res;
    for (auto& [canonical, group]: groups)
      res.push_back(move(group));
    return res;
  }
};

int main() {
  auto strs = vector<string>{ "eat", "tea", "tan", "ate", "nat", "bat" };
  auto groups = Solution().groupAnagrams(strs);
  print(cout, groups, '\n', ' ') << '\n';
  return 0;
}
