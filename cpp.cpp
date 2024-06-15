// std::cin treats all input lines as one object

#include <map>
#include <cstdio>
#include <string>
#include <iostream>
#include <cstdint>
#include "utils.hpp"

// Need newline or not?
int old_read_int ()
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
    { old_read_int (); }
  catch (std::ios_base::failure& e)
    { std::printf ("failure catched\n"); }
  print_bool (std::cin.fail ());
  printf (" ");
  print_bool (std::cin.exceptions () & std::ios_base::failbit);
  printnl ();
  old_read_int ();
}

void test_old_read_int ()
{
  print_int (old_read_int ());
  printf (" ");
  print_int (old_read_int ());
  printnl ();
}

int main (int argc, char *argv[])
{
  // int& i = 1;			// ERROR
  print_int (i); printnl ();
  return 0;
  
  if (std::cin.eof ())
    printf ("eof\n");
  return 0;
  
  printf ("%zu\n", sizeof (size_t));
  printf ("%zu\n", sizeof (int));
  printf ("%zu\n", sizeof (std::intptr_t));
  return 0;
  
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
  print_bool (ct[0] == 0);
  printnl ();
  ct[0] += 1;
  return 0;
}
