#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

void testcase(int n)
{
  long x, y, a, b; std::cin >> x >> y >> a >> b;
  
  K::Point_2 p1(x, y), p2(a, b);
  K::Ray_2 ray(p1, p2);
  
  bool hits = false;

  for (int i = 0; i < n; i++)
  {
    long r, s, t, u; std::cin >> r >> s >> t >> u;
    
    K::Point_2 p3(r, s), p4(t, u);
    K::Segment_2 segment(p3, p4);
    
    if (!hits && CGAL::do_intersect(ray, segment))
      hits = true;
  }
  
  if (hits)
    std::cout << "yes" << std::endl;
  else
    std::cout << "no" << std::endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false);

  int n;
  std::cin >> n;
  while (n != 0)
  {
    testcase(n);
    std::cin >> n;
  }
}
