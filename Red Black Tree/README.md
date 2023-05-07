# Red Black Tree

![Red-Black-Tree](https://upload.wikimedia.org/wikipedia/commons/6/66/Red-black_tree_example.svg)

## Brief
Red-Black tree is another type of self-balancing Binary Search Tree (BST) that guarantees a balanced height of the tree by assigning one of two possible colors to each node, red or black, and satisfying a set of conditions that preserve this balance.

## :hourglass: Complexity

| Operation     | Average       | Worst case   |
| ------------- | ------------- | ------------ |
| Space         | **O(n)**      | **O(n)**     |
| Search        | **O(log n)**  | **O(log n)** |
| Insert        | **O(log n)**  | **O(log n)** |
| Delete        | **O(log n)**  | **O(log n)** |
| Traverse      | **O(n)**      | **O(n)**     |

## Operations

1. `RedBlackTree<type>()` - creates a new empty Red-Black tree.
1. `insert(key)` - inserts a new node into the Red-Black tree.
1. `remove(key)` - removes existing node from the Red-Black tree.
1. `search(key)` - searches for the node with a specified key value.
1. `rotateLeft(node)` - rotates the nodes to the left, maintaining the Red-Black properties.
1. `rotateRight(node)` - rotates the nodes to the right, maintaining the Red-Black properties.
1. `print()` - traverses the tree using an In-order algorithm.