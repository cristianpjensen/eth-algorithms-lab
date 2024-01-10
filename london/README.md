# London

```
type: flow
runtime: technically O(1), but actually O(n^3), where n = 26 + 26^2
```

## Problem

In this problem, we have a note and cutouts with a front and backside. Can the
note be constructed from the cutouts?

## Implementation

This is a max flow problem. We construct the graph such that the note letters
can use a cutout by flowing to it. We connect the source to all the note letter
vertices with the capacity set to however many of those letters we need. Then,
we connect all the note letters to the cutouts that contain that letter with
the capacity set to how many letters we need. So, we have 26 vertices for all
the note letters, and 26^2 vertices for all the possible cutouts. Then, we
connect the cutouts to the target with how many of those cutouts we have.

Intuitively, a note letter is made by a cutout if there is flow between them,
constraining that cutout to no longer be used by another letter.

## Times

```
Test set 1 (10 pts / 2 s) : Correct answer      (0.022s)
Test set 2 (10 pts / 2 s) : Correct answer      (0.023s)
Test set 3 (20 pts / 2 s) : Correct answer      (0.025s)
Test set 4 (20 pts / 2 s) : Correct answer      (0.029s)
Test set 5 (40 pts / 2 s) : Correct answer      (0.194s)
```
