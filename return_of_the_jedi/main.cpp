#include <bits/stdc++.h>
#include <boost/pending/disjoint_sets.hpp>

typedef std::vector<int> VI;
typedef std::vector<VI> VVI;
typedef std::pair<int, int> Edge;
typedef std::pair<int, Edge> WeightedEdge;

int min_cost_constrained(
  std::vector<WeightedEdge>& edges,
  int n,
  Edge disallowed_edge
)
{
  int total_cost = 0;
  
  boost::disjoint_sets_with_storage<> uf(n);
  int n_components = n;

  // The edges have to be ordered in increasing order
  for (WeightedEdge cost_edge : edges) {
    int cost = cost_edge.first;
    Edge edge = cost_edge.second;
    
    // Skip over the disallowed edge
    if (
      (edge.first == disallowed_edge.first && edge.second == disallowed_edge.second)
      || (edge.first == disallowed_edge.second && edge.second == disallowed_edge.first)
    )
      continue;
    
    // Determine components of endpoints
    int c1 = uf.find_set(edge.first);
    int c2 = uf.find_set(edge.second);

    if (c1 != c2) {
      // This edge connects two different components => part of the EMST
      uf.link(c1, c2);
      total_cost += cost;

      if (--n_components == 1) break;
    }
  }
  
  return total_cost;
}

void testcase()
{
  int n, tattooine; std::cin >> n >> tattooine;
  
  // Make it 0-indexed...
  tattooine--;
  
  VVI costs(n, VI(n, 0));
  std::vector<WeightedEdge> edges;
  
  for (int j = 0; j < n-1; j++)
  {
    for (int k = 1; k < n-j; k++)
    {
      int cost; std::cin >> cost;
      costs[j][j+k] = cost;
      costs[j+k][j] = cost;
      edges.push_back({ cost, { j, j+k }});
    }
  }
  
  std::sort(edges.begin(), edges.end());

  // First, find all the edges that Leia uses, which she finds by Prim's
  // algorithm
  std::vector<Edge> leia;

  std::priority_queue<std::tuple<int, int, int>> Q;
  std::vector<bool> explored(n, false);
  Q.push({ 0, tattooine, -1 });
  for (int i = 0; i < n; i++)
  {
    auto p = Q.top(); Q.pop();
    
    // Make sure that the newly explored vertex has not been explored yet,
    // because this could be the case if we added this earlier
    while (explored[std::get<1>(p)])
    {
      p = Q.top();
      Q.pop();
    }

    int to_planet = std::get<1>(p);
    int from_planet = std::get<2>(p);

    if (from_planet != -1)
      leia.push_back({ from_planet, to_planet });

    explored[to_planet] = true;
    
    for (int j = 0; j < n; j++)
    {
      if (explored[j])
        continue;

      int cost = costs[to_planet][j];
      
      // Do the indices in this order, such that it first picks the most
      // important planet
      Q.push({ -cost, j, to_planet });
    }
  }
  
  // Find the minimum cost of a plan that differs from Leia's in at least one
  // edge, i.e., for every edge in Leia's plan, we constrain it such that this
  // edge is not allowed, and compute the cost
  int min_cost = INT_MAX;
  for (Edge disallowed_edge : leia)
  {
    int cost = min_cost_constrained(edges, n, disallowed_edge);
    min_cost = std::min(min_cost, cost);
  }

  std::cout << min_cost << std::endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) testcase();
}
