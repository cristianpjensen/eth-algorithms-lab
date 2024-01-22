#include <bits/stdc++.h>

typedef std::vector<int> VI;
typedef std::vector<VI> VVI;
typedef std::vector<VVI> VVVI;
typedef std::vector<VVVI> VVVVI;

// Compute unique fighters, where 0 is "no fighter", so we always add it and
// -1.
int unique_fighters(int f1, int f2, int f3)
{
  return std::set<int>({ 0, f1, f2, f3 }).size() - 1;
}

// The state consists of the difference in amount of fighters to each entrance,
// and the two histories.
struct State
{
  int diff;
  std::tuple<int, int> north_hist;
  std::tuple<int, int> south_hist;

  State(int diff_, std::tuple<int, int> north_hist_, std::tuple<int, int> south_hist_)
  {
    diff = diff_;
    north_hist = north_hist_;
    south_hist = south_hist_;
  }
};

// Get a key to use in the dynamic programming table, based on the state, which
// is previously seen fighters and the difference in amount of fighters sent to
// the two entrances. We do not need to know the actual values, only the
// difference.
std::tuple<int, int, int> get_key(State& state)
{
  int north1 = std::get<0>(state.north_hist);
  int north2 = std::get<1>(state.north_hist);
  int south1 = std::get<0>(state.south_hist);
  int south2 = std::get<1>(state.south_hist);

  return { north1 * 5 + north2, south1 * 5 + south2, state.diff + 12 };
}

// Compute excitement as specified: 1000 * amount of unique fighters, minus 2^{|p-1|}.
int excitement(int current, std::tuple<int, int>& hist, int diff)
{
  return 1000 * unique_fighters(current, std::get<0>(hist), std::get<1>(hist)) - pow(2, abs(diff));
}

// Recurrence relationship.
int max_score(
  VVVVI& dp,
  VI& queue,
  int m,
  int n,
  int i,
  State state
)
{
  // The difference may never be greater than 12, because 2^{12} > 4000, which
  // is the maximum score possible from excitement. This would cause the
  // excitement to be negative.
  if (abs(state.diff) >= 12)
    return INT_MIN;
  
  // There are no more fighters.
  if (i >= n)
    return 0;

  // Memoization.
  std::tuple<int, int, int> key = get_key(state);
  if (dp[i][std::get<0>(key)][std::get<1>(key)][std::get<2>(key)] != -1)
    return dp[i][std::get<0>(key)][std::get<1>(key)][std::get<2>(key)];

  int current = queue[i];

  int best_score = INT_MIN;

  // Compute the best score between sending  the fighter north or south
  int north_score = excitement(current, state.north_hist, state.diff + 1);
  int south_score = excitement(current, state.south_hist, state.diff - 1);

  // Excitement may never be negative.
  if (north_score >= 0)
  {
    int last = 0;
    if (m == 3)
      last = std::get<0>(state.north_hist);

    best_score = north_score + max_score(dp, queue, m, n, i+1, State(state.diff + 1, { current, last }, state.south_hist));
  }

  if (south_score >= 0)
  {
    int last = 0;
    if (m == 3)
      last = std::get<0>(state.south_hist);

    best_score = std::max(
      best_score,
      south_score + max_score(dp, queue, m, n, i+1, State(state.diff - 1, state.north_hist, { current, last }))
    );
  }
  
  dp[i][std::get<0>(key)][std::get<1>(key)][std::get<2>(key)] = best_score;
  return best_score;
}

void testcase()
{
  int n, k, m; std::cin >> n >> k >> m;
  
  VI queue(n);
  for (int i = 0; i < n; i++)
  {
    int x; std::cin >> x;
    queue[i] = x + 1;
  }
  
  VVVVI dp(n, VVVI(25, VVI(25, VI(25, -1))));

  State init_state(0, { 0, 0 }, { 0, 0 });
  std::cout << max_score(dp, queue, m, n, 0, init_state) << std::endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) testcase();
}
