# Hiking Maps

```
type: geometry, sliding window
runtime: O(m*n)
```

## Problem

In this problem, we have hiking legs that we need to cover with the map. But,
we can only purchase (contiguous, ordered in some random way) triangles that
cover some part of the map. So, we need to find out the smallest interval that
covers all the legs.

## Implementation

The triangles are given as the lines of its edges. However, we do not need to
construct a `K::Triangle_2`, because we only need to check whether a point is
within a triangle or not. This can be done by checking on which side of every
line a given point is. If it is on the left side of every line, it must be
within the triangle. We do this for every point to check whether it is within
the triangle or not. Then, for each leg, we can figure out whether it is within
a triangle or not.

Now, we need to find the smallest interval that covers all the legs, given that
we know which legs each triangle covers. We can do this with sliding window. We
make the window bigger if the amount of legs covered is less than `m-1` and
make it smaller if it is equal to `m-1`. Then, every time it is equal to `m-1`,
we update the minimum interval length.

## Times

```
Test set 1 (20 pts / 0.400 s) : Correct answer      (0.004s)
Test set 2 (20 pts / 0.400 s) : Correct answer      (0.009s)
Test set 3 (20 pts / 0.400 s) : Correct answer      (0.089s)
Test set 4 (20 pts / 0.400 s) : Correct answer      (0.265s)
Test set 5 (20 pts / 0.400 s) : Correct answer      (0.177s)
```
