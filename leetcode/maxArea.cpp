/**
 * https://leetcode.cn/problems/container-with-most-water/?envType=study-plan-v2&envId=top-100-liked
 */
#include <bits/stdc++.h>
using namespace std;
#define DUMP(x) (string(#x) + ": " + to_string(x))

class Solution {
public:
  int maxArea(vector<int>& height) {
    int i = 0, j = height.size() - 1;
    int res = 0;
    while (i < j) {
      // cerr << DUMP(i) << ' ' << DUMP(j) << '\n';
      if (height[i] < height[j]) {
	res = max(res, height[i] * (j - i));
	++i;
      } else {
	res = max(res, height[j] * (j - i));
	--j;
      }
    }
    return res;
  }
};

int main() {
  vector<int> height1 = {1,8,6,2,5,4,8,3,7},
    height2 = {1,1};
  cout << Solution().maxArea(height1) << '\n'
       << Solution().maxArea(height2) << '\n';
  return 0;
}
