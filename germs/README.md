# Germs

```
type: triangulation
runtime: O(n log n)
```

## Problem

In this problem, we have `n` bacteria in a rectangle (`l, b, r, t`) whose radii
all grow at the same speed. They die when they either touch a different
bacterium or an edge of the rectangle (but they continue growing after they
die). Compute when the first bacterium dies, when 50% have died, and when the
last bacterium dies.

## Implementation

The first bacterium a bacterium touches is the closest one to it. So, we use
triangulation to find the closest bacterium. We can iterate over the edges that
a bacterium is part of, and compute the minimum of that. We can easily compute
the distance to the edge. Then, take the minimum and compute the time the
bacterium dies. Sort this list of times, and take minimum, median, and maximum.

## Times

```
Test set 1 (20 pts / 0.600 s) : Correct answer      (0.002s)
Test set 2 (20 pts / 0.600 s) : Correct answer      (0.053s)
Test set 3 (30 pts / 0.600 s) : Correct answer      (0.198s)
Test set 4 (30 pts / 0.600 s) : Correct answer      (0.175s)
```
