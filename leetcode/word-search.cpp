/**
 * https://leetcode.cn/problems/word-search/?envType=study-plan-v2&envId=top-100-liked
 */
#include <bits/stdc++.h>
#include "print.h"
static_assert(sizeof(int) * CHAR_BIT >= 32);
using namespace std;
#define DUMP(x) (string(#x) + ": " + to_string(x))
#define FOR2(i, a, b) for (int i = a; i < b; ++i)

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size(),
            n = board[0].size();
        // Using set (unordered_set doesn't support pairs) leads to timeout
        auto positions = vector<vector<int>>(m, vector<int>(n, false));
        function<bool(int, int, int)> existFrom =
            [&](int i, int j, int k) {
                // cerr << DUMP(i) << ' ' << DUMP(j) << ' ' << DUMP(k) << '\n';
                if (k == word.length())
                    return true;
                if (!(0 <= i && i < m && 0 <= j && j < n))
                    return false;
                if (positions[i][j])
                    return false;
                if (board[i][j] != word[k])
                    return false;
                positions[i][j] = true;;
                auto res = existFrom(i - 1, j, k + 1)
                    || existFrom(i + 1, j, k + 1)
                    || existFrom(i, j - 1, k + 1)
                    || existFrom(i, j + 1, k + 1);
                positions[i][j] = false;
                return res;
            };
        bool res;
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j) {
                // cerr << "root " << DUMP(i)<< ' ' << DUMP(j) << '\n';
                if (existFrom(i, j, 0))
                    return true;
            }
        return false;
    }
};

int main() {
    auto board = vector<vector<char>>{{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}};
    cout << DUMP(Solution().exist(board, "ABCCED")) << '\n'
         << DUMP(Solution().exist(board, "SEE")) << '\n'
         << DUMP(Solution().exist(board, "ABCB")) << '\n';
    return 0;
}
