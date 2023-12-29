# Lord Voldemort

```
type: dynamic programming
runtime: O(mn)
```

## Problem

The task is to compute the maximum possible amount of `n` Horcruxes that can be
destroyed by `m` wizards with `k` power. Each Horcrux has a specific amount of
evil, and takes that amount of power to destroy. Every wizard must use all of
its power, and the Horcruxes that a wizard destroys, must be contiguous. No two
wizards may destroy the same Horcrux.

## Implementation

First, find all the intervals that sum up to `k`. Keep track of pointers where
the right side points to the left side of the interval. This is useful, because
we can then easily figure out whether an interval ends on a specific index,
which can be used in the recurrence relation for dynamic programming.

Now, we use dynamic programming to compute how to maximally assign wizards to
these intervals. The state space is the amount of wizards `m` (iterate `i`), and
the amount of Horcruxes `n` (iterate `j`). The recurrence relationship is that
if the `j` ends on an interval that sums to `k`, we either pick that one, and
add it to the maximum of `i-1` up to the interval start, or we do not pick it
and just take the solution of `(i, j-1)`. We can only pick the interval if `i ==
1` or if something has been picked before `int_start`, i.e. `rec(i-1, int_start)
!= 0` because otherwise it will not be valid, since not all wizards will have
used their power.

 - State space: Amount of wizards, Amount of Horcruxes.
 - Recurrence relationship: If `j` does not end on interval: `rec(i, j) =
   rec(i, j - 1)`. Otherwise: `rec(i, j) = max(rec(i, j-1), rec(i-1, int_start) + int_len)`.
 - Base case: If `j=0`: 0.

## Times

```
Test set 1 (20 pts / 3 s) : Correct answer      (0.0s)
Test set 2 (20 pts / 3 s) : Correct answer      (0.006s)
Test set 3 (20 pts / 3 s) : Correct answer      (0.074s)
Test set 4 (20 pts / 3 s) : Correct answer      (0.007s)
Test set 5 (20 pts / 3 s) : Correct answer      (0.086s)
```
