#include <array>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cstdio>
#include <stdexcept>
#include <cassert>
#include <memory>
using std::vector;
using std::map;
using std::string;
using std::array;
using std::printf;
using std::size_t;
using std::pair;
string true_string ("true"),
  false_string ("false");
void print_int (int i) { std::cout << i; }
void print_longlong (long long i) { std::cout << i; }
#define print_int_of(i) (printf (#i": "), print_int (i), printf ("\n"))
#define print_double_of(i) (printf (#i": "), print_double (i), printf ("\n"))
#define print_longlong_of(i) (printf (#i": "), print_longlong (i), printf ("\n"))
void printnl () { std::cout << std::endl; }
void print_bool (bool f) { std::cout << (f ? true_string : false_string); }
void print_double (double d) { std::cout << d; }
int max (int a, int b) { return a >= b ? a : b; }
int min (int a, int b) { return a >= b ? b : a; }

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

static int read_int ()
{
  int res;
  std::cin  >> res;
  return res;
}

static void expect (decltype(std::cin)::int_type c)
{
  if (std::cin.get () != c)
    throw std::logic_error (__func__);
}

template<std::size_t num>
array<int, num> read_space_seperated_ints (array<int, num>& res)
{
  if (num == 0) throw std::invalid_argument (__func__);
  size_t index = 0;
  failbit_setter<std::basic_ios<char>> fs (std::cin);
  noskipws_setter<decltype(std::cin)> ns (std::cin);
  for (;;)
    {
      res[index++] = read_int ();
      if (index == num) break;
      expect (' ');
    }
  expect ('\n');
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

vector<int> read_space_seperated_ints_inf ()
{
  vector<int> res;
  failbit_setter<std::basic_ios<char>> fs (std::cin);
  while (std::cin.peek () != '\n')
    {
      res.push_back (read_int ());
    }
  std::cin.get ();
  return res;
}

void print_vector (vector<int>& v)
{
  auto it = v.begin ();
  while (true)
    {
      print_int (*it++);
      if (it == v.end ()) break;
      printf (" ");
    }
  printnl ();
}

string read_capital_string ()
{
  string res;
  while (true)
    {
      char ch = std::cin.peek ();
      if (!('A' <= ch && ch <= 'Z')) break;
      res.push_back (std::cin.get ());
    }
  if (res.length () == 0)
    throw std::logic_error (__func__);
  return res;
}
