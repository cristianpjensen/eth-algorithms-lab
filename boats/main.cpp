#include <bits/stdc++.h>

typedef std::pair<int, int> PII;
typedef std::vector<PII> VPII;

void testcase()
{
  int n; std::cin >> n;

  VPII boats(n);

  for (int i = 0; i < n; i++)
  {
    int l, p; std::cin >> l >> p;
    boats[i] = { p, l };
  }

  std::sort(boats.begin(), boats.end());
  
  int prev_left = boats[0].first - boats[0].second;
  int left = boats[0].first;
  int num_boats = 1;
  
  for (int i = 1; i < n; i++)
  {
    int pos = boats[i].first;
    int length = boats[i].second;

    if (pos < left)
    {
      // Unable to place boat, because of the previous one.
      // Check whether we should replace the previous boat by the current one.
      int new_left = std::max(pos, prev_left + length);
      left = std::min(left, new_left);
    }
    else
    {
      // We can place the boat, so we place it as close to the left edge as
      // possible.
      int next_left = std::max(pos, left + length);
      prev_left = left;
      left = next_left;
      
      num_boats++;
    }
  }

  std::cout << num_boats << std::endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) testcase();
}
