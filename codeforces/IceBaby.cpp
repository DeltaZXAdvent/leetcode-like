/**
 * \file
 * <https://codeforces.com/contest/2121/problem/H>
 *
 * See the tutorial. I think this tricky.
 */
#include <bits/stdc++.h>
static_assert (sizeof (int) * CHAR_BIT >= 32);
typedef long long llong;
using namespace std;
#define FOR2(i, n) FOR3 (i, 0, n)
#define FOR3(i, p, q) for (int i = p; i < q; ++i)
#define DUMP(x) (string(#x) + ": " + to_string(x))
string& to_string(string& x) { return x; }

int main(int argc, char *argv[])
{
  int t;
  cin >> t;
  while (t--)
    {
      int n;
      cin >> n;
      vector<int> l(n), r(n);
      FOR2 (i, n)
	cin >> l[i] >> r[i];
      multiset<int> m;		// least upper bound of subsequence of key length
      FOR2 (i, n)
	{
	  auto it = m.upper_bound(r[i]);
	  if (it != m.end())
	    m.erase(it);
	  m.insert(l[i]);
	  cout << m.size() << (i == n - 1 ? '\n' : ' ');
	}
    }
  return 0;
}
