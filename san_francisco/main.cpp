#include <bits/stdc++.h>

typedef std::vector<long> VL;
typedef std::vector<VL> VVL;
typedef std::vector<std::vector<std::pair<int, long>>> VVPIL;

// State space: (current vertex, amount of moves left). Value: max_score.
long max_score(VVPIL& canals, VVL& dp_table, int k, int v)
{
  // Base case
  if (k == 0)
    return 0;

  // Memoization
  if (dp_table[k][v] != -1)
    return dp_table[k][v];

  // If no more children, go to start
  if (canals[v].empty())
  {
    dp_table[k][v] = max_score(canals, dp_table, k, 0);
    return dp_table[k][v];
  }

  // Find best continuing path
  long best_score = 0;

  for (auto canal : canals[v])
  {
    int v_next = canal.first;
    long score = canal.second;

    best_score = std::max(
      best_score,
      score + max_score(canals, dp_table, k-1, v_next)
    );
  }

  dp_table[k][v] = best_score;
  return dp_table[k][v];
}

void testcase()
{
  int n, m, k; long x; std::cin >> n >> m >> x >> k;

  VVPIL canals(n);
  for (int i = 0; i < m; i++)
  {
    int u, v; long p; std::cin >> u >> v >> p;
    canals[u].push_back({ v, p });
  }

  // Fill out DP table
  VVL dp_table(k+1, VL(n, -1));
  max_score(canals, dp_table, k, 0);

  for (int i = 1; i <= k; i++)
  {
    if (max_score(canals, dp_table, i, 0) >= x)
    {
      std::cout << i << std::endl;
      return;
    }
  }

  std::cout << "Impossible" << std::endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) testcase();
}
