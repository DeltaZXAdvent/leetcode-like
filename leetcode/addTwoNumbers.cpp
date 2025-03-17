/**
 * https://leetcode.cn/problems/add-two-numbers/
 */
#define MAIN main
#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
      auto raw = addTwoNumbersWithCarry(l1, l2, false);
      return raw ? raw : new ListNode();
    }
  ListNode* addTwoNumbersWithCarry(ListNode* l1, ListNode* l2, bool carry) {
    if (!l1 && !l2 && !carry) return nullptr;
    auto val1 = l1 ? l1->val : 0;
    auto val2 = l2 ? l2->val : 0;
    auto sum = val1 + val2 + carry;
    return new ListNode(sum % 10,
			addTwoNumbersWithCarry(l1 ? l1->next : nullptr,
					       l2 ? l2->next : nullptr,
					       sum >= 10));
  }
};
int MAIN() {
  auto l1 = ListNode(2, new ListNode(4, new ListNode(3))),
    l2 = ListNode(5, new ListNode(6, new ListNode(4)));
  auto l = Solution().addTwoNumbers(&l1, &l2);
  for (; l; l = l->next) {
    cout << l->val;
  }
  cout << '\n';
  return 0;
}
