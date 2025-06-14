/**
 * https://leetcode.cn/problems/find-all-anagrams-in-a-string/?envType=study-plan-v2&envId=top-100-liked
 */
#include <bits/stdc++.h>
#include "print.h"
static_assert(sizeof(int) * CHAR_BIT >= 32);
using namespace std;
#define DUMP(x) (string(#x) + ": " + to_string(x))

class Solution {
public:
  vector<int> findAnagrams(string s, string p) {
    vector<int> res;
    if (s.length() < p.length()) return res;
    int n = s.length(), m = p.length();
    unordered_map<char, int> counts, anagram;
    int i = 0, j = m;
    for (int k = 0; k < m; ++k) {
      ++counts[s[k]];
      ++anagram[p[k]];
    }
    for (;;) {
      if (counts == anagram) {
	res.push_back(j - m);
      }
      if (j == n) break;
      if (--counts[s[i++]] == 0) counts.erase(s[i - 1]);
      ++counts[s[j++]];
    }
    return res;
  }
};

int main() {
  print(cout, Solution().findAnagrams("cbaebabacd", "abc"), ' ') << '\n';
  print(cout, Solution().findAnagrams("abab", "ab"), ' ') << '\n';
  return 0;
}
