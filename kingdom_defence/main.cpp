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

typedef std::vector<int> VI;

// Time complexity: O(l^3)

void testcase()
{
  int l, p; std::cin >> l >> p;

  VI g(l), d(l);
  for (int i = 0; i < l; i++)
    std::cin >> g[i] >> d[i];

  graph G(l);
  edge_adder adder(G);

  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_target = boost::add_vertex(G);

  for (int j = 0; j < p; j++)
  {
    int f, t, c, C; std::cin >> f >> t >> c >> C;

    // See the max flow slides about minimum capacity consraints

    // Adjust for the minimum amount of flow through the edge
    d[f] += c;
    g[t] += c;

    // Add edge (f, t) with capacity C - c
    adder.add_edge(f, t, C - c);
  }

  int required_flow = 0;
  for (int i = 0; i < l; i++)
  {
    required_flow += d[i];

    // The location has g soldiers and requires d (adjusted for minimum flow
    // constraints)
    adder.add_edge(v_source, i, g[i]);
    adder.add_edge(i, v_target, d[i]);
  }

  int flow = boost::push_relabel_max_flow(G, v_source, v_target);
  if (flow == required_flow)
    std::cout << "yes" << std::endl;
  else
    std::cout << "no" << std::endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) testcase();
}
