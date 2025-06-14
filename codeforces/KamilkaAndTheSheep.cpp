#include <bits/stdc++.h>
static_assert (sizeof (int) * CHAR_BIT >= 32);
typedef long long llong;
using namespace std;

// the maximum difference

int main() {
  int t;
  cin >> t;
  while (t--)
    {
      int n;
      cin >> n;
      vector<int> a;
      a.reserve(n);
      for (int i = 0; i < n; ++i)
	{
	  int ai;
	  cin >> ai;
	  a.push_back(ai);
	}
      // is there a better standard lib function for max and min?
      int m, M;
      m = M = a[0];
      for (auto& ai: a)
	{
	  m = min(m, ai);
	  M = max(M, ai);
	}
      cout << M - m << '\n';
    }
  return 0;
}
