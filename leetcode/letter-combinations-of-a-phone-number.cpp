/**
 * https://leetcode.cn/problems/letter-combinations-of-a-phone-number/description/?envType=study-plan-v2&envId=top-100-liked
 */
#include <bits/stdc++.h>
#include "print.h"
static_assert(sizeof(int) * CHAR_BIT >= 32);
using namespace std;
#define DUMP(x) (string(#x) + ": " + to_string(x))
#define FOR2(i, a, b) for (int i = a; i < b; ++i)

class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> out;
        string cur;
        if (digits.empty()) return out; // to pass the test however I think the test case is wrong
        backtrack(digits, 0, cur, out);
        return out;
    }
    void backtrack(string& digits, int first, string& cur, vector<string>& out) {
        int n = digits.length();
        if (first == n) {
            out.push_back(cur);
            return;
        }
        static vector<string> digitToChars = {"abc", "def","ghi","jkl","mno","pqrs","tuv","wxyz"};
        string& chars = digitToChars[digits[first] - '2'];
        for (char ch: chars) {
            cur.push_back(ch);
            backtrack(digits, first + 1, cur, out);
            cur.pop_back();
        }
    }
};

int main() {
    PRINT1(cout, Solution().letterCombinations("23"), ' ') << '\n';
    return 0;
}
