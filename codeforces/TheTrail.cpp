#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <cstdint>
using namespace std;
using i64 = int_fast64_t;
ostream& operator<<(ostream& os, vector <i64>& a)
{
  int i = 0;
  if (a.size () == 0) return os;
  while (true)
    {
      os << a[i];
      if (++i == a.size ()) break;
      os << " ";
    }
  return os;
}
ostream& operator<<(ostream& os, vector <vector <i64> >& a)
{
  for (vector <i64>& row: a)
    os << row << "\n";
  return os;
}

void restoreAltitudesAndPrint (int n, int m, string& s, vector <vector <i64> >& a)
{
  int i = 0, j = 0;
  for (int k = 0; k < s.length (); ++k) {
    switch (s[k]) {
    case 'D':
      a[i][j] = -accumulate (a[i].begin (), a[i].end (), (i64) 0);
      cout << a[i] << "\n";
      ++i;
      break;
    case 'R':
      a[i][j] = -accumulate (a.begin (), a.end (), (i64) 0,
			     [=] (i64 acc, vector <i64>& row) { return acc + row[j]; });
      ++j;
      break;
    }
  }
  a[i][j] = -accumulate (a[i].begin (), a[i].end (), (i64) 0);
  cout << a[i] << "\n";
}

int main (int argc, char *argv[])
{
  int t;
  cin >> t;
  while (t--)
    {
      int n, m;
      cin >> n >> m;
      string s;
      cin >> s;
      vector <vector <i64> > a (n, vector <i64> (m, 0));
      for (vector <i64>& row: a)
	for (i64& element: row)
	  cin >> element;
      restoreAltitudesAndPrint (n, m, s, a);
    }
  return 0;
}
