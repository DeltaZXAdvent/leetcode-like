/**
 * https://leetcode.cn/problems/search-a-2d-matrix-ii/description/?envType=study-plan-v2&envId=top-100-liked
 */
#include <bits/stdc++.h>
static_assert(sizeof(int) * CHAR_BIT >= 32);
using namespace std;
#define DUMP(x) (string(#x) + ": " + to_string(x))
#define FOR2(i, a, b) for (int i = a; i < b; ++i)

/**
 * I have a solution with complexity O(log(mn))
 */

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(),
            n = matrix[0].size();
        int x = 0, y = n;
        while (x < m && y > 0) {
            if (matrix[x][y - 1] == target) return true;
            else if (matrix[x][y - 1] < target) ++x;
            else --y;
        }
        return false;
    }
};

int main() {
    
    return 0;
}
