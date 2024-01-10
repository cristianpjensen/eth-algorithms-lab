# Motorcycles

```
type: geometry
runtime: O(n^2)
```

## Problem

In this problem, we have `n` motorcycles that go in some direction into the
positive x-halfplane. If a motorcycle finds the track of another motorcycle, it
stops (edge case: if they arrive at the same time, the one on the right has
precedence). How many motorcycles go to infinity?

## Implementation

This implementation compares all pairs with each other in a strategically
ordered way such that we can early terminate a lot of iterations. For every
motorcycle, we compute a slope with the `CGAL::Gmpq` type that allows for easy
comparisons between slopes with infinite precision. Then, we go over every
motorcycle `i`, and compare it to everything below it `j`, starting from the
closest one. Skip if `j` already doesn't go to infinity.

Then, if the two motorcycle lines do not intersect, `slope_i >= slope_j`, we
can early terminate and go to the next `i`, because we will already have
stopped all drivers below `j` when `j` was `i`.

Now, we know that they will intersect, so we need to figure out who has to
stop, which is easy if we have the slopes (see the `i_stops` function). If `i`
stops, we early terminate.

## Times

This is not the fastest implementation possible, but it is the most
intuitive/easy (to me), and it fits within the time limit.

```
Test set 1        (20 pts / 4 s) : Correct answer      (0.013s)
Hidden test set 1 (05 pts / 4 s) : Correct answer      (0.013s)
Test set 2        (20 pts / 4 s) : Correct answer      (0.043s)
Hidden test set 2 (05 pts / 4 s) : Correct answer      (0.043s)
Test set 3        (20 pts / 4 s) : Correct answer      (0.122s)
Hidden test set 3 (05 pts / 4 s) : Correct answer      (0.122s)
Test set 4        (20 pts / 4 s) : Correct answer      (2.477s)
Hidden test set 4 (05 pts / 4 s) : Correct answer      (2.477s)
```
