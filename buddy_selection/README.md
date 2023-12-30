# Buddy Selection

```
type: graphs
runtime: O(n^3 + c*n^2 + n*c*log(c))
```

## Problem

In this problem, we have `n` students with `c` interests. We need to determine
whether it is possible to pair up students such that they all have at least `f`
interests in common.

## Implementation

First, we need to determine how to construct the graph. Eventually we want to
determine whether there is a matching of students such that every student is
part of a pair that has at least `f` interests in common. Thus, we need to use
Edmond's algorithm for determining the maximum cardinality matching. So, we
model the graph by adding an edge between two students if they have at least `f`
interests in common.

So, we now need to know how to efficiently determine whether two students have
at least `f` interests in common. If the interests are sorted, we can linearly
go over both to figure out how many interests two students have in common (see
code). Then, for every possible pair of students, we check whether the common
interest count is greater than `f`, and add an edge between them if it is.

Now, we only need to run Edmond's algorithm and figure out the matching size. If
every vertex is part of a pair, it is possible, otherwise not.

## Times

```
Test set 1  (30 pts / 2 s) : Correct answer      (0.045s)
Test set 2  (40 pts / 2 s) : Correct answer      (0.098s)
Test set 3  (20 pts / 2 s) : Correct answer      (0.755s)
bordercases (10 pts / 2 s) : Correct answer      (0.043s)
```
