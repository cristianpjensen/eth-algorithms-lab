# Inball

```
type: linear programming
runtime: O(max(n, d))
```

## Problem

In this problem, we have `n` lines in `d`-dimensional space that define a cave.
What is the largest ball that fits within this cave?

## Implementation

This is a linear programming problem. The ball is defined by a center and a
radius. We need to make sure that the entire ball fits into the cave, thus we
need to make sure that the center is within the cave and that the distance from
the center to any of the lines is greater than or equal to the radius.

So, to make sure that the center is within the cave, we need to satisfy the
following constraint for every line: $\vec{a}_i^\top \vec{x} \leq b_i$. To make
sure that the radius is less than the distance to every line, we need to
satisfy the following constraint: $r \leq \frac{|\vec{a}_i^\top \vec{x} -
b_i|}{\lVert \vec{a} \rVert}$. Since we have to satisfy $\vec{a}_i^\top \vec{x}
\leq b_i$, we know $|\vec{a}_i^\top \vec{x} - b_i| = b_i - \vec{a}_i^\top
\vec{x}$. So, we can simplify two constraints into a single constraint:
$\vec{a}_i^\top \vec{x} + \lVert \vec{a} \rVert r \leq b_i$.

Then, we solve the linear program by maximizing the radius.

## Times

```
Test set 1 (35 pts / 2 s) : Correct answer      (0.019s)
Test set 2 (35 pts / 2 s) : Correct answer      (0.196s)
Test set 3 (30 pts / 2 s) : Correct answer      (1.779s)
```
