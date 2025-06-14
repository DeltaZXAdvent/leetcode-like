/**
 * https://leetcode.cn/problems/rotate-array/description/?envType=study-plan-v2&envId=top-100-liked
 */
#include <bits/stdc++.h>
#include "print.h"
static_assert(sizeof(int) * CHAR_BIT >= 32);
using namespace std;
#define DUMP(x) (string(#x) + ": " + to_string(x))

class Solution {
public:
  void rotate(vector<int>& nums, int k) {
    vector<int> update;
    int n = nums.size();
    update.reserve(n);
    while (k > 0) k -= n;
    for (int i = 0; i < n; ++i)
      update.push_back(nums[(i - k) % n]);
    nums = update;
  }

  // using reverse may be better
};

int main() {
  vector<int> v1 = {1,2,3,4,5,6,7},
    v2 = {-1,-100,3,99};
  int k1 = 3, k2 = 2;
  Solution().rotate(v1, k1);
  Solution().rotate(v2, k2);
  PRINT1(cout, v1, ' ') << '\n';
  PRINT1(cout, v2, ' ') << '\n';
  return 0;
}
