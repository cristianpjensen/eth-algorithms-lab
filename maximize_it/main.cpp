#include <bits/stdc++.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef int IT;
typedef CGAL::Gmpz ET;

typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

void solve_problem_a()
{
  int a, b; std::cin >> a >> b;
  Program lp (CGAL::SMALLER, true, 0, false, 0); 

  const int X = 0; 
  const int Y = 1;

  lp.set_a(X, 0,  1); lp.set_a(Y, 0, 1); lp.set_b(0, 4);
  lp.set_a(X, 1, 4); lp.set_a(Y, 1, 2); lp.set_b(1, a*b);
  lp.set_a(X, 2, -1); lp.set_a(Y, 2, 1); lp.set_b(2, 1);

  lp.set_c(X, a);
  lp.set_c(Y, -b);

  Solution s = CGAL::solve_linear_program(lp, ET());

  if (s.is_unbounded())
    std::cout << "unbounded" << std::endl;
  else if (s.is_infeasible())
    std::cout << "no" << std::endl;
  else
  {
    ET value = -(s.objective_value_numerator() / s.objective_value_denominator());
    std::cout << floor(value.to_double()) << std::endl;
  }
}

void solve_problem_b()
{
  int a, b; std::cin >> a >> b;
  Program lp (CGAL::SMALLER, false, 0, true, 0); 

  const int X = 0; 
  const int Y = 1;
  const int Z = 2;

  lp.set_a(X, 0, -1); lp.set_a(Y, 0, -1); lp.set_b(0, 4);
  lp.set_a(X, 1, -4); lp.set_a(Y, 1, -2); lp.set_a(Z, 1, -1); lp.set_b(1, a*b);
  lp.set_a(X, 2, 1); lp.set_a(Y, 2, -1); lp.set_b(2, 1);

  lp.set_c(X, a);
  lp.set_c(Y, b);
  lp.set_c(Z, 1);

  Solution s = CGAL::solve_linear_program(lp, ET());

  if (s.is_unbounded())
    std::cout << "unbounded" << std::endl;
  else if (s.is_infeasible())
    std::cout << "no" << std::endl;
  else
  {
    ET value = s.objective_value_numerator() / s.objective_value_denominator();
    std::cout << ceil(value.to_double()) << std::endl;
  }
}

int main()
{
  int p; std::cin >> p;
  while (p != 0)
  {
    if (p == 1)
      solve_problem_a();
    else
      solve_problem_b();

    std::cin >> p;
  }
}
