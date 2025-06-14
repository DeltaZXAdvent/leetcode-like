#include <bits/stdc++.h>
static_assert (sizeof (int) * CHAR_BIT >= 32);
typedef long long llong;
using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--)
    {
      int n;
      cin >> n;
      // TODO getline or .getline?
      bool f = true;
      int ct1 = 0, ct2 = 0;
      cin.get();
      for (int i = 0; i < n; ++i){
	if (cin.get() == '0')
	  {
	    if (f) ct1++; else ct2++;
	  }
	f = !f;
      }
      cin.get();
      f = false;
      for (int i = 0; i < n; ++i){
	if (cin.get() == '0')
	  {
	    if (f) ct1++; else ct2++;
	  }
	f = !f;
      }
      cerr << ct1 << ' ' << ct2 << '\n';
      cout << (ct1 >= (n + 1) / 2 && ct2 >= n / 2 ? "yes" : "no") << '\n';
    }
  return 0;
}
