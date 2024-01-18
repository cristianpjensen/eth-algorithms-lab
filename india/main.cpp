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
                boost::property <boost::edge_weight_t, long>>>>> graph;

typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;

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
  int c, g; long b; int k, a; std::cin >> c >> g >> b >> k >> a;

  // Construct graph => binary search over amount of luggage to their price
  graph G(c);
  edge_adder adder(G);  

  const int v_source = boost::add_vertex(G);

  for (int i = 0; i < g; i++)
  {
    int x, y, d, e; std::cin >> x >> y >> d >> e;
    adder.add_edge(x, y, e, d);
  }

  adder.add_edge(v_source, k, INT_MAX, 0);

  long flow = boost::push_relabel_max_flow(G, v_source, a);
  boost::successive_shortest_path_nonnegative_weights(G, v_source, a);

  // Upper bounded by the maximum flow
  int left = 0;
  int right = flow;

  while (left <= right)
  {
    int mid = (left + right) / 2;

    // Set max luggage
    boost::remove_edge(v_source, k, G);
    adder.add_edge(v_source, k, mid, 0);

    // Compute minimum cost of bringing `mid` amount of luggage
    flow = boost::push_relabel_max_flow(G, v_source, a);
    boost::successive_shortest_path_nonnegative_weights(G, v_source, a);
    int cost = boost::find_flow_cost(G);

    if (cost <= b)
      left = mid+1;
    else
      right = flow-1;
  }

  std::cout << right << std::endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) testcase();
}
