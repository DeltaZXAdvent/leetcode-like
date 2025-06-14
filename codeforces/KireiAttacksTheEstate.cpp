#include <bits/stdc++.h>
#include <functional>
static_assert (sizeof (int) * CHAR_BIT >= 32);
typedef long long llong;
using namespace std;
#define FOR2(i, n) FOR3 (i, 0, n)
#define FOR3(i, p, q) for (int i = p; i < q; ++i)
#define DUMP(x) (string(#x) + ": " + to_string(x))

/**
 * https://codeforces.com/contest/2114/problem/E
 *
 * My solution is complicated.
 * 
 * Use data from p[i] rather than p[p[i]] might be better
 * because it reduces the pointer references but require additional data:
 * maxmimum and minimum threats. See the official tutorial.
 */
int main (int argc, char *argv[])
{
  int t;
  cin >> t;

  while (t-- > 0)
    {
      int n; cin >> n;
      vector<int> a(n + 1);
      FOR3 (i, 1, n + 1) cin >> a[i];

      vector<int> p(n + 1);
      set<int> graph[n + 1];
      
      FOR2 (i, n - 1)
	{
	  int v, u;
	  cin >> v >> u;
	  graph[v].insert(u);
	  graph[u].insert(v);
	}
      // FOR3 (i, 1, n + 1)
      // 	  cerr << DUMP(graph[i].size()) << '\n';

      p[1] = 1;
      queue<int> parents;
      parents.push(1);
      while (!parents.empty()) {
	int& parent = parents.front();
	// cerr << DUMP(parent) << '\n';
	for (auto iter = graph[parent].begin();
	     iter != graph[parent].end();
	     ++iter)
	  {
	    // cerr << DUMP(*iter) << '\n';
	    p[*iter] = parent;
	    graph[*iter].erase(parent); // use "if(*iter!=p[parent])" might be better
	    parents.push(*iter);
	  }
	graph[parent].clear();
	parents.pop();
      }
      // FOR3 (i, 1, n + 1) {
      // 	cerr << "i: " << i << " p[i]: " << p[i] << '\n';
      // }

      vector<llong> threat(n + 1);
      threat[1] = a[1];
      function<llong (int i)> compute_threat = [&](int i) -> llong {
	return threat[i] ? threat[i] :
	  (threat[i] = max((llong) a[i], a[i] - a[p[i]] + compute_threat(p[p[i]])));
      };
      FOR3 (i, 1, n + 1) {
	cout << compute_threat(i) << (i == n ? '\n' : ' ');
      }
      
    }
  return 0;
}
