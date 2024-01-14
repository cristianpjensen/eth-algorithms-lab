# Placing knights

```
type: flow, max independent set
runtime: O(n^6)
```

## Problem

In this problem, we have an `n` x `n` chess board where some spots cannot be
filled. How many knights can we place such that no knights attack each other?

## Implementation

If we model the problem as there being an edge between all positions that collide
with each other, we want to compute the size of the maximum independent set.
Luckily this graph is a bipartite graph, because white positions can only
constrain black positions, and vice versa. The max flow of this graph is equal to
the size of the minimum vertex cover, so we take the inverse of it to obtain the
size of the maximum independent set.

## Times

```
Test set 1 (30 pts / 0.500 s) : Correct answer      (0.0s)
Test set 2 (35 pts / 0.500 s) : Correct answer      (0.048s)
Test set 3 (35 pts / 0.500 s) : Correct answer      (0.154s)
```
