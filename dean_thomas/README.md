# Dean Thomas

```
type: triangulation
runtime: O(n log n + m log n)
```

## Problem

We have `n` dementors that are always within `d` (global value) range of their
point. We also have `m` wizards that need to escape the dementors. The wizards
can be at most `s` (individual value) from any point a dementor may be. At night
`d` and `s` double. The wizards can move during the day as long as they stay `s+d`
away from any dementor location. They need to move to a point such that they can
stay there during the night when they have to be `2*(s+d)` away. For each wizard,
figure out whether they can stay at a safe distance from the dementors.

## Implementation

The first test case is easy. Just do a triangulation of the dementor locations
and check whether the wizard can stay there during the night. The next two are
also not hard (they are very similar to H1N1). We need to figure out what the
largest radius is that can escape from a location. A wizard is in some face, and
we need to figure out whether the wizard can escape to an infinite face. We can
move from a face to another face with a bottleneck of the distance of the edge.
We then need to find out what the path is such that the smallest edge is
maximized. We then precompute this bottleneck from any face to the infinite face
(i.e., outside of the convex hull) by using a modified version of Dijkstra's
algorithm.

The last test set adds some complexity where we also need to consider larger
faces that we might be able to reach, rather than getting outside the convex
hull. We do this by adding the faces with their face size to the priority queue,
just as we add the infinite face to it (with its infinitely large face size). We
have to add the face size divided by 2 (which is just the radius), though, so it
is in the same scale as the edges. We can compute the radius of a face by
computing the distance of the dual point (furthest away from vertices that make
up face edges) to any of the vertices of the face.

## Times

```
Test set 1 (30 pts / 2 s) : Correct answer      (1.382s)
Test set 2 (30 pts / 2 s) : Correct answer      (0.657s)
Test set 3 (20 pts / 2 s) : Correct answer      (1.091s)
Test set 4 (20 pts / 2 s) : Correct answer      (1.42s)
```
