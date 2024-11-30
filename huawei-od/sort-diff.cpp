#include "utils.hpp"
#include <algorithm>
vector<int>& sort_diff (int pivot, vector<int>& array)
{
  if (array.size () <= 1) return array;
  auto mid = array.begin () + array.size () / 2;
  vector left_in_place (array.begin (), mid),
    right_in_place(mid, array.end ());
  sort_diff (pivot, left_in_place);
  sort_diff (pivot, right_in_place);
  vector left (left_in_place),
    right (right_in_place);
  auto left_it = left.begin (), right_it = right.begin (),
    it = array.begin ();
  while (left_it != left.end () && right_it != right.end ())
    {
      int left_diff = *left_it - pivot,
	right_diff = *right_it - pivot;
      if (abs (left_diff) < abs (right_diff) ||
	  abs (left_diff) == abs (right_diff) && left_diff < 0)
	{
	  *it++ = *left_it++;
	}
      else
	{
	  *it++ = *right_it++;
	}
    }
  while (left_it != left.end ())
    *it++ = *left_it++;
  while (right_it != right.end ())
    *it++ = *right_it++;
  return array;
}

struct diff_compare
{
  int pivot;
  bool operator() (int left, int right)
  {
    int left_diff = left - pivot,
      right_diff = right - pivot;
    return abs (left_diff) < abs (right_diff) ||
      left_diff + right_diff == 0 && left_diff < 0;
  }
};

vector<int>& sort_diff_lib (int pivot, vector<int>& array)
{
  diff_compare cmp = { .pivot = pivot };
  std::stable_sort (array.begin (), array.end (), cmp);
  return array;
}

int main (int argc , char * argv[])
{
  auto first_line = read_space_seperated_ints (2);
  int pivot = first_line[0];
  assert (first_line[1] >= 0);
  size_t ct = first_line[1];
  auto heights = read_space_seperated_ints (ct);
  sort_diff_lib (pivot, heights);
  print_vector (heights);
  return 0;
}
