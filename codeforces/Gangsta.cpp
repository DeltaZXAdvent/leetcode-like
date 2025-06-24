/**
 * \file
 * <https://codeforces.com/contest/2121/problem/G>
 *
 * Let \\( f(l-1,r)=f(s_l s_{l+1} \\ldots s_r) \\),
 * If \\(f(p,q),f(q,r),f(p,r)\\) have a relationship,
 * then we can omit computation repetitions.
 *
 * When \\(f(l,r) = \sum_{i=l+1}^{r}s_i\\),
 * we already have used that in problem F.
 *
 * In this case, \\( f(l,r)=\max \\{c_0(l,r), c_1(l,r)\\} \\),
 * where \\( c_0, c_1 \\) are the numbers of 0's and 1's
 * in the segment, as defined in the tutorial.
 *
 * \\( c(p,q)=c(p,r)-c(q,r)\\). Let \\( c(0,q)=c(q) \\),
 * then \\( f(l,r)=\max \\{ c_0(r)-c_0(l), c_1(r)-c_1(l)\\} \\).
 *
 * If some maximums are always chosen from the first,
 * we can group them and eliminate them.
 * Kinda hard to describe, but let's write \\( \max \\) in
 * absolute values. Then we have only to discuss the original
 * values are positive or non-positive.
 *
 * \\(2f(l,r)=r-l+|(c_1-c_0)(r)-(c_1-c_0)(l)|\\).
 * The summation of the right term can be optimized using sorting.
 * Let \\( \Delta c=c_1-c_0 \\), \\( \Delta'c(i) \\) be the ordered version,
 * Then,
 * \\[ 2\sum_{0\le l<r\le n}f(l,r)=\frac{n(n+1)(n+2)}{6}
 * +\sum_{i=0}^n (2i-n)\Delta'c(i) \\]
 */
#include <bits/stdc++.h>
static_assert (sizeof (int) * CHAR_BIT >= 32);
typedef long long llong;
using namespace std;
#define FOR2(i, n) FOR (i, 0, n)
#define FOR3(i, p, q) for (int i = p; i < q; ++i)
#define DUMP(x) (string(#x) + ": " + to_string(x))

string& to_string(string& x) { return x; }

int main (int argc, char *argv[])
{
  int t; cin >> t;
  while (t--)
    {
      int n; cin >> n;
      cin.ignore();
      string s;
      getline(cin, s);
      // cerr << DUMP(n) << ' ' << DUMP(s) << '\n';
      vector<int> ones_sub_zeroes(n + 1);
      int ones = 0, zeroes = 0;
      for (int i = 0;; ++i)
	{
	  ones_sub_zeroes[i] = ones - zeroes;
	  if (i == n) break;
	  ++(s[i] == '1' ? ones : zeroes);
	}
      // cerr << "ones_sub_zeroes: ";
      // FOR3 (i, 0, n + 1) cerr << ones_sub_zeroes[i] << (i == n ? '\n' : ' ');
      sort(ones_sub_zeroes.begin(), ones_sub_zeroes.end());
      // cerr << "ones_sub_zeroes: ";
      // FOR3 (i, 0, n + 1) cerr << ones_sub_zeroes[i] << (i == n ? '\n' : ' ');
      llong left_sum = (llong) n * (n + 1) * (n + 2) / 6;
      llong right_sum = 0;
      FOR3 (i, 0, n + 1)
	{
	  right_sum += ((llong) 2 * i - n) * ones_sub_zeroes[i];
	}
      llong ans = (left_sum + right_sum) / 2;
      cout << ans << '\n';
    }
  return 0;
}
