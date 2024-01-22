# DHL

```
type: dynamic programming
runtime: O(n^3)
```

## Problem

We have `n` parcels on two stacks A and B. Picking up parcel $k$ from A and B
has $a_k$ and $b_k$ cost, respectively. Every iteration, we have to pick at least
one from each stack (we can only access from the top). The cost of an iteration
is then $(S_a - k_a) \cdot (S_b - k_b)$, where $S_a$ and $S_b$ are the sum of
costs of the picked up parcels of A and B, and $k_a$ and $k_b$ are the amount of
parcels picked up from the two stacks. What is the minimum sum of cost such that
all parcels are picked up?

## Implementation

This is an obvious dynamic programming problem, where the state is how many
parcels are left on the stacks, and the value the minimum cost. The recurrence
is obvious,

$$
(S_a - k_a) \cdot (S_b - k_b) + cost(|A| - k_a, |B| - k_b)
$$

Naively computing all values would result in `O(n^4)` complexity (which is good
enough for the first two test sets). To make it more efficient, we have to make
a key insight: we should always pick at most 1 from A or at most 1 from B.
Then, the cost is added additively, instead of multiplicatively. Then, we can
optimize it to `O(n^3)`. (Also, to easily compute $S_a$ and $S_b$ in `O(1))`,
we store a cumulative sum of their values.)

The last set probably requires finding the best distribution of (a,b) on the
most inner loop in `log n`. There's probably some monotonous ordering, but the
last test set only gives 1 point.

## Times

```
Test set 1 (20 pts / 1 s) : Correct answer      (0.0s)
Test set 2 (40 pts / 1 s) : Correct answer      (0.006s)
Test set 3 (39 pts / 1 s) : Correct answer      (0.177s)
Test set 4 (01 pts / 1 s) : Time limit exceeded
```
