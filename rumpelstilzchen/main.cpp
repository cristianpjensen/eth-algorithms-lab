#include <bits/stdc++.h>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > graph; // new! weightmap corresponds to costs

typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it; // Iterator

class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}
  void add_edge(int from, int to, long capacity, long cost) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto w_map = boost::get(boost::edge_weight, G); // new!
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
    w_map[e] = cost;   // new assign cost
    w_map[rev_e] = -cost;   // new negative cost
  }
};

void testcase()
{
  int n, pG, pH, eG, eH, fG, fH, sG, sH;
  std::cin >> n >> pG >> pH >> eG >> eH >> fG >> fH >> sG >> sH;
  
  graph G(2*n + pG + pH);
  edge_adder adder(G);
  
  const int v_source = boost::add_vertex(G);
  const int v_target = boost::add_vertex(G);
  
  // Encode preference, and make sure only one capacity goes through an island
  for (int i = 0; i < n; i++)
  {
    int preference; std::cin >> preference;
    adder.add_edge(i*2, i*2+1, 1, pow(2, 10) - preference);
  }
  
  // Network G
  for (int i = 0; i < eG; i++)
  {
    int u, v, c; std::cin >> u >> v >> c;
    adder.add_edge(2*n+u, 2*n+v, c, 0);
  }
  
  // Network H. Reversed.
  for (int i = 0; i < eH; i++)
  {
    int u, v, c; std::cin >> u >> v >> c;
    adder.add_edge(2*n+pG+v, 2*n+pG+u, c, 0);
  }
  
  // From G to islands.
  for (int i = 0; i < fG; i++)
  {
    int u, v, c; std::cin >> u >> v >> c;
    adder.add_edge(2*n+u, 2*v, c, 0);
  }
  
  // From H to islands. Reversed.
  for (int i = 0; i < fH; i++)
  {
    int u, v, c; std::cin >> u >> v >> c;
    adder.add_edge(2*v+1, 2*n+pG+u, c, 0);
  }
  
  // Source to the castles
  adder.add_edge(v_source, 2*n, sG, 0);
  adder.add_edge(2*n+pG, v_target, sH, 0);
  
  int flow = boost::push_relabel_max_flow(G, v_source, v_target);
  boost::successive_shortest_path_nonnegative_weights(G, v_source, v_target);
  int cost = boost::find_flow_cost(G);
  
  std::cout << flow << ' ' << flow * pow(2, 10) - cost << std::endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) testcase();
}
