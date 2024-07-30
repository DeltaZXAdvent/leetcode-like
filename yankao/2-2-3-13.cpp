#include <iostream>
#include <vector> 
#include <list>
#include <limits>
using namespace std;
typedef vector<int> vec;
struct range {
  int from, to;
};
typedef list<range> lis;
int minimum (vec v)
{
  lis l = {{ 1, numeric_limits<int>::max () }};
  for (int e: v) {
    for (lis::iterator it = l.begin (); it != l.end (); ++it) {
      if (it->from <= e && e <= it->to) {
	if (e < it->to) l.insert (next (it), { e + 1, it->to });
	if (it->from < e) it->to = e - 1;
	else l.erase (it);
	break;
      }
    }
  }
  return l.front ().from;
}

int main (int argc, char *argv[])
{
  cout << minimum ({-5, 3, 2, 3}) << endl
       << minimum ({1, 2, 3}) << endl;
  return 0;
}
