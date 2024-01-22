# The Augean Stables

```
type: linear programming, binary search
runtime: O(48^2 * log 48 * n)
```

## Problem

We have `n` stalls with some filth and some value that it must be to be
considered clean. We can open some holes $h_1, h_2, h_3$ to let water get
through that positively or negatively impacts the cleanliness per stall.
Furthermore, we can dig for 2 rivers to get water to the stalls, which makes
the stalls cleaner by some amount. For every hour we work some predetermined
amount of more water flows through $a_{0:24},p_{0:24}$. We can work at most 24
hours on each river. The amount of filth removed from the $i$-th stall is 

$$
(k_i + a^2) h_1 + (\ell_i + p^2) h_2 + (m_i + ap) h_3
$$

What is the minimum amount of hours we need to work to
consider every stall clean.

## Implementation

If we do not consider the rivers, this is an easy linear programming problem
with only three variables $h_1, h_2, h_3$, and one constraint per stall,

$$
f_i - ((k_i + a^2) h_1 + (\ell_i + p^2) h_2 + (m_i + ap) h_3) \leq c_i
$$

But, we need to know how many hours we need to work. If we work more hours, the
stalls will be cleaner, thus there is a monotonous relationship. So, we use
binary search over the number of hours worked. Then, for each number of hours, we
compute for every combination `(a,p)` if it is clean enough. Do this until the
minimum number of hours is found.

## Times

```
Test set 1 (30 pts / 1 s) : Correct answer      (0.021s)
Test set 2 (30 pts / 1 s) : Correct answer      (0.019s)
Test set 3 (25 pts / 1 s) : Correct answer      (0.077s)
Test set 4 (15 pts / 1 s) : Correct answer      (0.114s)
```
