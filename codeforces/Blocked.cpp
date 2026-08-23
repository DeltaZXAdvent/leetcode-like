/**
 * \file
 * <https://codeforces.com/contest/2220/problem/A>
 *
 * 
 */
#include <bits/stdc++.h>
static_assert (sizeof (int) * CHAR_BIT >= 32);
typedef long long llong;
using namespace std;
#define FOR2(i, n) FOR3 (i, 0, n)
#define FOR3(i, p, q) for (int i = p; i < q; ++i)
#define DUMP(x) (string(#x) + ": " + to_string(x))
string& to_string (string& x) { return x; }

bool vector_sorted_has_repetition (vector<int> &a)
{
  if (a.empty ())
    return false;
  for (auto it = a.begin (); next (it) != a.end (); ++it)
    if (*it == *next (it))
      return true;
  return false;
}

int main(int argc, char *argv[])
{
  // TODO C++ sort and repetition check at the same time?
  int t;
  cin >> t;
  while (t--)
    {
      int n;
      cin >> n;
      vector<int> a;
      int ai;
      FOR2 (i, n)
	{
	  cin >> ai;
	  a.push_back (ai);
	}
      sort (a.begin(), a.end(), greater<int> ());
      if (vector_sorted_has_repetition (a))
	cout << -1;
      else
	for (auto ai: a)
	  cout << ai << ' ';
      cout << '\n';
    }
  return 0;
}
