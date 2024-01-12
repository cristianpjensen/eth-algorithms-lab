# Kingdom Defence

```
type: flow
runtime: O(l^3)
```

## Problem

We have `l` locations that have `g` soldiers and need `d` soldiers. We also
have `p` roads between these locations, along which at least `c` and at most
`C` soldiers have to walk. Is it possible that all locations get their required
amount of soldiers?

## Implementation

This is an easy max flow problem. We just need to make the graph as specified
with the locations and roads. And, we need to adjust the flow such that we
adhere to the minimum and maximum constraint (see max flow slides). Then, we
just need to check whether the max flow is equal to the needed flow, which is
the total amount of needed soldiers (i.e., every location gets what they need).

## Times

```
Test set 1        (15 pts / 5 s) : Correct answer      (1.358s)
Test set 2        (15 pts / 5 s) : Correct answer      (0.475s)
Test set 3        (25 pts / 5 s) : Correct answer      (1.544s)
Test set 4        (25 pts / 5 s) : Correct answer      (1.36s)
Hidden test set 1 (05 pts / 5 s) : Correct answer      (1.467s)
Hidden test set 2 (05 pts / 5 s) : Correct answer      (0.507s)
Hidden test set 3 (05 pts / 5 s) : Correct answer      (1.36s)
Hidden test set 4 (05 pts / 5 s) : Correct answer      (1.792s)
```
