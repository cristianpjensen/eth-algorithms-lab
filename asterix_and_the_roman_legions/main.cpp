#include <bits/stdc++.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef int IT;
typedef CGAL::Gmpz ET;

typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

double floor_to_double(const CGAL::Quotient<CGAL::Gmpq>& x)
{
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

void testcase()
{
  int xs, ys, n; std::cin >> xs >> ys >> n;
  
  Program lp(CGAL::SMALLER, false, 0, false, 0);
  
  const int X = 0;
  const int Y = 1;
  const int T = 2;

  lp.set_l(T, true, 0);
  
  for (int i = 0; i < n; i++)
  {
    long a, b, c, v; std::cin >> a >> b >> c >> v;
    
    // Signed distance = numerator / denominator
    long numerator = a * xs + b * ys + c;
    long denominator = std::sqrt(a*a + b*b);
    
    // This also makes sure that the position stays on the same side of all the
    // Legion lines
    if (numerator >= 0)
    {
      lp.set_a(X, i, -a);
      lp.set_a(Y, i, -b);
      lp.set_a(T, i, denominator * v);
      lp.set_b(i, c);
    }
    else
    {
      lp.set_a(X, i, a);
      lp.set_a(Y, i, b);
      lp.set_a(T, i, denominator * v);
      lp.set_b(i, -c);
    }
  }
  
  // Maximize preparation time
  lp.set_c(T, -1);

  Solution s = CGAL::solve_linear_program(lp, ET());
  std::cout << floor_to_double(-s.objective_value()) << std::endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) testcase();
}
