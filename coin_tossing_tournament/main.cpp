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

  // One vertex for each player and each match
  graph G(n+m);
  edge_adder adder(G);

  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_target = boost::add_vertex(G);

  for (int i = 0; i < m; i++)
  {
    int a, b, c; std::cin >> a >> b >> c;
    int match_vertex = n+i;

    // Each match gets 1 point to distribute
    adder.add_edge(v_source, match_vertex, 1);

    // Each match distributes its point to its winner
    // If unsure about who won, make it possible to distribute to both
    if (c == 0)
    {
      adder.add_edge(match_vertex, a, 1);
      adder.add_edge(match_vertex, b, 1);
    }
    else if (c == 1)
      adder.add_edge(match_vertex, a, 1);
    else if (c == 2)
      adder.add_edge(match_vertex, b, 1);
  }

  // Each player should receive at most its amount of wins
  int total_wins = 0;
  for (int i = 0; i < n; i++)
  {
    int wins; std::cin >> wins;
    adder.add_edge(i, v_target, wins);
    total_wins += wins;
  }

  // Dumb ass cheaters
  if (total_wins != m)
  {
    std::cout << "no" << std::endl;
    return;
  }

  int flow = boost::push_relabel_max_flow(G, v_source, v_target);

  if (flow == m)
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
