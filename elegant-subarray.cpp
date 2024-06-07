// https://blog.csdn.net/AlgorithmHero/article/details/130743114
// subarray: continuous subsequence
// #include <cstddef>
// using std::size_t;
#include <map>
#include <string>
#include <iostream>
#include <stdexcept>
#include <vector>
using std::string;
using std::vector;
void print_int (int i) { std::cout << i; }
void printnl () { std::cout << std::endl; }

size_t number_of_elegant_subarrays (vector<int>& A, size_t k)
{
  if (A.size () == 0 || k == 0) throw std::invalid_argument (__func__);
  size_t l = A.size (),
    left = 0, right = 0, res = 0; // right exclusive
  std::map<int, int> ct{}; // WARNING are all elements initialized to 0?
  ct[A[right++]]++;
  while (true)
    {
      if (ct[A[right - 1]] >= k)
	{
	  res += l - right + 1;
	  ct[A[left++]]--;
	}
      else
	{
	  if (right == l) break;
	  ct[A[right++]]++;
	}
    }
  return res;
}

// 1. The subarray must include the start and the end of the repeated element
// 2. If there's only one such pair that the subarray inclusively between this pair has exact k occurrences of the element of the pair (the elements of the pair are same), it's easy to derive the number of k-elegant subarrays:
//    p_i * (l - p_j)
// 3. If there are larger than k occurrences of one element, then we can treat them as different elements
// 4. When there are multiple kinds of elements, we can use inclusion-exclusion principle:
//    i1 * (l - j1) + i2 * (l - j2) - min(i1, i2) * (l - max(j1, j2))
//    (it should be (pi + 1) * (l - pj))
// 5. This will involve expotential calculations
//    We don't have to use the inclusion-exclusion principle because the sets are not randomly arranged
// 6. Another way of thinking:
//    There are l*(l-1)/2 ways of composing the pair or l*(l+1)/2 pairs if k == 1
//    1. For every pair, left <= right
//    2. If pair (l0, r0) passes, then pair (l, r) (l <= l0, r >= r0) passes
//       So consider the minimal pairs
//    3. There are no minimal pair which includes another minimal pair for it will not be minimal
//       So if sort the pairs by the left index, then the right index will also be sorted
//       The pairs included by the former pair will be (i1 + 1) * (l - j1)
// Let's just use two pointers

template<class ios_t>		// std::basic_ios<CharT, Traits>
struct failbit_setter
{
  std::ios_base::iostate original_mask;
  ios_t& ios;
  failbit_setter (ios_t& ios): ios (ios)
  {
    original_mask = ios.exceptions ();
    ios.exceptions (std::ios_base::badbit |
		    std::ios_base::eofbit |
		    std::ios_base::failbit);
  }
  ~failbit_setter ()
  {
    ios.exceptions (original_mask);
    ios.clear ();
  }
};

template<class is_t>		// std::basic_istream
struct noskipws_setter
{
  is_t& is;
  noskipws_setter (is_t& is): is (is)
  {
    is >> std::noskipws;
  }
  ~noskipws_setter ()
  {
    is >> std::skipws;
  }
};

int read_int ()
{
  int res;
  std::cin  >> res;
  return res;
}

void expect (decltype(std::cin)::int_type c)
{
  if (std::cin.get () != c)
    throw std::logic_error (__func__);
}

vector<int> read_space_seperated_ints (size_t num)
{
  vector<int> res;
  failbit_setter<std::basic_ios<char>> fs (std::cin);
  noskipws_setter<decltype(std::cin)> ns (std::cin);
  for (;;)
    {
      res.push_back (read_int ());
      if (--num == 0) break;
      expect (' ');
    }
  expect ('\n');
  return res;
}

int main (int argc, char *argv[])
{
  vector<int> v;
  v = read_space_seperated_ints (2);
  size_t l = v[0];
  size_t k = v[1];
  v = read_space_seperated_ints (l);
  print_int (number_of_elegant_subarrays (v, k));
  printnl ();
  return 0;
}
