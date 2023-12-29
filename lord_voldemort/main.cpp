#include <bits/stdc++.h>

typedef std::vector<int> VI;
typedef std::vector<VI> VVI;

// Time complexity: O(m*n).

void testcase() {
  int n, m, k; std::cin >> n >> m >> k;

  VI cumsum(n+1);
  cumsum[0] = 0;
  for (int i = 0; i < n; i++)
  {
    int x; std::cin >> x;
    cumsum[i+1] = cumsum[i] + x;
  }

  VI interval_pointers(n, -1);

  // Find all intervals that sum to k (O(n)) and have a pointer from the end
  // index to the start index. This will come in handy later.
  int i = 0, j = 0;
  while (j < n) {
    int window_sum = cumsum[j + 1] - cumsum[i];

    if (window_sum == k)
      interval_pointers[j] = i;

    if (window_sum < k)
      j++;
    else
      i++;
  }

  VVI table(m+1, VI(n+1, 0));

  // Fill the table such that table[i][j] corresponds to the subproblem of m=i
  // and n=j. Then, table[i][j] is equal to the maximum between the smaller
  // subarray (table[i][j-1]) and the current interval length + the previous
  // non-overlapping subarray (which is the entire subarray - the current
  // interval). If there is no interval at the current index, just copy the
  // previous subarray's value. O(m*n).
  for (int i = 1; i <= m; i++)
  {
    for (int j = 1; j <= n; j++)
    {
      int interval_start = interval_pointers[j-1];

      table[i][j] = table[i][j-1];

      // Make sure that we are allowed to pick this interval by making sure that
      // either i=1 or something has been picked before, i.e.,
      // table[i-1][interval_start] != 0. Because otherwise, not all i wizards
      // will have used their power.
      if (interval_start != -1 && (table[i-1][interval_start] != 0 || i == 1))
      {
        int interval_length = j - interval_start;
        table[i][j] = std::max(table[i][j-1], table[i-1][interval_start] + interval_length);
      }
    }
  }

  // Then, the longest non-overlapping sum of subarrays is equal to table[m][n],
  // since that is how we defined the table.
  if (table[m][n] == 0)
    std::cout << "fail" << std::endl;
  else
    std::cout << table[m][n] << std::endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) testcase();
}
