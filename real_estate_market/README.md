# Real Estate Market

```
type: min cost max flow
runtime: 
```

## Problem

We have `N` bidders that all bid on the same `M` properties. These properties
are within `S` states, where each state has rules on how many properties may be
sold there. Each bidder may only purchase one property. How many properties can
we sell, and how much can we sell them for maximally?

## Implementation

This is an easy max flow problem. We first map the source to all bidders such
that each can only buy 1 property. We then map the bidders to the properties
with a flow of 1 and the cost being the negative of their bid (i.e., we want to
maximize the total sale price). Then, we map the properties to their state, and
the state to the sink with a flow equal to how many properties may be sold
there.

## Times

```
Test set 1 (20 pts / 1 s) : Correct answer      (0.011s)
Test set 2 (20 pts / 1 s) : Correct answer      (0.018s)
Test set 3 (20 pts / 1 s) : Correct answer      (0.013s)
Test set 4 (20 pts / 1 s) : Correct answer      (0.015s)
Test set 5 (20 pts / 1 s) : Correct answer      (0.093s)
```
