# Severus Snape

```
type: dynamic programming, greedy
runtime: O(n^2 * H + m log m + n * m)
```

## Problem

In this problem, we have three values that we care about: power, happiness, and
wit. We need at least `P` power, at least `H` happiness, and at least `W` wit.
We have A potions that increase power and happiness by some value and decrease
wit by `a`. We have B potions that increase wit and decrease power by `b`. What
are the minimum amount of potions that we need to satisfy the power, happiness,
and wit requirements?

## Implementation

For this problem, to compute how much wit we need from the B potions, we first
need to know how many A potions we picked. But, we also need to know how much
power we have, so we know how many B potions we are allowed to pick. The only
thing that cannot decrease is the happiness, so we want to know what the
maximum attainable power is, given a fixed amount of A potions and that the
happiness of those A potions sums to at least `H`. We can do this with dynamic
programming with the following state space:
 - `j`: Amount of A potions picked;
 - `h`: Minimum amount of happiness.
And, the value is the maximum amount of power. The recurrence relationship is
then that we take the maximum of all possible sequences that result in `j`
potions picked and `h` happiness, i.e., $P_{j,h} = \max_{(p',h') \in
\text{Potions A}} P_{j-1,h-h'} + p'$.

Then, for every `j` A potions that results in at least `H` happiness and has a
maximum of `p` power, we find out whether it is possible to pick `(p - P) / b`
(edge case: b = 0, then we can pick as many as we want) B potions such that the
wit is `W + j*a`. We do this greedily.

## Times

```
Test set 1 (30 pts / 5.500 s) : Correct answer      (0.187s)
Test set 2 (30 pts / 5.500 s) : Correct answer      (0.254s)
Test set 3 (20 pts / 5.500 s) : Correct answer      (0.261s)
Test set 4 (20 pts / 5.500 s) : Correct answer      (0.246s)
```
