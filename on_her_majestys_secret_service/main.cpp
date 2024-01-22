#include <bits/stdc++.h>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

typedef std::vector<int> VI;
typedef std::vector<VI> VVI;

// Normal graph
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
  boost::no_property, boost::property<boost::edge_weight_t, int>>      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;

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
    c_map[rev_e] = 0;
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};

bool is_possible(
  VVI& min_time,
  int a,
  int s,
  int c,
  int d,
  int t
)
{
  // Bipartite matching between agents and shelters with only the combinations
  // such that they are reachable within `t`.
  graph G(a+c*s);
  edge_adder adder(G);

  const int v_source = boost::add_vertex(G);
  const int v_target = boost::add_vertex(G);
  
  for (int i = 0; i < a; i++)
  {
    adder.add_edge(v_source, i, 1);
    for (int j = 0; j < s; j++)
    {
      if (min_time[i][j] == -1)
        continue;

      // For every mapping, also make sure that it would be possible to get
      // inside in time. Add one spot for every time such that we have to wait
      // `k*d` seconds for the `k` people before.
      for (int k = 0; k < c; k++)
        if (min_time[i][j] + (k + 1) * d <= t && min_time[i][j] != -1)
          adder.add_edge(i, a + s*k + j, 1);
    }
  }
  
  for (int j = 0; j < s; j++)
    for (int k = 0; k < c; k++)
      adder.add_edge(a + s*k + j, v_target, 1);

  int flow = boost::push_relabel_max_flow(G, v_source, v_target);

  // Return whether every agent can get to safety within `t` time.
  return flow == a;
}

void testcase()
{
  int n, m, a, s, c, d; std::cin >> n >> m >> a >> s >> c >> d;
  
  weighted_graph G(n);
  weight_map weights = boost::get(boost::edge_weight, G);
  
  // Read in slopes and ski lifts.
  for (int i = 0; i < m; i++)
  {
    char w; int x, y, z; std::cin >> w >> x >> y >> z;
    
    edge_desc e = boost::add_edge(x, y, G).first; weights[e] = z;
    if (w == 'L') 
    {
      edge_desc e = boost::add_edge(y, x, G).first; weights[e] = z;
    }
  }

  // Read in agent positions.
  VI agents(a);
  for (int i = 0; i < a; i++)
    std::cin >> agents[i];
  
  // Read in shelter positions.
  VI shelters(s);
  for (int i = 0; i < s; i++)
    std::cin >> shelters[i];

  VVI min_time(a, VI(s, -1));
  for (int i = 0; i < a; i++)
  {
    // Find min time to all shelters with Dijkstra
    std::vector<int> dist_map(n);
    boost::dijkstra_shortest_paths(G, agents[i],
      boost::distance_map(
        boost::make_iterator_property_map(
          dist_map.begin(),
          boost::get(boost::vertex_index, G))));

    for (int j = 0; j < s; j++)
    {
      if (dist_map[shelters[j]] != INT_MAX)
        min_time[i][j] = dist_map[shelters[j]];
    }
  }

  // Monotonous relationship: more time => more agents get to safety. So, we
  // binary search over time and search for the minimum time to get everyone to
  // safety.
  int left = 0;
  int right = 10000000;
  while (left < right)
  {
    int mid = (left + right) / 2;
    if (is_possible(min_time, a, s, c, d, mid))
      right = mid;
    else
      left = mid + 1;
  }

  std::cout << left << std::endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) testcase();
}
