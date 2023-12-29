#include <bits/stdc++.h>

typedef std::vector<int> VI;
typedef std::vector<VI> VVI;

// Idea: The red and black meeples play parallel minimax games, where Sherlock
// wants to minimize the amount of steps for the red game while Moriarty tries
// to maximize it (vice versa for the black meeple). We can make sure that it
// is a guaranteed winning strategy by letting both players play optimally,
// i.e. the minimizer assumes the maximizer will always play the move that
// maximizes the amount of steps, and vice versa.

void testcase() {
  int n, m, r, b; std::cin >> n >> m >> r >> b;

  VVI transitions(n+1);
  for (int i = 0; i < m; i++) {
    int u, v; std::cin >> u >> v;
    transitions[u].push_back(v);
  }

  // Keep track of a step that minimizes the amount of step and one the
  // maximizes it. Since red and black have the same transitions, they can also
  // use the same minimizers and maximizers.
  VI mini(n+1, INT_MAX);
  VI maxi(n+1, -1);

  mini[n] = 0;
  maxi[n] = 0;

  // All edges i -> j have the property i < j, so we can start from the target
  // and know that the minimum and maximum amount of steps at vertex j is always
  // correct, since it can no longer be changed if we have already considered
  // it.
  for (int i = n-1; i >= 1; i--) {
    for (int neighbor : transitions[i]) {
      // The minimizer assumes the maximizer plays optimally, thus the minimizer
      // wants to choose the step that minimizes the maximum steps in the next
      // neighbor.
      mini[i] = std::min(mini[i], maxi[neighbor] + 1);
      // And vice versa.
      maxi[i] = std::max(maxi[i], mini[neighbor] + 1);
    }
  }

  // Sherlock's minimum amount of steps considering all players play optimally
  // is the minimum amount of steps starting from the red meeple.
  int sherlock = mini[r];
  // The black meeple for Moriarty.
  int moriarty = mini[b];

  if (sherlock < moriarty)
    std::cout << 0 << std::endl;
  else if (moriarty < sherlock)
    std::cout << 1 << std::endl;
  else if (sherlock % 2 == 1)
    std::cout << 0 << std::endl;
  else
    std::cout << 1 << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) testcase();
}
