/**
 * https://leetcode.cn/problems/set-matrix-zeroes/?envType=study-plan-v2&envId=top-100-liked
 */
#include <bits/stdc++.h>
#include "print.h"
static_assert(sizeof(int) * CHAR_BIT >= 32);
using namespace std;
#define DUMP(x) (string(#x) + ": " + to_string(x))

#define FOR2(i, a, b) for (int i = a; i < b; ++i)
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        bool col1 = false;
        FOR2 (i, 0, m)
            if (matrix[i][0] == 0) {
                col1 = true;
                break;
            }
        FOR2 (i, 0, m)
            FOR2 (j, 1, n)
            if (matrix[i][j] == 0)
                matrix[i][0] = matrix[0][j] = 0;
        FOR2 (j, 1, n)
            if (matrix[0][j] == 0)
                FOR2 (i, 1, m)
                    matrix[i][j] = 0;
        FOR2 (i, 0, m)
            if (matrix[i][0] == 0)
                FOR2 (j, 1, n)
                    matrix[i][j] = 0;
        if (col1)
            FOR2(i, 0, m) matrix[i][0] = 0;
    }
};

int main() {
    vector<vector<int>> m1 = {{1,1,1},{1,0,1},{1,1,1}},
        m2 = {{0,1,2,0},{3,4,5,2},{1,3,1,5}};
    Solution().setZeroes(m1);
    Solution().setZeroes(m2);
    PRINT2(cout, m1, ';', ' ') << '\n';
    PRINT2(cout, m2, ';', ' ') << '\n';
    return 0;
}
