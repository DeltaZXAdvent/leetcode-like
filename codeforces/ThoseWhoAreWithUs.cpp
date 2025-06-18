#include <bits/stdc++.h>
static_assert (sizeof (int) * CHAR_BIT >= 32);
typedef long long llong;
using namespace std;
#define FOR2(i, n) FOR3 (i, 0, n)
#define FOR3(i, p, q) for (int i = p; i < q; ++i)
#define DUMP(x) (string(#x) + ": " + to_string(x))

/**
 * https://codeforces.com/contest/2121/problem/C
 */

struct automaton
{
  struct point { int row; int column; };
  union attribs_union {
    int row;
    int column;
    pair<point, point> centers;
    point center;
    point cell;
    attribs_union() { }
  } attribs;
  enum
    {
      none,
      one_cell,
      one_row,
      one_column,
      two_centers,
      one_center,
      null
    } state;
  int maximum;
  automaton()
  {
    state = none;
    maximum = 0;
  }
  void check(point cell, int value)
  {
    // cerr << state << ' ';
    if (value < maximum) return;
    if (value > maximum)
      {
	maximum = value;
	state = one_cell;
	attribs.cell = cell;
	return;
      }
    switch (state)
      {
      case none:
	state = one_cell;
	attribs.cell = cell;
	break;
      case one_cell:
	if (cell.row == attribs.cell.row)
	  {
	    int r = cell.row;
	    state = one_row;
	    attribs.row = r;
	  }
	else if (cell.column == attribs.cell.column)
	  {
	    int c = cell.column;
	    state = one_column;
	    attribs.column = cell.column;
	  }
	else
	  {
	    point p = attribs.cell;
	    state = two_centers;
	    attribs.centers =
	      make_pair(point { .row = p.row, .column = cell.column },
			point { .row = cell.row, .column = p.column });
	  }
	break;
      case one_row:
	if (cell.row != attribs.row)
	  {
	    int r = attribs.row;
	    state = one_center;
	    attribs.row = r;
	    attribs.column = cell.column;
	  }
	break;
      case one_column:
	if (cell.column != attribs.column)
	  {
	    int c = attribs.column;
	    state = one_center;
	    attribs.column = c;
	    attribs.row = cell.row;
	  }
	break;
      case two_centers:
	if (cell.row == attribs.centers.first.row
	    || cell.column == attribs.centers.first.column)
	  {
	    point ctr = attribs.centers.first;
	    state = one_center;
	    attribs.center = ctr;
	  }
	else if (cell.row == attribs.centers.second.row
		 || cell.column == attribs.centers.second.column)
	  {
	    point ctr = attribs.centers.second;
	    state = one_center;
	    attribs.center = ctr;
	  }
	else
	  {
	    state = null;
	  }
	break;
      case one_center:
	if (cell.row != attribs.center.row
	    && cell.column != attribs.center.column)
	  {
	    state = null;
	  }
	break;
      case null:
	break;
      }
  }
};

int main (int argc, char *argv[])
{
  int t; cin >> t;
  while (t--)
    {
      int n, m; cin >> n >> m;
      automaton am;
      // cerr << "am.state: ";
      FOR2 (i, n) FOR2 (j, m)
	{
	  int value;
	  cin >> value;
	  am.check(automaton::point { .row = i, .column = j },
		   value);
	}
      // cerr << am.state << '\n';
      if (am.state != automaton::null)
	cout << am.maximum - 1 << '\n';
      else
	cout << am.maximum << '\n';
    }

  return 0;
}
