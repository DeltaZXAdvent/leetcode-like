/**
 * https://leetcode.cn/problems/pascals-triangle/description/?envType=study-plan-v2&envId=top-100-liked
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
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> res;
        int i = 2;
        res.push_back(vector<int>{1});
        for (; i <= numRows; ++i) {
            auto row = vector<int>();
            row.reserve(i);
            row.push_back(1);
            for (int j = 1; j < i - 1; ++j) {
                row.push_back(res[i - 2][j - 1] + res[i - 2][j]);
            }
            row.push_back(1);
            res.push_back(move(row));
        }
        return res;
    }
};

int main() {
    PRINT2(cout, Solution().generate(5), '\n', ' ') << '\n';
    return 0;
}
