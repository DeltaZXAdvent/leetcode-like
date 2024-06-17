// https://blog.csdn.net/2301_76848549/article/details/134769333?csdn_share_tail=%7B%22type%22%3A%22blog%22%2C%22rType%22%3A%22article%22%2C%22rId%22%3A%22134769333%22%2C%22source%22%3A%222301_76848549%22%7D

#include "utils.hpp"
#include "graph.hpp"
#include "mapped_container.hpp"
#include <limits>

using vertex_t = int;	// I should have write vertex_t for node_type in graph.hpp but I never tried refactoring so let's put aside this

const int infinity = std::numeric_limits<int>::max ();

struct
{
  std::unordered_set<vertex_t> Vertices; // If the vertices are already determined at the start, we don't have to use std::set or others
  auto neighbors (vertex_t u)
  {
    if (Vertices.find (u) == Vertices.end ()) throw std::exception ();
    return mapped_container (edges_internal[u], [] (std::pair<vertex_t, int> p)->vertex_t { return p.first; });
  }
  int Edges (vertex_t u, vertex_t v)
  {
    if (Vertices.find (u) == Vertices.end () ||
	edges_internal.find (u) ==  edges_internal.end ())
      throw std::exception ();
    return edges_internal[u][v];
  }

  std::map<vertex_t, std::unordered_map<vertex_t, int>> edges_internal;
  void add_vertex (vertex_t u)
  {
    Vertices.insert (u);
    edges_internal[u];
  }
  void add_edge_undirected (vertex_t u, vertex_t v, int length)
  {
    if (Vertices.find (u) == Vertices.end () ||
	Vertices.find (v) == Vertices.end ()) throw std::exception (); // protection for user
    edges_internal[u][v] = length;
    edges_internal[v][u] = length;
  }
} Graph;

template<class container>
struct pseudo_map_value
{
  container data;
  using key_type = typename container::key_type;
  using mapped_type = typename container::mapped_type;
  key_type key, default_key;
  operator key_type ()
  {
    return data.find (key) == data.end () ? data[key] : default_key;
  }
  auto operator= (mapped_type value)
  {
    return data[key] = value;
  }
};

struct
{
  std::map<vertex_t, int> data;
  auto operator[] (vertex_t u)
  {
    return pseudo_map_value<decltype (data)> { .data = data, .key = u, .default_key = infinity } ;
  }
  size_t size ()
  {
    return data.size ();
  }
} dist;				// the number of vertices is fixed when the algorithm starts, we can use a continuous array
				// but then it has to be initialized at the algorithm starts
				// Let's just use maps because the vertices may have random integers

struct
{
  bool empty () { return data.empty (); }
  void add_with_priority (vertex_t v, int priority)
  {
    size_t size = data.size ();
    data.push_back (std::make_pair (v, priority));
    indices[v] = size;
    up_heap (size);
  }
  void up_heap (size_t i)
  {
    if (i == 0) return;
    size_t parent = (i - 1) / 2;
    if (data[parent].second <= data[i].second) return;
    std::swap (data[parent], data[i]);
    std::swap (indices[data[parent].first], indices[data[i].first]);
    up_heap (parent);
  }
  void min_heapify (size_t i)
  {
    size_t largest = i,
      left = 2 * i + 1, right = 2 * i + 2;
    if (left < data.size (), data[left].second > data[largest].second)
      largest = left;
    if (right < data.size (), data[right].second > data[largest].second)
      largest = right;
    if (largest != i)
      {
	std::swap (data[i], data[largest]);
	std::swap (indices[data[i].first], indices[data[largest].first]);
	min_heapify (largest);
      }
  }
  vertex_t extract_min ()
  {
    vertex_t res = data.front ().first;
    std::swap (data.front (), data.back ());
    std::swap (indices[data.front ().first], indices[data.back ().first]);
    data.pop_back ();
    indices.erase (data.back ().first);
    min_heapify (0);
    return res;
  }
  void decrease_priority (vertex_t v, int priority) // use priority from dist
  {
    data[v].second = priority;
    min_heapify (v);
  }
  void change_priority (vertex_t v, int priority)
  {
    if (indices.find (v) == indices.end ())
      decrease_priority (v, priority);
    else add_with_priority (v, priority);
  }
  std::vector<std::pair<vertex_t, int>> data;
  std::map<vertex_t, size_t> indices;
  
} Q;				// min-heap

