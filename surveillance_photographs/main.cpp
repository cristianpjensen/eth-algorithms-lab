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
  int n, m, k, l; std::cin >> n >> m >> k >> l;

  // We define two graphs within `G`. One where the policemen can drive as much
  // as they want through the streets, and one where the policemen can use each
  // street once. Then, to collect a photograph, the policeman has to traverse
  // the following: police station -> photograph -> limited graph -> police
  // station.
  graph G(2*n);
  edge_adder adder(G);
  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_target = boost::add_vertex(G);

  // Police stations
  for (int i = 0; i < k; i++)
  {
    int x; std::cin >> x;

    // There is one policeman that starts here
    adder.add_edge(v_source, x*2, 1);

    // There is one safe that can store one photograph here
    adder.add_edge(x*2+1, v_target, 1);
  }

  // Photograph locations
  for (int i = 0; i < l; i++)
  {
    int x; std::cin >> x;

    // The policeman has to go from the graph where all edges can be used as
    // much as wanted to the graph where each edge can be used once.
    adder.add_edge(x*2, x*2+1, 1);
  }

  for (int i = 0; i < m; i++)
  {
    int x, y; std::cin >> x >> y;
    adder.add_edge(x*2, y*2, k);
    adder.add_edge(x*2+1, y*2+1, 1);
  }

  int flow = boost::push_relabel_max_flow(G, v_source, v_target);
  std::cout << flow << std::endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) testcase();
}
