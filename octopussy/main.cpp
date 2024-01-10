#include <bits/stdc++.h>

typedef std::pair<int, int> PII;
typedef std::vector<PII> VPII;
typedef std::vector<int> VI;
typedef std::vector<bool> VB;

// Returns how many descendants were defused, including j
int defuse_descendants(VB& defused, int n, int j)
{
  if (j >= n || defused[j])
    return 0;
  
  defused[j] = true;
  return defuse_descendants(defused, n, 2*j + 1) + defuse_descendants(defused, n, 2*j + 2) + 1;
}

void testcase()
{
  int n; std::cin >> n;

  VPII bombs(n);

  for (int j = 0; j < n; j++)
  {
    int bomb_time; std::cin >> bomb_time;
    bombs[j] = { bomb_time, j };
  }

  // Work toward the bomb that has the least time until it explodes
  std::sort(bombs.begin(), bombs.end());

  VB defused(n, false);

  int current_time = 0;

  for (PII bomb : bombs)
  {
    // We need to defuse the current bomb asap, so we defuse all its
    // descendants and current, which takes `bomb_time` time.
    // A descendant will not explode while working toward the current bomb,
    // because then it would have had to have less time to explode than the
    // current bomb, and it would already have been defused or exploded.
    int bomb_time = bomb.first;
    int j = bomb.second;
    int time_to_defuse = defuse_descendants(defused, n, j);
    
    current_time += time_to_defuse;
    
    if (bomb_time < current_time)
    {
      std::cout << "no" << std::endl;
      return;
    }
  }
  
  std::cout << "yes" << std::endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) testcase();
}
