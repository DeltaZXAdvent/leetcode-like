#include <iostream>
template<class X>
std::ostream& print(std::ostream& os, X& a, char delim)
{
  for (auto i = a.begin (); i != a.end (); ++i)
    {
      os << *i;
      if (std::next(i) != a.end())
	os << delim;
    }
  return os;
}
template<class X>
std::ostream& print(std::ostream& os, X& a, char outerDelim, char innerDelim)
{
  for (auto i = a.begin (); i != a.end (); ++i)
    {
      print(os, *i, innerDelim);
      if (std::next(i) != a.end())
	os << outerDelim;
    }
  return os;
}
