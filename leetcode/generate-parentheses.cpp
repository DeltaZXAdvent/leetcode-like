/**
 * https://leetcode.cn/problems/generate-parentheses/?envType=study-plan-v2&envId=top-100-liked
 */
#include <bits/stdc++.h>
#include "print.h"
static_assert(sizeof(int) * CHAR_BIT >= 32);
using namespace std;
#define DUMP(x) (string(#x) + ": " + to_string(x))
#define FOR2(i, a, b) for (int i = a; i < b; ++i)

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> out;
        string cur;
        function<void(int, int)> backtrack = [&out, &cur, &backtrack](int open, int close) {
            if (open == 0) {
                out.push_back(cur + string(close, ')'));
                return;
            }
            if (close != 0) {
                cur.push_back(')');
                backtrack(open, close - 1);
                cur.pop_back();
            }
            cur.push_back('(');
            backtrack(open - 1, close + 1);
            cur.pop_back();
        };
        backtrack(n, 0);
        return out;
    }
};

int main() {
    print(cout, Solution().generateParenthesis(3), '\n') << '\n';
    return 0;
}
