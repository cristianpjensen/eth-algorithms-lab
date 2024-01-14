# Algocoon Group

```
type: min cut
runtime: O(n^4)
```

## Problem

We have a sculpture with `n` figures and `m` limbs that connect the limbs.
Every limb has some cost to cut it. How do we separate the figures such that
each side has at least 1 figure and the cost cutting is minimized?

## Implementation

This is obviously a min cut problem, where we need to find the min cut of any
pair of figures. So, the naive way to solve this problem is to compute the
minimum cut of all pairs in O(n^2). However, this can be done in O(n) by fixing
one figure and computing the min cut to all other figures. This works because
every possible cut is also between these cuts. We need to compute the min cut
both ways because we need to know whose side has the smaller cost.

## Times

```
Test set 1 (10 pts / 3 s) : Correct answer      (1.203s)
Test set 2 (10 pts / 3 s) : Correct answer      (1.049s)
Test set 3 (20 pts / 3 s) : Correct answer      (0.07s)
Test set 4 (30 pts / 3 s) : Correct answer      (1.159s)
Test set 5 (30 pts / 3 s) : Correct answer      (0.911s)
```
