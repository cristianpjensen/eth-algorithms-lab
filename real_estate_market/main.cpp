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
  int N, M, S; std::cin >> N >> M >> S;

  graph G(N+M+S);
  edge_adder adder(G);

  const int v_source = boost::add_vertex(G);
  const int v_target = boost::add_vertex(G);

  // Restrict the amount of properties can be bought within each state
  for (int k = 0; k < S; k++)
  {
    int l; std::cin >> l;
    adder.add_edge(N+M+k, v_target, l, 0);
  }

  // Assign each property to its state. Together with the previous constraint,
  // we constrain the amount of properties that can be sold within a state. We
  // also constrain how many times a property can be purchased to 1.
  for (int j = 0; j < M; j++)
  {
    int s; std::cin >> s;
    adder.add_edge(N+j, N+M+s-1, 1, 0);
  }

  for (int i = 0; i < N; i++)
  {
    // Each buyer can buy one property
    adder.add_edge(v_source, i, 1, 0);

    // Link each buyer to the property by their bid on that property
    for (int j = 0; j < M; j++)
    {
      int b; std::cin >> b;
      adder.add_edge(i, N+j, 1, 100-b);
    }
  }

  int flow = boost::push_relabel_max_flow(G, v_source, v_target);
  boost::successive_shortest_path_nonnegative_weights(G, v_source, v_target);
  int cost = boost::find_flow_cost(G);
  int profit = flow * 100 - cost;

  std::cout << flow << ' ' << profit << std::endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) testcase();
}
