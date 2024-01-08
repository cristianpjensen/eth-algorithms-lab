# Planet Express

```
type: graph
runtime: O(m + n log n)
```

## Problem

We have a special network with `n` vertices and `m` normal edges, which
contains a teleportation network. `T` vertices are part of this teleportation
network, and if two vertices `u,v` within this teleportation network are
pairwise reachable, we can teleport from one to the other in `t(u)` time, which
is equal to the amount of vertices that can be teleported to from `u`. The
first `k` vertices are warehouses and we need to figure out how fast we can get
from any of these warehouses to vertex `n-1`.

## Implementation

We simply use a graph with `2*n+1` vertices. This is very important, because
otherwise there is an edge case which results in segmentation fault. The reason
for this is that later we compute strong components which have an index between
`0` and `n`, not `0` and `T`.

Then, we compute the strong components to figure out which vertices are
pairwise reachable. We use the size of the strong component of a teleportation
vertex to compute `t(u)`. Then, we connect all teleportation vertices within
the same component.

Then, we connect a "super vertex" to all the warehouses and run Dijkstra's from
there to get the distance to vertex `n-1`.

## Times

```
Test set 1        (20 pts / 1.000 s) : Correct answer      (0.045s)
Hidden test set 1 (05 pts / 1.000 s) : Correct answer      (0.045s)
Test set 2        (20 pts / 1.000 s) : Correct answer      (0.283s)
Hidden test set 2 (05 pts / 1.000 s) : Correct answer      (0.283s)
Test set 3        (20 pts / 1.000 s) : Correct answer      (0.45s)
Hidden test set 3 (05 pts / 1.000 s) : Correct answer      (0.45s)
Test set 4        (20 pts / 1.000 s) : Correct answer      (0.45s)
Hidden test set 4 (05 pts / 1.500 s) : Correct answer      (0.45s)
```
