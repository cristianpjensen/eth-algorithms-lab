# Beach Bars

```
type: sliding window
runtime: O(n log n)
```

## Problem

In this problem, we want to find the best location for a bar along a
one-dimensional beach. We need to find a location that maximizes the number of
parasols within 100 meters of it. If there are multiple such locations, pick the
one that minimizes the distance to the farthest parasol at most 100 meters away.

The output consists of the maximum amount of parasols of any location, the
minimum maximum distance within an optimal bar location, and all optimal
locations.

## Implementation

This is a simple sliding window problem, so we first need to sort the
coordinates. A valid location is one where the two outer parasols are less than
200 meter apart, i.e. `coord[j] - coord[i] <= 200`. Thus, if the next parasol no
longer makes it valid, we have to add one to `i`. If it the location is valid,
we check whether it contains more than the maximum amount of parasols, etc.

## Times

```
Test set 1 (20 pts / 1 s) : Correct answer      (0.001s)
Test set 2 (20 pts / 1 s) : Correct answer      (0.002s)
Test set 3 (60 pts / 1 s) : Correct answer      (0.392s)
```
