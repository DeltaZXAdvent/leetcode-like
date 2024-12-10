#include <iostream>
#include <vector>
#include <random>
#include "util.hpp"
using namespace std;
/**
 * I can't actually comprehend this now
 */
int my_rand (int min, int max)
{
  static random_device dev;
  static mt19937 rng(dev ());
  return uniform_int_distribution (min, max) (rng);
}

vector <int> rand_vec (vector<int>::size_type size,
		       int min, int max)
{
  vector <int>&& vec = vector <int>();
  while (size--)
    vec.push_back (my_rand (min, max));
  return vec;
}

namespace my
{
  void getline ()
  {
    cin.ignore (std::numeric_limits <int>::max (), '\n');
  }
}

