#include <bits/stdc++.h>
static_assert (sizeof (int) * CHAR_BIT >= 32);
typedef long long llong;
using namespace std;
#define FOR2(i, n) FOR3 (i, 0, n)
#define FOR3(i, p, q) for (int i = p; i < q; ++i)

/**
 * https://codeforces.com/contest/2114/problem/C
 *
 * I made it complicated and failed the tests. Idk what's wrong... Just put this aside.
 */

int main (int argc, char *argv[])
{
  int t;
  cin >> t;

  while (t-- > 0)
    {
      int n;
      cin >> n;
      vector<int> a(n);
      FOR2(i, n) cin >> a[i];
      int consecutive = 1,
	total = 0,
	cur = a[0];
      int i = 1;
      while (i < n) {
	if (cur + 1 >= a[i])
	  {
	    if (a[i] == cur + 1) {
	      cur = a[i];
	      consecutive += 1;
	    }
	  }
	else
	  {
	    total += (consecutive + 1) / 2;
	    consecutive = 1;
	  }
	++i;
      }
      total += (consecutive + 1) / 2;
      cout << total << '\n';
    }
  return 0;
}
