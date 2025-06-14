#include <iostream>
#include <string>
#define PRINT1(os, a, delim) print(os << #a << ": ", a, delim)
#define PRINT2(os, a, outerDelim, innerDelim) print(os << #a << ": ", a, outerDelim, innerDelim)
std::string to_string(char ch) {
  return std::string(1, ch);
}
std::string to_string(bool f) {
  return f ? "true" : "false";
}
template<class X>
std::ostream& print(std::ostream& os, const X& a, char delim)
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
std::ostream& print(std::ostream& os, const X& a, char outerDelim, char innerDelim)
{
  for (auto i = a.begin (); i != a.end (); ++i)
    {
      print(os, *i, innerDelim);
      if (std::next(i) != a.end())
	os << outerDelim;
    }
  return os;
}
