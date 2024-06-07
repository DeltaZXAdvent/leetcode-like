// std::cin treats all input lines as one object

#include <map>
#include <cstdio>
#include <string>
#include <iostream>
using std::string;
string true_string ("true"),
  false_string ("false");

string print_bool (bool v)
{
  return v ? true_string : false_string;
}
void print (string s) { std::cout << s; }
void printnl () { std::cout << std::endl; }
void print_int (int i)
{
  std::cout << i;
}

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

// Need newline or not?
int read_int ()
{
  using namespace std;
  int res;
  failbit_setter<std::basic_ios<char>> fs(cin);
  cin >> noskipws >> res;
  return res;
}

void test_failbit_setter ()
{
  using std::printf;		// DEBUG
  try
    { read_int (); }
  catch (std::ios_base::failure& e)
    { std::printf ("failure catched\n"); }
  print (print_bool (std::cin.fail ()));
  print (" ");
  print (print_bool (std::cin.exceptions () & std::ios_base::failbit));
  printnl ();
  read_int ();
}

void test_read_int ()
{
  print_int (read_int ());
  print (" ");
  print_int (read_int ());
  printnl ();
}

int main (int argc, char *argv[])
{
  // noskipws has to be cleared ^^;
  int var;
  std::cin >> std::noskipws >> var;
  print_int (var);
  failbit_setter<std::basic_ios<char>> fs (std::cin);
  std::cin >> var;
  print_int (var);
  return 0;
  
  test_failbit_setter ();
  return 0;
  
  
  using map = std::map<int, int>;
  map ct{};
  print (print_bool (ct[0] == 0));
  printnl ();
  ct[0] += 1;
  return 0;
}
