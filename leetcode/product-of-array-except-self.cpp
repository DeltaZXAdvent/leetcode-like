/**
 * https://leetcode.cn/problems/product-of-array-except-self/?envType=study-plan-v2&envId=top-100-liked
 */
#include <bits/stdc++.h>
#include "print.h"
static_assert(sizeof(int) * CHAR_BIT >= 32);
using namespace std;
#define DUMP(x) (string(#x) + ": " + to_string(x))

class Solution {
public:
  vector<int> productExceptSelf(const vector<int>& nums) {
    vector<int> answer;
    int n = nums.size();
    answer.reserve(n);
    int product;
    product = 1;
    for (int i = 0; i < n; product *= nums[i++])
      answer.push_back(product);
    product = 1;
    for (int i = n - 1; i >= 0; product *= nums[i--])
      answer[i] *= product;
    return answer;
  }
};

int main() {
  PRINT1(cout, Solution().productExceptSelf({1,2,3,4}), ' ') << '\n';
  PRINT1(cout, Solution().productExceptSelf({-1,1,0,-3,3}), ' ') << '\n';
  return 0;
}
