#include <bits/stdc++.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

typedef std::vector<int> VI;

int floor_to_double(const CGAL::Quotient<ET> &x)
{
  int a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

void testcase(int n, int m)
{
  Program lp (CGAL::SMALLER, true, 0, false, 0);

  for (int i = 0; i < n; i++)
  {
    int min, max; std::cin >> min >> max;
    lp.set_b(i*2, max);
    lp.set_b(i*2+1, -min);
  }

  for (int j = 0; j < m; j++)
  {
    int price; std::cin >> price;
    lp.set_c(j, price);

    for (int i = 0; i < n; i++)
    {
      int amount; std::cin >> amount;
      lp.set_a(j, i*2, amount);
      lp.set_a(j, i*2+1, -amount);
    }
  }

  Solution s = CGAL::solve_linear_program(lp, ET());

  if (s.is_infeasible())
    std::cout << "No such diet." << std::endl;
  else
    std::cout << floor_to_double(s.objective_value()) << std::endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  int n, m; std::cin >> n >> m;
  while (n != 0 && m != 0)
  {
    testcase(n, m);
    std::cin >> n >> m;
  }
}
