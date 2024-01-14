#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;

typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

class edge_adder {
  graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}

  void add_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const auto e = boost::add_edge(from, to, G).first;
    const auto rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};

void testcase()
{
  int n, m; std::cin >> n >> m;

  graph G(n);
  edge_adder adder(G);

  for (int j = 0; j < m; j++)
  {
    int a, b, c; std::cin >> a >> b >> c;
    adder.add_edge(a, b, c);
  }

  // Find the minimum cut from any to any other figure. Instead of iterating
  // over every pair (i, j) in (O(n^2)), we only need to iterate over every
  // sculpture and find their min cut to a fixed sculpture. This is because every
  // possible cut is also between these.
  int min_cut = INT_MAX;
  for (int i = 1; i < n; i++)
  {
    int min_cut_0i = boost::push_relabel_max_flow(G, 0, i);
    int min_cut_i0 = boost::push_relabel_max_flow(G, i, 0);
    
    min_cut = std::min({
      min_cut,
      min_cut_0i,
      min_cut_i0
    });
  }

  std::cout << min_cut << std::endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) testcase();
}
