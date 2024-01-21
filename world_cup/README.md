# World Cup

```
type: linear programming
runtime: O(n*m + n*c + m*c)
```

## Problem

We have `n` warehouses with a supply of beer with an alcohol percentage, at some
location. The amount of beer outgoing from the warehouses may not be greater than
their supply. We have `m` stadia with a demand of beer at some location. Each
stadia has an upper bound on how much pure alcohol may be served. The demand must
be met exactly. With each stadium and warehouse is also a revenue per liter of
beer.

Furthermore, we have contour lines in the shape of circles. If a truck has to go
over it between warehouse and stadium, a penalty of 0.01 CHF per liter is
incurred.

What is the maximum amount of total revenue?

## Implementation

The first two test sets are not hard at all. We just need to set up a linear
program that has the constraints as specified. The variables are $a_{w,s}$, which
is the amount of beer transported from warehouse $w$ to stadium $s$. The
constraints are easy to find from there.

The hard part is the contour lines. The key insight is that we only have to go
over a contour line if only one of the warehouse or stadium is within a circle
and not the other, because then we have to travel over the line to get to the
other circle. Thus, we just need to precompute within which circle each warehouse
and stadium is. Then, compute the size of the union minus intersection set. This
is the penalty per liter of beer between these two locations.

Finally, just solve the linear program and output the solution as specified.

## Times

```
Test set 1 (25 pts / 4 s) : Correct answer      (0.094s)
Test set 2 (25 pts / 4 s) : Correct answer      (0.243s)
Test set 3 (25 pts / 4 s) : Correct answer      (0.258s)
Test set 4 (25 pts / 4 s) : Correct answer      (1.419s)
```
