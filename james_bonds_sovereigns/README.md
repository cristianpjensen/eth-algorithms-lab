# James Bond's Sovereigns

```
type: dynamic programming
runtime: O(n^2)
```

## Problem

This problem is essentially just Burning Coins with more players. What is the
maximum value that player `k` is guaranteed to get if he plays optimally. There
are `n` coins and `m` players.

For this, we do minimax, where all players but `k` play as mini and player `k`
plays as maxi.

## Implementation

See Burning Coins, and then just do maxi whenever it is player `k`'s turn.

## Times

```
Test set 1        (20 pts / 2 s) : Correct answer      (0.458s)
Test set 2        (40 pts / 2 s) : Correct answer      (0.914s)
Test set 3        (20 pts / 2 s) : Correct answer      (1.365s)
Hidden test set 1 (05 pts / 2 s) : Correct answer      (0.458s)
Hidden test set 2 (10 pts / 2 s) : Correct answer      (0.914s)
Hidden test set 3 (05 pts / 2 s) : Correct answer      (1.365s)
```
