#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/biconnected_components.hpp>

typedef boost::adjacency_list<
  boost::vecS,
  boost::vecS,
  boost::undirectedS
> graph;

typedef boost::graph_traits<graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<graph>::vertex_descriptor vertex_Desc;

// Idea: If a biconnected component only consists of one edge, it is an important
// bridge.
// Time complexity: O(n+m log m) with sorting and O(n+m) without.

void testcase()
{
  int n, m; std::cin >> n >> m;

  graph G(n);
  for (int i = 0; i < m; i++)
  {
    int s, t; std::cin >> s >> t;
    boost::add_edge(s, t, G);
  }

  // Find all connected components O(n+m)
  std::map<edge_desc, int> component_map;
  auto components = boost::make_assoc_property_map(component_map);
  int num_components = boost::biconnected_components(G, components);

  // Restructure the data, such that the component points to all edges that are
  // part of it, instead of all edges pointing to the component they are part
  // of O(m)
  std::vector<std::vector<edge_desc>> component_edges(num_components);
  auto edges = boost::edges(G);
  for (auto eit = edges.first; eit != edges.second; eit++) {
    edge_desc edge = *eit;
    int component = components[edge];
    component_edges[component].push_back(edge);
  }

  // Find all components that only consist of a single edge, i.e. an important
  // bridge O(m)
  std::vector<std::pair<int, int>> important_bridges;
  for (int i = 0; i < num_components; i++)
  {
    std::vector<edge_desc> edges = component_edges[i];
    if (edges.size() == 1)
    {
      edge_desc edge = edges[0];
      int a = edge.m_source;
      int b = edge.m_target;

      // Output with smaller node index first, as specified
      if (a > b) std::swap(a, b);

      important_bridges.push_back({ a, b });
    }
  }

  // Sort O(m log m)
  std::sort(important_bridges.begin(), important_bridges.end());

  std::cout << important_bridges.size();
  for (auto edge : important_bridges)
    std::cout << '\n' << edge.first << ' ' << edge.second;

  std::cout << std::endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) testcase();
}
