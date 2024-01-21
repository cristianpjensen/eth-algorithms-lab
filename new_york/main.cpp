#include <bits/stdc++.h>

typedef std::vector<bool> VB;
typedef std::vector<int> VI;
typedef std::vector<VI> VVI;

void dfs(
  VVI& adj,
  VI& temps,
  int m,
  int k,
  VB& safe,
  std::deque<int>& trips,
  std::multiset<int>& trip_temps,
  int v
)
{
  int head = trips.front();

  // Check if valid trip and whether or not it is safe
  if (
    (int) trips.size() == m
    && (*trip_temps.rbegin()) - (*trip_temps.begin()) <= k
  )
    safe[head] = true;

  // Remove the head such that the trip length stays `m`
  bool remove_head = (int) trips.size() >= m;

  if (remove_head)
  {
    trips.pop_front();
    trip_temps.erase(trip_temps.find(temps[head]));
  }

  // Add child and then remove it afterward to get back to the original state,
  // such that we can go to the next child
  for (int child : adj[v])
  {
    trips.push_back(child);
    trip_temps.insert(temps[child]);

    dfs(adj, temps, m, k, safe, trips, trip_temps, child);

    trips.pop_back();
    trip_temps.erase(trip_temps.find(temps[child]));
  }

  // Put the head back to get back to the original state
  if (remove_head)
  {
    trips.push_front(head);
    trip_temps.insert(temps[head]);
  }
}

void testcase()
{
  int n, m, k; std::cin >> n >> m >> k;

  VI temps(n);
  for (int i = 0; i < n; i++)
    std::cin >> temps[i];

  VVI adj(n);
  for (int i = 0; i < n-1; i++)
  {
    int u, v; std::cin >> u >> v;
    adj[u].push_back(v);
  }

  std::deque<int> trips = { 0 };
  std::multiset<int> trip_temps = { temps[0] };

  VB safe(n, false);
  dfs(adj, temps, m, k, safe, trips, trip_temps, 0);

  bool abort = true;
  for (int i = 0; i < n; i++)
  {
    if (safe[i])
    {
      abort = false;
      std::cout << i << ' ';
    }
  }

  if (abort)
    std::cout << "Abort mission";

  std::cout << std::endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) testcase();
}
