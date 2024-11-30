// https://blog.csdn.net/2301_76848549/article/details/135261648?csdn_share_tail=%7B%22type%22%3A%22blog%22%2C%22rType%22%3A%22article%22%2C%22rId%22%3A%22135261648%22%2C%22source%22%3A%222301_76848549%22%7D
// Let's review the single string matching algorithm
// The KMP (Knuth-Morris-Pratt) algorithm:
// It's generally a backtraced version of the naive one
// Let's not discuss more.
// Consider the multiple-string one,
// just make a string tree, or forest, and calculate the backtrace array for every node,
// completely the same method as the single-string one.
// Constructing the tree:
// Simply traverse every comparison string.
// But how add to the ordered sibling list? Red-black tree?
// Because there are only 26 kinds of values, red-black tree probably costs too much.
//
// By the way:
// Here some algorithmic questions:
// * How is a iterable set (iterable hash table?) implemented?
//   And let's see the libstdc++ (of GCC) implementation
//   Just use linked nodes. And rehashing iterates over all nodes, with complexity O(n) (probably in averge)
//
// The Boyer--Moore string-search algorithm is an alternative.
//
// And let's see <regex> implementation of libstdc++ for C++11, OK let's don't because it's not that interesting
// And maybe of Boost (Oh boost does not provide this)
//
// C++11 uses ECMAScript regular expressions. And ECMAScript RegExp
// is imperative rather than declarative, probably for all regular expression engines.
// For example, "ab|abc" matches "ab" in "abcd" rather than "abc"

#include <vector>
#include <string>
#include <regex>
#include <stdexcept>
#include <iostream>
#include <map>
using namespace std;

#define debug(exp) do { cout << #exp << ": " << (exp) << endl; } while (0)

ostream& operator<< (ostream& os, vector<string> v)
{
  for (vector<string>::iterator it = v.begin ();
       it != v.end ();
       ++it)
    {
      os << *it << ' ';
    }
  return os;
}

// Does not work, fuck, regular expressions are not compiled into automatons
// vector<string> delimit_words (string text, vector<string> dict)
// {
//   vector<string> res;
//   string pattern;
//   if (dict.empty ()) throw invalid_argument (__func__);
//   vector<string>::iterator dict_it = dict.begin ();
//   while (true)
//     {
//       pattern += *dict_it;
//       if (++dict_it == dict.end ()) break;
//       pattern += "|";
//     }
//   regex re (pattern);
//   if (text.empty ()) return res;
//   sregex_iterator ri (text.begin (), text.end (), re),
//     ri_end;
//   for (; ri != ri_end; ++ri)
//     {
//       if (ri->prefix ().length () != 0)
// 	throw runtime_error ("not a instant match");
//       res.push_back (ri->str (0));
//       if (ri->suffix ().first == text.end ())
// 	return res;
//     }
//   throw runtime_error ("search failed");
// }

// Seems like C++ cannot avoid pointers here?
struct trie
{
  bool match;			// false by default
  map<char, trie> next;
  void add_string (string s)
  {
    trie* node = this;
    for (string::iterator it = s.begin (); it != s.end (); ++it)
      node = &node->next[*it];
    node->match = true;
  }
  string::iterator longest_match_end (string::iterator begin, string::iterator end)
  {
    trie *node = this;
    string::iterator res = begin;
    for (; begin != end; ++begin)
      {
	map<char, trie>::iterator n = node->next.find (*begin);
	if (n != node->next.end ())
	  {
	    debug (*begin);
	    node = &n->second;
	    if (node->match)
	      {
		res = begin + 1;
		debug (node->match);
	      }
	  }
	else break;
      }
    return res;
  }
};

vector<string> delimit_words (string text, vector<string> dict)
{
  vector<string> res;
  trie root;
  vector<string>::iterator dict_it = dict.begin ();
  for (; dict_it != dict.end (); ++dict_it)
    {
      root.add_string (*dict_it);
    }
  string::iterator matched = text.begin ();
  while (matched != text.end ())
    {
      string::iterator new_matched =
	root.longest_match_end (matched, text.end ());
      debug (new_matched - text.begin ());
      if (new_matched == matched)
	throw runtime_error (string ("mismatch in ").append (__func__));
      res.push_back (string (matched, new_matched));
      matched = new_matched;
    }
  return res;
}

int main (int argc, char *argv[])
{
  string text ("ilovechina");
  string dict_arr[] = { "i", "love", "china", "lovechina", "ilove" };
  vector<string> dict (dict_arr, dict_arr + sizeof (dict_arr) / sizeof (dict_arr[0]));
  cout << delimit_words (text, dict) << endl;
  return 0;
}
