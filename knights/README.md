# Knights

```
type: flow
runtime: O((n+m)^3)
```

## Problem

In this problem, we have an `m x n` grid where we can move up, down, left, or
right. From one of the sides of the grid, you can escape. You can only move
between intersections once, and each intersection can only be used `C` times.
There are `k` knights in the grid, how many can escape?

## Implementation

This is a max flow solution, where we model each intersection by an input and
output vertex with capacity `C`. Then, each intersection is connected to its
neighbors by connecting the input to the output, with capacity 1 to model that
each hallway can only be used once. The starting position of each knight is
modeled as an edge from the source to its starting position with capacity 1.
The escaping from the grid is modeled as an edge to the target. Notice that the
corner intersections need more than 1 capacity, since they have multiple
escapes.

Then, the maximum flow within this graph is the amount of knights that can
escape.

## Times

```
Test set 1        (35 pts / 1 s) : Correct answer      (0.125s)
Test set 2        (35 pts / 1 s) : Correct answer      (0.109s)
Test set 3        (10 pts / 1 s) : Correct answer      (0.112s)
Hidden test set 1 (05 pts / 1 s) : Correct answer      (0.126s)
Hidden test set 2 (05 pts / 1 s) : Correct answer      (0.109s)
Hidden test set 3 (10 pts / 1 s) : Correct answer      (0.109s)
```
