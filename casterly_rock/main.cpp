#include <bits/stdc++.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpq.h>

typedef long IT;
typedef CGAL::Gmpz ET;

typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

long quotient_ceil(const CGAL::Quotient<ET>& x)
{
 double a = ceil(CGAL::to_double(x));
 while (a+1 >= x) a -= 1;
 while (a < x) a += 1;
 return a;
}

void testcase()
{
  int n, m; long s; std::cin >> n >> m >> s;

  Program lp(CGAL::SMALLER, false, 0, false, 0);
  
  int num_constraints = 0;

  // Sewage line
  const int a_sewer = 0;
  const int b_sewer = 1;
  const int c_sewer = 2;

  // a = 1, so the sewage line is never horizontal
  lp.set_l(a_sewer, true, 1);
  lp.set_u(a_sewer, true, 1);

  long noble_sum_x = 0;
  long noble_sum_y = 0;
  
  std::vector<std::pair<long, long>> points(n+m);

  for (int i = 0; i < n; i++)
  {
    long x, y; std::cin >> x >> y;
    points[i] = { x, y };

    noble_sum_x += x;
    noble_sum_y += y;

    // Nobles on the left side: a*x + b*y + c <= 0
    lp.set_a(a_sewer, num_constraints, x);
    lp.set_a(b_sewer, num_constraints, y);
    lp.set_a(c_sewer, num_constraints, 1);
    lp.set_b(num_constraints, 0);

    num_constraints++;
  }

  long common_sum_x = 0;
  long common_sum_y = 0;

  for (int j = 0; j < m; j++)
  {
    long x, y; std::cin >> x >> y;
    points[n+j] = { x, y };

    common_sum_x += x;
    common_sum_y += y;

    // Commoners on the right side: a*x + b*y + c >= 0
    lp.set_a(a_sewer, num_constraints, -x);
    lp.set_a(b_sewer, num_constraints, -y);
    lp.set_a(c_sewer, num_constraints, -1);
    lp.set_b(num_constraints, 0);

    num_constraints++;
  }

  Solution sol = CGAL::solve_linear_program(lp, ET());

  // Cersei's constraint is not possible
  if (sol.is_infeasible())
  {
    std::cout << "Yuck!" << std::endl;
    return;
  }

  // If s == -1, infinite money, i.e., Lord Tywin's constraint doesn't matter
  if (s != -1)
  {
    lp.set_a(b_sewer, num_constraints, common_sum_y - noble_sum_y);
    lp.set_a(c_sewer, num_constraints, m - n);
    lp.set_b(num_constraints, s - (common_sum_x - noble_sum_x));

    num_constraints++;

    Solution sol = CGAL::solve_linear_program(lp, ET());

    // Lord Tywin's constraint is not possible
    if (sol.is_infeasible())
    {
      std::cout << "Bankrupt!" << std::endl;
      return;
    }
  }

  // Fresh water line
  const int a_water = 3;
  const int b_water = 4;
  const int c_water = 5;

  // b = 1, so the water line is never vertical
  lp.set_l(b_water, true, 1);
  lp.set_u(b_water, true, 1);

  // `d` represents the maximum distance to the fresh water canal, which we want
  // to minimize
  const int d = 6;
  lp.set_l(d, true, 0);

  // Constrain `d` to be greater than all distances to the fresh water canal (if
  // we then minimize it, it becomes the maximum). It has to be greater than the
  // absolute value, but we do not know on which side it is, so it has to be
  // greater than both.
  for (auto point : points)
  {
    long x = point.first;
    long y = point.second;
    
    lp.set_a(a_water, num_constraints, x);
    lp.set_a(c_water, num_constraints, 1);
    lp.set_a(d, num_constraints, -1);
    lp.set_b(num_constraints, -y);

    num_constraints++;

    lp.set_a(a_water, num_constraints, -x);
    lp.set_a(c_water, num_constraints, -1);
    lp.set_a(d, num_constraints, -1);
    lp.set_b(num_constraints, y);

    num_constraints++;
  }
  
  // Right angle constraint, we need b_sewer = -a_water
  lp.set_a(b_sewer, num_constraints, 1);
  lp.set_a(a_water, num_constraints, 1);
  lp.set_b(num_constraints, 0);

  num_constraints++;

  lp.set_a(b_sewer, num_constraints, -1);
  lp.set_a(a_water, num_constraints, -1);
  lp.set_b(num_constraints, 0);
  
  num_constraints++;

  // Minimize `d`
  lp.set_c(d, 1);

  Solution final_sol = CGAL::solve_linear_program(lp, ET());
  std::cout << quotient_ceil(final_sol.objective_value()) << std::endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) testcase();
}
