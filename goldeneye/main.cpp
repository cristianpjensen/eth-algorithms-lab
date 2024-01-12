#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <boost/pending/disjoint_sets.hpp>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<size_t, K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;

// Runtime: O(m + n log n)

void testcase()
{
  int n, m; long p; std::cin >> n >> m >> p;

  std::vector<std::pair<K::Point_2, size_t>> points(n);

  for (int i = 0; i < n; i++)
  {
    int x, y; std::cin >> x >> y;
    points[i] = { K::Point_2(x, y), i };
  }

  // O(n log n)
  Triangulation t;
  t.insert(points.begin(), points.end());

  // Extract edges of triangulation, which are implicitly defined using the
  // vertices and faces
  std::vector<std::tuple<long, size_t, size_t>> edges;
  for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e)
  {
    size_t v1 = e->first->vertex((e->second+1)%3)->info();
    size_t v2 = e->first->vertex((e->second+2)%3)->info();
    if (v1 > v2) std::swap(v1, v2);

    long sq_dist = t.segment(e).squared_length();
    edges.push_back({ sq_dist, v1, v2 });
  }

  // Sort according to length
  // O(n log n)
  std::sort(edges.begin(), edges.end());

  std::vector<std::pair<K::Point_2, K::Point_2>> missions(m);
  for (int j = 0; j < m; j++)
  {
    int x0, y0, x1, y1; std::cin >> x0 >> y0 >> x1 >> y1;
    missions[j] = { K::Point_2(x0, y0), K::Point_2(x1, y1) };
  }

  // First figure out all the missions that we can do with `p`. For this, we
  // first make the EMST with only edges less than `p`. Then, if two vertices
  // are in the same set, they are reachable under the `p`-umbrella.
  // O(n)
  boost::disjoint_sets_with_storage<> uf_max_p(n);
  size_t n_components = n;

  for (auto edge : edges)
  {
    size_t v1 = std::get<1>(edge);
    size_t v2 = std::get<2>(edge);
    long sq_dist = std::get<0>(edge);

    size_t set1 = uf_max_p.find_set(v1);
    size_t set2 = uf_max_p.find_set(v2);

    if (sq_dist > p)
      break;

    if (set1 != set2)
    {
      uf_max_p.link(set1, set2);
      if (--n_components == 1) break;
    }
  }

  std::vector<bool> p_possible(m, false);

  // O(m)
  for (int j = 0; j < m; j++)
  {
    auto mission = missions[j];

    auto start_nearest = t.nearest_vertex(mission.first);
    size_t start_index = start_nearest->info();
    long start_sq_dist = CGAL::squared_distance(mission.first, start_nearest->point());

    auto end_nearest = t.nearest_vertex(mission.second);
    size_t end_index = end_nearest->info();
    long end_sq_dist = CGAL::squared_distance(mission.second, end_nearest->point());

    // The mission is possible if the start and end points are under the
    // umbrella, and we can reach from the start nearest point to the end
    // nearest point under the umbrella
    if (
      4 * start_sq_dist <= p
      && 4 * end_sq_dist <= p
      && uf_max_p.find_set(start_index) == uf_max_p.find_set(end_index)
    )
    {
      std::cout << 'y';
      p_possible[j] = true;
    }
    else
      std::cout << 'n';
  }

  std::cout << std::endl;

  // Now, we need to compute the smallest power consumption that allows to
  // execute all missions. We do this by adding all edges until every mission is
  // do-able.
  boost::disjoint_sets_with_storage<> uf_all(n);
  n_components = n;
  int edge_index = 0;
  long p_all = 0;

  // O(n + m)
  for (auto mission : missions)
  {
    auto start_nearest = t.nearest_vertex(mission.first);
    size_t start_index = start_nearest->info();
    long start_sq_dist = CGAL::squared_distance(mission.first, start_nearest->point());

    auto end_nearest = t.nearest_vertex(mission.second);
    size_t end_index = end_nearest->info();
    long end_sq_dist = CGAL::squared_distance(mission.second, end_nearest->point());

    p_all = std::max({
      p_all,
      4 * start_sq_dist,
      4 * end_sq_dist
    });

    // Keep adding edges until the current mission is possible
    while (uf_all.find_set(start_index) != uf_all.find_set(end_index))
    {
      auto edge = edges[edge_index];
      size_t v1 = std::get<1>(edge);
      size_t v2 = std::get<2>(edge);
      long sq_dist = std::get<0>(edge);

      size_t set1 = uf_all.find_set(v1);
      size_t set2 = uf_all.find_set(v2);

      p_all = std::max(p_all, sq_dist);

      if (set1 != set2)
      {
        uf_all.link(set1, set2);
        if (--n_components == 1) break;
      }

      edge_index++;
    }
  }

  std::cout << p_all << std::endl;
  
  // Now, we need to compute the smallest power consumption that can make the
  // same missions possible as `p`
  boost::disjoint_sets_with_storage<> uf_min_p(n);
  n_components = n;
  edge_index = 0;
  long min_p = 0;

  // O(m + n)
  for (int j = 0; j < m; j++)
  {
    // Only need to make the possible missions possible
    if (!p_possible[j])
      continue;

    auto mission = missions[j];

    auto start_nearest = t.nearest_vertex(mission.first);
    size_t start_index = start_nearest->info();
    long start_sq_dist = CGAL::squared_distance(mission.first, start_nearest->point());

    auto end_nearest = t.nearest_vertex(mission.second);
    size_t end_index = end_nearest->info();
    long end_sq_dist = CGAL::squared_distance(mission.second, end_nearest->point());

    min_p = std::max({
      min_p,
      4 * start_sq_dist,
      4 * end_sq_dist
    });

    // Keep adding edges until the current mission is possible
    while (uf_min_p.find_set(start_index) != uf_min_p.find_set(end_index))
    {
      auto edge = edges[edge_index];
      size_t v1 = std::get<1>(edge);
      size_t v2 = std::get<2>(edge);
      long sq_dist = std::get<0>(edge);

      size_t set1 = uf_min_p.find_set(v1);
      size_t set2 = uf_min_p.find_set(v2);

      min_p = std::max(min_p, sq_dist);

      if (set1 != set2)
      {
        uf_min_p.link(set1, set2);
        if (--n_components == 1) break;
      }

      edge_index++;
    }
  }

  std::cout << min_p << std::endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) testcase();
}
