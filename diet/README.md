# Diet

```
type: linear programming
runtime: O(n*m)
```

## Problem

We have `m` foods that consist of an amount of calories and any amount of `n`
different nutrients. We have requirements for how many calories and nutrients a
diet must consist of. Each food also has a price. Is it possible to make such a
diet, and if so, what is its cheapest price?

## Implementation

This is a very easy linear programming problem, where we set constraints based on
the requirements and minimize the price. The amount of each food we take are the
variables.

## Times

```
Test set 1 (35 pts / 0.200 s) : Correct answer      (0.001s)
Test set 2 (35 pts / 0.200 s) : Correct answer      (0.005s)
Test set 3 (30 pts / 0.200 s) : Correct answer      (0.07s)
```
