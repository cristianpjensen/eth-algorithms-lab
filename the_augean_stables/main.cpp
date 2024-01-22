#include <bits/stdc++.h>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef int IT;

// This makes it much faster and is needed for the last test set... Even though
// a TA advised against it on Moodle.
typedef double ET;

typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

typedef std::vector<int> VI;

bool is_possible(
  VI& k,
  VI& l,
  VI& m,
  VI& needed,
  int n,
  int a,
  int p
)
{
  Program lp (CGAL::SMALLER, true, 0, true, 1); 
  const int H1 = 0;
  const int H2 = 1;
  const int H3 = 2;
  
  for (int i = 0; i < n; i++)
  {
    lp.set_a(H1, i, -(k[i] + a*a));
    lp.set_a(H2, i, -(l[i] + p*p));
    lp.set_a(H3, i, -(m[i] + a*p));
    lp.set_b(i, -needed[i]);
  }
  
  Solution s = CGAL::solve_linear_program(lp, ET());
  return !s.is_infeasible();
}

void testcase()
{
  int n; std::cin >> n;

  VI k(n);
  VI l(n);
  VI m(n);
  VI needed(n);
  for (int i = 0; i < n; i++)
  {
    int f, c; std::cin >> f >> c >> k[i] >> l[i] >> m[i];
    needed[i] = f - c;
  }
  
  // Read in `a` and `p` as cumsum
  std::array<int, 25> a;
  a[0] = 0;
  for (int i = 1; i < 25; i++)
  {
    int current; std::cin >> current;
    a[i] = a[i-1] + current;
  }
  
  std::array<int, 25> p;
  p[0] = 0;
  for (int i = 1; i < 25; i++)
  {
    int current; std::cin >> current;
    p[i] = p[i-1] + current;
  }

  const int MAX_HOURS = 24;
  
  // Binary search over the amount of hours, since more hours equals cleaner
  // stalls
  int min_hours = -1;
  int left = 0;
  int right = MAX_HOURS * 2;
  while (left <= right)
  {
    int hours = (left + right) / 2;
    
    for (
      int a_hours = std::max(hours - MAX_HOURS, 0);
      a_hours <= std::min(hours, MAX_HOURS);
      a_hours++
    )
    {
      int p_hours = hours - a_hours;

      if (is_possible(k, l, m, needed, n, a[a_hours], p[p_hours]))
      {
        min_hours = hours;
        break;
      }
    }
    
    if (min_hours == hours)
      right = hours - 1;
    else
      left = hours + 1;
  }
  
  if (min_hours != -1)
    std::cout << min_hours << std::endl;
  else
    std::cout << "Impossible!" << std::endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) testcase();
}
