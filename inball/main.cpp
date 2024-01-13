#include <bits/stdc++.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

// The polyhedron is d-dimensional with n faces. It is defined by n hyperplanes.
// We need to find the largest d-dimensional ball that fits within this
// polyhedron. I.e. we need to find a ball at a center that is within the
// polyhedron and the radius of the ball may not exceed the distance to any
// hyperplane that is part of the polyhedron. Thus, we want to maximize the
// radius under these constraints.

// We will define the following variables in the LP:
//  - 0 for radius.
//  - 1..d additional variables for the center.
//
// We must satisfy the following constraints:
//  - Center is within polyhedron.
//  - Distances from center to hyperplanes are greater than radius.
// We can put these together into `n` LP constraints
// 
// Thus, we have d (1 <= d <= 10) variables and n (1 <= n <= 10^3)
// constraints.

void testcase(int n)
{
  int d; std::cin >> d;

  Program lp (CGAL::SMALLER, false, 0, false, 0);

  // Radius has to be positive
  const int R = 0;
  lp.set_l(R, true, 0);

  for (int i = 0; i < n; i++)
  {
    long moving_square = 0;
    for (int j = 1; j <= d; j++)
    {
      long a; std::cin >> a;
      moving_square += a * a;
      
      // a^T x
      lp.set_a(j, i, a);
    }

    long norm = sqrt(moving_square);
    int b; std::cin >> b;

    // ||a|| R
    lp.set_a(R, i, norm);
    // <= b
    lp.set_b(i, b);
  }

  // Max R = Min -R
  lp.set_c(R, -1);

  Solution s = CGAL::solve_linear_program(lp, ET());

  if (s.is_infeasible())
    std::cout << "none" << std::endl;
  else if (s.is_unbounded())
    std::cout << "inf" << std::endl;
  else
  {
    ET value = -s.objective_value_numerator() / s.objective_value_denominator();
    std::cout << long(value.to_double()) << std::endl;
  }
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  int n; std::cin >> n;
  while (n != 0)
  {
    testcase(n);
    std::cin >> n;
  }
}
