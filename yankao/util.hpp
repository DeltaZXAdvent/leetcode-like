#include <iostream>
#include <vector>
#include <limits>
int my_rand (int min = std::numeric_limits <int>::min (),
	     int max = std::numeric_limits <int>::max ());
std::vector <int> rand_vec (std::vector<int>::size_type size,
			    int min = std::numeric_limits <int>::min (),
			    int max = std::numeric_limits <int>::max ());

template <class T>
std::ostream& operator<< (std::ostream& os, std::vector <T>& vec)
{
  for (T& e: vec)
    os << e << ' ';
  return os;
}

namespace my
{
  void getline ();
}

#define display(v) std::cout << #v ": " << v << '\n';
