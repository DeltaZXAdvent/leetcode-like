#include <bits/stdc++.h>
static_assert (sizeof (int) * CHAR_BIT >= 32);
typedef long long llong;
using namespace std;
#define FOR2(i, n) FOR3 (i, 0, n)
#define FOR3(i, p, q) for (int i = p; i < q; ++i)

/**
 * https://codeforces.com/contest/2121/problem/D
 */

int main (int argc, char *argv[])
{
  int t; cin >> t;
  while (t--)
    {
      int n; cin >> n;
      vector<int> a(n), b(n);
      FOR2 (i, n) cin >> a[i];
      FOR2 (i, n) cin >> b[i];

      vector<pair<int, int>> ops;
      FOR2 (i, n)
	if (!(a[i] < b[i]))
	  {
	    ops.push_back({3, i + 1});
	    swap(a[i], b[i]);
	  }
      FOR2 (i, n)
	{
	  for (int j = n - 1; j > i; --j)
	    {
	      if (!(a[j - 1] < a[j]))
		{
		  ops.push_back({1, (j - 1) + 1});
		  swap(a[j - 1], a[j]);
		}
	    }
	}
      FOR2 (i, n)
	{
	  for (int j = n - 1; j > i; --j)
	    {
	      if (!(b[j - 1] < b[j]))
		{
		  ops.push_back({2, (j - 1) + 1});
		  swap(b[j - 1], b[j]);
		}
	    }
	}
      cout << ops.size() << '\n';
      for (const auto& op: ops)
	{
	  cout << op.first << ' ' << op.second << '\n';
	}
    }
  return 0;
}
