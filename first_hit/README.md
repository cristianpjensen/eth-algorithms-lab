# First Hit

```
type: geometry
runtime: O(n)
```

## Problem

In this problem, we have a ray and many segments. We need to figure out whether
the ray hits a segment and, if it hits, figure out where it hits a segment
first.

## Implementation

The naive way of implementing this is to just check for every segment whether
it intersects and then checking with the current closest point which is closer.
However, this introduces an unnecessary amount of intersection computations. If
we already know some point where it hit, we can make sure we do not check for
further intersections if we keep track of a segment from the origin to the
current closest hit point. Then, we only need to check whether this hit segment
intersects with the next segment.

Now we only need to differentiate between two types of intersections:
 1. Intersect in some point: Just set the end point of the hit segment to be
    this point;
 2. Intersect over the entire segment, i.e., the two segments overlap: Set the
    end point of the hit segment to be the closest of the two end points.

Then, we can simply output the end point of the hit segment.

In the worst case, the segments are in descending order in their distance to
the origin (which is the case for the last two test sets). The above assumes
that the segments are in random order. So, before iterating over the segments,
randomly shuffle them.

## Times

```
Test set 1 (15 pts / 1.000 s) : Correct answer      (0.007s)
Test set 2 (15 pts / 1.000 s) : Correct answer      (0.063s)
Test set 3 (15 pts / 1.000 s) : Correct answer      (0.076s)
Test set 4 (15 pts / 1.000 s) : Correct answer      (0.061s)
Test set 5 (10 pts / 1.000 s) : Correct answer      (0.186s)
Test set 6 (10 pts / 1.000 s) : Correct answer      (0.067s)
Test set 7 (10 pts / 1.000 s) : Correct answer      (0.06s)
Test set 8 (10 pts / 0.200 s) : Correct answer      (0.06s)
```
