// https://blog.csdn.net/2301_76848549/article/details/138068594?csdn_share_tail=%7B%22type%22%3A%22blog%22%2C%22rType%22%3A%22article%22%2C%22rId%22%3A%22138068594%22%2C%22source%22%3A%222301_76848549%22%7D

// Prim's algorithm
// Dijkstra's algorithm does not give a minimum spanning tree because the sum of the shortest paths eventually assign every edge a weight
#include <boost/config.hpp>
#include <iostream>

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/property_map/property_map.hpp>
#include "utils.hpp"

using namespace boost;

typedef adjacency_list< listS, vecS, undirectedS, no_property,
			property< edge_weight_t, int > > // used to specify the edge_weight location for get (edge_weight, g)
graph_t;
typedef graph_traits< graph_t >::vertex_descriptor vertex_descriptor;
typedef graph_traits< graph_t >::edge_descriptor edge_descriptor;

int main(int, char*[])
{
  
}
