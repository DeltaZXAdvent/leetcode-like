#include <bits/stdc++.h>
static_assert (sizeof (int) * CHAR_BIT >= 32);
typedef long long llong;
using namespace std;
#define for3(i, p, q) for (int i = p; i < q; ++i)
#define for2(i, n) for3 (i, 0, n)

/**
 * <https://codeforces.com/contest/2064/problem/E>
 *
 * \f$ c' \f$ should be the same as \f$ c \f$.
 *
 * Linked disjoint sets?
 */

int repr (vector <int> &rp, int i)
{
  if (rp[i] == i)
    return i;
  return rp[i] = repr (rp, rp[i]);
}

int main (int argc, char *argv[])
{
  int t;
  cin >> t;

  while (t-- > 0)
    {
      int n;
      cin >> n;

      int null = n;
      vector <int>
	p (n),
	c (n),
	rp (n),			// representative
	prev (n + 1),		// previous representative
	next (n + 1),
	order (n),
	count (n),
	rank (n);
      for2 (i, n) {
	cin >> p[i];
	order[p[i] - 1] = i;
      }
      for2 (i, n) cin >> c[i];

      rp[0] = 0;
      prev[0] = null;
      next[0] = 1;
      count[0] = 1;
      rank[0] = 0;
      for3 (i, 1, n)
	{
	  if (c[i - 1] == c[i])
	    {
	      rp[i] = rp[i - 1];
	      count[rp[i]]++;
	    }
	  else
	    {
	      rp[i] = i;
	      prev[i] = i - 1;
	      count[i] = 1;
	    }
	  next[rp[i]] = i + 1;
	}

      llong choices = 1;
      for2 (i, n)
	{
	  auto root = repr (rp, order[i]);
	  auto &ct = count[root];
      
	  choices = (choices * ct) % 998244353;
	  if (--ct == 0)
	    {
	      auto pr = prev[root] = repr (rp, prev[root]);
	      auto nx = next[root] = repr (rp, next[root]);

	      if (pr == null | nx == null)
		{
		  next[pr] = nx;
		  prev[nx] = pr;
		}
	      else if (c[pr] == c[nx])
		{
		  if (rank[pr] > rank[nx])
		    {
		      rp[nx] = pr;
		      count[pr] += count[nx];
		      next[pr] = next[nx];
		    }
		  else
		    {
		      rp[pr] = nx;
		      if (rank[pr] == rank[nx])
			rank[nx]++;
		      count[nx] += count[pr];
		      prev[nx] = prev[pr];
		    }
		}
	    }
	}
      cout << choices << '\n';
    }
  return 0;
}
