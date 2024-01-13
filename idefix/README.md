# Idefix

```
type: triangulation, kruskal
runtime: O((n + m) log(n + m))
```

## Problem

In this problem, we have `n` trees at various points and `m` bones at various
locations. Each tree has a shadow of radius `r` around it. How many bones can
we reach while staying under shadows if we are allowed to start anywhere? What
is the minimum radius such that we can reach `k` bones?

## Implementation

This is obviously a triangulation problem. Figuring out how many bones are
reachable with `r` is quite simple. We use a modified version of Kruskal's by
figuring out which trees are reachable from each other given `r`. Then, for
each component of trees that are all reachable from each other, compute how
many bones are reachable from them. This is quite simple if you start from the
EMST example code on Moodle.

The second question can be answered by using the previous solution. This is
possible by binary searching over `r` and finding the minimum radius that
satisfies more than or equal to `k` findable bones. BUT, this is only fast
enough for the first three test cases, because of the large space of possible
values for `r`.

The solution for all test cases involves another modified version of Kruskal's
algorithm. Now, we also add edges from bones to their closest trees. Then, we
iterate over the edges, and there are two cases:
 - tree-bone edge: Just add 1 to the amount of reachable bones from the
   component of the tree.
 - tree-tree edge: Link the 2 sets and add together the amount of reachable
   bones.
Then, when we find a component with more than `k` bones, we output the current
radius needed (which is the smallest, because the edges are sorted
ascendingly).

## Times

```
Test set 1        (20 pts / 1 s) : Correct answer      (0.018s)
Hidden test set 1 (05 pts / 1 s) : Correct answer      (0.018s)
Test set 2        (20 pts / 1 s) : Correct answer      (0.098s)
Hidden test set 2 (05 pts / 1 s) : Correct answer      (0.098s)
Test set 3        (20 pts / 1 s) : Correct answer      (0.028s)
Hidden test set 3 (05 pts / 1 s) : Correct answer      (0.028s)
Test set 4        (20 pts / 1 s) : Correct answer      (0.27s)
Hidden test set 4 (05 pts / 1 s) : Correct answer      (0.145s)
```
