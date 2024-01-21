# Return of the Jedi

```
type: mst
runtime: O(n^2 log (n^2))
```

## Problem

What is the minimum cost spanning tree that differs at least one edge from the
minimum spanning tree?

## Implementation

Leia constructs her plan using Prim's algorithm, which computes the MST. Thus,
we first compute the MST. Then, we iterate over the edges of her MST and
disallow the current edge, and construct the MST without it. Then, return the
minimum cost out of all those MSTs. This only requires sorting the edges once.

## Times

```
Test set 1 (40 pts / 2 s) : Correct answer      (0.008s)
Test set 2 (40 pts / 2 s) : Correct answer      (0.583s)
Test set 3 (20 pts / 2 s) : Correct answer      (0.975s)
```
