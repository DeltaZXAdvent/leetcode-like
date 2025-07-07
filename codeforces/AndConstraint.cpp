/**
 * \file
 * <https://codeforces.com/contest/2119/problem/E>
 *
 * TODO
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
      int st, n;
      cin >> st >> n;
      vector<int> w(n);
      FOR (i, 0, n) cin >> w[i];
      multimap<int, int> edges;
      FOR (i, 0, n - 1)
	{
	  int u, v;
	  cin >> u >> v;
	  --u; --v;
	  edges.insert({u, v});
	  edges.insert({v, u});
	}
      int result = 0;

      vector<int> p(n);
      // TODO there could be a continuation, function vs function pointer?
      function<void (int, int)> dfs = [&] (int i, int parent)
      {
	auto [from, to] = edges.equal_range(i);
	for (auto it = from; from != to; ++from)
	  if (it->second != parent)
	    {
	      p[i->first] = i;
	      dfs(i->first, i);
	    }
      };
      dfs(0, 0);
      auto down_moves = [&] (int i)
      {
      };
      int i = st;
      while (w[i] != 1 && i != 0)
	i = p[i];
      result = max(result, down_moves(i));
    }
  return 0;
}
