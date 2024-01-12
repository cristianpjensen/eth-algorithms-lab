#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<size_t, K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;
typedef Triangulation::Face_handle Face_handle;

// Time complexity: O(n log n + m log n)

void testcase(int n)
{
  std::vector<K::Point_2> points(n);
  for (int i = 0; i < n; i++)
  {
    int x, y; std::cin >> x >> y;
    points[i] = K::Point_2(x, y);
  }

  // O(n log n)
  Triangulation t;
  t.insert(points.begin(), points.end());

  // Give every interior face a unique index
  size_t num_faces = 1;
  for (auto f = t.finite_faces_begin(); f != t.finite_faces_end(); ++f)
    f->info() = num_faces++;

  // Treat every exterior face as the same face, i.e., give index 0
  auto f = t.incident_faces(t.infinite_vertex());
  do {
    f->info() = 0;
  } while (++f != t.incident_faces(t.infinite_vertex()));


  // Compute the maximum width that can go between any two faces and insert it
  // into the adjacency list. This builds a graph where adjacent faces have an
  // edge with the weight being the maximum width that can go between them.
  // O(n)
  std::vector<std::vector<std::pair<size_t, long>>> adjacency_list(num_faces);

  for (auto f = t.finite_faces_begin(); f != t.finite_faces_end(); ++f)
  {
    size_t index = f->info();

    K::Point_2 v0 = f->vertex(0)->point();
    K::Point_2 v1 = f->vertex(1)->point();
    K::Point_2 v2 = f->vertex(2)->point();
    Face_handle f0 = f->neighbor(0);
    Face_handle f1 = f->neighbor(1);
    Face_handle f2 = f->neighbor(2);
    size_t index0 = f0->info();
    size_t index1 = f1->info();
    size_t index2 = f2->info();

    // See the proximity structures slides or the CGAL documentation
    long max_width0 = CGAL::squared_distance(v1, v2);
    long max_width1 = CGAL::squared_distance(v2, v0);
    long max_width2 = CGAL::squared_distance(v0, v1);

    adjacency_list[index].push_back({ index0, max_width0 });
    adjacency_list[index].push_back({ index1, max_width1 });
    adjacency_list[index].push_back({ index2, max_width2 });

    // Only add the other way if the index is 0, because that is the exterior
    // face, which we will not iterate over. If we do not add this condition, we
    // will have duplicate edges.
    if (index0 == 0) adjacency_list[index0].push_back({ index, max_width0 });
    if (index1 == 0) adjacency_list[index1].push_back({ index, max_width1 });
    if (index2 == 0) adjacency_list[index2].push_back({ index, max_width2 });
  }

  // From outside the convex hull, precompute the bottleneck to every face,
  // i.e., what is the maximum width that can go from outside the convex hull to
  // this face (the other way is what we actually want, but this is the same
  // maximum width).
  std::vector<long> bottlenecks(num_faces, -1);

  // Dijkstra in the min tropical semiring
  // O(n log n)
  std::priority_queue<std::pair<long, size_t>> Q;
  Q.push({ LONG_MAX, 0 });

  while (!Q.empty())
  {
    auto p = Q.top(); Q.pop();
    long bottleneck = p.first;
    size_t face_index = p.second;

    // If this face has already been explored, there will not be a higher
    // bottleneck, since we use a priority queue, thus all bottlenecks can only
    // get lower from now on
    if (bottlenecks[face_index] != -1)
      continue;

    bottlenecks[face_index] = bottleneck;

    for (auto neighbor : adjacency_list[face_index])
    {
      size_t neighbor_index = neighbor.first;
      long max_width = neighbor.second;
      Q.push({ std::min(bottleneck, max_width), neighbor_index });
    }
  }

  // For each point, find its closest infected person, and check whether its
  // distance is less than `d`. Then, the bottleneck to get outside the convex
  // hull must be less than `2*d`. Everything is squared, so we get `4*d`.
  // O(m log n)
  int m; std::cin >> m;
  for (int j = 0; j < m; j++)
  {
    int x, y; long sq_d; std::cin >> x >> y >> sq_d;
    K::Point_2 point(x, y);
    K::Point_2 nearest = t.nearest_vertex(point)->point();
    Face_handle face = t.locate(point);
    size_t face_index = face->info();

    if (
      CGAL::squared_distance(point, nearest) >= sq_d
      && bottlenecks[face_index] >= 4*sq_d
    )
      std::cout << 'y';
    else
      std::cout << 'n';
  }

  std::cout << std::endl;
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
