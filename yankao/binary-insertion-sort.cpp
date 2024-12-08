// #define BOOST_TEST_MODULE sentinel test
// BUG if you use g++ with -l flag it still links statistically?
#define BOOST_TEST_DYN_LINK
// TODO wtf link failure
// #define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>
#include <algorithm>
#include <iterator>
#include <vector>
#include <iostream>
#include <type_traits>
#include <boost/type_traits/has_less.hpp>

#include "util.hpp"
#include "timer.hpp"

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

BOOST_AUTO_TEST_CASE (test_binary_insertion_sort)
{
  vector <int> foo = rand_vec (15000, 10000, 99999),
    bar = foo;
  cout << "foo: ";
  cin.ignore (std::numeric_limits <int>::max (), '\n');
  cout << foo;
  cout << "bar: ";
  cin.ignore (std::numeric_limits <int>::max (), '\n');
  cout << bar;
  timer (insertion_sort (foo.begin (), foo.end ()));
  timer (binary_insertion_sort (bar.begin (), bar.end ()));
  cout << "foo: ";
  cin.ignore (std::numeric_limits <int>::max (), '\n');
  cout << foo;
  cout << "bar: ";
  cin.ignore (std::numeric_limits <int>::max (), '\n');
  cout << bar;
}
