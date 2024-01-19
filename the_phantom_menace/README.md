# The Phantom Menace

```
type: min cut
runtime: O(n^3)
```

## Problem

We have a graph of `n` vertices and `m` edges. There are `s` potential starting
points and `d` potential destinations. What is the minimum amount of _vertices_
that need to blocked such that no starting point can reach a destination?

## Implementation

This is a very easy max flow problem. We just model the graph as specified and
add vertex capacities (because we want to know how many vertices to block, not
the min cut of edges), and compute the max flow, which is equal to the min cut.

## Times

```
Test set 1        (25 pts / 1 s) : Correct answer      (0.312s)
Test set 2        (25 pts / 1 s) : Correct answer      (0.029s)
Test set 3        (30 pts / 1 s) : Correct answer      (0.323s)
Hidden test set 1 (05 pts / 1 s) : Correct answer      (0.31s)
Hidden test set 2 (05 pts / 1 s) : Correct answer      (0.029s)
Hidden test set 3 (10 pts / 1 s) : Correct answer      (0.323s)
```
