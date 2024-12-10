// #define BOOST_TEST_MODULE sentinel test
// BUG if you use g++ with -l flag it still links statistically?
#define BOOST_TEST_DYN_LINK
// #define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>
#include <algorithm>
#include <iterator>
#include <vector>
#include <iostream>
#include <type_traits>
#include <boost/type_traits/has_less.hpp>
#include <cassert>
#include <functional>

#include "util.hpp"
#include "timer.hpp"
#include "textbook-qsort.hpp"

using namespace std;

template <class iter>
void binary_insertion_sort (iter first, iter last)
{
  for (iter last_sorted = first; last_sorted != last; ++last_sorted)
    {
      auto element = *last_sorted;
      iter upper = upper_bound (first, last_sorted, element);
      reverse_iterator i (last_sorted);
      for (i; i != reverse_iterator (upper); ++i)
	*(i - 1) = *i;
      *(i - 1) = element;
    }
}

template <class iter,
	  enable_if_t <is_base_of_v <random_access_iterator_tag,
				     typename iterator_traits <iter>::iterator_category>
		       && is_copy_constructible_v <typename iterator_traits <iter>::value_type>
		       && is_copy_assignable_v <typename iterator_traits <iter>::value_type>
		       && boost::has_less<typename iterator_traits<iter>::value_type>::value,
		       int> = 0>
void insertion_sort (iter first, iter last);

BOOST_AUTO_TEST_CASE (test_sort)
{
  vector <int> foo = rand_vec (900000, 100000, 999999),
    bar = foo, var = foo;
  my::getline ();
  display (foo);
  my::getline ();
  display (bar);
  display (sizeof (int));
  display (sizeof (foo.begin ()));
  timer (qsort_textbook (foo.begin (), foo.end ()));
  BOOST_TEST (foo != bar);
  // my::getline ();
  // display (foo);
  timer (qsort_declarative (bar.begin (), bar.end ()));
  timer (qsort_ita <vector <int> > (var, 0, var.size () - 1));
  BOOST_TEST ((foo == bar && bar == var));
  my::getline ();
  if (foo != bar)
    {
      display (foo[0]);
      display (bar[0]);
      my::getline ();
      transform (foo.begin (), foo.end (),
		 bar.begin (), foo.begin (),
		 minus <int>());
      display (foo[0]);
      display (bar[0]);
    }
  my::getline ();
  display (bar);
}
