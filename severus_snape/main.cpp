#include <bits/stdc++.h>

typedef std::pair<long, long> PLL;
typedef std::vector<PLL> VPLL;
typedef std::vector<long> VL;
typedef std::vector<VL> VVL;

void testcase()
{
  long n, m; std::cin >> n >> m;
  long a, b; std::cin >> a >> b;
  long P, H, W; std::cin >> P >> H >> W;

  VPLL potions_a(n);
  for (int i = 0; i < n; i++)
  {
    long p, h; std::cin >> p >> h;
    potions_a[i] = { p, h };
  }

  // Dynamic programming.
  // State space:
  //  - Amount of A potions picked;
  //  - Minimum amount of happiness.
  // Value: maximum amount of power that can be attained.
  VVL max_power(n+1, VL(H+1, -1));
  max_power[0][0] = 0;

  for (int i = 1; i <= n; i++)
  {
    PLL potion = potions_a[i-1];

    // Start from the top, so we do not use the same potion twice. If we go from
    // 1 to i, we are able to use the potion twice, since we used it in 1, and
    // we use those results for 2, where we still consider using the current
    // potion. If we start from the top, this is not a problem.
    for (int j = i; j >= 1; j--)
    {
      for (int h = 0; h <= H; h++)
      {
        int prev_h = std::max((long) 0, h - potion.second);

        // Check if it was even possible to get to (j-1, prev_h), because
        // otherwise we should not consider it.
        if (max_power[j-1][prev_h] == -1)
          continue;

        // Recurrence relationship
        max_power[j][h] = std::max(
          max_power[j][h],
          max_power[j-1][prev_h] + potion.first
        );
      }
    }
  }

  VL potions_b(m);
  for (int j = 0; j < m; j++)
    std::cin >> potions_b[j];

  // Sort potions B, because we can pick these greedily, since they all decrease
  // the same amount of power, but increase different amounts of wit. So, we
  // first want to use the potions that give the maximum amount of wit.
  std::sort(potions_b.begin(), potions_b.end(), std::greater<int>());

  int min_potions = INT_MAX;

  for (int j = 0; j <= n; j++)
  {
    // Check if it is possible to get `H` happiness with `j` A potions.
    // Otherwise, we will not consider it.
    if (max_power[j][H] == -1)
      continue;

    // Check if it is possible to get `P` power with `j` A potions. Otherwise,
    // we will not consider it.
    if (max_power[j][H] < P)
      continue;

    // How many B potions we are allowed to pick such that we still have more
    // than `P` power.
    long available_b_potions = b == 0 ? m : (max_power[j][H] - P) / b;

    // How much wit we need, given the amount of chosen A potions and `W`.
    long wit_needed = W + j * a;

    long total_wit = 0;
    for (int k = 0; k < std::min(available_b_potions, m); k++)
    {
      total_wit += potions_b[k];

      if (total_wit >= wit_needed)
      {
        min_potions = std::min(min_potions, j + (k + 1));
        break;
      }
    }
  }

  if (min_potions == INT_MAX)
    std::cout << -1 << std::endl;
  else
    std::cout << min_potions << std::endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) testcase();
}
