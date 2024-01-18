# India

```
type: min cost max flow, binary search
```

## Problem

We have a graph with `c` vertices and `g` edges. Each edge has a maximum amount
of elephants carrying 1 luggage that can go through it (capacity), and a cost
per elephant (cost). We want to find the maximum amount of luggage that we can
get from vertex `k` to `a` with less than or equal to a cost of `b`.

## Implementation

This is an obvious min cost max flow problem. However, the hard part is
figuring out how to constrain the cost. This is not possible with a single call
to min cost max flow functions. But, we do have a monotonous function: more
luggage costs more money. Thus, we can use binary search to search over the
amount of luggage until we have one that is as close to `b` as possible. Then,
output the max flow of this. We can constrain the amount of luggage (i.e. the
max flow) by adding a bottleneck between the source and `k` with at most the
maximum luggage as capacity.

## Times

```
Test set 1  (20 pts / 5 s) : Correct answer      (0.098s)
Test set 2  (20 pts / 5 s) : Correct answer      (0.434s)
Test set 3  (20 pts / 5 s) : Correct answer      (0.176s)
Test set 4  (20 pts / 5 s) : Correct answer      (0.276s)
Test set 1h (05 pts / 5 s) : Correct answer      (0.145s)
Test set 2h (05 pts / 5 s) : Correct answer      (0.373s)
Test set 3h (05 pts / 5 s) : Correct answer      (0.126s)
Test set 4h (05 pts / 5 s) : Correct answer      (0.261s)
```
