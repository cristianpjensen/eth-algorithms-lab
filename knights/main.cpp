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
  int m, n, k, c; std::cin >> m >> n >> k >> c;

  graph G(2*m*n);
  edge_adder adder(G);

  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_target = boost::add_vertex(G);

  for (int i = 0; i < m; i++)
  {
    for (int j = 0; j < n; j++)
    {
      int index = i * n + j;
      int input = index;
      int output = m*n + index;

      // An intersection can be used at most `c` times
      adder.add_edge(input, output, c);

      // Hallway up
      if (i-1 >= 0)
        adder.add_edge(output, (i-1) * n + j, 1);

      // Hallway down
      if (i+1 < m)
        adder.add_edge(output, (i+1) * n + j, 1);

      // Hallway left
      if (j-1 >= 0)
        adder.add_edge(output, i * n + (j-1), 1);

      // Hallway right
      if (j+1 <= n)
        adder.add_edge(output, i * n + (j+1), 1);

      // On the top side
      if (i == 0)
        adder.add_edge(output, v_target, 1);

      // On the bottom side
      if (i == m-1)
        adder.add_edge(output, v_target, 1);

      // On the left side
      if (j == 0)
        adder.add_edge(output, v_target, 1);

      // On the right side
      if (j == n-1)
        adder.add_edge(output, v_target, 1);
    }
  }

  // Connect to input vertices of where they start
  for (int i = 0; i < k; i++)
  {
    int x, y; std::cin >> x >> y;
    adder.add_edge(v_source, x * n + y, 1);
  }

  // The maximum flow is the maximum amount of soldiers that can get from their
  // position to the target, i.e., outside
  int flow = boost::push_relabel_max_flow(G, v_source, v_target);
  std::cout << flow << std::endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) testcase();
}
