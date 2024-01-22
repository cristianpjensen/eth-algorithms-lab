# Casino Royale

```
type: min cost max flow
runtime: O(n^3)
```

## Problem

We have `n` train stops and `m` missions with each a preference score. We have a
fixed amount of seats `l` on the train at any given moment. Each mission needs to
go from `x` to `y`, taking up a seat between those stops. What is the maximum
amount of preference score we can achieve?

## Implementation

This is pretty obviously a min cost max flow problem, but figuring out how to
model it is quite hard. We model the train as a long line of nodes and edges
between consecutive stops with flow `l`. Then, as a potentially executed mission,
we add an edge from `x` to `y` with flow 1 and cost equal to -preference (to
maximize).  Intuitively, a mission takes a seat between `x` and `y`, not allowing
anyone else to take it.

Now, we need the costs to be positive and we need to know how much positive
values we add to the cost. So, we add 128 to all costs, which is the upper bound
of the preference. The mission then needs `(y-x) * 128` cost added, because
otherwise we do not know how much cost is added in the end.

## Times

```
Test set 1 (30 pts / 5 s) : Correct answer      (0.014s)
Test set 2 (30 pts / 5 s) : Correct answer      (0.93s)
Test set 3 (40 pts / 5 s) : Correct answer      (0.895s)
```
