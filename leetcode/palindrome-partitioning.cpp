/**
 * https://leetcode.cn/problems/palindrome-partitioning/description/?envType=study-plan-v2&envId=top-100-liked
 */
#include <bits/stdc++.h>
#include "print.h"
static_assert(sizeof(int) * CHAR_BIT >= 32);
using namespace std;
#define DUMP(x) (string(#x) + ": " + to_string(x))
#define FOR2(i, a, b) for (int i = a; i < b; ++i)

// isPalindrome results can be firstly calculated
class Solution {
public:
    vector<vector<string>> partition(string s) {
        int n = s.length();
        vector<vector<string>> out;
        vector<string> cur;
        function<void(int)> partitionFrom =
            [&](int i) {
                if (i == n) out.push_back(cur);
                for (int j = i + 1; j <= n; ++j) {
                    if (isPalindrome(s, i, j)) {
                        cur.push_back(s.substr(i, j - i));
                        partitionFrom(j);
                        cur.pop_back();
                    }
                }
            };
        partitionFrom(0);
        return out;
    }
    bool isPalindrome(const string& s, int i, int j) {
        for (int k = 0; 2 * k + 1 < j - i; ++k) {
            if (s[i + k] != s[j - 1 - k])
                return false;
        }
        return true;
    }
};

int main() {
    cerr << DUMP(Solution().isPalindrome("efe", 0, 3)) << '\n';
    PRINT2(cout, Solution().partition("aab"), ' ', ',') << '\n';
    PRINT2(cout, Solution().partition("a"), ' ', ',') << '\n';
    return 0;
}
