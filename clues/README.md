# Clues

```
type: triangulation, connected components, bipartite
runtime: O(n log n + m log n)
```

## Problem

We have `n` stations that each have a range of `r`. We then have `m` queries to
check whether we can send a message from `(x,y)` to `(x',y')` such that all
stations used are within `r` range of each other, or just directly connect to
each other. We also have to make sure there is no "interference". There is
interference if cannot assign 0 or 1 to the stations such that all 0 stations
touch 1 stations and vice versa.

## Implementation

The hardest part is figuring out whether is interference or not. Naively, we
could connect all vertices that are within `r` range and check whether the
resulting graph is bipartite. However, this is too slow. Thus, we should use
triangulation and only add the edges in the triangulation with less than `r`
length. Then, we check whether this graph is bipartite. However, there is an
edge case. There might be two stations with less than `r` distance such that
they are not connected in the triangulation (e.g. when a station is behind a
different station closer to the original station). Thus, we need to check the
partitions of the bipartite graph for whether there are edges between them with
less than `r` length. This can again be done by triangulation.

Then, we need to check for each query whether it is possible. If interference,
return no. Otherwise, check whether the closest station is less than `r`
distance to both points, and then check whether the two stations are within the
same connected component. Could also use Kruskal's algorithm for this, like in
previous problems.

## Times

```
Test set 1 (20 pts / 2 s) : Correct answer      (0.086s)
Test set 2 (30 pts / 2 s) : Correct answer      (0.804s)
Test set 3 (30 pts / 2 s) : Correct answer      (1.114s)
Test set 4 (20 pts / 2 s) : Correct answer      (1.412s)
```
