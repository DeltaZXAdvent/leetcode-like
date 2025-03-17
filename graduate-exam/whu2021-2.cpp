#include <bits/stdc++.h>
using namespace std;
#define DUMP(obj) (string(#obj) + ": " + to_string(obj))

optional<vector<int>> get_vector_internal(istream& is)
{
  vector<int> vec;
  while (true) {
    int n;
    is >> n;
    if (!is)
      return nullopt;
    vec.push_back(move(n));
    switch (is.get()) {
    case ' ':
      continue;
    case '\n':
      return vec;
    default:
      return nullopt;
    }
  }
}

optional<vector<int>> get_vector(istream& is)
{
  auto flags = is.flags();
  is >> noskipws;
  optional<vector<int>> res = get_vector_internal(is);
  is.flags(flags);
  return res;
}

optional<vector<vector<int>>> get_matrix(istream& is)
{
  vector<vector<int>> res;
  auto first_opt = get_vector(is);
  if (!first_opt) return nullopt;
  auto first = move(first_opt).value();
  
  auto cols = first.size();
  res.push_back(move(first));
  while (is.peek() != '\n') {
    auto vopt = get_vector(is);
    if (!vopt) return nullopt;
    auto v = move(vopt).value();
    
    if (v.size() != cols) return nullopt;
    res.push_back(move(v));
  }
  is.get();
  return res;
}

vector<vector<double>> get_adjacent_avg(vector<vector<int>>& m)
{
  auto r = m.size(),
    c = m[0].size();
  cerr << DUMP(r) << '\n' << DUMP(c) << '\n';
  cerr << DUMP(m[1][1]) << '\n';
  auto res = vector<vector<double>>(r, vector<double>(c));
  cerr << "yes\n";
  for (auto i = 0 * r; i < r; ++i)
    for (auto j = 0 * c; j < c; ++j) {
      int sum = m[i][j], num = 1;
      cerr << DUMP(i) << '|' << DUMP(j) << '\n';
      if (i >= 1) {
	sum += m[i - 1][j];
	++num;
      }
      if (i + 1 < r) {
	sum += m[i + 1][j];
	++num;
      }
      if (j >= 1) {
	sum += m[i][j - 1];
	++num;
      }
      if (j + 1 < c) {
	sum += m[i][j + 1];
	++num;
      }
      res[i][j] = sum * 1.0 / num;
      cerr << DUMP(i) << '|' << DUMP(j) << '\n';
    }
  return res;
}

template<class X>
ostream& print(ostream& os, X& a, char delim)
{
  for (auto i = a.begin (); i != a.end (); ++i)
    {
      os << *i;
      if (next(i) != a.end())
	os << delim;
    }
  return os;
}

template<class X>
ostream& print(ostream& os, X& a, char outerDelim, char innerDelim)
{
  for (auto i = a.begin (); i != a.end (); ++i)
    {
      print(os, *i, innerDelim);
      if (next(i) != a.end())
	os << outerDelim;
    }
  return os;
}


int main() {
  auto mopt = get_matrix(cin);
  if (!mopt) {
    cerr << string ("invalid input\n");
    return 0;
  }
  auto m = move(mopt).value();
  cerr << DUMP(m.size()) << '\n'
       << DUMP(m[0].size()) << '\n';
  print(cerr, m, '\n', ' ') << '\n';
  auto avg = get_adjacent_avg(m);
  cerr << string ("yes\n");
  cout << fixed << setprecision(2);
  print(cout, avg, '\n', ' ') << '\n';
  return 0;
}
