#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<size_t, K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;

void testcase()
{
  int n, m; long s; int k; std::cin >> n >> m >> s >> k;

  std::vector<std::pair<K::Point_2, size_t>> points(n);

  for (int i = 0; i < n; i++)
  {
    int x, y; std::cin >> x >> y;
    points[i] = { K::Point_2(x, y), i };
  }

  Triangulation t;
  t.insert(points.begin(), points.end());

  std::vector<std::tuple<long, size_t, size_t>> edges;
  edges.reserve(3*n);

  for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
    size_t i1 = e->first->vertex((e->second+1)%3)->info();
    size_t i2 = e->first->vertex((e->second+2)%3)->info();
    if (i1 > i2) std::swap(i1, i2);
    edges.emplace_back(t.segment(e).squared_length(), i1, i2);
  }

  std::sort(edges.begin(), edges.end());

  // Modified Kruskal's algorithm to find the amount of bones reachable from each
  // tree. This is done by making unions using only the edges with edge smaller
  // than s.
  boost::disjoint_sets_with_storage<> uf(n);
  int n_components = n;

  for (auto edge : edges)
  {
    int set1 = uf.find_set(std::get<1>(edge));
    int set2 = uf.find_set(std::get<2>(edge));
    long sq_dist = std::get<0>(edge);

    if (sq_dist > s)
      break;

    if (set1 != set2) {
      uf.link(set1, set2);
      if (--n_components == 1) break;
    }
  }

  // Then, we find the amount of bones reachable from each union component, and
  // take the maximum
  std::vector<int> component_bones(n, 0);
  for (int j = 0; j < m; j++)
  {
    int x, y; std::cin >> x >> y;
    K::Point_2 bone(x, y);

    auto nearest_handle = t.nearest_vertex(bone);
    K::Point_2 tree_point = nearest_handle->point();
    size_t tree_index = nearest_handle->info();
    long dist = CGAL::squared_distance(bone, tree_point);

    // Add an edge from every bone to its nearest tree. q will need to be
    // 4 * dist to reach this bone
    edges.push_back({ 4 * dist, tree_index, n + j });

    // This bone is not reachable from any tree
    if (4 * dist > s)
      continue;

    size_t tree_set = uf.find_set(tree_index);
    component_bones[tree_set]++;
  }

  int max_k = *std::max_element(component_bones.begin(), component_bones.end());

  // ---

  // Compute the minimum q for at least k bones
  // The edges now contain the bone-tree edges
  std::sort(edges.begin(), edges.end());

  // Modified Kruskal's algorithm, where we continue until some union satisfies
  // the constraint of at least being k, then we need to know the minimum q
  boost::disjoint_sets_with_storage<> uf_min_q(n);
  n_components = n;
  long min_q = 0;
  std::vector<int> reachable_bones(n);

  for (auto edge : edges)
  {
    int v1 = std::get<1>(edge);
    int v2 = std::get<2>(edge);
    long sq_dist = std::get<0>(edge);

    if (v2 >= n)
    {
      // This is a tree-bone edge
      int set1 = uf_min_q.find_set(v1);
      reachable_bones[set1]++;
      
      if (reachable_bones[set1] >= k)
      {
        min_q = sq_dist;
        break;
      }
    }
    else
    {
      // This is a tree-tree edge
      int set1 = uf_min_q.find_set(v1);
      int set2 = uf_min_q.find_set(v2);
      
      if (set1 != set2)
      {
        uf_min_q.link(set1, set2);

        int new_set = uf_min_q.find_set(v1);
        reachable_bones[new_set] = reachable_bones[set1] + reachable_bones[set2];
        if (reachable_bones[new_set] >= k)
        {
          min_q = sq_dist;
          break;
        }
      }
    }
  }

  std::cout << max_k << ' ' << min_q << std::endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) testcase();
}
