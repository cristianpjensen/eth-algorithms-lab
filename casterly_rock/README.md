# Casterly Rock

```
type: linear programming
runtime: O(n + m)
```

## Problem

We have `n` noble houses and `m` common houses. We need to find a sewer and fresh
water line that satisfy the following constraints:
 - The sewer line may not be horizontal and the fresh water line may not be
   vertical.
 - The noble houses must be on the left and the common houses must be on the right
   of the sewer line.
 - The total horizontal distance to the sewer line may not exceed `s`.
 - The fresh water line and the sewer line meet at a right angle.

We want to minimize the maximum vertical distance to the fresh water line. 

## Implementation

This is linear programming problem, where the lines are the variables, so we have
`a_sewer`, `b_sewer`, `c_sewer`, `a_water`, `b_water`, and `c_water` variables.
We need the sewer line to not be horizontal, so we set `a_sewer` to 1, because we
can still represent any line, because `a_sewer` and `b_sewer` are defined up to
scale, except for the line with `a_sewer = 0`, which is the horizontal one. For
the same reason, we constrain `b_water` to be 1.

For the second constraint, we need to make sure that the following holds for all
noble houses: $ax + by + c \leq 0$, and the following for all common houses:
$ax + by + c \geq 0$ for the sewer line.

For the third constraint, we need to make sure the total horizontal distance to
the sewer line does not exceed `s`. The point that is on the sewer line and the
same horizontal line as point $(x,y)$ is the following: $(-by-c, y)$ ($a=1$). So,
we need to satisfy the following constraint:

$$ \sum_{x,y} | x - (-by-c) | \leq s. $$

We know that all the noble houses are on the left and the common houses on the
right, thus the constraint becomes the following:

$$ \left( \sum_{x,y}^{\text{common}} x - (-by - c) \right) + \left( \sum_{x,y}^{\text{noble}} (-by-c) - x \right) \leq s. $$

This simplifies to the following linear programming constraint:

$$ (Y_c - Y_n) \cdot b + (m - n) \cdot c \leq s - (X_c - X_n), $$

where $Y_n$ is the sum of y coordinates of the nobles, $Y_c$ is the sum of y
coordinates of the commoners, $X_n$ is the sum of x coordinates of the nobles,
$X_c$ is the sum of x coordinates of the commoners.



For the fourth constraint, we need to make sure they meet at a right angle. We
know that $a_s = b_w = 1$, so we need the following constraint: $a_w = -b_s$, i.e.,
$a_w+b_s \geq 0$ and $a_w+b_w \leq 0$.

Now, we need to minimize the maximum vertical distance to the fresh water canal.
We represent this value as a variable $d$. This value must be greater than all
vertical distances to the fresh water canal. So, we get the following constraint
for all points: $|y-(-ax-c)| \leq d$. We do not know on which side the points are
w.r.t. the fresh water line, so we have to make sure it $d$ is greater than both
the negative and positive.

## Times

```
Test set 1        (20 pts / 2 s) : Correct answer      (0.069s)
Test set 2        (20 pts / 2 s) : Correct answer      (0.843s)
Test set 3        (20 pts / 2 s) : Correct answer      (0.24s)
Test set 4        (20 pts / 2 s) : Correct answer      (0.65s)
Hidden test set 1 (05 pts / 2 s) : Correct answer      (0.065s)
Hidden test set 2 (05 pts / 2 s) : Correct answer      (0.654s)
Hidden test set 3 (05 pts / 2 s) : Correct answer      (0.179s)
Hidden test set 4 (05 pts / 2 s) : Correct answer      (0.418s)
```
