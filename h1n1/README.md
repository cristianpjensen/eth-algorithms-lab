# H1N1

```
type: triangulation, dijkstra
runtime: O(m log n + n log n)
```

## Problem

In this problem, we have `n` sick people located at some positions. We have `m`
healthy people that are at `(x,y)` and want to escape the sick people, while
remaining `sqrt(d)` distance away from any sick people. Is this possible?

## Implementation

For this problem, we can do a lot of precomputation. We can first make a
triangulation of the sick people. This creates faces, and we can move from face
to face while remaining half the distance of the edge between those two faces
from any sick person. For any face, we can precompute what the minimum distance
edge is to get outside the convex hull. To do this, we first build up a graph
where the faces are the vertices, adjacent faces have edges between them where
the weight is the length. Then, we use Dijkstra's in the min tropical semiring
to compute the bottleneck to getting outside the convex hull. Now, for every
healthy person, we only need to check whether the closest vertex is at least
`d` away, and whether the bottleneck allows this person to escape.

## Times

```
Test set 1 (20 pts / 1 s) : Correct answer      (0.005s)
Test set 2 (20 pts / 1 s) : Correct answer      (0.049s)
Test set 3 (20 pts / 1 s) : Correct answer      (0.364s)
Test set 4 (20 pts / 1 s) : Correct answer      (0.571s)
Test set 5 (20 pts / 1 s) : Correct answer      (0.489s)
```
