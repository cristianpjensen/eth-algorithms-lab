# Moving Books

```
type: greedy
runtime: O(n*m log m)
```

## Problem

In this problem, we have a set of `n` books, each with a weight. We also have a
set of `m` people, each with a strength. Bringing a book to the car takes 2
minutes, and going back takes 1 minute. What is the minimum amount of time we
need to bring all books to the car?

Assume that the friends can use the stair at the same time without
interference.

## Implementation

This is an easy greedy problem. Each iteration, every person greedily picks the
heaviest book they can carry. We model the people as a sorted list of their
strengths. We model the books as a `multiset`, from which we can remove the
books as they are "brought to the car". The multiset also makes it easy to find
the heaviest book a person can carry with `multiset.lower_bound()`. Then, we
just count the amount of iterations that all people have brought books to the
car, and compute the amount of time from there.

## Times

```
Test set 1 (20 pts / 1.500 s) : Correct answer      (0.008s)
Test set 2 (40 pts / 1.500 s) : Correct answer      (0.533s)
Test set 3 (40 pts / 1.500 s) : Correct answer      (0.934s)
```
