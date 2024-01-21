#include <bits/stdc++.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

typedef std::vector<int> VI;
typedef std::vector<VI> VVI;

int floor_to_double(const CGAL::Quotient<ET> &x)
{
  int a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

void testcase()
{
  int n, m, c; std::cin >> n >> m >> c;

  Program lp(CGAL::SMALLER, true, 0, false, 0); 

  int num_constraints = 0;

  VI percentages(n);
  std::vector<K::Point_2> warehouse_points(n);

  for (int i = 0; i < n; i++)
  {
    int x, y, s; std::cin >> x >> y >> s >> percentages[i];
    warehouse_points[i] = K::Point_2(x, y);

    // Upper bound the amount out of the warehouses by their supply
    for (int j = 0; j < m; j++)
      lp.set_a(i*m + j, num_constraints, 1);

    lp.set_b(num_constraints, s);

    num_constraints++;
  }

  std::vector<K::Point_2> stadium_points(m);

  for (int j = 0; j < m; j++)
  {
    int x, y, d, u; std::cin >> x >> y >> d >> u;
    stadium_points[j] = K::Point_2(x, y);

    // Let the total amount of beer to the stadia be exactly their demand and
    // the pure alcohol be upper bounded by `u`
    for (int i = 0; i < n; i++)
    {
      lp.set_a(i*m + j, num_constraints, 1);
      lp.set_a(i*m + j, num_constraints + 1, -1);
      lp.set_a(i*m + j, num_constraints + 2, percentages[i]);
    }

    lp.set_b(num_constraints, d);
    lp.set_b(num_constraints + 1, -d);
    lp.set_b(num_constraints + 2, 100 * u);

    num_constraints += 3;
  }

  VVI revenue(n, VI(m));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      std::cin >> revenue[i][j];

  VVI warehouse_in_circle(n);
  VVI stadium_in_circle(m);

  for (int k = 0; k < c; k++)
  {
    int x, y, r; std::cin >> x >> y >> r;
    K::Point_2 point(x, y);

    for (int i = 0; i < n; i++)
      if (CGAL::squared_distance(point, warehouse_points[i]) <= r * r)
        warehouse_in_circle[i].push_back(k);

    for (int j = 0; j < m; j++)
      if (CGAL::squared_distance(point, stadium_points[j]) <= r * r)
        stadium_in_circle[j].push_back(k);
  }

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      std::set<int> warehouse_circles;
      std::set<int> stadium_circles;

      for (int k : warehouse_in_circle[i])
        warehouse_circles.insert(k);

      for (int k : stadium_in_circle[j])
        stadium_circles.insert(k);

      int union_minus_intersection_size = 0;
      for (int k : warehouse_circles)
        if (stadium_circles.find(k) == stadium_circles.end())
          union_minus_intersection_size++;

      for (int k : stadium_circles)
        if (warehouse_circles.find(k) == warehouse_circles.end())
          union_minus_intersection_size++;
      
      // If they are in the same circle, they will not go over any contour line.
      // If they are in different circles, they have to be crossed.
      lp.set_c(i*m + j, -(100 * revenue[i][j] - union_minus_intersection_size));
    }
  }

  Solution s = CGAL::solve_linear_program(lp, ET());
  
  if (s.is_infeasible())
    std::cout << "RIOT!" << std::endl;
  else
    std::cout << floor_to_double(-s.objective_value() / 100) << std::endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) testcase();
}
