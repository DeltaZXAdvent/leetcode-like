/**
 * https://leetcode.cn/problems/word-break/description/?envType=study-plan-v2&envId=top-100-liked
 */
#include <bits/stdc++.h>
#include "print.h"
static_assert(sizeof(int) * CHAR_BIT >= 32);
using llong = long long;
using namespace std;
#define DUMP(x) (string(#x) + ": " + to_string(x))
#define FOR2(i, a, b) for (int i = a; i < b; ++i)

class Solution {
public:
    bool wordBreak(string s, const vector<string>& wordDict) {
        int n = s.length();
        auto dp = vector<bool>();
        dp.reserve(n + 1);
        dp.push_back(true);
        for (int i = 1; i <= n; ++i) {
            bool breakable = false;
            for (auto& word: wordDict) {
                // s.length() is smaller, I should have loop on the positions rather than on the dict
                if (word.length() <= i
                    && dp[i - word.length()]
                    && s.substr(i - word.length(), word.length()) == word)
                    breakable = true;
            }
            dp.push_back(breakable);
        }
        // PRINT1(cerr, dp, ' ') << '\n';
        return dp[n];
    }
};

int main() {
    cout << DUMP(Solution().wordBreak("leetcode", vector<string>{"leet","code"})) << '\n'
         << DUMP(Solution().wordBreak("applepenapple", vector<string>{"apple","pen"})) << '\n'
         << DUMP(Solution().wordBreak("catsandog", vector<string>{"cats","dog","sand","and","cat"})) << '\n';
    return 0;
}
