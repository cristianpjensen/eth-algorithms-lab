#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/bipartite.hpp>
#include <boost/graph/connected_components.hpp>

typedef CGAL::Exact_predicates_inexact_constructions_kernel    K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K>    Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb>           Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds>                 Triangulation;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;

typedef std::vector<boost::default_color_type> partition_t;
typedef typename boost::property_map<graph, boost::vertex_index_t>::type index_map_t;
typedef boost::iterator_property_map<partition_t::iterator, index_map_t> partition_map_t;
typedef boost::color_traits<boost::default_color_type> color;

void testcase()
{
  int n, m; long r; std::cin >> n >> m >> r;

  std::vector<std::pair<K::Point_2, int>> points(n);

  for (int i = 0; i < n; i++)
  {
    int x, y; std::cin >> x >> y;
    points[i] = { K::Point_2(x, y), i };
  }

  // O(n log n)
  Triangulation t;
  t.insert(points.begin(), points.end());

  graph G(n);

  // O(n)
  for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e)
  {
    int i1 = e->first->vertex((e->second+1)%3)->info();
    int i2 = e->first->vertex((e->second+2)%3)->info();

    if (t.segment(e).squared_length() <= r * r)
      boost::add_edge(i1, i2, G);
  }

  // Check for interference
  partition_t partition(n);
  partition_map_t partition_map(
    partition.begin(),
    boost::get(boost::vertex_index, G)
  );

  // The graph must be at least bipartite for there to be no interference.
  // Afterwards, we still have to check whether each partition has no
  // interference, because there is an edge case where two vertices are closer than
  // `r`, but not connected in Delaunay triangulation.
  bool no_interference = boost::is_bipartite(
    G,
    boost::get(boost::vertex_index, G),
    partition_map
  );

  // O(n log n)
  if (no_interference)
  {
    // Partition the white and black points, and make sure that within the
    // partitions, they are not closer than `r`, because otherwise there will be
    // interference
    std::vector<K::Point_2> white_points;
    std::vector<K::Point_2> black_points;

    for (auto v = t.finite_vertices_begin(); v != t.finite_vertices_end(); ++v)
    {
      if (partition[v->info()] == color::white())
        white_points.push_back(v->point());
      else
        black_points.push_back(v->point());
    }

    // Check white points to have less than `r` distance from each other
    Triangulation white_t;
    white_t.insert(white_points.begin(), white_points.end());

    for (auto e = white_t.finite_edges_begin(); e != white_t.finite_edges_end(); ++e)
    {
      if (white_t.segment(e).squared_length() <= r * r)
      {
        no_interference = false;
        break;
      }
    }

    // Check black points to have less than `r` distance from each other
    Triangulation black_t;
    black_t.insert(black_points.begin(), black_points.end());

    for (auto e = black_t.finite_edges_begin(); e != black_t.finite_edges_end(); ++e)
    {
      if (black_t.segment(e).squared_length() <= r * r)
      {
        no_interference = false;
        break;
      }
    }
  }

  // O(n)
  std::vector<int> component_map(n);
  boost::connected_components(
    G,
    boost::make_iterator_property_map(
      component_map.begin(),
      boost::get(boost::vertex_index, G)
    )
  );

  // O(m log n)
  for (int j = 0; j < m; j++)
  {
    int xa, ya, xb, yb; std::cin >> xa >> ya >> xb >> yb;

    if (!no_interference)
    {
      std::cout << 'n';
      continue;
    }

    K::Point_2 a(xa, ya);
    K::Point_2 b(xb, yb);

    // If reachable without stations, do that
    if (CGAL::squared_distance(a, b) <= r * r)
    {
      std::cout << 'y';
      continue;
    }

    // O(log n)
    auto a_station = t.nearest_vertex(a);
    auto b_station = t.nearest_vertex(b);
    K::Point_2 a_station_point = a_station->point();
    K::Point_2 b_station_point = b_station->point();
    int a_component = component_map[a_station->info()];
    int b_component = component_map[b_station->info()];

    // `a` and `b` connect to their closest station. So, we need to check
    // whether the stations are reachable and whether the stations are
    // connected.
    if (
      CGAL::squared_distance(a, a_station_point) <= r * r
      && CGAL::squared_distance(b, b_station_point) <= r * r
      && a_component == b_component
    )
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
