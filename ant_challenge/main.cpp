#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>

typedef boost::adjacency_list<
  boost::vecS,
  boost::vecS,
  boost::undirectedS,
  boost::no_property,
  boost::property<boost::edge_weight_t, int>
> graph;
typedef boost::graph_traits<graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<graph>::vertex_descriptor vertex_desc;

typedef std::vector<int> VI;
typedef std::vector<VI> VVI;

// Time complexity: O(n*s + m log n + m*s + n log n)

void testcase()
{
  int n, e, s, source, target; std::cin >> n >> e >> s >> source >> target;

  // Initialize graphs for all species. O(n*s)
  std::vector<graph> species_graph(s, graph(n));
  for (int i = 0; i < e; i++)
  {
    int t1, t2; std::cin >> t1 >> t2;

    for (int j = 0; j < s; j++)
    {
      int w; std::cin >> w;
      boost::add_edge(t1, t2, w, species_graph[j]);
    }
  }

  // Create MSTs for all graphs starting from the hive root with Prim's
  // algorithm, since that is how they explore their graphs. O(m log n)
  VVI mst_parents(s, VI(n));
  for (int i = 0; i < s; i++)
  {
    int hive_root; std::cin >> hive_root;
    boost::prim_minimum_spanning_tree(
      species_graph[i],
      &mst_parents[i][0],
      boost::root_vertex(hive_root)
    );
  }

  // Build graph with minimum weights from all species' explored graphs. O(m*s)
  graph G(n);
  auto edges = boost::edges(species_graph[0]);
  for (auto eit = edges.first; eit != edges.second; eit++)
  {
    edge_desc edge = *eit;
    int a = edge.m_source;
    int b = edge.m_target;

    int min_weight = INT_MAX;
    for (int i = 0; i < s; i++)
    {
      // Check whether the MST has this edge
      if (mst_parents[i][a] == b || mst_parents[i][b] == a)
      {
        edge_desc current_edge = boost::edge(a, b, species_graph[i]).first;
        int weight = boost::get(boost::edge_weight_t(), species_graph[i], current_edge);
        min_weight = std::min(min_weight, weight);
      }
    }

    if (min_weight != INT_MAX)
      boost::add_edge(a, b, min_weight, G);
  }

  // Compute distance map to get the distance to the end starting from start. O(n log n)
  VI dist_map(n);
  boost::dijkstra_shortest_paths(G, source,
    boost::distance_map(
      boost::make_iterator_property_map(
        dist_map.begin(),
        boost::get(boost::vertex_index, G)
      )
    )
  );

  std::cout << dist_map[target] << std::endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) testcase();
}
