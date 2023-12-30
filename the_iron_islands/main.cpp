#include <bits/stdc++.h>

typedef std::vector<int> VI;
typedef std::vector<VI> VVI;

void testcase()
{
  // Number of islands, Number of men at disposal, Number of waterways
  int n, k, w; std::cin >> n >> k >> w;

  VI cost(n);
  for (int i = 0; i < n; i++)
    std::cin >> cost[i];

  VI waterway_length(w);
  VVI cumsums(w, VI(1, 0));
  for (int i = 0; i < w; i++)
  {
    int l; std::cin >> l;
    waterway_length[i] = l;

    // Cumsum makes it easier to compute how many men are necessary for a subset
    // of islands
    for (int j = 1; j <= l; j++)
    {
      int r; std::cin >> r;
      cumsums[i].push_back(cumsums[i][j-1] + cost[r]);
    }
  }

  int max_islands = 0;

  // Sliding window over every waterway
  for (int i = 0; i < w; i++)
  {
    int a = 0, b = 0;
    while (a <= waterway_length[i] && b <= waterway_length[i])
    {
      int total_cost = cumsums[i][b] - cumsums[i][a];

      if (total_cost == k)
      {
        max_islands = std::max(max_islands, b - a);
        a++;
        b++;
      }
      else if (total_cost > k)
        a++;
      else if (total_cost < k)
        b++;
    }
  }

  // Construct a look-up table that maps cost to maximum amount of islands
  // attainable, minus Pyke. Also, keep track of what waterway is the maximum,
  // since we need to make sure we do not use the same waterway twice. This does
  // not make it impossible to find the maximum value in some edge cases,
  // because we always go from every waterway, so we can find it from the other
  // way
  std::vector<std::pair<int, int>> lookup(k+1, { -1, -1 });
  for (int i = 0; i < w; i++)
  {
    for (int j = 2; j <= waterway_length[i]; j++)
    {
      int total_cost = cumsums[i][j] - cost[0];
      
      if (total_cost <= k)
      {
        if (j - 1 > lookup[total_cost].first)
          lookup[total_cost] = { j - 1, i };
      }
      else
        break;
    }
  }

  for (int i = 0; i < w; i++)
  {
    for (int j = 2; j <= waterway_length[i]; j++)
    {
      if (cumsums[i][j] >= k)
        break;

      int more_needed = k - cumsums[i][j];

      // Make sure that it is possible, and that it is not possible by going
      // back up the same waterway
      if (lookup[more_needed].first != -1 && lookup[more_needed].second != i)
        max_islands = std::max(max_islands, j + lookup[more_needed].first);
    }
  }

  std::cout << max_islands << std::endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) testcase();
}
