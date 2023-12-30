# Ant Challenge

```
type: graphs
runtime: O(n*s + m log n + m*s + n log n)
```

## Problem

In this problem, we have a graph and multiple species that each assign different
weights to the edges in the graph. Each species explores the graph like Prim's
algorithm and the species can only use those edges. We need to find the fastest
route through the combined private networks of all species from a source to a
target vertex.

## Implementation

Each species explores the graph like Prim's algorithm, so we first read in all
the graphs and then run Prim's algorithm on all of them. Then, we combine all
the graphs by taking the minimum weight of the edge of all species' MST. Then,
run Dijkstra's on this graph to find the distance between the source and target
vertex.

## Times

```
Test set 1 (20 pts / 1 s) : Correct answer      (0.007s)
Test set 2 (20 pts / 1 s) : Correct answer      (0.037s)
Test set 3 (20 pts / 1 s) : Correct answer      (0.024s)
Test set 4 (40 pts / 1 s) : Correct answer      (0.144s)
```
