# Pied Piper

```
type: dynamic programming
runtime: O(m*n)
```

## Problem

We have `n` vertices with `m` edges. Each edge has some rats that give one gold
each. We have to go from vertex `0` to vertex `n-1`, and back, while the
forward direction is monotonously increasing and backward direction
monotonously decreasing. We are not allowed to visit the same vertex twice.
What is the maximum amount of rats that can be caught?

## Implementation

This is a very difficult problem. At first glance, you might think that it is a
max flow problem, but there is no way to constrain each vertex to be visited
once on the forward or backward pass (to my knowledge). The correct way to
solve this problem is using dynamic programming, while keeping track of both
the forward and backward vertex, starting from `0`, and ending at `n-1` (base
case). They both traverse the graph, but forward uses the edges in the correct
direction, while backward uses the edges in the opposite way (which is logical
since the backward should go from `n-1` to `0`). The reason for not having
backward traversing from `n-1` to `0` is because we then do not have a way of
constraining vertices to be only visited once.

The state space is the forward and backward vertex. The value is the maximum
amount of rats that can be caught starting from those vertices. 

There are three special cases:
 - The forward and backward vertex are equal, which means that this vertex
   would be visited twice, which is not allowed. So, "mark" this path as
   invalid.
 - The forward path cannot continue and is not at `n-1`. Again, this is then an
   invalid path.
 - The same for the backward path.

## Times

```
Test set 1        (25 pts / 4 s) : Correct answer      (0.015s)
Test set 2        (25 pts / 4 s) : Correct answer      (0.015s)
Test set 3        (15 pts / 4 s) : Correct answer      (0.866s)
Test set 4        (15 pts / 4 s) : Correct answer      (2.786s)
Hidden test set 1 (05 pts / 4 s) : Correct answer      (0.015s)
Hidden test set 2 (05 pts / 4 s) : Correct answer      (0.015s)
Hidden test set 3 (05 pts / 4 s) : Correct answer      (0.855s)
Hidden test set 4 (05 pts / 4 s) : Correct answer      (2.756s)
```
