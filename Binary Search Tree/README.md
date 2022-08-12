
# Binary Search tree

## Brief
Binary Search Tree is a node-based binary tree data structure which has the following properties:

- The left subtree of a node contains only nodes with keys lesser than the node’s key.
- The right subtree of a node contains only nodes with keys greater than the node’s key.
- The left and right subtree each must also be a binary search tree.

## :hourglass: Complexity

| Operation     | Average       | Worst case   |
| ------------- | ------------- | ------------ |
| Space         | **O(n)**      | **O(n)**     |
| Search        | **O(log n)**  | **O(n)** |
| Insert        | **O(log n)**  | **O(n)** |
| Delete        | **O(log n)**  | **O(n)** |
| Traverse        | **O(n)**  | **O(n)** |

## Operations

1. `BST<type>()` - creates a new empty binary search tree.
1. `Insert(key)` - inserts a new node into the binary search tree.
1. `Remove(key)` - removes existing node from the binary search tree.
1. `Find(key)` - searches for the node with a specified key value.
1. `isBalance()` - check if the tree is balanced.
1. `isSubTree(node1, node2)` - check if tree of node2 is subtree of tree of node1.
1. `printRange(num1, num2)` - print value of nodes of the tree within range of num1 and num2.
1. `preorder(node)` - traverses the tree using an Pre-order algorithm.
1. `inorder(node)` - traverses the tree using an In-order algorithm.
1. `postorder(node)` - traverses the tree using an Post-order algorithm.
1. `breadthFirst(node)` - traverses the tree using an Breadth-first algorithm.
