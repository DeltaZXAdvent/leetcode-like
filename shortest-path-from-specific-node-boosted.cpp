//=======================================================================
// Modified
// Copyright 2001 Jeremy G. Siek, Andrew Lumsdaine, Lie-Quan Lee,
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
#include <boost/config.hpp>
#include <iostream>
#include <fstream>

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/property_map/property_map.hpp>
#include "utils.hpp"

using namespace boost;

typedef adjacency_list< listS, vecS, undirectedS, no_property,
			property< edge_weight_t, int > > // used to specify the edge_weight location for get (edge_weight, g)
graph_t;
typedef graph_traits< graph_t >::vertex_descriptor vertex_descriptor;
typedef graph_traits< graph_t >::edge_descriptor edge_descriptor;

struct Vis
{
  int& vertices,
    last_vertex;
  void initialize_vertex(int u, graph_t g)
  {
  }
  void examine_vertex(int u, graph_t g)
  {
    last_vertex = u;
    vertices++;
  }
  void examine_edge(edge_descriptor e, graph_t g)
  {
  }
  void discover_vertex(int u, graph_t g)
  {
  }
  void edge_relaxed(edge_descriptor e, graph_t g)
  {
  }
  void edge_not_relaxed(edge_descriptor e, graph_t g)
  {
  }
  void finish_vertex(int u, graph_t g)
  {
  }
};

int main(int, char*[])
{
    typedef std::pair< int, int > Edge;

    int num_nodes = read_space_seperated_ints(1)[0];
    graph_t g(num_nodes);

    for (int num_edges = read_space_seperated_ints(1)[0];
	 num_edges > 0;
	 num_edges--)
      {
	vector<int> line = read_space_seperated_ints(3);
	add_edge(line[0] - 1, line[1] - 1, line[2], g);
      }
    
    
    std::vector< vertex_descriptor > p(num_vertices(g));
    std::vector< int > d(num_vertices(g));

    vertex_descriptor s = vertex(read_space_seperated_ints(1)[0], g);

    int vis_vertices, vis_last_vertex;
    Vis vis {.vertices = vis_vertices, .last_vertex = vis_last_vertex};
    // need to know the last vertex and the total count of vertex reached
    dijkstra_shortest_paths(g, s,
        predecessor_map(boost::make_iterator_property_map(
                            p.begin(), get(boost::vertex_index, g)))
            .distance_map(boost::make_iterator_property_map(
                d.begin(), get(boost::vertex_index, g)))
			    .visitor(vis));

    std::cout << "distances and parents:" << std::endl;
    graph_traits< graph_t >::vertex_iterator vi, vend;
    for (boost::tie(vi, vend) = vertices(g); vi != vend; ++vi)
    {
        std::cout << "distance(" << *vi + 1 << ") = " << d[*vi] << ", ";
        std::cout << "parent(" << *vi + 1 << ") = " << p[*vi]
                  << std::endl;
    }
    std::cout << std::endl;

    // print_int_of(vis_vertices);
    // print_int_of(num_nodes);
    if (vis_vertices != num_nodes) std::cout << -1;
    else std::cout << d[vis_last_vertex];
    std::cout << std::endl;
    return EXIT_SUCCESS;
}

