#include <bits/stdc++.h>

typedef std::vector<int> VI;
typedef std::vector<VI> VVI;

void testcase()
{
  int n; std::cin >> n;

  VI a_cumsum(n+1);
  a_cumsum[0] = 0;
  for (int i = 0; i < n; i++)
  {
    int a_current; std::cin >> a_current;
    a_cumsum[i+1] = a_cumsum[i] + a_current;
  }

  VI b_cumsum(n+1);
  b_cumsum[0] = 0;
  for (int j = 0; j < n; j++)
  {
    int b_current; std::cin >> b_current;
    b_cumsum[j+1] = b_cumsum[j] + b_current;
  }

  VVI dp(n+1, VI(n+1, 0));

  // Base case: b=1, then we have to pick all of a
  for (int i = 1; i <= n; i++)
    dp[i][1] = (a_cumsum[i] - i) * (b_cumsum[1] - 1);

  // Base case: a=1, then we have to pick all of b
  for (int j = 1; j <= n; j++)
    dp[1][j] = (a_cumsum[1] - 1) * (b_cumsum[j] - j);

  // a=i, b=j
  for (int i = 2; i <= n; i++)
  {
    for (int j = 2; j <= n; j++)
    {
      int minimum = INT_MAX;

      // Either pick 1 on a or 1 on b, since then it is additively added to the
      // cost, instead of multiplicatively
      for (int i_picked = 1; i_picked < i; i_picked++)
      {
        int j_picked = 1;
        int a_sum = a_cumsum[i] - a_cumsum[i - i_picked];
        int b_sum = b_cumsum[j] - b_cumsum[j - j_picked];
        int cost = (a_sum - i_picked) * (b_sum - j_picked);
        minimum = std::min(minimum, cost + dp[i-i_picked][j-j_picked]);
      }

      for (int j_picked = 1; j_picked < j; j_picked++)
      {
        int i_picked = 1;
        int a_sum = a_cumsum[i] - a_cumsum[i - i_picked];
        int b_sum = b_cumsum[j] - b_cumsum[j - j_picked];
        int cost = (a_sum - i_picked) * (b_sum - j_picked);
        minimum = std::min(minimum, cost + dp[i-i_picked][j-j_picked]);
      }

      dp[i][j] = minimum;
    }
  }

  std::cout << dp[n][n] << std::endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) testcase();
}
