# Interval Tree

![Interval-Tree](https://tutorialcup.com/wp-content/uploads/2020/05/IntervalTree1-4.png)

## Brief
An Interval Tree is a self-balancing binary search tree that stores a set of intervals and allows for fast interval overlap queries. Each node of the tree represents an interval, and the subtree of a node represents the intervals that overlap with the node's interval.

## :hourglass: Complexity

| Operation          | Average        | Worst case    |
| ------------------ | -------------- | ------------- |
| Space              | **O(n)**       | **O(n)**      |
| Search             | **O(log n)**   | **O(n)**      |
| Insertion          | **O(log n)**   | **O(n)**      |
| Deletion           | **O(log n)**   | **O(n)**      |

## Operations

1. `IntervalTree<type>()` - creates a new empty Interval Tree.
2. `InsertInterval(interval)` - inserts a new interval into the Interval Tree.
3. `DeleteInterval(interval)` - removes an existing interval from the Interval Tree.
4. `SearchInterval(interval)` - searches for all intervals that overlap with a specified interval.
5. `inorder()` - traverses the tree using an in-order algorithm.