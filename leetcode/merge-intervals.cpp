/**
 * https://leetcode.cn/problems/merge-intervals/?envType=study-plan-v2&envId=top-100-liked
 */
#include <bits/stdc++.h>
#include "print.h"
static_assert(sizeof(int) * CHAR_BIT >= 32);
using namespace std;
#define DUMP(x) (string(#x) + ": " + to_string(x))

class Solution {
public:
  vector<vector<int>> merge(vector<vector<int>>& intervals) {
    vector<vector<int>> res;
    int n = intervals.size();
    sort(intervals.begin(), intervals.end());
    for (int i = 0; i < n;) {
      vector<int> merged = intervals[i];
      while (++i < n && intervals[i][0] <= merged[1])
	  merged[1] = max(merged[1], intervals[i][1]);
      res.push_back(move(merged));
    }
    return res;
  }
};

int main() {
  vector<vector<int>> v1 = {{1,3},{2,6},{8,10},{15,18}},
    v2 = {{1,4},{4,5}};
  PRINT2(cout, Solution().merge(v1), ' ', ';') << '\n';
  PRINT2(cout, Solution().merge(v2), ' ', ';') << '\n';
  return 0;
}
