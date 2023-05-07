# B-tree

![B-tree](https://upload.wikimedia.org/wikipedia/commons/6/65/B-tree.svg)

## Brief
B-tree is a self-balancing tree data structure that keeps data sorted and allows searches, sequential access, insertions, and deletions in logarithmic time. 

## :hourglass: Complexity

| Operation     | Average       | Worst case   |
| ------------- | ------------- | ------------ |
| Space         | **O(n)**      | **O(n)**     |
| Search        | **O(log n)**  | **O(log n)** |
| Insert        | **O(log n)**  | **O(log n)** |
| Delete        | **O(log n)**  | **O(log n)** |
| Traverse        | **O(n)**  | **O(n)** |

## Operations

1. `BTree<type>(order)` - creates a new empty B-tree with a specified order.
1. `insert(key)` - inserts a new key into the B-tree.
1. `remove(key)` - removes an existing key from the B-tree.
1. `search(key)` - searches for the key with a specified value.