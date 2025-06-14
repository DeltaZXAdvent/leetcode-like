#include <bits/stdc++.h>
static_assert (sizeof (int) * CHAR_BIT >= 32);
typedef long long llong;
using namespace std;
#define FOR2(i, n) FOR (i, 0, n)
#define FOR3(i, p, q) for (int i = p; i < q; ++i)
#define DUMP(x) (string(#x) + ": " + to_string(x))

/**
 * https://codeforces.com/blog/entry/143268
 * 
 * wrong, bad-written, so many edge cases, shit...
 * <2025-05-30 Fri 14:31>  Made it complicated... See the tutorial...
 */
int main (int argc, char *argv[])
{
  int t;
  cin >> t;

  while (t-- > 0)
    {
      int n;
      cin >> n;
      int xmin = 1000000001,
	ymin = 1000000001,
	xmax = 0,
	ymax = 0;
      int ixmin, ixmax, iymin, iymax;
      FOR3(i, 0, n)
	{
	  int xi, yi;
	  cin >> xi >> yi;
	  if (xi < xmin) { xmin = xi; ixmin = i; }
	  else if (xi == xmin) { ixmin = n; }
	  if (yi < ymin) { ymin = yi; iymin = i; }
	  else if (yi == ymin) { iymin = n; }
	  if (xi > xmax) { xmax = xi; ixmax = i; }
	  else if (xi == xmax) { ixmax = n; }
	  if (yi > ymax) { ymax = yi; iymax = i; }
	  else if (yi == ymax) { iymax = n; }
	}
      int dx = xmax - xmin + 1,
	dy = ymax - ymin + 1;
      cerr << DUMP(xmin) << '\n'
	   << DUMP(xmax) << '\n'
	   << DUMP(ymin) << '\n'
	   << DUMP(ymax) << '\n';
      int ans = dx * dy;
      if (ixmin || ixmax)
	ans = min(ans, (dx - 1) * dy == n - 1 ? (dx - 1) * (dy + 1) : (dx - 1) * dy);
      if (iymin || iymax)
	ans = min(ans, (dy - 1) * dx == n - 1 ? (dx + 1) * (dy - 1) : dx * (dy - 1));
      cout << ans << '\n';
    }
  return 0;
}
