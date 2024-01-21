# Rumpelstilzchen

```
type: min cost max flow
runtime: O((n + pG + pH)^3)
```

## Problem

We have `n` islands, `pG` cities in city G, `pH` cities in city H. There are
edges between the islands and the two cities and within the cities and islands.
Each island can spin one yarn using 1 material from each of the cities. Each
island also has a preference score. How much yarn can Rumpelstilzchen spin? And
what is the maximum preference score if he spins yarn maximally?

## Implementation

This is a min cut max flow problem. The key insight of this problem is that the
flow from source to target is the same as the flow from target to flow if you
reverse the edge directions. Thus, if we flip the edges in graph H, and set the
source to be castle G and target to be castle H, then we get the maximum
combined flow to the islands. Now, each island can only spin one yarn, thus we
add vertex capacities with 1 capacity and cost equal to the preference score.
Then, just compute the flow and min cost (set costs to be negative of
preference score to maximize).

## Times

```
Test set 1        (20 pts / 1 s) : Correct answer      (0.143s)
Test set 2        (20 pts / 1 s) : Correct answer      (0.015s)
Test set 3        (20 pts / 1 s) : Correct answer      (0.213s)
Test set 4        (20 pts / 1 s) : Correct answer      (0.18s)
Hidden test set 1 (05 pts / 1 s) : Correct answer      (0.143s)
Hidden test set 2 (05 pts / 1 s) : Correct answer      (0.017s)
Hidden test set 3 (05 pts / 1 s) : Correct answer      (0.193s)
Hidden test set 4 (05 pts / 1 s) : Correct answer      (0.171s)
```
