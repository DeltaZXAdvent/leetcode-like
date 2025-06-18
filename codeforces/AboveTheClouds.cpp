#include <bits/stdc++.h>
static_assert (sizeof (int) * CHAR_BIT >= 32);
typedef long long llong;
using namespace std;
#define FOR2(i, n) FOR3 (i, 0, n)
#define FOR3(i, p, q) for (int i = p; i < q; ++i)

/**
 * https://codeforces.com/contest/2121/problem/B
 */

int main (int argc, char *argv[])
{
  int t; cin >> t;
  while (t--)
    {
      int n; cin >> n;
      string s;
      cin.ignore();
      getline(cin, s);
      // cerr << "hi\n" << s.length() << ' ' << n << '\n';
      auto decide = [&] () -> bool
      {
	unordered_set<char> present;
	FOR3 (i, 1, n - 1)
	  {
	    if (present.find(s[i]) != present.end())
	      return true;
	    else present.insert(s[i]);
	  }
	if (present.find(s[0]) != present.end()
	    || present.find(s[n - 1]) != present.end())
	  return true;
	return false;
      };
      cout << (decide() ?  "Yes" : "No") << '\n';
    }
  return 0;
}
