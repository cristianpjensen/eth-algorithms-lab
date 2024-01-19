# Asterix and the Chariot Race

```
type: dfs
runtime: O(n)
```

## Problem

We have `n` vertices with `n-1` edges (i.e., a tree). Each vertex has an
associated cost for repairing it. A vertex is considered saved if it is
repaired or one of its connected vertices is repaired. What is the minimum
cost for saving all the vertices?

## Implementation

Each vertex can be seen as a subtree with the same problem statement. We need
to compute the following values for each subtree, which we can use for a
recurrence relationship:
 - $a$: Minimum cost such that the root is repaired.
 - $b$: Minimum cost such that the root is saved.
 - $c$: Minimum cost such that the children of the root are saved.

We then have the following recurrence relationship,

$$
\begin{align\*}
    a_u &= \text{cost}(u) + \sum_{v\in\text{children}(u)} c_v \\
    b_u &= \min \left\\{ a_u, \min_{v\in\text{children}(u)} a_v + \sum_{v'\neq v} b_{v'} \right\\} \\
    c_u &= \min \left\\{ b_u, \sum_{v\in\text{children}(u)} b_v \right\\}
.\end{align\*}
$$ 

(Draw a tree and you can easily confirm the above equations.)

Then, just output the $b_0$.

## Times

```
Test set 1 (25 pts / 3 s) : Correct answer      (0.084s)
Test set 2 (25 pts / 3 s) : Correct answer      (0.091s)
Test set 3 (25 pts / 3 s) : Correct answer      (0.09s)
Test set 4 (25 pts / 3 s) : Correct answer      (1.364s)
```
