#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef std::vector<int> VI;
typedef std::vector<VI> VVI;

// Time complexity: O(m*n)

void testcase()
{
  int m, n; std::cin >> m >> n;
  
  std::vector<K::Point_2> segment_points(m);
  for (int i = 0; i < m; i++)
  {
    int x, y; std::cin >> x >> y;
    segment_points[i] = K::Point_2(x, y);
  }

  VVI segments_contained(n);

  for (int i = 0; i < n; i++)
  {
    int p11, p12, p21, p22, p31, p32, p41, p42, p51, p52, p61, p62;
    std::cin >> p11 >> p12 >> p21 >> p22 >> p31 >> p32 >> p41 >> p42 >> p51 >> p52 >> p61 >> p62;
    K::Point_2 p1(p11, p12), p2(p21, p22), p3(p31, p32), p4(p41, p42), p5(p51, p52), p6(p61, p62);
    K::Line_2 l1(p1, p2), l2(p3, p4), l3(p5, p6);

    if (l1.oriented_side(p3) < 0)
      l1 = K::Line_2(p2, p1);
    
    if (l2.oriented_side(p5) < 0)
      l2 = K::Line_2(p4, p3);
    
    if (l3.oriented_side(p1) < 0)
      l3 = K::Line_2(p6, p5);

    std::vector<bool> in_triangle(m, false);

    // Check whether each point is within triangle, instead of checking for each
    // leg, since the legs overlap in their points
    for (int j = 0; j < m; j++)
    {
      K::FT or1 = l1.oriented_side(segment_points[j]);
      K::FT or2 = l2.oriented_side(segment_points[j]);
      K::FT or3 = l3.oriented_side(segment_points[j]);

      // If on the left side of all the lines, it is within the triangle
      in_triangle[j] = or1 >= 0 && or2 >= 0 && or3 >= 0;
    }
    
    // Keep track of which legs are contained by each triangle
    for (int j = 0; j < m-1; j++)
      if (in_triangle[j] && in_triangle[j+1])
        segments_contained[i].push_back(j);
  }
  
  // Sliding window (O(m*n))
  int min_cost = INT_MAX;
  int b = 0, e = 1;

  // Keep track of how many unique legs are covered, and for each leg how many
  // times it has been covered, so we can easily add/remove unique leg count
  VI segment_contain_counts(m-1, 0);
  int unique_leg_count = 0;
  
  for (int segment_idx : segments_contained[b])
  {
    unique_leg_count++;
    segment_contain_counts[segment_idx]++;
  }

  while (b < n && e <= n)
  {
    // If all legs are covered, make the interval smaller, otherwise make it bigger
    if (unique_leg_count == m-1)
    {
      // Update minimum cost
      min_cost = std::min(min_cost, e - b);
      
      // Remove everything that `b` covered and move along
      for (int segment_idx : segments_contained[b])
      {
        segment_contain_counts[segment_idx]--;
        if (segment_contain_counts[segment_idx] == 0)
          unique_leg_count--;
      }
      
      b++;
    }
    else
    {
      // Add whatever the next `e` will cover
      if (e != n)
      {
        for (int segment_idx : segments_contained[e])
        {
          // Check whether the leg was not already covered
          if (segment_contain_counts[segment_idx] == 0)
            unique_leg_count++;
          
          segment_contain_counts[segment_idx]++;
        }
      }

      e++;
    }
  }
  
  std::cout << min_cost << std::endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) testcase();
}
