# Tiles

```
type: flow
runtime: O((h*w)^3)
```

## Problem

In this problem, we have a rectangular layout of width `w` and height `h`. Some
squares need to be tiled, and some do not. We only have 1x2 tiles. Can the
layout be tiled?

## Implementation

This is an easy max flow problem. Consider a chess board with the white and
black squares. We connect the source to the white squares (that need to tiled),
and the black squares (that need to be tiled) to the target. Then, we connect
all white squares to its neighboring black squares (only the ones that need to
be tiled). Then, run max flow on this and check whether the flow is equal to
the amount of tiles needed.

Intuition of model: If we go from source to target through white tile $x$ and
black tile $y$, then it is locked in. No other white tile can go through the
black tile, and no other black tile can go through the white tile. So, that
means we lay a 1x2 tile over $x$ and $y$. Now, we try to maximize the amount of
flow from source to target, i.e., we maximize the amount of tiles we lay. If
the maximum amount of tiles we can lay is not equal to the amount of tiles that
would be required to cover $n$ squares, it is not possible to tile the layout
fully.

## Times

```
Test set 1 (40 pts / 0.200 s) : Correct answer      (0.001s)
Test set 2 (30 pts / 0.200 s) : Correct answer      (0.012s)
Test set 3 (20 pts / 0.200 s) : Correct answer      (0.04s)
Test set 4 (10 pts / 0.200 s) : Correct answer      (0.003s)
```
