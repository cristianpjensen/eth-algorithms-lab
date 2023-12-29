#include <bits/stdc++.h>

// Time complexity: O(n^2), because the tree is n x n that needs to be filled.

typedef std::vector<int> VI;
typedef std::vector<VI> VVI;

int minimax(
  VVI &memo,
  VI &values,
  int n,
  int m,
  int k,
  int left,
  int right
)
{
  if (memo[left][right] != -1)
    return memo[left][right];

  int coins_taken = left + (n-1) - right;
  bool maxi = coins_taken % m == k;

  if (left == right)
  {
    if (maxi)
      return values[left];
    else
      return 0;
  }

  if (maxi)
  {
    memo[left][right] = std::max(
      minimax(memo, values, n, m, k, left + 1, right) + values[left],
      minimax(memo, values, n, m, k, left, right - 1) + values[right]
    );
  }
  else
  {
     memo[left][right] = std::min(
      minimax(memo, values, n, m, k, left + 1, right),
      minimax(memo, values, n, m, k, left, right - 1)
    );
  }

  return memo[left][right];
}

void testcase()
{
  int n, m, k; std::cin >> n >> m >> k;

  VI values(n);
  for (int i = 0; i < n; i++)
    std::cin >> values[i];

  VVI memo(n, VI(n, -1));
  std::cout << minimax(memo, values, n, m, k, 0, n-1) << std::endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) testcase();
}
