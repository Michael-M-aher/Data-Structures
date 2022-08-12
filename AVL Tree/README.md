
# AVL tree

![AVL-tree](https://upload.wikimedia.org/wikipedia/commons/a/ad/AVL-tree-wBalance_K.svg)

## Brief
AVL tree is a self-balancing Binary Search Tree (BST) where the difference between heights of left and right subtrees cannot be more than one for all nodes. 

## :hourglass: Complexity

| Operation     | Average       | Worst case   |
| ------------- | ------------- | ------------ |
| Space         | **O(n)**      | **O(n)**     |
| Search        | **O(log n)**  | **O(log n)** |
| Insert        | **O(log n)**  | **O(log n)** |
| Delete        | **O(log n)**  | **O(log n)** |
| Traverse        | **O(log n)**  | **O(log n)** |

## Operations

1. `BST<type>()` - creates a new empty AVL tree.
1. `Insert(key)` - inserts a new node into the AVL tree.
1. `Remove(key)` - removes existing node from the AVL tree.
1. `Find(key)` - searches for the node with a specified key value.
1. `leftRotate(node)` - transform the arrangement of the nodes on the right into the left node.
1. `rightRotate(node)` - transform the arrangement of the nodes on the left into the right node.
1. `preorder(node)` - traverses the tree using an Pre-order algorithm.
1. `inorder(node)` - traverses the tree using an In-order algorithm.
1. `postorder(node)` - traverses the tree using an Post-order algorithm.
1. `levelprint(node)` - traverses the tree using an Breadth-first algorithm.