struct
{
  std::map<vertex_t, vertex_t> data;
  auto operator[] (vertex_t u)
  {
    return pseudo_map_value<decltype (data)> { .data = data, .key = u, .default_key = nil_node } ;
  }
} prev;

// Dijkstra's algorithm
// Whether the graph is directed or undirected is not important
// because we will not walk in circular
//
// https://en.wikipedia.org/wiki/Dijkstra's_algorithm
// for each vertex v in Graph.Vertices:
//     dist[v] ← INFINITY
//     prev[v] ← UNDEFINED
//     add v to Q
// dist[source] ← 0
// 
// while Q is not empty:
//     u ← vertex in Q with minimum dist[u]
//     remove u from Q
// 
//     for each neighbor v of u still in Q:
//         alt ← dist[u] + Graph.Edges(u, v)
//         if alt < dist[v]:
//             dist[v] ← alt
//             prev[v] ← u
// 
// return dist[], prev[]
//
// Priority queue version:
// function Dijkstra(Graph, source):
//     create vertex priority queue Q
// 
//     dist[source] ← 0                          // Initialization
//     Q.add_with_priority(source, 0)            // associated priority equals dist[·]
// 
//     for each vertex v in Graph.Vertices:
//         if v ≠ source
//             prev[v] ← UNDEFINED               // Predecessor of v
//             dist[v] ← INFINITY                // Unknown distance from source to v
//             Q.add_with_priority(v, INFINITY)
// 
// 
//     while Q is not empty:                     // The main loop
//         u ← Q.extract_min()                   // Remove and return best vertex
//         for each neighbor v of u:             // Go through all v neighbors of u
//             alt ← dist[u] + Graph.Edges(u, v)
//             if alt < dist[v]:
//                 prev[v] ← u
//                 dist[v] ← alt
//                 Q.decrease_priority(v, alt)
// 
//     return dist, prev

int Dijkstra (vertex_t source)
{
  "init Q";
  dist[source] = 0;
  Q.add_with_priority (source, 0);

  for (vertex_t v: Graph.Vertices)
    if (v != source)
      {
	"prev[v] = nil_node";
	"dist[v] = infinity";
	"Q.add_with_priority (v, infinity)";
      }
  size_t vertex_ct = Graph.Vertices.size ();

  vertex_t u;
  while (!Q.empty ())
    {
      u = Q.extract_min ();
      for (vertex_t v: Graph.neighbors (u))
	{
	  print_int (v); printf (" ");
	  int alt = dist[u] + Graph.Edges (u, v);
	  if (alt < dist[v])
	    {
	      prev[v] = u;
	      dist[v] = alt;
	      Q.change_priority (v, alt);
	    }
	}
      printnl ();
    }

  "return std::make_pair (dist, prev)";
  print_int (dist.size ()); printnl ();
  print_int (vertex_ct); printnl ();
  if (dist.size () != vertex_ct)
    return -1;
  else return dist[u];
}

int main (int argc, char *argv[])
{
  int vertex_ct = read_space_seperated_ints (1)[0];
  for (vertex_t i = 1; i <= vertex_ct; i++)
    {
      Graph.add_vertex (i);
    }
  int edge_ct = read_space_seperated_ints (1)[0];
  while (edge_ct > 0)
    {
      vector<int> edge_args = read_space_seperated_ints (3);
      Graph.add_edge_undirected (edge_args[0], edge_args[1], edge_args[2]);
      edge_ct--;
    }
  vertex_t source = read_space_seperated_ints (1)[0];
  print_int (Dijkstra (source));
  printnl ();

  return 0;
}
