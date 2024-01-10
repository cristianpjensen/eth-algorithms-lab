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
  int w, h; std::cin >> w >> h;

  int num_tiles = 0;
  VVB tiles(h, VB(w, false));
  for (int i = 0; i < h; i++)
  {
    for (int j = 0; j < w; j++)
    {
      char c; std::cin >> c;
      if (c == '.')
      {
        num_tiles++;
        tiles[i][j] = true;
      }
    }
  }

  if (num_tiles % 2 != 0)
  {
    std::cout << "no" << std::endl;
    return;
  }

  graph G(h*w);
  edge_adder adder(G);

  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_target = boost::add_vertex(G);

  for (int i = 0; i < h; i++)
  {
    for (int j = 0; j < w; j++)
    {
      if (!tiles[i][j])
        continue;

      int vertex = i * w + j;

      if ((i + j) % 2 == 0)
      {
        adder.add_edge(v_source, vertex, 1);

        // Add edge up
        if (i - 1 >= 0 && tiles[i-1][j])
          adder.add_edge(vertex, (i-1) * w + j, 1);
        
        // Add edge down
        if (i + 1 < h && tiles[i+1][j])
          adder.add_edge(vertex, (i+1) * w + j, 1);
        
        // Add edge left
        if (j - 1 >= 0 && tiles[i][j-1])
          adder.add_edge(vertex, i * w + (j-1), 1);

        // Add edge right
        if (j + 1 < w && tiles[i][j+1])
          adder.add_edge(vertex, i * w + (j+1), 1);
      }
      else
        adder.add_edge(vertex, v_target, 1);
    }
  }

  int flow = boost::push_relabel_max_flow(G, v_source, v_target);

  if (flow == num_tiles / 2)
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
