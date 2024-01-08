# Antenna

```
type: geometry
```

## Problem

We need to find the minimum enclosing circle of points, and then output the
ceiling of its radius.

## Implementation

CGAL has a type for this exact problem, see the code. The only "hard" part of this problem is the ceiling function:
```c++
double ceil_to_double(const K::FT& x)
{
  double a = std::ceil(CGAL::to_double(x));
  while (a-1 >= x) a -= 1;
  while (a < x) a += 1;
  return a;
}
```

## Times

```
Test set 1 (10 pts / 1 s) : Correct answer      (0.001s)
Test set 2 (10 pts / 1 s) : Correct answer      (0.003s)
Test set 3 (20 pts / 1 s) : Correct answer      (0.022s)
Test set 4 (20 pts / 1 s) : Correct answer      (0.383s)
Test set 5 (10 pts / 1 s) : Correct answer      (0.745s)
Test set 6 (10 pts / 1 s) : Correct answer      (0.0s)
Test set 7 (10 pts / 1 s) : Correct answer      (0.669s)
Test set 8 (10 pts / 1 s) : Correct answer      (0.668s)
```
