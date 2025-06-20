#include <bits/stdc++.h>
static_assert (sizeof (int) * CHAR_BIT >= 32);
typedef long long llong;
using namespace std;
#define FOR2(i, n) FOR3 (i, 0, n)
#define FOR3(i, p, q) for (int i = p; i < q; ++i)
#define DUMP(x) (string(#x) + ": " + to_string(x))

/**
 * https://codeforces.com/contest/2121/problem/C
 *
 * Lesson: Don't care about single-pass or multiple-pass
 * Maybe my solution is not cache-friendly?
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
	    attribs.column = c;
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
	    attribs.center = { r, cell.column };
	  }
	break;
      case one_column:
	if (cell.column != attribs.column)
	  {
	    int c = attribs.column;
	    state = one_center;
	    attribs.center = { cell.row, c };
	  }
	break;
      case two_centers:
	{
	  bool first_ok = cell.row == attribs.centers.first.row
	    || cell.column == attribs.centers.first.column,
	    second_ok = cell.row == attribs.centers.second.row
	    || cell.column == attribs.centers.second.column;
	  if (first_ok && second_ok) // seems not possible for there is an order
	    ;
	  else if (first_ok)
	    {
	      point ctr = attribs.centers.first;
	      state = one_center;
	      attribs.center = ctr;
	    }
	  else if (second_ok)
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
	}
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
  if (false)			// t == 10000 for debug
    {
      for (int k = 1; k <= t; ++k)
	{
	  int n, m; cin >> n >> m;
	  automaton am;
	  // cerr << "am.state: ";
	  FOR2 (i, n) FOR2 (j, m)
	    {
	      int value;
	      cin >> value;
	      if (k == 206)
		{
		  cout << '(' << am.state << ')' << value << (j == m - 1 ? '\n' : ' ');
		  am.check(automaton::point { .row = i, .column = j },
			   value);
		}
	    }
	  if (k == 206)
	    cout << '(' << am.state << ')' << '\n';
	  // cerr << am.state << '\n';
	  if (k == 206)
	    {
	      cout << DUMP(n) << '\n'
		   << DUMP(m) << '\n'
		   << DUMP(am.state) << '\n'
		   << DUMP(am.attribs.center.row) << '\n'
		   << DUMP(am.attribs.center.column) << '\n';
	      if (am.state != automaton::null)
		cout << am.maximum - 1 << '\n';
	      else
		cout << am.maximum << '\n';
	    }
	}
    }
  else
    {
      for (int k = 1; k <= t; ++k)
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
    }

  return 0;
}
