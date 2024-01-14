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

typedef std::vector<bool> VB;
typedef std::vector<VB> VVB;

void testcase()
{
  int n; std::cin >> n;

  VVB present(n, VB(n));
  int valid_positions = 0;

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      std::cin >> present[i][j];
      if (present[i][j])
        valid_positions++;
    }
  }


  graph G(n * n);
  edge_adder adder(G);

  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_target = boost::add_vertex(G);

  const std::vector<std::pair<int, int>> knight_offsets = {
    { -1, -2 },
    { -1, +2 },
    { +1, -2 },
    { +1, +2 },
    { -2, -1 },
    { -2, +1 },
    { +2, -1 },
    { +2, +1 }
  };

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      if (!present[i][j])
        continue;

      bool is_white = (i + j) % 2 == 0;

      if (is_white)
      {
        adder.add_edge(v_source, i*n + j, 1);

        for (auto offset : knight_offsets)
        {
          int i_black = i + offset.first;
          int j_black = j + offset.second;

          if (
            i_black >= 0 && i_black < n
            && j_black >= 0 && j_black < n
            && is_present[i_black][j_black]
          )
            adder.add_edge(i*n + j, i_black*n+j_black, 1);
        }
      }
      else
      {
        adder.add_edge(i*n+j, target, 1);
      }
    }
  }

  // The maximum flow is the amount of white positions that we can pick without
  // considering black positions. Each white position also constrains a unique
  // black position. Since each white position constrains a black position, this
  // is also the minimum amount of positions that cannot be filled. Black
  // positions do not constrain each other, so we can fill all unconstrained
  // black positions up, since no white positions constrain them.
  //
  // In other words, we are computing the maximum amount of collisions.
  int flow = boost::push_relabel_max_flow(G, v_source, v_target);
  std::cout << valid_positions - flow << std::endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) testcase();
}
