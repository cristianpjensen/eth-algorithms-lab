#include <bits/stdc++.h>

// Time complexity: O(n^2).

typedef std::vector<int> VI;
typedef std::vector<VI> VVI;

int minimax(VVI& memo, VI& values, bool maxi, int left, int right)
{
  // Base case
  if (left == right)
  {
    if (maxi)
      return values[left];
    else
      return 0;
  }

  // Check if memoized
  if (memo[left][right] != -1)
    return memo[left][right];

  // Add value of picked coin if maxi, otherwise not
  if (maxi)
  {
    memo[left][right] = std::max(
      minimax(memo, values, false, left + 1, right) + values[left],
      minimax(memo, values, false, left, right - 1) + values[right]
    );
  }
  else
  {
    memo[left][right] = std::min(
      minimax(memo, values, true, left + 1, right),
      minimax(memo, values, true, left, right - 1)
    );
  }

  return memo[left][right];
}

void testcase()
{
  int n; std::cin >> n;
  VI values(n);
  for (int i = 0; i < n; i++)
    std::cin >> values[i];

  VVI memo(n, VI(n, -1));
  std::cout << minimax(memo, values, true, 0, n-1) << std::endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) testcase();
}
