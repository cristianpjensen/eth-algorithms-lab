# The Fighting Pits of Meereen

```
type: dynamic programming
runtime: O(n * k^m)
```

## Problem

We have `n` fighters in a queue that are one of `k` different fighters. We can
send each fighter either to the north or the south entrance. The total
excitement of a round is computed as `1000 * unique fighters in last m sent
through entrance - 2^{|p-q|}`, where `p` and `q` are the amount of fighters
sent through the two entrances. In none of the round, the excitement may be
negative. What is the total summed amount of excitement that can be achieved?

## Implementation

This is a dynamic programming problem, where the state space is
 - How many fighters have been seen;
 - The last `m` fighters sent through the north entrance;
 - The last `m` fighters sent through the south entrance;
 - The difference in amount of fighters sent through the two entrances `p-q`.

We then do a DFS with memoization where we send each fighter north and south
and compute the maximum summed excitement from there. Then, each time we add
the excitement of the current round. If this excitement is negative, make the
path invalid (just return the smallest possible integer).

## Times

```
Test set 1 (25 pts / 2 s) : Correct answer      (0.161s)
Test set 2 (25 pts / 2 s) : Correct answer      (0.229s)
Test set 3 (25 pts / 2 s) : Correct answer      (0.26s)
Test set 4 (25 pts / 2 s) : Correct answer      (1.255s)
```
