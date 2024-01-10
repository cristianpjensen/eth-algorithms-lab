# Coin Tossing Tournament

```
type: flow
runtime: O((n+m)^3)
```

## Problem

In this problem, we have `n` players that play `m` coin tosses. For some
matches we know who won, and we get some scoreboard. Is this scoreboard
possible, given the match outcomes that we know?

## Implementation

This is a max flow solution, where each player and each match is represented by
a vertex. The match vertices can distribute a single point (because we only
give it 1 flow from the source) to its winner, and we need to know whether it
is possible for each player to achieve their final score. So, for each match,
if we know who won, we just distribute the point to the winner with an edge
with capacity 1. If we do not know who won, we add edges from the match vertex
to both of its players, so it is possible for both players to win, but only one
player can win, because there is only 1 flow through the match vertex. Then, we
add an edge from each player to the target with their final score.

To check whether the scoreboard is possible by checking whether the max flow
through this graph is equal to the amount of points distributed.

## Times

```
Test set 1 (40 pts / 1 s) : Correct answer      (0.009s)
Test set 2 (40 pts / 1 s) : Correct answer      (0.103s)
Test set 3 (20 pts / 1 s) : Correct answer      (0.259s)
```
