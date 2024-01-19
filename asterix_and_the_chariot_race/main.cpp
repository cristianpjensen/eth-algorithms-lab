#include <bits/stdc++.h>

typedef std::vector<int> VI;
typedef std::vector<VI> VVI;

struct State {
  int min_picked;
  int min_covered;
  int min_children_covered;

  State(int a, int b, int c)
  {
    min_picked = a;
    min_covered = b;
    min_children_covered = c;
  }
};

State dfs(VVI& adjacency_lists, VI& costs, int v)
{
  if (adjacency_lists[v].empty())
  {
    return State(
      costs[v],
      costs[v],
      0
    );
  }

  int covered_sum = 0;
  int children_covered_sum = 0;
  int min_diff = INT_MAX;

  for (int child : adjacency_lists[v])
  {
    State child_state = dfs(adjacency_lists, costs, child);
    covered_sum += child_state.min_covered;
    children_covered_sum += child_state.min_children_covered;
    min_diff = std::min(min_diff, child_state.min_picked - child_state.min_covered);
  }

  int min_picked = costs[v] + children_covered_sum;
  int min_covered = std::min(
    min_picked,
    covered_sum + min_diff
  );
  int min_children_covered = std::min(
    min_covered,
    covered_sum
  );

  return State(
    min_picked,
    min_covered,
    min_children_covered
  );
}

void testcase()
{
  int n; std::cin >> n;

  VVI adjacency_lists(n);
  for (int i = 0; i < n-1; i++)
  {
    int x, y; std::cin >> x >> y;
    adjacency_lists[x].push_back(y);
  }

  VI costs(n);
  for (int i = 0; i < n; i++)
  {
    int c; std::cin >> c;
    costs[i] = c;
  }

  State final_state = dfs(adjacency_lists, costs, 0);

  std::cout << final_state.min_covered << std::endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) testcase();
}
