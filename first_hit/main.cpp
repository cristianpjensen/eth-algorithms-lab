#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;

double floor_to_double(const K::FT& x)
{
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a+= 1;
  return a;
}

void testcase(int n)
{
  long x, y, a, b; std::cin >> x >> y >> a >> b;
  
  K::Point_2 p1(x, y), p2(a, b);
  K::Ray_2 ray(p1, p2);
  
  std::vector<K::Segment_2> segments(n);
  for (int i = 0; i < n; i++)
  {
    long r, s, t, u; std::cin >> r >> s >> t >> u;
    segments[i] = K::Segment_2(K::Point_2(r, s), K::Point_2(t, u));
  }
  
  // If this is not done, the last two test cases do not pass. They are probably
  // ordered such that the furthest intersecting segments are first.
  std::random_shuffle(segments.begin(), segments.end());

  // Keep track of the segment from the source of the ray to the currently first
  // hit point. This has the consequence that only segments that intersect
  // closer will intersect than the current closest point, so we perform less
  // intersection constructions and we do not have to check whether the new
  // segment is closer than the current one.
  K::Segment_2 hit_segment;
  bool first_hit = false;

  for (int i = 0; i < n; i++)
  {
    K::Segment_2 segment = segments[i];
    K::Point_2 p3 = segment.source();
    K::Point_2 p4 = segment.target();
    
    // We first have to make sure we have a hit segment
    if (!first_hit && CGAL::do_intersect(ray, segment))
    {
      first_hit = true;
      auto intersection = CGAL::intersection(ray, segment);

      if (const K::Point_2* ip = boost::get<K::Point_2>(&*intersection))
        // The intersection is a point, so we just set that as the new segment
        hit_segment = K::Segment_2(p1, *ip);
      else
      {
        // The intersection is a segment, i.e., they overlap, so we have to
        // figure out which endpoint is closer and set that as the new segment
        K::Point_2 closest_point = CGAL::has_larger_distance_to_point(p1, p3, p4) ? p4 : p3;
        hit_segment = K::Segment_2(p1, closest_point);
      }
    }

    // We first check with do_intersect and then compute the intersection,
    // because do_intersect is very fast
    if (first_hit && CGAL::do_intersect(hit_segment, segment))
    {
      auto intersection = CGAL::intersection(hit_segment, segment);
      if (const K::Point_2* ip = boost::get<K::Point_2>(&*intersection))
        // The intersection is a point, so we just set that as the new segment
        hit_segment = K::Segment_2(p1, *ip);
      else
      {
        // The intersection is a segment, i.e., they overlap, so we have to
        // figure out which endpoint is closer and set that as the new segment
        K::Point_2 closest_point = CGAL::has_larger_distance_to_point(p1, p3, p4) ? p4 : p3;
        hit_segment = K::Segment_2(p1, closest_point);
      }
    }
  }

  if (first_hit)
  {
    K::Point_2 point = hit_segment.target();
    std::cout << long(floor_to_double(point.x())) << ' ' << long(floor_to_double(point.y())) << std::endl;
  } 
  else
    std::cout << "no" << std::endl;
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
