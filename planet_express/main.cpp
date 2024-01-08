#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/strong_components.hpp>

typedef boost::adjacency_list<
  boost::vecS,
  boost::vecS,
  boost::directedS,
  boost::no_property,
  boost::property<boost::edge_weight_t, int>
> graph;
typedef boost::graph_traits<graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<graph>::vertex_descriptor vertex_desc;

typedef std::vector<int> VI;
typedef std::vector<VI> VVI;

void testcase()
{
  int n, m, k, T; std::cin >> n >> m >> k >> T;

  // There will be at most 2 * n + 1 nodes (could also be upper bounded by
  // n+T+1, but this is cleaner), because the component index of the telenetwork
  // will not necessarily be between 0 and T, but will be between 0 and n, so
  // there is an edge case, where it won't work if we upper bound by n+T+1.
  graph G(2 * n + 1);

  VI tele_network(T);
  for (int i = 0; i < T; i++)
    std::cin >> tele_network[i];

  for (int j = 0; j < m; j++)
  {
    int u, v, c; std::cin >> u >> v >> c;
    boost::add_edge(u, v, c, G);
  }

  // Compute the strongly connected components (O(m+n)) of the graph to figure
  // out which vertices in the teleportation network are pairwise reachable
  VI scc_map(2 * n + 1);
  int nscc = boost::strong_components(
    G,
    boost::make_iterator_property_map(
      scc_map.begin(),
      boost::get(boost::vertex_index, G)
    )
  );

  // Compute the time it takes to teleport to a linked vertex
  VI comp_sizes(nscc, -1);
  for (int t : tele_network)
    comp_sizes[scc_map[t]]++;

  // Add super node for every component, such that we do not have to doubly
  // iterate over all teleportation network vertices
  for (int t : tele_network)
  {
    int tele_supernode = n + scc_map[t];
    int tele_time = comp_sizes[scc_map[t]];
    boost::add_edge(t, tele_supernode, tele_time, G);
    boost::add_edge(tele_supernode, t, 0, G);
  }

  // Add supernode that connects to all warehouses, so we only have to run
  // Dijkstra's once
  int supernode = 2 * n;
  for (int i = 0; i < k; i++)
    boost::add_edge(supernode, i, 0, G);

  VI dist_map(2 * n + 1);
  boost::dijkstra_shortest_paths(
    G,
    supernode,
    boost::distance_map(
      boost::make_iterator_property_map(
        dist_map.begin(),
        boost::get(boost::vertex_index, G)
      )
    )
  );

  int microseconds = dist_map[n-1];
  if (microseconds <= 1000000)
    std::cout << microseconds << std::endl;
  else
    std::cout << "no" << std::endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) testcase();
}
