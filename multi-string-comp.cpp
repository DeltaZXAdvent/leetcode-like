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
// TODO
// And let's see <regex> implementation of libstdc++ for C++11
// And maybe of Boost
// 

int main (int argc, char *argv[])
{
  return 0;
}
