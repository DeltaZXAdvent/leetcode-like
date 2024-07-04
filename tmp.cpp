#include <iostream>
#include <regex>
#include <string>
#include <vector>
using namespace std;
#define debug(exp) do { cout << #exp << ": " << (exp) << endl; } while (0)
vector<string> delimit_words (string text, vector<string> dict)
{
  vector<string> res;
  string pattern;
  if (dict.empty ()) throw invalid_argument (__func__);
  vector<string>::iterator dict_it = dict.begin ();
  while (true)
    {
      pattern += *dict_it;
      if (++dict_it == dict.end ()) break;
      else pattern += "|";
    }
  regex re (pattern);
  if (text.empty ()) return res;
  sregex_iterator ri (text.begin (), text.end (), re),
    ri_end;
  for (; ri != ri_end; ++ri)
    {
      if (ri->prefix ().length () != 0)
	throw runtime_error ("not a instant match");
      res.push_back (ri->str (0));
      if (ri->position (0) + ri->length (0) == text.length ())
	return res;
    }
  throw runtime_error ("search failed");
}

int main (int argc, char *argv[])
{
  string text = "ilovechina";
  vector<string> dict = { "i", "love", "china", "lovechina", "ilove" };
  vector<string> words = delimit_words (text, dict);
  for (vector<string>::iterator it = words.begin ();
       it != words.end ();
       ++it)
    {
      cout << *it << ' ';
    }
  cout << endl;
  return 0;
}
