# San Francisco

```
type: dynamic programming
runtime: O(n*k)
```

## Problem

We play a game with `n` vertices and `m` directed edges. When taking an edge,
we get some score. If there are no more edges we can take, we go back to the
beginning. We can play `k` moves, can we get more than score `x`? And, what is
the minimum amount of moves, less than `k`, that we can get a higher score than
`x`?

## Implementation

This is a pretty easy dynamic programming problem (just make sure that you use
`long` where needed). The table has state space `(amount of moves left, current
vertex)`, then we DFS through all children and maximize the score. The base
case is when `k=0`. The only special case is when there are no more children,
then just go to the start and leave the amount of steps left the same.

Then, you just iterate over the amount of moves `1 ... k` and compute the
maximum score. If maximum score is greater than `x`, return the amount of moves
and early terminate. Otherwise, return `Impossible`.

## Times

```
Test set 1 (30 pts / 4 s) : Correct answer      (0.003s)
Test set 2 (30 pts / 4 s) : Correct answer      (0.057s)
Test set 3 (40 pts / 4 s) : Correct answer      (1.804s)
```
