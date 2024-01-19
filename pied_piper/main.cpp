#include <bits/stdc++.h>

typedef std::pair<int, int> PII;
typedef std::vector<PII> VPII;
typedef std::vector<VPII> VVPII;
typedef std::vector<int> VI;
typedef std::vector<VI> VVI;

int dp(
  VVPII& adj_forward,
  VVPII& adj_backward,
  int n,
  VVI& memo,
  int v_forward,
  int v_backward
)
{
  // Base case
  if (v_forward == n-1 && v_backward == n-1)
    return 0;

  // Cannot go forward anymore, so it is not a valid forward path that can reach
  // n-1 from 0
  if (v_forward != n-1 && adj_forward[v_forward].empty())
    return -2;

  // Cannot go backward anymore, so it is not a valid backward path that can
  // reach 0 from n-1
  if (v_backward != n-1 && adj_backward[v_backward].empty())
    return -2;

  // Vertices may never be visited twice (except for 0), so it is not a valid
  // concatenation of forward and backward paths
  if (v_forward == v_backward && v_forward != 0)
    return -2;

  // Memoization
  if (memo[v_forward][v_backward] != -1)
    return memo[v_forward][v_backward];

  // If no next paths are valid, we want to output -2, which can be the case if
  // all next paths from this path are invalid according to the above rules
  int max_rats = -2;

  if (v_forward <= v_backward)
  {
    // Increase the forward layer
    for (auto p : adj_forward[v_forward])
    {
      int v_forward_next = p.first;
      int rats = p.second;
      
      int rats_cont = dp(adj_forward, adj_backward, n, memo, v_forward_next, v_backward);
      if (rats_cont >= 0)
        max_rats = std::max(max_rats, rats + rats_cont);
    }
  }
  else
  {
    // Increase the backward layer
    for (auto p : adj_backward[v_backward])
    {
      int v_backward_next = p.first;
      int rats = p.second;
      
      int rats_cont = dp(adj_forward, adj_backward, n, memo, v_forward, v_backward_next);
      if (rats_cont >= 0)
        max_rats = std::max(max_rats, rats + rats_cont);
    }
  }
  
  memo[v_forward][v_backward] = max_rats;
  return memo[v_forward][v_backward];
}

void testcase()
{
  int n, m; std::cin >> n >> m;
  
  VVPII adj_forward(n);
  VVPII adj_backward(n);
  
  for (int i = 0; i < m; i++)
  {
    int u, v, f; std::cin >> u >> v >> f;
    
    if (u < v)
      adj_forward[u].push_back({ v, f });
    else
      adj_backward[v].push_back({ u, f });
  }
  
  VVI memo(n, VI(n, -1));
  int max_rats = dp(adj_forward, adj_backward, n, memo, 0, 0);
  std::cout << max_rats << std::endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) testcase();
}
