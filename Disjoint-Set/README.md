# DisjointSet

DisjointSet is a data structure that keeps track of a set of elements partitioned into a number of disjoint (non-overlapping) subsets. It provides operations for merging sets and finding the representative element of a set.

## Brief
DisjointSet is used to efficiently manage a partition of a set into disjoint subsets. It is commonly used in algorithms that involve finding connected components in a graph.

## :hourglass: Complexity

| Operation     | Average       | Worst case   |
| ------------- | ------------- | ------------ |
| Space         | **O(n)**      | **O(n)**     |
| MakeSet(x)    | **O(1)**      | **O(1)**     |
| Find(x)       | **O(α(n))**   | **O(α(n))**  |
| Union(x, y)   | **O(α(n))**   | **O(α(n))**  |

Where `α(n)` is the inverse Ackermann function, which grows very slowly and is practically constant for any feasible value of `n`.

## Operations

1. `DisjointSet()` - creates a new empty disjoint set.
2. `makeSet(x)` - creates a new set containing the element `x`.
3. `find(x)` - returns the representative element of the set that contains `x`.
4. `Union(x, y)` - merges the sets containing elements `x` and `y` into a single set. 