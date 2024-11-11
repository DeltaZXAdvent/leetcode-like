// https://blog.csdn.net/2301_76848549/article/details/135311214?csdn_share_tail=%7B%22type%22%3A%22blog%22%2C%22rType%22%3A%22article%22%2C%22rId%22%3A%22135311214%22%2C%22source%22%3A%222301_76848549%22%7D
// * Different specification
// Find segments to cover points
// - number of segments :: s
// - size of point range :: l
// * Solution
// 1. If there are gaps no shorter than the length of the longest segment,
//    we can consider the two parts seperately.
// 2. For every segment, there is a gap length threshold,
//    in cases that which is overcome, there is no use for that segment across the gap
// 3. Are the thresholds ascending by the segment length?
// * OK, fuck, just use linear programming and there may be some branch and cut
// * Maintain an array
//
// * Branch and cut may be efficient for large number of segments, but let's not discuss about it here

#include <iostream>
#include <stdexcept>
#include <map>
#include <limits>
#include <algorithm>
#include <functional>
#include <cassert>
#include <sstream>
#include "utils.hpp"
using namespace std;
typedef vector<int> vec;
int segments_cover_points (vec segments, vec costs, vec points);
int wonderland (vec costs, vec days)
{
  if (not (costs.size () == 4))
    throw invalid_argument (__func__);
  return segments_cover_points (vec {1, 3, 7, 30}, costs, days);
}

int segments_cover_points (vec segments, vec costs, vec points)
{
  "points must be sorted";
  vec choice (points.size ()),
    total (points.size ());
  for (int p = 0; p < points.size (); ++p)
    {
      print_int_of (p);
      total[p] = numeric_limits<int>::max ();
      for (int s = 0; s < segments.size (); ++s)
	{
	  print_int_of (points[p] - segments[s]);
	  vec::iterator q =
	    lower_bound (points.begin (), points.begin () + p,
			 points[p] - segments[s]); // lower_equal_bound
	  print_int_of (q - points.begin ());
	  int new_total = costs[s];
	  if (points[p] - segments[s] < points.front ())
	    new_total += 0;
	  else if (q == points.begin () + p)
	    {
	      if (p == 0)
		new_total += 0;
	      else new_total += *(total.begin () + p - 1);
	    }
	  else
	    new_total += *(total.begin () + (q - points.begin ()));

	  print_int_of (new_total);
	  if (new_total < total[p])
	    {
	      total[p] = new_total;
	      choice[p] = s;
	    }
	}
      print_int_of (total[p]);
    }
  for (int t: total)
    cout << t << ' ';
  cout << endl;
  return total[points.size () - 1];
}

int main (int argc, char *argv[])
{
  vec costs (4);
  for (int &cost: costs)
    cin >> cost;
  for (int &cost: costs)
    {
      cout << cost << ' ';
    }
  cout << endl;
  // istream::sentry s (cin);
  // cin >> noskipws;
  // while (true)
  //   {
  //     int i;
  //     cin >> i;
  //     cout << i << ' ';
  //     days.push_back (i);
  //     if (cin.get () == '\n')
  // 	break;
  //     else
  // 	{
  // 	  // printf ("%c\n", (char) cin.get ());
  // 	  // exit (-1);
  // 	  assert (cin.get () == ' ');
  // 	}
  //   }
  // cout << endl;
  //
  // OK I give up using C++ iostream

  cin.get ();
  vec days = read_space_seperated_ints_inf ();
  print_vector (days);
  print_int_of (days.size ());
  cout << wonderland (costs, days) << endl;
  return 0;
}
