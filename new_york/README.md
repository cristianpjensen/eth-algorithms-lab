# New York

```
type: dfs
runtime: O(n log m)
```

## Problem

We have a tree with `n` vertices that each have an associated temperature.
Which vertices have an `m`-length path down such that the difference between
the maximum and minimum temperature along this path is less than `k`?

## Implementation

This problem is not hard. It only requires you to know how to use
`std::multiset` and `std::deque`. We first need to find every path of length
`m`. We do this with DFS, starting from node 0, using `std::deque`. We can
remove from and push to the front and back from the deque in O(1), which are
the only operations we need. Every time we go deeper in the graph, we add the
child and then remove it again from the back after getting back to restore the
deque state. And, then we also need to make sure to remove the front whenever
the path is greater than `m`, and put it back again. Now, we also need a way of
efficiently keeping track of the temperatures in the current path. We do this
with the `std::multiset`, because we can get the maximum and minimum in O(1),
with insertion time O(log m). Then, whenever the path is of length `m`, we
check whether the difference in max-min temperature is less than `k`, and mark
it as safe if it is.

## Times

```
Test set 1 (20 pts / 4 s) : Correct answer      (0.013s)
Test set 2 (20 pts / 4 s) : Correct answer      (1.592s)
Test set 3 (20 pts / 4 s) : Correct answer      (0.004s)
Test set 4 (40 pts / 4 s) : Correct answer      (2.211s)
```
