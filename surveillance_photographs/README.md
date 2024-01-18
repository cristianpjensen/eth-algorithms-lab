# Surveillance Photograph

```
type: max flow
runtime: O(n^3)
```

## Problem

We have a graph with `n` vertices and `m` edges. There are `k` police stations at
some vertices with 1 policeman and 1 place for a photograph. There are `l`
photographs located at some vertices. The policeman can travel freely over the
edges without carrying a photograph. But, each edge may only be used once by
policemen that travel with a photograph. How many photographs can we store under
these constraints?

## Implementation

This is obviously a max flow problem. We satisfy the constraints by using two
copies of the graph (within the same graph data structure). In graph 1, the
policemen can travel freely, while, in graph 2, they can only use each edge
once. The policemen start in graph 1 from their police station. The only way to
get to graph 2 is by travelling to a photograph. Then, they have to travel back
to a police station to get to the sink of the graph.

## Times

```
Test set 1 (50 pts / 1.500 s) : Correct answer      (0.153s)
Test set 2 (50 pts / 1.500 s) : Correct answer      (0.245s)
```
