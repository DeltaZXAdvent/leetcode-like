// https://blog.csdn.net/2301_76848549/article/details/134757695?csdn_share_tail=%7B%22type%22%3A%22blog%22%2C%22rType%22%3A%22article%22%2C%22rId%22%3A%22134757695%22%2C%22source%22%3A%222301_76848549%22%7D
#include "utils.hpp"
// using dynamic programming, we want to get the values of a function f (m, n).
// We can see from the graph that f (m, n) = min (f (m-1, n) + 1, f (m, n-1) + 1, f (m-1, n-1) + 1 if A[m-1] == B[m-1])

// Let's not care more about optimization.

struct cache_t
{
  std::unique_ptr<int[]> data;
  size_t m, n;
  cache_t (size_t m, size_t n): data (std::make_unique<int[]> (m * n)),
				m (m), n (n) { }
  int& cached_f (int i, int j)
  {
    // Some argument checking...
  
    return data[n * i + j];
  }

  int f (size_t i, size_t j)
  {
    if (i == 0) return j;
    if (j == 0) return i;
    return cached_f (i, j);
  }
};

int shortest_path (string s, string t)
{
  cache_t cache (s.size (), t.size ());
  int m = cache.m,
    n = cache.n;
  for (size_t i = 1; i <= m; i++)
    for (size_t j = 1; j <= n; j++)
      {
	int tmp_min = min (cache.f (i-1, j), cache.f (i, j-1)) + 1;
	if (s[i - 1] == t[j - 1])
	  cache.cached_f (i, j) = min (tmp_min, cache.f (i-1, j-1) + 1);
	else cache.cached_f (i, j) = tmp_min;
      }
  return cache.f (m, n);
}

int main (int argc, char *argv[])
{
  string s = read_capital_string ();
  std::cout << s; printnl ();
  expect (' ');
  string t = read_capital_string ();
  std::cout << t; printnl ();
  print_int (shortest_path (s, t)); printnl ();
  return 0;
}
