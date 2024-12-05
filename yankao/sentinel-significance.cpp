#define BOOST_TEST_MODULE cpp essentials
// BUG if you use g++ with -l flag it still links statistically?
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <cstdio>
#include <iterator>
#include <algorithm>
#include <type_traits>
#include <vector>
#include <iostream>
#include <random>
#include <limits>
#include <utility>
#include <boost/test/unit_test.hpp>
#include <boost/type_traits/has_less.hpp>
#include "timer.hpp"

using namespace std;

/**
 * Holy crap, what is this stupid monster...
 * I intended to write in C++ rationale...
 * C++ templates are statically-typed generic programming
 *
 * Template programming problems:
 * - TODO Unexpected implicit conversion of the argument during the initialization of a template class?
 *
 * SFINAE problems:
 * - what are these iterator tags?
 *   Maybe OK... but the rule for these fields seem very complex...
 * - It seems impossible to define a type alias in template arguments for the purpose of
 *   simplifying the type requirment
 * - the failure for the default type argument will not matter if there is a provided type parameter
 * - Maybe I shouldn't use SFINAE for this because generic programming does not care about potential bad
 *   template instantiations
 */
template <class iter,
	  enable_if_t <is_base_of_v <random_access_iterator_tag,
				     typename iterator_traits <iter>::iterator_category>
		       && is_copy_constructible_v <typename iterator_traits <iter>::value_type>
		       && is_copy_assignable_v <typename iterator_traits <iter>::value_type>
		       && boost::has_less<typename iterator_traits<iter>::value_type>::value,
		       int> = 0>
void insertion_sort (iter first, iter last)
{
  for (iter last_sorted = first; last_sorted != last; ++last_sorted)
    {
      auto element = *last_sorted;
      reverse_iterator i (last_sorted);
      for (; i != reverse_iterator (first); ++i)
	{
	  if (*i > element) *(i - 1) = *i;
	  else break;
	}
      *(i - 1) = element;
    }
}

/**
 * Don't care concepts
 */
template<class iter>
void insertion_sort_sentinel (iter first, iter last)
{
  if (first == last) return;
  iter start = first + 1;
  auto backup = *first;
  for (iter last_sorted = start; last_sorted != last; ++last_sorted)
    {
      auto element = *last_sorted;
      *first = element;
      reverse_iterator i (last_sorted);
      while (*i > element)
	{
	  *(i - 1) = *i;
	  ++i;
	}
      *(i - 1) = element;
    }
  iter j = start;
  for (; j != last; ++j)
    {
      if (*j < backup)
	*(j - 1) = *j;
      else break;
    }
  *(j - 1) = backup;
}

/**
 * I can't actually comprehend this now
 */
int my_rand (int min = numeric_limits <int>::min (),
	     int max = numeric_limits <int>::max ())
{
  static random_device dev;
  static mt19937 rng(dev ());
  return uniform_int_distribution (min, max) (rng);
}

vector <int> rand_vec (vector<int>::size_type size,
		       int min = numeric_limits <int>::min (),
		       int max = numeric_limits <int>::max ())
{
  vector <int>&& vec = vector <int>();
  while (size--)
    vec.push_back (my_rand (min, max));
  return vec;
}

template <class T>
ostream& operator<< (ostream& os, vector <T> vec)
{
  for (T& e: vec)
      os << e << ' ';
  os << endl;
  return os;
}

/**
 * Wow sentinel version is really faster:(the compiler probably cannot handle this)
 * Running 1 test case...
 * Start timer for task "insertion_sort (vec.begin (), vec.end ())"? 
 * Cost time: 2.6511
 * Start timer for task "insertion_sort_sentinel (vec2.begin (), vec2.end ())"? 
 * Cost time: 1.79313
 * 
 * *** No errors detected
 */
BOOST_AUTO_TEST_CASE (test_insertion_sort_sentinel)
{
  vector vec (rand_vec (15000, 10000, 99999)),
    vec2 = vec;
  
  // cout << vec;
  timer (insertion_sort (vec.begin (), vec.end ()));
  // cout << vec;
  // cout << vec2;
  timer (insertion_sort_sentinel (vec2.begin (), vec2.end ()));
  // cout << vec2;
  BOOST_TEST (vec == vec2);
}
