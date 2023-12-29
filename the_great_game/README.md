# The Great Game

```
type: dynamic programming
runtime: O(n^2)
```

## Problem

In this problem, Holmes plays against Moriarty. There are two _meeples_ (red and
black) on the board (defined by given transitions), where they alternate in
making moves. Holmes starts by moving the red meeple, then Moriarty moves the
black one, Holmes moves the black one, Moriarty moves the red one, etc. Thus,
they alternate in moving a meeple, and alternate in which color they move.
Holmes wins if the red meeple reaches position `n` first, and Moriarty wins if
the black meeple reaches position `n` first. The problem is to determine who has
a strategy that wins no matter what.

## Implementation

The key insight of this problem is that the two meeples play the game in
parallel, they do not influence each other. Thus, the idea of the algorithm is
to run a minimax algorithm on the board.

For the red meeple, Holmes tries to minimize the amount of steps to `n`, while
Moriarty tries to maximize it. Vice versa for the red meeple. Thus, if we can
find the minimum amount of steps given that they both play optimally to `n` from
any of the positions, we can figure out who can get to `n` first.

Thus, `mini` tries to minimize the amount of steps, assuming that `maxi` plays
optimally, and `maxi` tries to maximize the amount of steps, assuming that
`mini` plays optimally, giving the following recurrence function,
```
mini[i] = min(maxi[neighbor 1], ..., maxi[neighbor m]) + 1
maxi[i] = max(mini[neighbor 1], ..., mini[neighbor m]) + 1
```
Make sure to do this in reverse order, `n-1, ..., 1`, and the base case is
`mini[n] = 0, maxi[n] = 0`.

The minimum amount of steps that red needs to get to `n` is then `mini[red start
pos]`, and `mini[black start pos]` for black.

If red needs strictly less steps than black, Holmes automatically wins, and vice
versa for Moriarty to win. If they are equal, Sherlock wins if the amount of
steps is odd, otherwise Moriarty wins. This is because Sherlock starts with
moving red once, and then black gets to move twice.

## Times

```
Test set 1 (25 pts / 3.500 s) : Correct answer      (0.0s)
Test set 2 (25 pts / 3.500 s) : Correct answer      (0.001s)
Test set 3 (25 pts / 3.500 s) : Correct answer      (0.035s)
Test set 4 (25 pts / 3.500 s) : Correct answer      (2.473s)
```
