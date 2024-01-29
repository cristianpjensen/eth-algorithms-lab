# Asterix and the Roman Legions

```
type: linear programming
runtime: O(n)
```

## Problem

We have `n` legion lines and an initial position `(xs, ys)`. Each legion has an
associated speed. If we start a fire, someone from the legion will run directly
from its line to the chosen position at its associated speed. We need to find
the position such that the time till someone from a legion gets to it is
maximized. What is the maximum time? We are not allowed to cross any lines to
get to the final position.

## Implementation

This is a linear program where the variables are the new position `(X, Y)` and
minimum time `t_{\min}`. We need to make sure that the new position is on the same
side of all the lines as the initial position. We also need to make sure that
`t_{\min}` does not exceed any of the times that the line takes to get to `(X, Y)`. We
can do this with one constraint per line. Namely, we need the signed distance to
keep the same sign (and `t_{\min} >= 0`), and make sure that `t_{\min}` does not exceed
`|dist| / v`.

$$
t_{\min} \leq \frac{|dist([X,Y], \ell_i)|}{v}
$$

## Times

```
Test set 1 (25 pts / 3 s) : Correct answer      (0.038s)
Test set 2 (25 pts / 3 s) : Correct answer      (0.106s)
Test set 3 (25 pts / 3 s) : Correct answer      (1.473s)
Test set 4 (25 pts / 3 s) : Correct answer      (1.651s)
```
