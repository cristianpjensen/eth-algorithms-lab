#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;

// Time complexity: O(m log n + n log n)

void testcase(int n)
{
  std::vector<K::Point_2> points(n);
  for (int i = 0; i < n; i++)
  {
    int x, y; std::cin >> x >> y;
    points[i] = K::Point_2(x, y);
  }

  // O(n log n)
  // Precompute a triangulation, so we can find the closest point to any other
  // point in O(log n), instead of O(n)
  Triangulation t;
  t.insert(points.begin(), points.end());

  // O(m log n)
  int m; std::cin >> m;
  for (int i = 0; i < m; i++)
  {
    int x, y; std::cin >> x >> y;
    K::Point_2 point(x, y);
    K::Point_2 nearest = t.nearest_vertex(point)->point();
    long dist = CGAL::squared_distance(point, nearest);
    std::cout << dist << '\n';
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
