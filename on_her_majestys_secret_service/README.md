# On Her Majesty's Secret Service

```
type: graph, bipartite matching
runtime: O(a * n log n +  (a+c*s)^3 * log t_max)
```

## Problem

We have `n` positions, `m` (un)directed edges, `a` secret agents, `s` shelters,
`c` capacity per shelter, and `d` time to enter shelter. The edges can be taken
by any number of agents at once, but the shelters can only be accessed
one-by-one.

What is the minimum amount of time for every agent to get to safety?

## Implementation

We first need to know what the minimum time is for each (agent, shelter)
combination to get to safety. We will do this by running Dijkstra's for every
agent. We cannot use this to directly compute the minimum time, but given some
time, we can compute whether all agents can get to safety within that time.
Furthermore, this has a monotonous relationship, where more time => more agents
get to safety. So, we can binary search over time to find the minimum time to
get everyone to safety.

We can compute whether everyone can get to safety by bipartite matching. We add
an edge between all pairs of (agent, shelter) that can get to safety within the
time, i.e., if `min_time[agent][shelter] + d <= t`. Then, we check whether
there is a possible matching or not. If there is, everyone can get to safety.
Now, we also need to account for multiple spots being available per shelter. We
do this by simply by acting as if the new spot is another shelter and then only
adding the edge if `min_time[agent][shelter] + 2*d <= t`, i.e., if the agent can
wait on another agent to access the shelter.

## Times

```
Test set 1        (20 pts / 5 s) : Correct answer      (0.027s)
Test set 2        (20 pts / 5 s) : Correct answer      (0.072s)
Test set 3        (10 pts / 5 s) : Correct answer      (0.236s)
Test set 4        (10 pts / 5 s) : Correct answer      (0.145s)
Test set 5        (15 pts / 5 s) : Correct answer      (0.258s)
Hidden test set 1 (05 pts / 5 s) : Hidden
Hidden test set 2 (05 pts / 5 s) : Hidden
Hidden test set 3 (05 pts / 5 s) : Hidden
Hidden test set 4 (05 pts / 5 s) : Hidden
Hidden test set 5 (05 pts / 5 s) : Hidden
```
