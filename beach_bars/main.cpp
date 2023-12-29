#include <bits/stdc++.h>

// Time complexity: O(n log n).
// The slowest operation in this chain of operations is the sorting, which has
// O(n log n) complexity.

typedef std::vector<int> VI;

void testcase()
{
  int n; std::cin >> n;

  VI coords(n);
  for (int i = 0; i < n; i++)
    std::cin >> coords[i];

  // Sort (O(n log n)).
  std::sort(coords.begin(), coords.end());

  // Sliding window (O(n)).
  int i = 0, j = 0;
  int max_parasols = 0;
  int min_max_dist = INT_MAX;

  // A set makes sure the locations are ordered and also removes duplicates when
  // adding both ceiling and floor of a location, because there might be optimal
  // floating-point locations.
  std::set<int> best_locations;

  while (j < n) {
    // Check if window is valid
    if (coords[j] - coords[i] <= 200)
    {
      int parasol_count = j - i + 1;
      float loc = coords[i] + float(coords[j] - coords[i]) / 2;
      int current_max_dist = std::max(
        abs(coords[i] - ceil(loc)),
        abs(coords[j] - ceil(loc))
      );

      if (
        parasol_count > max_parasols
        || (parasol_count == max_parasols && current_max_dist < min_max_dist)
      )
      {
        max_parasols = parasol_count;
        min_max_dist = current_max_dist;
        best_locations.clear();
      }

      if (parasol_count == max_parasols && current_max_dist == min_max_dist)
      {
        best_locations.insert(ceil(loc));
        best_locations.insert(floor(loc));
      }

      // Make window bigger
      j++;
    }
    else
    {
      // Make window smaller if invalid
      i++;
    }
  }

  std::cout << max_parasols << ' ' << min_max_dist << '\n';
  for (int loc : best_locations)
    std::cout << loc << ' ';

  std::cout << std::endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) testcase();
}
