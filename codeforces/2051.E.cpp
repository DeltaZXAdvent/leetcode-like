/**
 * https://codeforces.com/contest/2051/problem/E
 *
 * Just sort $a_i$ and $b_i$ and traverse??
 *
 * TODO
 * What? Doesn't work??? Boring...
 */
#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>
#include <limits>

#define print_int(i) fprintf (stderr, #i ": %d\n", i)
#define print_long(l) fprintf (stderr, #l ": %ld\n", l)

using namespace std;

long long max_earnings (long &n, long &k, vector <long> &a, vector <long> &b)
{
  sort (a.begin (), a.end (), greater_equal <> ());
  sort (b.begin (), b.end (), greater_equal <> ());
  long price_candidate = numeric_limits <long>::max ();
  long long earnings = 0;
  vector <long>::iterator
    a_iter = a.begin (),
    b_iter = b.begin ();
  long sales = 0,
    negative_reviews = 0;
  while (true)
    {
      bool a_end = a_iter == a.end (),
	b_end = b_iter == b.end ();
      long price;
      if (a_end)
	{
	  if (b_end) break;
	  else price = *b_iter;
	}
      else
	{
	  if (b_end) price = *a_iter;
	  else price = max (*a_iter, *b_iter);
	}
      for (; b_iter != b.end () && *b_iter >= price; ++b_iter)
	{
	  ++sales;
	  ++negative_reviews;
	}
      for (; a_iter != a.end () && *a_iter >= price; ++a_iter)
	--negative_reviews;
      if (negative_reviews <= k)
	{
	  long long new_earnings = sales * price;
	  if (new_earnings > earnings)
	    {
	      price_candidate = price;
	      earnings = new_earnings;
	    }
	}
    }
  return earnings;
}

int main (int argc, char *argv[])
{
  int t;
  scanf ("%d\n", &t);
  // print_int (t);
  while (t--)
    {
      long n, k;
      scanf ("%ld%ld\n", &n, &k);
      // print_long (n);
      // print_long (k);
      {
	vector <long> a (n), b (n);
	for (long &ai: a) scanf ("%ld", &ai);
	scanf ("\n");
	for (long &bi: b) scanf ("%ld", &bi);
	scanf ("\n");
	printf ("%lld\n", max_earnings (n, k, a, b));
      }
    }
  return 0;
}
