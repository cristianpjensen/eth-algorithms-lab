# Bistro

```
type: triangulation
runtime: O(m log n + n log n)
```

## Problem

We have `n <= 110_000` bistro locations and `m <= 110_000` potential new bistro
locations. Compute the distance of each potential new bistro location to the
closest existing bistro location.

## Implementation

This is a very easy triangulation problem. The naive way to solve this is to
compare all new bistro location to all existing bistro locations, resulting in
`O(m*n)` runtime. But, we can do it smarter. We can first compute a
triangulation of all the old bistro locations, which runs in `O(n log n)`.
Then, we can find the closest point in `O(log n)`, which we run `O(m)` times.
This has an `O((m+n) log n)` overall runtime, which scales much better.

## Times

```
Test set 1 (20 pts / 0.600 s) : Correct answer      (0.026s)
Test set 2 (20 pts / 0.600 s) : Correct answer      (0.142s)
Test set 3 (20 pts / 0.600 s) : Correct answer      (0.132s)
Test set 4 (20 pts / 0.600 s) : Correct answer      (0.21s)
Test set 5 (20 pts / 0.600 s) : Correct answer      (0.407s)
```
