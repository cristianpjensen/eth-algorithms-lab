#include <bits/stdc++.h>

// Time complexity: O(n^2).
// There are n layers. Each layer d has 2 + d - 1 values that need to be
// computed. The maximum value of d is n, so each layer has O(n) complexity
// which has to be computed n times, thus the time complexity is O(n^2).

typedef std::vector<int> VI;
typedef std::vector<VI> VVI;

int minimax(VI& values, VVI& memo, int n, int left, int right)
{
  // The current layer is the amount of times that has been shifted left and
  // right.
  int layer = left + (n - 1) - right;

  // The players alternate with our player starting.
  bool maxi = layer % 2 == 0;

  // Base case
  if (left == right)
    return values[left] * maxi;

  // All values with the same amount of left shift and layer are the exact same,
  // since the right shift for this layer is also the same for all of these.
  if (memo[layer][left] != -1)
    return memo[layer][left];

  if (maxi)
  {
    memo[layer][left] = std::max(
      minimax(values, memo, n, left + 1, right) + values[left],
      minimax(values, memo, n, left, right - 1) + values[right]
    );
  }
  else
  {
    memo[layer][left] = std::min(
      minimax(values, memo, n, left + 1, right),
      minimax(values, memo, n, left, right - 1)
    );
  }

  return memo[layer][left];
}

void testcase()
{
  int n; std::cin >> n;
  VI values(n);
  for (int i = 0; i < n; i++)
    std::cin >> values[i];

  VVI memo(n, VI(n, -1));
  std::cout << minimax(values, memo, n, 0, n-1) << std::endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) testcase();
}
