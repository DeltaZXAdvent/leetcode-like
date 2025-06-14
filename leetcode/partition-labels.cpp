/**
 * https://leetcode.cn/problems/partition-labels/description/?envType=study-plan-v2&envId=top-100-liked
 */
#include <bits/stdc++.h>
#include "print.h"
static_assert(sizeof(int) * CHAR_BIT >= 32);
using namespace std;
#define DUMP(x) (string(#x) + ": " + to_string(x))
#define FOR2(i, a, b) for (int i = a; i < b; ++i)

class Solution {
public:
    vector<int> partitionLabels(string s) {
        int latests[26];
        int n = s.length();
        vector<int> out;
        for (int i = 0; i < n; ++i) {
            latests[s[i] - 'a'] = max(latests[s[i] - 'a'], i + 1);
        }
        for (int i = 0; i < n;) {
            int next = i + 1;
            for (int j = i; j < next; ++j) {
                next = max(next, latests[s[j] - 'a']);
            }
            out.push_back(next - i);
            i = next;
        }
        return out;
    }
};

int main() {
    return 0;
}
