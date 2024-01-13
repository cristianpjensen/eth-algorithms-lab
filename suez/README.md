# Suez

```
type: linear programming
runtime: O(n*m + n^2)
```

## Problem

We have `n` centers where we want to place pictures, and there are `m` centers
where we have already placed pictures. The pictures are `w` by `h`, but the new
pictures can be magnified by some value `a >= 1`, individually. What is the
maximum attainable perimeter of the new pictures?

## Implementation

This is an obvious linear programming problem. The variables are the
magnification values for each new picture, lower bounded by 1 (30 variables). We
now need to add constraints such that none of the new pictures overlap. Only the
axis with the biggest difference matters for this. So, we need to make sure that
the sum of their new widths and heights are less than their distance on this axis.
Let's say that the biggest difference is on the x-axis, then we have the following
inequality that needs to be satisfied:
$\frac{a_i w}{2} + \frac{a_j w}{2} \leq |x_i - x_j|$, which simplifies to 
$a_i + a_j \leq \frac{2|x_i - x_j|}{w}$. Thus, that is the constraint that we
need to add.

Now, we also need to make sure the new pictures do not overlap with the old
pictures, which are all fixed at `w` by `h`. For each new picture `i` and old
picture `j`, we need the following inequality to be satisfied:
$\frac{a_iw}{2} + \frac{w}{2} \leq |x_i - x_j|$ (in the case that the biggest axis
difference is the x-axis), which simplifies to $a_i \leq \frac{2|x_i-x_j|}{w} - 1$.
This needs to be satisfied for all old pictures, but only the one with the
smallest $\frac{2|x_i-x_j|}{w} - 1$ matters (because if that is satisfied, all of
them are), so we only add that constraint.

Then, we maximize the total perimeter, which is computed as $a_i * 2 * (h + w)$.

## Times

```
Test set 1 (25 pts / 1.500 s) : Correct answer      (0.139s)
Test set 2 (25 pts / 1.500 s) : Correct answer      (0.4s)
Test set 3 (25 pts / 1.500 s) : Correct answer      (0.687s)
Test set 4 (25 pts / 1.500 s) : Correct answer      (0.764s)
```
