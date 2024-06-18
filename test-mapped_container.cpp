#include "mapped_container.hpp"
#include <vector>
#include "utils.hpp"
void test_mapped_container ()
{
  std::vector<int> v {1, 2, 3, 4, 5};
  mapped_container m (v, [] (int e)->int { return e * e; } );
  for (int e: m)
    {
      print_int (e); printf (" ");
    }
  printnl ();
}

int main (int argc, char *argv[])
{
  test_mapped_container ();
  return 0;
}
