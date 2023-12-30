# The Iron Islands

```
type: sliding window, look-up table
runtime: O(w*n)
```

## Problem

There are `n` islands, each with an associated cost. The islands are structured
in a star-shape with `w` arms. We need to find the maximum amount of contiguous
islands such that their cost sums to `k`. Constraint: Must be able to visit the
islands without going to an island twice.

## Implementation

There are two cases. Either we use one arm of the star and we can use any region
in this arm. Or, we use exactly two arms and we go over the middle of the star.
So, we first cover the first case, where we just do sliding window on all arms.
For the first two test sets, we can also just do sliding window on all pairs of
arms. However, for the rest of the test sets, we need a more efficient
implementation. We construct a look-up table that maps cost to maximum amount of
islands that can be gotten in any arm. Then, we iterate over all the islands and
check whether it is possible to sum to `k` with the look-up table and update the
maximum island count.

Implementation details:
 - Make sure that the look-up table does not include the middle island.
 - Also keep track of the arm that has the maximum islands in the look-up table.
   Because, we are not allowed to use the same arm twice. Thus, we need to make
   sure this does not happen.

## Times

```
Test set 1        (20 pts / 2 s) : Correct answer      (0.38s)
Hidden test set 1 (05 pts / 2 s) : Correct answer      (0.382s)
Test set 2        (20 pts / 2 s) : Correct answer      (0.383s)
Hidden test set 2 (05 pts / 2 s) : Correct answer      (0.382s)
Test set 3        (20 pts / 2 s) : Correct answer      (0.507s)
Hidden test set 3 (05 pts / 2 s) : Correct answer      (0.506s)
Test set 4        (20 pts / 2 s) : Correct answer      (0.505s)
Hidden test set 4 (05 pts / 2 s) : Correct answer      (0.507s)
```
