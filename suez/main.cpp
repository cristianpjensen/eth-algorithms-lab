#include <bits/stdc++.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpq.h>

typedef CGAL::Gmpq IT;
typedef CGAL::Gmpq ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

double floor_to_double(const CGAL::Quotient<ET> &x)
{
    double a = std::floor(CGAL::to_double(x));
    while (a > x)
        a -= 1;
    while (a + 1 <= x)
        a += 1;
    return a;
}

struct Point
{
  int x;
  int y;
};

// Linear program with n=30, m=475.
// min(n,m) = 30 < 200, so it is solvable in O(max(n,m)=475).
// Furthermore, the algorithm runs in O(n*m + n^2)

void testcase()
{
  int n, m, h, w; std::cin >> n >> m >> h >> w;

  std::vector<Point> points(n);
  for (int i = 0; i < n; i++)
  {
    int x, y; std::cin >> x >> y;
    points[i] = { x, y };
  }

  std::vector<Point> fixed_points(m);
  for (int i = 0; i < m; i++)
  {
    int x, y; std::cin >> x >> y;
    fixed_points[i] = { x, y }; 
  }

  Program lp (CGAL::SMALLER, true, 1, false, 0);
  int constraint_count = 0;

  // At most, 435 constraints, which is fine.
  for (int i = 0; i < n; i++)
  {
    Point point1 = points[i];
    for (int j = i+1; j < n; j++)
    {
      Point point2 = points[j];

      int x_dist = abs(point1.x - point2.x);
      int y_dist = abs(point1.y - point2.y);
      ET b = std::max(ET(2 * x_dist, w), ET(2 * y_dist, h));
      
      lp.set_a(i, constraint_count, 1);
      lp.set_a(j, constraint_count, 1);
      lp.set_b(constraint_count, b);
      constraint_count++;
    }
  }

  // Only the closest fixed point matters for the new point. Thus, we only add
  // 30 constraints. Could technically be done in O(n log m + m log m) by using
  // Delaunay triangulation, but that is overkill for this problem.
  for (int i = 0; i < n; i++)
  {
    Point point = points[i];
    ET min_b = ET(DBL_MAX);

    for (int j = 0; j < m; j++)
    {
      Point fixed_point = fixed_points[j];

      // We only need to consider the fixed point with the smallest
      // max(x distance / w, y distance / h).
      int x_dist = abs(point.x - fixed_point.x);
      int y_dist = abs(point.y - fixed_point.y);
      
      // Check on which side, they will first hit. This is the maximum value.
      IT current_b = std::max(IT(2 * x_dist - w, w), IT(2 * y_dist - h, h));
      min_b = std::min(min_b, current_b);
    }

    // Upper bound the size of the picture by how close it is to its closest
    // fixed point.
    lp.set_u(i, true, min_b);
  }

  // Maximize sum of perimeters
  for (int i = 0; i < n; i++)
    lp.set_c(i, -2 * (h + w));

  Solution s = CGAL::solve_linear_program(lp, ET());
  
  // The floor of the minimum is the ceiling of the maximum.
  std::cout << long(-floor_to_double(s.objective_value())) << std::endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) testcase();
}
