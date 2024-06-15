// https://blog.csdn.net/2301_76848549/article/details/134757505?csdn_share_tail=%7B%22type%22%3A%22blog%22%2C%22rType%22%3A%22article%22%2C%22rId%22%3A%22134757505%22%2C%22source%22%3A%222301_76848549%22%7D
#include "utils.hpp"
#include "graph.hpp"

// every edge of every node (so it's the (node, edge) pair) can be assigned a number,
// which indicates the number of the subtree designated by the edge
// To calculated these numbers, we can use depth-first search
//
// according to the set of the neighbors of a node and the numbers assigned e_i respectively
// We can know the following assertions:
// 1. If another node is in the subtree of the edge E_i which has a number e_i, and
//    the node is one which has the smallest DP,
//    Then e_i is the greatest (possibly several) among {e_i}
// 2. In case 1, if sum {e_i} - e_i + 1 > e_i then the nodes in the ith subtree are not the optimal node
//    That is, if 2 * max{e_i} < nodes, then the current node is the optimal node
//    If 2 * e_i == nodes, then E_i.to and e_i are both optimal nodes
//    If 2 * e_i > nodes, then optimal node or nodes are in the ith subtree

// Calculate all subtrees divided by n but omit node 'omit'
// Return: the sum of the subtree counts plus 1 (the node itself)
subtree_ct_type calculate_subtree_cts (graph& g, node_type n, node_type omit)
{
  subtree_ct_type sum = 0;
  node_set_type& edges = get_edges (g, n);
  for (auto it: edges)
    if (it.node != omit)
      {
	subtree_ct_type ct = calculate_subtree_cts (g, it.node, n);
	edge_set_subtree_ct (edges, it.node, ct);
	sum += ct;
      }
  return sum + 1;
}

void most_polymerized (graph& g, node_type n, node_type omit, size_t nodes)
{
  // assume at first the node count is not known
  // (Thus, we can generalize this algorithm to apply to a tree in a forest)
  // If it is known: we can further optimize the algorithm:
  // we can already know all the subtree counts of some deep nodes
  // so throw exceptions when finding a node that satisfies the condition
  // and there will be no need for count recorders
  for (auto it: get_edges (g, n))
    if (it.node != omit)
      {
	if (2 * it.subtree_ct == nodes)
	  {
	    print_int (n + 1); printf (" ");
	    print_int (it.node + 1); printnl ();
	    return;
	  }
	else if (2 * it.subtree_ct > nodes)
	  {
	    most_polymerized (g, it.node, n, nodes);
	    return;
	  }
      }
  print_int (n + 1); printnl ();
}

void real_most_polymerized (graph& g)
{
  subtree_ct_type nodes = calculate_subtree_cts (g, 0, nil_node);
  most_polymerized (g, 0, nil_node, nodes);
}

int main (int argc, char *argv[])
{
  size_t nodes = read_space_seperated_ints (1)[0];
  graph g (nodes);
  while (std::cin.peek () != decltype (std::cin)::traits_type::eof ())
    {
      auto edge = read_space_seperated_ints (2);
      node_type from = edge[0] - 1,
	to = edge[1] - 1;
      add_edge (g, from, to);
    }
  real_most_polymerized (g);
  return 0;
}
