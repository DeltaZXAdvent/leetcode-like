#include <iostream>
#include <regex>
#include <string>
#include <vector>
using namespace std;
#define debug(exp) do { cout << #exp << ": " << (exp) << endl; } while (0)
int main2 (int argc, char *argv[])
{
  vector<string> res;
  string pattern (""),
    text ("ilovechina");
  vector<string> dict = { "i", "love", "china", "lovechina", "ilove" };
  vector<string>::iterator dict_it = dict.begin ();
  if (dict_it == dict.end ()) throw invalid_argument (__func__);
  while (true)
    {
      pattern += *dict_it;
      if (++dict_it == dict.end ()) break;
      else pattern += "|";
    }
  debug (pattern);
  regex re (pattern);
  sregex_iterator ri (text.begin (), text.end (), re),
    ri_end;
  for (; ri != ri_end; ++ri)
    {
      ssub_match sm = (*ri)[0];
      if (ri->position (0))
	{
	  debug (ri->position (0));
	  debug (ri->length (0));
	  debug (string (sm.first, sm.second));
	  throw runtime_error ("not in dictionary");
	}
      if (ri->position (0) + ri->length (0) == text.length ())
	break;
      res.push_back (sm.str ());
    }
}

int main (int argc, char *argv[])
{
  string pattern (""),
    text ("ilovechina");
  string dict_arr[] = { "i", "love", "china", "lovechina", "ilove" };
  vector<string> dict (dict_arr, dict_arr + sizeof (dict_arr) / sizeof (dict_arr[0]));
  for (vector<string>::iterator it = dict.begin (); it != dict.end (); ++it)
    {
      pattern.append (*it)
	.append ("|");
    }
  pattern.pop_back ();
  cout << pattern << endl;
  regex re (pattern);
  sregex_iterator ri (text.begin (), text.end (), re),
    ri_end;
  for (; ri != ri_end; ++ri)
    {
      cout << ri->position (0) << ' ';
    }
  cout << endl;
}
