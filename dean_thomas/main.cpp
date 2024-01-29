#include <bits/stdc++.h>

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;

typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<size_t, K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;

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
  
  Triangulation::Face_circulator f = t.incident_faces(t.infinite_vertex());
  do {
    f->info() = 0;
  } while (++f != t.incident_faces(t.infinite_vertex()));
  
  size_t num_faces = 1;
  for (auto f = t.finite_faces_begin(); f != t.finite_faces_end(); ++f)
    f->info() = num_faces++;

  std::vector<std::vector<std::pair<size_t, K::FT>>> adj(num_faces);
  
  for (auto f = t.finite_faces_begin(); f != t.finite_faces_end(); ++f)
  {
    size_t index = f->info();
    
    for (int i = 0; i < 3; i++)
    {
      size_t neighbor_index = f->neighbor(i)->info();
      K::FT dist = t.segment(f, i).squared_length();
      
      if (neighbor_index == 0)
        adj[neighbor_index].push_back({ index, dist });
      else
        adj[index].push_back({ neighbor_index, dist });
    }
  }
  
  std::priority_queue<std::pair<K::FT, size_t>> Q;
  Q.push({ K::FT(DBL_MAX * DBL_MAX), 0 });
  
  for (auto f = t.finite_faces_begin(); f != t.finite_faces_end(); ++f)
  {
    K::FT face_size = CGAL::squared_distance(t.dual(f), f->vertex(0)->point());
    Q.push({ face_size, f->info() });
  }
  
  std::vector<K::FT> bottlenecks(num_faces, -1);

  while (!Q.empty())
  {
    auto p = Q.top(); Q.pop();
    size_t index = p.second;
    K::FT b = p.first;

    // Will not get better
    if (bottlenecks[index] != -1)
      continue;

    bottlenecks[index] = b;

    for (std::pair<size_t, K::FT> q : adj[index])
    {
      if (bottlenecks[q.first] == -1)
        Q.push({ std::min(b, q.second), q.first });
    }
  }
  
  for (int j = 0; j < m; j++)
  {
    long x, y; K::FT s; std::cin >> x >> y >> s;
    K::Point_2 point(x, y);

    K::FT day_distance = (d + s) * (d + s);
    K::FT night_distance = (2 * (d + s)) * (2 * (d + s));
    
    K::Point_2 nearest = t.nearest_vertex(point)->point();
    
    if (CGAL::squared_distance(nearest, point) < day_distance)
    {
      std::cout << 'n';
      continue;
    }

    size_t face_index = t.locate(point)->info();

    if (bottlenecks[face_index] >= night_distance)
      std::cout << 'y';
    else
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
