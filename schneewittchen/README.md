# Schneewittchen

```
type: dfs, linear programming
runtime: O(n*m)
```

## Problem

We have a tree graph of `n` mines and each have some amount of `m` materials.
There are some "dangerous" mines through which only some amount of materials can
go through, and everything halves when it goes through a dangerous mine. We need
some specific amount of each material, is this possible? If necessary, there is
also a shop that sells the materials with some supply and price. What is the
minimum amount we need to spend at the shop if it is possible?

## Implementation

This was quite a hard problem, because it is not obviously a linear programming
problem (because there is a recurrence relationship between the vertices, which
lead me to think it was a dynamic programming problem). A key insight is also
that only the dangerous mines matter, because anything after it that comes before
a dangerous mine can be taken for free to the dangerous mine. Thus, we first have
to compute how much material can be taken to each dangerous mine. Furthermore, we
also need to construct a danger graph (graph with all non-dangerous mines removed)
so we can use the recurrence relationship in the linear program.

The variables of the linear program are the amount of materials that we take
through a dangerous mine (and the root). We first need to upper bound the amount
that is taken through the mines by the danger level,

$$
\forall i\in\text{dangerous mines} : \sum_{j=1}^m x_{ij} \leq d_i.
$$

Then, we need to make sure that the amount of material that goes through a
dangerous mine is less than what we can take from its children that are not
dangerous and dangerous children

$$
\forall i,j : x_{ij} \leq v_{ij} + \frac{1}{2} \sum_{i' \in \text{dangerous children(i)}} x_{i'j},
$$

where $v_{ij}$ is the amount of material $j$ we can get through mine $i$ for free.
This can be rederived to the following constraint,

$$
\forall i,j : 2x_{ij} - \sum_{i'} x_{i'j} \leq v_{ij}.
$$

We also need to add this constraint to the root.

Now, we need to constrain the materials in the root such that whatever is left
from what is required is less than the supply,

$$
\forall j : \text{required}(j) - x_{0j} \leq \text{supply}(j).
$$

Lastly, we want to minimize the price we pay,

$$
\sum_j (\text{required}(j) - x_{0j}) \cdot \text{price}(j),
$$

which can be rederived to the following,

$$
\sum_j \text{required}(j) \cdot \text{price}(j) - \sum_j \text{price}(j) \cdot x_{0j}.
$$

Then, just solve the linear program.

## Times

```
Test set 1        (20 pts / 1 s) : Correct answer      (0.032s)
Test set 2        (15 pts / 1 s) : Correct answer      (0.1s)
Test set 3        (20 pts / 1 s) : Correct answer      (0.063s)
Test set 4        (15 pts / 1 s) : Correct answer      (0.089s)
Test set 5        (10 pts / 1 s) : Correct answer      (0.12s)
Hidden test set 2 (05 pts / 1 s) : Correct answer      (0.113s)
Hidden test set 3 (05 pts / 1 s) : Correct answer      (0.138s)
Hidden test set 4 (05 pts / 1 s) : Correct answer      (0.164s)
Hidden test set 5 (05 pts / 1 s) : Correct answer      (0.153s)
```
