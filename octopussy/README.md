# Octopussy

```
type: greedy, dfs
runtime: O(n)
```

## Problem

We have a full and complete binary tree of `n` bombs, each with a different
times until they explode. Defusing a bomb takes 1 minute. A bomb may only be
defused if its children have been defused. Is it possible to defuse all the
bombs?

## Implementation

For this problem, we take a greedy approach. We always want to be working
toward the undefused bomb with the least amount of time until it explodes. So,
we sort the bombs according to their times. Then, we defuse all of its
descendants (with DFS), and compute how long that would take and add it to the
timer. If the timer is beyond the time of the current bomb, the bomb explodes.

## Times

```
Test set 1        (20 pts / 1 s) : Correct answer      (0.0s)
Test set 2        (20 pts / 1 s) : Correct answer      (0.006s)
Test set 3        (20 pts / 1 s) : Correct answer      (0.015s)
Test set 4        (20 pts / 1 s) : Correct answer      (0.139s)
Hidden test set 1 (05 pts / 1 s) : Correct answer      (0.0s)
Hidden test set 2 (05 pts / 1 s) : Correct answer      (0.006s)
Hidden test set 3 (05 pts / 1 s) : Correct answer      (0.015s)
Hidden test set 4 (05 pts / 1 s) : Correct answer      (0.139s)
```
