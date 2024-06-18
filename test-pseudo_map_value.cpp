template<class container>
struct pseudo_map_value
{
  container& data;
  using key_type = typename container::key_type;
  using mapped_type = typename container::mapped_type;
  key_type key;
  mapped_type default_mapped;
  operator key_type ()
  {
    return data.find (key) == data.end () ? default_mapped : data[key];
  }
  auto operator= (mapped_type mapped)
  {
    return data[key] = mapped;
  }
};

#include <map>
#include "utils.hpp"
int main ()
{
  std::map<int, int> m;
  pseudo_map_value<decltype (m)> mv { .data = m, .key = 0, .default_mapped = 8 };
  print_int_of (mv);
  print_bool_of (m.find (0) == m.end ());
  mv = 4;
  print_int_of (mv);
}
