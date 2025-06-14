#include <bits/stdc++.h>
static_assert (sizeof (int) * CHAR_BIT >= 32);
typedef long long llong;
using namespace std;

// the numbers of odd numbers and even numbers cannot change

int main() {
  int t;
  cin >> t;
  while(t--) {
    int n;
    cin >> n;
    vector<int> a;
    a.reserve(n);
    for (int i  =0; i<n;++i) {
      int ai;
      cin >>ai;
      a.push_back(ai);
    }
    int even = 0, odd = 0, M = 0;
    llong sum = 0;
    for (auto& ai: a) {
      if (ai % 2) odd ++; else even++;
      sum += ai;
      M = max(M, ai);
    }
    if (!even || !odd) cout << M << '\n';
    else {
      cout << sum + 1 - odd << '\n';
    }
  }

  // TODO no return UB?
  return 0;
}
