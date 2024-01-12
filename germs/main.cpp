#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;

void testcase(int n)
{
  int left, bottom, right, top; std::cin >> left >> bottom >> right >> top;

  std::vector<K::Point_2> points(n);
  for (int i = 0; i < n; i++)
  {
    int x, y; std::cin >> x >> y;
    points[i] = K::Point_2(x, y);
  }

  Triangulation t;
  t.insert(points.begin(), points.end());

  std::vector<long> min_dist(n, LONG_MAX);
  int index = 0;

  // For every bacterium, compute the distance to its closest point, which is
  // used to eventually compute the time of death. We do not care about when
  // each individual bacterium dies, so the order does not matter.
  for (auto v = t.finite_vertices_begin(); v != t.finite_vertices_end(); ++v)
  {
    K::Point_2 point = v->point();

    // Distance to edge
    long edge_dist = std::min({
      point.y() - bottom,
      top - point.y(),
      point.x() - left,
      right - point.x()
    });
    long sq_edge_dist = CGAL::square(2 * edge_dist);
    min_dist[index] = sq_edge_dist;

    // Distance to closest vertices
    Triangulation::Edge_circulator c = t.incident_edges(v);
    if (c != 0)
    {
      do
      {
        if (!t.is_infinite(c))
        {
          long dist = t.segment(c).squared_length();
          min_dist[index] = std::min(min_dist[index], dist);
        }
      }
      while (++c != t.incident_edges(v));
    }

    index++;
  }

  std::sort(min_dist.begin(), min_dist.end());

  // Compute minimum, median, and maximum
  double min_distance = min_dist[0];
  double mid_distance = min_dist[n / 2];
  double max_distance = min_dist[n - 1];
  long t_min = ceil(sqrt((sqrt(min_distance) - 1) / 2));
  long t_mid = ceil(sqrt((sqrt(mid_distance) - 1) / 2));
  long t_max = ceil(sqrt((sqrt(max_distance) - 1) / 2));

  std::cout << t_min << ' ' << t_mid << ' ' << t_max << std::endl;
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
