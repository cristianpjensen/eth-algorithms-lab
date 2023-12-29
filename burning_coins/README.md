# Burning Coins

```
type: dynamic programming
runtime: O(n^2)
```

## Problem

In this game, we play against another player. We try to maximize the value,
while the other tries to minimize the value. There is a deque, where each player
can take a coin from either the front or back. We start.

## Implementation

This is a simple dynamic programming minimax algorithm. We keep track of two
values, `left` and `right`, which define our state space. If it is maxi's turn,
the value is the maximum of the two possible actions. We add the value of the
picked coin. If it is mini's turn, we minimize the value of the two possible
actions, and do not add the value of the coin.

The base case is when there is one more coin to pick, i.e. `left == right`.
Then, we return the value of the coin if it is maxi's turn, otherwise return 0.

 - State space: Coins taken from each side, defined by `left, right`.
 - Recurrence relationship: If maxi: `rec(left, right) = max(rec(left+1, right) value[left], rec(left, right-1) + value[right])`, if mini: `rec(left, right) = min(rec(left+1, right), rec(left, right-1))`.
 - Base case: If maxi: `rec(x, x) = value[x]`, if mini: `rec(x, x) = 0`.

## Times

```
Test set 1 (30 pts / 2 s) : Correct answer      (0.0s)
Test set 2 (40 pts / 2 s) : Correct answer      (0.022s)
Test set 3 (30 pts / 2 s) : Correct answer      (0.66s)
```
