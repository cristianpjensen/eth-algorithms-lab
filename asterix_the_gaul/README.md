# Asterix the Gaul

```
type: split and list, binary search
runtime: O(2^(n/2) * n * log m)
```

## Problem

In this problem, we have a distance `D` that we have to cross within a time
`T`. We have a certain amount of moves that cross some distance `d` and take
some time `t`. We also have potions that increase the distance of every move by
a constant value. What is the minimum amount of potions that we need to take to
cross the entire distance?

## Implementation

The potions monotonously increase the amount of distance per move. So, if we
can do it with `p` potions, then we can also do it with `q > p` potions. So, we
do binary search on the amount of potions, and find the smallest value for
which it is possible.

Now, we need to be able to check whether it is possible for some set amount of
potions. We do this with an augmented version of split and list. First, we
compute every possible half, like split and list. Then, for every right half
combination, we search for the left half combination with binary search.

## Times

```
Test set 1 (20 pts / 5 s) : Correct answer      (0.003s)
Test set 2 (20 pts / 5 s) : Correct answer      (0.013s)
Test set 3 (20 pts / 5 s) : Correct answer      (0.456s)
Test set 4 (40 pts / 5 s) : Correct answer      (2.537s)
```
