/**
 * https://leetcode.cn/problems/spiral-matrix/?envType=study-plan-v2&envId=top-100-liked
 */
#include <bits/stdc++.h>
#include "print.h"
static_assert(sizeof(int) * CHAR_BIT >= 32);
using namespace std;
#define DUMP(x) (string(#x) + ": " + to_string(x))

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        vector<int> res;
        res.reserve(m * n);
        int k;
        for (k = 0; 2 * k + 1 < n && 2 * k + 1 < m; ++k) {
            for (int j = k; j < n - 1 - k; ++j)
                res.push_back(matrix[k][j]);
            for (int i = k; i < m - 1 - k; ++i)
                res.push_back(matrix[i][n - 1 - k]);
            for (int j = n - 1 - k; j > k; --j)
                res.push_back(matrix[m - 1 - k][j]);
            for (int i = m - 1 - k; i > k; --i)
                res.push_back(matrix[i][k]);
        }
        if (2 * k + 1 == n)
            for (int i = k; i <= m - 1 - k; ++i)
                res.push_back(matrix[i][k]);
        else if (2 * k + 1 == m)
            for (int j = k; j <= n - 1 - k; ++j)
                res.push_back(matrix[k][j]);
        return res;
    }
};

int main() {
    vector<vector<int>> m1 = {{1,2,3},{4,5,6},{7,8,9}},
        m2 = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};
    PRINT1(cout, Solution().spiralOrder(m1), ' ') << '\n';
    PRINT1(cout, Solution().spiralOrder(m2), ' ') << '\n';
    return 0;
}
