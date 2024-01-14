# Canteen

```
type: min cost max flow
runtime: 
```

## Problem

In this problem, we have `n` days, on which there are each `a_i` menus that
cost `c_i` to produce. There are also `s_i` students and the price of a menu is
`p_i`. Furthermore, we between day `i` and `i+1`, we can store `v_i` menus in
the freezer at a cost of `e_i`. Can we feed all students? How many students can
we maximally feed? What would be the profit/loss of feeding as many students as
possible?

## Implementation

This is an easy min cost max flow problem for getting familiar with the syntax.
Each day is represented as a vertex, and we add an edge from the source to a
day, where the capacity is the amount of menus and the cost the menu production
cost. Then, we connect each day to the target, where the capacity is the amount
of students that want a meal, with the cost being the negative of the price of
a single meal. Then, we add between days an edge with capacity of how many
meals we can store and much it costs as the cost. Then, just compute maximum
flow and minimum cost.

To make it faster, we need to make sure the costs are nonnegative, so just set
the price of a meal to `MAX-p_i`, where `MAX` is set to 20 in the problem
statement. Then, we need to remove this cost after computing cost.

## Times

```
Test set 1 (30 pts / 2 s) : Correct answer      (1.276s)
Test set 2 (50 pts / 2 s) : Correct answer      (0.153s)
Test set 3 (20 pts / 2 s) : Correct answer      (1.614s)
```
