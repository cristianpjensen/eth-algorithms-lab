# Rubeus Hagrid

```
type: dfs, greedy
runtime: O(n log n)
```

## Problem

We have `n` nodes that are connected in a tree graph. Each edge takes a certain
amount of time, and each vertex stores a certain amount of gold. 1 gold
disappears from every node every minute. There is guaranteed to always be gold
in a vertex when we visit it. We can only go down and up each edge once. What
is the maximum amount of gold that can be gotten?

## Implementation

We can only go down and up each edge once, which means that we need to do DFS.
Since there is guaranteed to be enough gold such that it never runs out before
we get there, we take a greedy approach to minimize the amount of gold lost
each time we have to choose which subtree to choose. If we choose a subtree, we
lose `(nodes in other subtrees) * (time to traverse full subtree with DFS)`
gold. Thus, we need to greedily the edge that minimize this. We could naively
go over every subtree to pick the next one, but this results in `O(n^2)`
complexity, which is too slow. But, we can also sort the edges according to the
following: `e1.traversal_time / e1.descendants < e2.traversal_time /
e2.descendants`, which sorts the subtrees according to losing the least amount
of gold. Then, visit the next subtrees of a vertex in that order, and count the
amount of gold.

## Times

```
Test set 1 (30 pts / 3 s) : Correct answer      (0.013s)
Test set 2 (30 pts / 3 s) : Correct answer      (0.406s)
Test set 3 (30 pts / 3 s) : Correct answer      (0.377s)
Test set 4 (10 pts / 3 s) : Correct answer      (0.466s)
```
