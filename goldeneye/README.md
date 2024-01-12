# GoldenEye

```
type: triangulation, kruskal
runtime: O(m + n log n)
```

## Problem

In this problem, we have `n` jammers at certain locations, `m` missions, and
`p` power that the jammers have. The power decides how far the jammers jam.
Given power `p`, which missions can be executed? What is the minimum power such
that all missions can be executed? What is the minimum power such that all the
same missions as in the first question can be executed?

## Implementation

This problem makes use of triangulation and a modified version of Kruskal's
algorithm. We first compute the triangulation, such that we can compute the
EMST quickly. But, we do not need the whole EMST, we only want to add the edges
that require less than or equal to `p` power. Then, when we want to check
whether a mission is possible, we check whether they start and end under the
jammer umbrella, and also check whether the closest vertices to the start and
end are in the same set from the union-find from Kruskal's algorithm. That
answers the first question.

The second question involves finding the minimum power for all missions. For
this, we can again use Kruskal's. We iterate over all missions and add the
edges such that each mission becomes possible using Kruskal's union-find
datastructure. We need to keep track of what the power is that is necessary for
these edges.

For the last question, we do the same as for the second, but then only iterate
over the missions that were possible with `p` power.

## Times

```
Test set 1 (25 pts / 2 s) : Correct answer      (0.022s)
Test set 2 (25 pts / 2 s) : Correct answer      (0.054s)
Test set 3 (25 pts / 3 s) : Correct answer      (0.091s)
Test set 4 (25 pts / 3 s) : Correct answer      (0.591s)
```

Note that this could be twice as fast by computing all the values at once and
iterating only over the missions once. But, this way it is more clear how the
solution works.
