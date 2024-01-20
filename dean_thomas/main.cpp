#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<size_t, K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;

typedef std::vector<std::vector<std::pair<size_t, K::FT>>> adjacency;

void testcase()
{
  int n, m; K::FT d; std::cin >> n >> m >> d;

  std::vector<K::Point_2> points(n);
  for (int i = 0; i < n; i++)
  {
    long x, y; std::cin >> x >> y;
    points[i] = K::Point_2(x, y);
  }

  Triangulation t;
  t.insert(points.begin(), points.end());

  auto f = t.incident_faces(t.infinite_vertex());
  do {
    f->info() = 0;
  } while (++f != t.incident_faces(t.infinite_vertex()));

  size_t num_faces = 1;
  for (auto f = t.finite_faces_begin(); f != t.finite_faces_end(); ++f)
    f->info() = num_faces++;

  // Fill in the adjacency lists of the triangulation faces
  adjacency adj(num_faces);
  for (auto f = t.finite_faces_begin(); f != t.finite_faces_end(); ++f)
  {
    size_t index = f->info();

    for (int i = 0; i < 3; i++)
    {
      size_t n_index = f->neighbor(i)->info();
      K::FT length = t.segment(f, i).squared_length();

      // We never want to be able to go outside the convex hull from inside, so
      // we do not add edges to the outside
      if (n_index == 0)
        adj[n_index].push_back({ index, length });
      else
        adj[index].push_back({ n_index, length });
    }
  }

  std::vector<K::FT> bottlenecks(num_faces, -1);
  std::priority_queue<std::pair<K::FT, size_t>> Q;
  Q.push({ K::FT(LONG_MAX) * K::FT(LONG_MAX), 0 });

  while (!Q.empty())
  {
    auto p = Q.top(); Q.pop();
    K::FT bottleneck = p.first;
    size_t index = p.second;

    // We are using a priority queue, so it won't get any better from now on
    if (bottlenecks[index] != -1)
      continue;

    bottlenecks[index] = bottleneck;

    for (auto neighbor : adj[index])
      Q.push({ std::min(bottleneck, neighbor.second), neighbor.first });
  }

  for (int j = 0; j < m; j++)
  {
    long x, y; K::FT s; std::cin >> x >> y >> s;
    K::Point_2 point(x, y);

    K::FT min_dist_day = (d + s) * (d + s);
    K::FT min_dist_night = (2*d + 2*s) * (2*d + 2*s);
    K::FT dist_to_closest = CGAL::squared_distance(point, t.nearest_vertex(point)->point());

    // We do not need to move
    if (dist_to_closest >= min_dist_night)
    {
      std::cout << 'y';
      continue;
    }

    // We are initially too close to a dementor
    if (dist_to_closest < min_dist_day)
    {
      std::cout << 'n';
      continue;
    }

    // Check whether we can escape the convex hull
    size_t face_index = t.locate(point)->info();
    if (bottlenecks[face_index] >= 4 * min_dist_day)
    {
      std::cout << 'y';
      continue;
    }

    std::cout << 'n';
  }
  
  std::cout << std::endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) testcase();
}
