# Important Bridges

```
type: graphs
runtime: O(n + m log m)
```

## Problem

We have `n` islands with `m` bridges that connect them. We need to find all
bridges such that if they were unusable, two islands would become inaccessible
from each other. We need to find all such bridges.

Output all the important bridges ordered lexicographically.

## Implementation

If a biconnected component contains only one edge, then this edge connects two
different biconnected components. Thus, if we remove this edge, at least two
islands will become disconnected. So, we only need to find all the biconnected
components with a single edge and output those.

## Times

```
Test set 1 (40 pts / 2 s) : Correct answer      (0.007s)
Test set 2 (40 pts / 2 s) : Correct answer      (0.512s)
Test set 3 (20 pts / 2 s) : Correct answer      (0.0s)
```
