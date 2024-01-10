#include <bits/stdc++.h>

typedef std::vector<int> VI;

// Worst-case: O(n * m log m), but, on average, it performs much better.

void testcase()
{
  int n, m; std::cin >> n >> m;
  VI strengths(n);
  for (int i = 0; i < n; i++)
    std::cin >> strengths[i];
  
  // Sort, so we take the strongest people first, since they are more likely to
  // be able to carry anything.
  std::sort(strengths.begin(), strengths.end(), std::greater<int>());
  
  // Use multiset, because we need the values to be sorted, so we can take the
  // lower bound and we need multiple duplicate values.
  std::multiset<int, std::greater<>> weights;
  for (int i = 0; i < m; i++)
  {
    int w; std::cin >> w;
    weights.insert(w);
  }

  int iters = 0;
  
  // O(m)
  while (!weights.empty())
  {
    iters++;
    bool is_box_taken = false;

    // For every person, greedily take the maximum weight it can carry, starting
    // with the strongest people.
    // O(n), but actually it depends very much on the weights.
    for (int i = 0; i < n; i++)
    {
      int strength = strengths[i];
      // O(log m)
      auto take_it = weights.lower_bound(strength);
      
      if (take_it != weights.end())
      {
        weights.erase(take_it);
        is_box_taken = true;
      }
      else
      {
        // It is sorted, so if the current person cannot take anything, all
        // later people will not be able to take anything.
        break;
      }
    }
    
    // If nothing was taken for an iteration, it is impossible.
    if (!is_box_taken)
    {
      std::cout << "impossible" << std::endl;
      return;
    }
  }
  
  int time = 2 + (iters - 1) * 3;
  std::cout << time << std::endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) testcase();
}
