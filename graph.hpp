#include <unordered_set>
#include <unordered_map>
#include <memory>
#include <functional>
template<std::size_t nodes>	// number of nodes
struct directional_graph
{
  using node_type = int;
  using node_set_type = std::unordered_set<node_type>;
  std::unique_ptr<node_set_type[]> outs;
  std::unique_ptr<node_set_type[]> ins;
  directional_graph (): outs (std::make_unique<node_set_type[]> (nodes)),
	    ins (std::make_unique<node_set_type[]> (nodes)) { }
  void add_edge (node_type from, node_type to)
  {
    outs[from].insert (to);
    ins[to].insert (from);
  }
};

using node_type = int;
const node_type nil_node = -1;
using subtree_ct_type = int;
struct edge_type
{
  node_type node;
  subtree_ct_type subtree_ct;
};
struct edge_hash
{
  std::hash<node_type> hash;
  auto operator() (edge_type e) const
  {
    return hash (e.node);
  }
};
struct edge_pred
{
  bool operator() (edge_type e1, edge_type e2) const
  {
    return e1.node == e2.node;
  }
};
using node_set_type = std::unordered_set<edge_type, edge_hash, edge_pred>;
// using node_set_type = std::unordered_map<node_type, subtree_ct_type>; // using maps and there are pairs which are not good

struct graph
{
  size_t node_ct;
  std::unique_ptr<node_set_type[]> edges;
  graph (size_t node_ct): node_ct (node_ct),
			  edges (std::make_unique<node_set_type[]> (node_ct))
  { }
};

void add_edge (graph& g, node_type from, node_type to)
{
  g.edges[from].insert ({ .node = to });
  g.edges[to].insert ({ .node = from });
}

node_set_type& get_edges (graph& g, node_type n)
{
  return g.edges[n];
}
void edge_set_subtree_ct (node_set_type& ns, node_type to, subtree_ct_type ct)
{
  ns.erase ({ .node = to });
  ns.insert ({ .node = to, .subtree_ct = ct });
}
