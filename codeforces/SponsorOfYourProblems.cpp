#include <bits/stdc++.h>
static_assert (sizeof (int) * CHAR_BIT >= 32);
typedef long long llong;
using namespace std;
#define FOR2(i, n) FOR (i, 0, n)
#define FOR3(i, p, q) for (int i = p; i < q; ++i)

/**
 * https://codeforces.com/contest/2121/problem/E
 */

int solve(int l, int r, int digits)
{
  if (digits == 0) return 0;
  if (l == r) return 2 * digits;
  if (l + 1 == r)
    {
      int same_digits = digits;
      while (l != r)
	{
	  l /= 10; r /= 10;
	  --same_digits;
	}
      return digits + same_digits;
    }
  return solve(l / 10, r / 10, digits - 1);
}

int main (int argc, char *argv[])
{
  int t;
  cin >> t;

  while (t-- > 0)
    {
      int l, r;
      cin >> l >> r;

      int digits = 0;
      for (int i = l; i > 0; i /= 10)
	++digits;
      cout << solve(l, r, digits) << '\n';
    }

  return 0;
}
