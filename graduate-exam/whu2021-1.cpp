#include <bits/stdc++.h>
using namespace std;

unordered_set <int> removeDuplicate (vector <int> &input)
{
  unordered_map <int, int> counts;
  for (auto i: input)
    {
      if (counts.find (i) == counts.end ())
	counts [i] = 0;
      counts[i] += 1;
    }
  auto ans = unordered_set <int> ();
  for (auto [i, count]: counts)
    if (count == 1)
      ans.insert (i);
  return ans;
}

template<class T, class F>
vector<T> fill_vec (F& f, typename vector<T>::size_type n)
{
  auto A = vector<T> ();
  A.reserve (n);
  for (auto i = 0 * n; i < n; ++i)
    A.push_back (f ());
  return A;
}

template<class X1, class X2>
bool range_eq (X1& a, X2& b)
{
  return make_pair (a.end (), b.end ())
    == mismatch (a.begin (), a.end (),
		 b.begin (), b.end ());
}

template<class X>
ostream& operator<<(ostream& os, X& a)
{
  for (auto i = a.begin (); i != a.end (); ++i)
    {
      os << *i;
      os << (next(i) == a.end() ? '\n' : ' ');
    }
  return os;
}

int main (int argc, char *argv[])
{
  int m = 9, n = 15;
  auto d = uniform_int_distribution (0, m);
  auto g = mt19937 (random_device () ());
  auto f = [&] () {
    return d (g);
  };
  auto A = fill_vec<int, decltype (f)> (f, n);
  auto S = removeDuplicate (A);
  cout << A;
  sort (A.begin (), A.end ());
  cout << A << S;
  return 0;
}
