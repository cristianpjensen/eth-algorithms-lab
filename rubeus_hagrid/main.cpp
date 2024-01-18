#include <bits/stdc++.h>

struct State {
  long total_time;
  long total_gold;

  State()
  {
    total_time = 0;
    total_gold = 0;
  }
};

struct GreedyEdge {
  int to;
  long time;
  long descendants;
  long time_cost;

  GreedyEdge(int to_, long time_, long descendants_, long time_cost_)
  {
    to = to_;
    time = time_;
    descendants = descendants_;
    time_cost = time_cost_;
  }
};

typedef std::vector<long> VL;
typedef std::vector<GreedyEdge> VGreedyEdge;
typedef std::pair<int, long> PII;
typedef std::vector<PII> VPII;
typedef std::vector<VPII> VVPII;

long descendants(
  VVPII& children,
  VL& num_descendants,
  int v
)
{
  long total_desc = 1;
  for (PII child : children[v])
    total_desc += descendants(children, num_descendants, child.first);

  num_descendants[v] = total_desc;
  return total_desc;
}

long traversal_time(
  VVPII& children,
  VL& time_cost,
  int v,
  long edge_time
)
{
  long total_time = edge_time * 2;
  for (PII child : children[v])
    total_time += traversal_time(children, time_cost, child.first, child.second);

  time_cost[v] = total_time;
  return total_time;
}

void greedy_dfs(
  State& state,
  VL& gold,
  VVPII& children,
  VL& num_descendants,
  VL& time_cost,
  int v
)
{
  state.total_gold += gold[v] - state.total_time;
  
  // Make the data structure such that we can compare edges
  VGreedyEdge greedy_edges;
  for (PII child : children[v])
  {
    greedy_edges.push_back(GreedyEdge(
      child.first,
      child.second,
      num_descendants[child.first],
      time_cost[child.first]
    ));
  }
  
  // Decide the order in which we should visit children subtrees. Greedily choose
  // such that we lose the least amount of gold.
  std::sort(
    greedy_edges.begin(),
    greedy_edges.end(),
    [](const GreedyEdge& e1, const GreedyEdge& e2) -> bool { 
      return e1.time_cost * e2.descendants < e2.time_cost * e1.descendants;
    }
  );

  // Visit the children subtrees and compute how much gold is collected. Time
  // has to be added twice: once down and once up.
  for (GreedyEdge edge : greedy_edges)
  {
    state.total_time += edge.time;
    greedy_dfs(state, gold, children, num_descendants, time_cost, edge.to);
    state.total_time += edge.time;
  }
}

void testcase()
{
  int n; std::cin >> n;

  VL gold(n+1, 0);

  for (int i = 1; i <= n; i++)
    std::cin >> gold[i];

  VVPII children(n+1);

  for (int i = 0; i < n; i++)
  {
    int u, v, l; std::cin >> u >> v >> l;
    children[u].push_back({ v, l });
  }

  // Compute how many descendants, including the parent, every subtree has
  VL num_descendants(n+1);
  descendants(children, num_descendants, 0);
  
  // Compute how much time each subtree costs to traverse down and up. This is
  // how much gold per node in the other subtrees we lose. Thus, that is what we
  // want to minimize every step of the DFS traversal.
  VL time_cost(n+1);
  traversal_time(children, time_cost, 0, 0);

  // Keep track of a global state (all instances of the DFS function can access
  // it) that stores the time that has passed and the amount of gold collected
  State state;
  greedy_dfs(state, gold, children, num_descendants, time_cost, 0);

  std::cout << state.total_gold << std::endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) testcase();
}
