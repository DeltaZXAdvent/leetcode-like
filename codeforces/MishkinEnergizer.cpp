#include <bits/stdc++.h>
static_assert (sizeof (int) * CHAR_BIT >= 32);
typedef long long llong;
using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    string s = cin.getline();
    int lct = 0, ict = 0, tct = 0;
    for (auto& ch: s) {
      switch(ch) {
      case 'L': lct++; break;
      case 'I': ict++; break;
      case 'T': tct++; break;
      }
    }
    lct = max(lct, ict, tct) - lct;
    tct = max(lct, ict, tct) - tct;
    ict = max(lct, ict, tct) - ict;
    // TODO strategy (not verified) : when there is position insert
    for (int i = 1; i <= n - 1; ++i) {
      if (s[i] != s[i - 1]) {
	
      }
    }
  }
  return 0;
}
