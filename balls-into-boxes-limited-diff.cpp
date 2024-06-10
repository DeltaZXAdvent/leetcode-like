// https://blog.csdn.net/2301_76848549/article/details/134624658
#include "utils.hpp"
// rearrange the staff by the original order and how many pies they get
// there can be only one rearrangement for every distribution
// and every rearrangement corresponds to m! distributions or less because there may be same amount of pies
// So let's think of another way to model this
//
// Firstly the problem is talking about the ordered set
// Secondly every gap must be less than a specific amount
// We can try inclusion-exclusion principles
// There are (m - 1) gaps
// But it's hard to calculate when the positions of the gaps are certain
// Because when the gap positions are different, the number combinations change
//
// Oh shit, I omit one statement: the number of distributions only relies on the ordered numbers
// What if the distribution does not specify an order? It will be much harder I suppose. Let's not dig into it.
// -- But it's certain that if it can be solved in polynomial time using dynamic programming like below I will for the ordered one.
// Try another approach:
// We can specify the relation of gaps to the sum
// n1 .. nm: the sorted numbers of balls got
// let d_i = n_{i+1} - n_i
// The sum will be n = \Sigma_{i=1}^{m-1}{i d_i} + m n_m
// let f(a, b, d) be the number of a-sequence {d_i} of {0, 1, ..., d}, which fulfills \Sigma_i i d_i = b
// a >= 1, b >= 0, d >= 1
//
// Then the objective of the problem is \Sigma f (m-1, b, 3) where (n - b) mod m = 0 and 0 <= b < n (because n_m > 0)
// The induction formula is: f (a, b, d) =  f (a - 1, b, d) + f (a - 1, b - 1*a, d) + f (a - 1, b - d*a, d), b - d >= 0
// Or just let f (a, b, d) = 0 when b < 0
// if a == 1, f (a, b, d) = 1 if b<= d
// (d actually can be seen as a subscript of f)
//
// And let's see if there are any trivial cases:
// 0. if b < 0 then f (a, b) = 0
// 1. if d * a < b then f (a, b) = 0 (this should omit many trivial calculations)
// 2. if a == 1 then f (a, b) = 1 (because condition 1 has already been satisfied) or f (0, 0) == 0
// f (a, b) = f (a - 1, b) + f (a - 1, b-1) + ... + f (a-1, b-d)

const int d = 3;
#ifdef POPULATION
const int m = POPULATION;
#else
const int m = 32;
#endif
#ifdef RESOURCES
const int n = RESOURCES;
#else
const int n = m * (m - 1) / 2 * d;
#endif

using slot = long long;
const slot UNDEFINED = 0;

// This algorithm only provides support for calculating when m and n is fixed
// The cache only manages 0 <= a < m and 0 <= b <= n
static slot values[(m) - (0)][(n + 1) - (0)] = { UNDEFINED }; // No need for b larger than n
slot& cache (int a, int b)
{
  if (!(0 <= a && a < m &&
	0 <= b && b <= n))
    throw std::invalid_argument (__func__);
  return values[a][b];
}

int counter;

slot f (int a, int b)
{
  
  if (a < 0) throw std::invalid_argument (__func__);
  if (b < 0) return 0;	  // f (a, -1) shall derive \Theta (n^2) cases
  if (a * (a + 1) / 2 * d < b) return 0; // This shall also derive \Theta (n^2) trivial cases
  // Comparison for recursion and from small values up
  // From small values up:
  // - Values calculated \Theta (a^3 * d)
  // Recursion:
  // - Values calculated TODO
  // - Stack size: \Theta (a * d)
  // Through experiments, using recursion can reduce a fair proportion of calculated slots
  slot& cached_value = cache (a, b);
  if (cached_value != UNDEFINED)
    return cached_value;

  counter += 1;
  
  if (a == 0)			// (a, b) == (0, 0)
    return cached_value = 1;
  
  slot acc = 0;
  for (int i = 0; i <= d; i++)
    acc += f (a - 1, b - i * a);
  return cached_value = acc;
}

slot solution (int m, int n)
{
  slot acc = 0;
  for (int b = n - m; b >= 0; b -= m)
    acc += f (m - 1, b);
  return acc;
}

int main (int argc, char *argv[])
{
  print_longlong_of (solution (m, n));
  return 0;
  
  counter = 0;
  for (int M = m - 1; M < m; M++)
    {
      int N = M * (M + 1) / 2 * d / 2;
      print_int_of (M);
      print_int_of (N);
      slot sol = f (M, N);
      print_longlong_of (sol);
      print_int_of (counter);
      int slots = (M - 1) * M * (2 * M - 1) / 6;
      print_int_of (slots);
      print_double_of ((double) counter / slots);
    }
  return 0;
}
