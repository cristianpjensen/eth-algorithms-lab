#include <bits/stdc++.h>

typedef std::pair<long, long> PLL;
typedef std::vector<PLL> VPLL;
typedef std::vector<int> VI;

bool contains_subset(
  VPLL& moves,
  int potion,
  long D,
  long T,
  int n
)
{
  int l1_size = n / 2;
  int l2_size = n - l1_size;
  
  // Construct L1.
  VPLL l1(1 << l1_size);
  for (int s = 0; s < (1 << l1_size); s++)
  {
    long total_distance = 0;
    long total_time = 0;
    for (int j = 0; j < l1_size; j++)
    {
      if (s & (1 << j))
      {
        total_distance += moves[j].first + potion;
        total_time += moves[j].second;
      }
    }
    
    l1[s] = { total_distance, total_time };
  }

  // Construct L2.
  VPLL l2(1 << l2_size);
  for (int s = 0; s < (1 << l2_size); s++)
  {
    int s_ = s << l1_size;

    long total_distance = 0;
    long total_time = 0;
    for (int j = l2_size; j < n; j++)
    {
      if (s_ & (1 << j))
      {
        total_distance += moves[j].first + potion;
        total_time += moves[j].second;
      }
    }

    l2[s] = { total_distance, total_time };
  }

  // Sort by total time in ascending order.
  std::sort(
    l2.begin(),
    l2.end(),
    [](const PLL& m1, const PLL& m2) -> bool { return m1.second < m2.second; }
  );

  // If we are able to do distance d in t' < t seconds, we are also able to do
  // distance d in t seconds.
  for (int i = 1; i < (1 << l2_size); i++)
    l2[i].first = std::max(l2[i].first, l2[i-1].first);

  // For every (d1, t1) find its complement (d2, t2) such that d1+d2 >= D and
  // t1+t2 < T.
  for (int i = 0; i < (1 << l1_size); i++)
  {
    long d1 = l1[i].first;
    long t1 = l1[i].second;
    
    // Binary search to find d2 and t2
    int left = 0;
    int right = (1 << l2_size) - 1;

    while (left <= right)
    {
      int mid = (left + right) / 2;
      long d2 = l2[mid].first;
      long t2 = l2[mid].second;
      
      long total_distance = d1 + d2;
      long total_time = t1 + t2;

      // There is a match!
      if (total_distance >= D && total_time < T)
        return true;

      // If we do not go far enough, we need d2 to be higher, so we move to the
      // right. Otherwise, it must be taking too long, so we go to the left.
      if (total_distance < D)
        left = mid + 1;
      else
        right = mid - 1;
    }
  }

  return false;
}

void testcase()
{
  int n, m; std::cin >> n >> m;
  long D, T; std::cin >> D >> T;
  
  VPLL moves(n);
  for (int i = 0; i < n; i++)
  {
    long d, t; std::cin >> d >> t;
    moves[i] = std::make_pair(d, t);
  }
  
  VI potions(m);
  for (int i = 0; i < m; i++)
    std::cin >> potions[i];
  
  // Binary search over all potions, since they are ordered and if p' > p and p
  // causes there to be a subset, then p' ditto.
  // O(log m * n * 2^(n/2))
  int left = 0;
  int right = m;
  while (left <= right)
  {
    int mid = (left + right) / 2;
    int potion = 0;
    if (m > 0)
      potion = potions[mid - 1];
    
    // O(n * 2^(n/2))
    if (contains_subset(moves, potion, D, T, n))
      right = mid - 1;
    else
      left = mid + 1;
  }
  
  if (left > m)
    std::cout << "Panoramix captured" << std::endl;
  else
    std::cout << left << std::endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) testcase();
}
