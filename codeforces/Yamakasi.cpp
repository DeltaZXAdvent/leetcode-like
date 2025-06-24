#include <bits/stdc++.h>
static_assert (sizeof (int) * CHAR_BIT >= 32);
typedef long long llong;
using namespace std;
#define FOR2(i, n) FOR (i, 0, n)
#define FOR3(i, p, q) for (int i = p; i < q; ++i)
#define DUMP(x) (string(#x) + ": " + to_string(x))

/**
 * <https://codeforces.com/contest/2121/problem/F>
 *
 * Already read the tutorial.
 * 
 * The first step is to determine the intervals that fulfill the maximum
 * If the right boundary is determined, the left boundary lies in a interval
 * The interval's left and right boundaries both move to the right.
 *
 * Thus we can optimize the choice of left boundaries
 * that fulfill the summation condition.
 *
 * Summation of subsegments can be reduced to subtraction
 * of partial sums.
 *
 * The result program can be tagged "three pointers".
 */

int main (int argc, char *argv[])
{
  int t; cin >> t;
  while (t--)
    {
      int n; llong s; int x;
      cin >> n >> s >> x;
      // cerr << DUMP(n) << ' ' << DUMP(s) << ' ' << DUMP(x) << '\n';
      vector<int> a(n + 1);
      FOR3 (i, 1, n + 1) cin >> a[i];
      vector<llong> sum(n + 1);
      sum[0] = 0;
      FOR3 (i, 1, n + 1) sum[i] = sum[i - 1] + a[i];
      int begin_from = 0, begin_to = 0;
      map<llong, int> partial_sum_cts; // in the range [begin_from, begin_to)
      llong pair_cts = 0;
      int end = 0;
      while (end < n)
	{
	  if (a[end + 1] == x)
	    {
	      while (begin_to != end + 1)
		{
		  ++partial_sum_cts[sum[begin_to]];
		  ++begin_to;
		}
	    }
	  else if (a[end + 1] > x)
	    {
	      begin_to = begin_from = end + 1;
	      partial_sum_cts.clear();
	    }
	  else
	    ;
	  ++end;
	  // cerr << DUMP(sum[end]) << ' '
	  //      << DUMP(sum[end] - s) << ' ';
	  auto iter = partial_sum_cts.find(sum[end] - s);
	  if (iter != partial_sum_cts.end())
	    {
	      // cerr << DUMP(iter->second);
	      pair_cts += iter->second;
	    }
	  // cerr << '\n';
	  // cerr << DUMP(end) << ' '
	  //      << DUMP(begin_from) << ' '
	  //      << DUMP(begin_to) << ' '
	  //      << DUMP(pair_cts) << '\n';
	}
      cout << pair_cts << '\n';
    }
  return 0;
}
