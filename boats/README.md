# Boats

```
type: greedy
runtime: O(n log n)
```

## Problem

In this problem, we have `n` boats with length `l` and ring position `p`. What
is the maximum amount of boats that we can place at their ring position?

## Implementation

This is an easy greedy problem, where we linearly go over the boats from left
to right. The first boat can always be picked. Then, for each subsequent boat,
there are two cases:
 - It is not covered by any other boats: Place the boat no matter what;
 - It is covered by the previous boat: Replace the previous boat by the current
   one, if it results in the total width of the placed boats becoming smaller.

## Times

```
Test set 1 (30 pts / 2 s) : Correct answer      (0.002s)
Test set 2 (30 pts / 2 s) : Correct answer      (0.005s)
Test set 3 (40 pts / 2 s) : Correct answer      (0.68s)
```
