#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
using namespace std;
typedef vector<int> vec;
// struct position
// {
//   bool interval;
//   int pos;
// };
// position binary_search (vec v, int start, int end, int e)
// {
//   if (start == end)
//     return { .interval = true, .pos = start };
//   int mid = (start + end) / 2;
//   if (v[mid] == e) return { .interval = false, .pos = mid };
//   else if (v[mid] > e)
//     return binary_search (v, mid + 1, end, e);
//   else return binary_search (v, start, mid, e);
// }

// all of the vectors are strictly ascending

// return the index beginning with 1 or the position of the interval
int binary_search (vec v, int start, int end, int e)
{
  if (start == end)
    return start;
  int mid;
  if (start != end - 1)
    mid = (e - v[start]) * (end - start) / (v[end - 1] - v[start]) + start;
  else mid = (start + end) / 2;
  if (not (start <= mid && mid < end))
    {
      // cout << "change mid" << endl;
      mid = (start + end) / 2;
    }
  if (v[mid] == e) return mid + 1;
  else if (v[mid] > e)
    return binary_search (v, start, mid, e);
  else 
    return binary_search (v, mid + 1, end, e);
}

vec::iterator binary_search_normal (vec::iterator begin, vec::iterator end, int e)
{
  if (begin == end)
    return begin;
  vec::iterator mid = begin + (end - begin) / 2;
  if (*mid == e) return mid + 1;
  else if (*mid > e)
    return binary_search_normal (begin, mid, e);
  else
    return binary_search_normal (mid + 1, end, e);
}

vec binary_search_multiple (vec v, int start, int end, vec u)
{
  vec res;
  for (int ue: u)
    {
      res.push_back(start = binary_search (v, start, end, ue));
      // cout << "new start: " << start << endl;
    }
  return res;
}
vec binary_search_normal_multiple (vec::iterator begin, vec::iterator end, vec u)
{
  vec res;
  for (int ue: u)
    {
      begin = binary_search_normal (begin, end, ue);
      res.push_back (*begin);
      cout << "new begin: " << *begin << endl;
    }
  return res;
}

int search (vec::iterator start, vec::iterator end, int j)
{
  vec res;
  vec::iterator i = start;
  while (*i < j && i != end)
    ++i;
  if (i == end or *i != j)
    return i - start;
  else return i - start + 1;
}

vec search_multiple (vec::iterator start, vec::iterator end, vec u)
{
  vec res;
  vec::iterator i = start,
    j = u.begin ();
  for (; j != u.end (); ++j)
    {
      while (*i < *j && i != end)
	++i;
      if (i == end or *i != *j)
	res.push_back (i - start);
      else res.push_back (i - start + 1);
    }
  return res;
}

// TODO random seed
// generates an array and sorts it (this is probably not that efficient)
vec random_sorted_vector (int l, default_random_engine &re)
{
  uniform_int_distribution rg;
  vec v (l);
  for (int &ve: v)
    ve = rg (re);
  sort (v.begin (), v.end ());
  return v;
}

ostream &operator<< (ostream &is, vec v)
{
  is << '[';
  for (int e: v)
    is << e << ',';
  is << ']';
  return is;
}

struct task_timer
{
  chrono::system_clock clock;
  chrono::time_point<chrono::system_clock> begin;
  void start (string task)
  {
    cout << "Start timer for task \"" << task << "\"?" << endl;
    cin.ignore (numeric_limits<int>::max (), '\n');
    begin = clock.now ();
  }
  void stop ()
  {
    cout << "Cost time: "
	 << chrono::duration_cast<chrono::duration<double>> (clock.now () - begin).count ()
	 << endl;
  }
};

#define tt_start(exp) tt.start (string (#exp)); (exp)
// why is modified binary_search especially slower????
// OK... maybe it's slow when applied to a small-sized search array.
int main ()
{
  random_device rd;
  default_random_engine re;
  uniform_int_distribution ud;
  task_timer tt;
  vec v, u, sm;
  re.seed (rd ());
  int size = 1024*1024;
  int i;
  tt_start (v = random_sorted_vector (size, re));
  tt.stop ();
  tt_start (u = random_sorted_vector (10000, re));
  tt.stop ();
  tt_start (cout << v << endl << u << endl);
  tt.stop ();
  for (int k = 0; k < 1; ++k)
    {
      tt_start (cout << binary_search_normal (v.begin (), v.end (), ud (re)) - v.begin () << endl);
      tt.stop ();
      tt_start (cout << binary_search (v.begin (), v.end (), ud (re)) << endl);
      tt.stop ();
      tt_start (cout << search (v.begin (), v.end (), ud (re)) << endl);
      tt.stop ();
    }
  tt_start (search_multiple (v.begin (), v.end (), u));
  tt.stop ();
  tt_start (cout << binary_search_normal_multiple (v.begin (), v.end (), u) << endl);
  tt.stop ();
  tt_start (cout << binary_search_multiple (v, 0, v.size (), u) << endl);
  tt.stop ();
  return 0;
}
