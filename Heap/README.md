
# Heap

## Brief
A Heap is a special Tree-based data structure in which the tree is a complete binary tree. Generally, Heaps can be of two types:

- Max-Heap: In a Max-Heap the key present at the root node must be greatest among the keys present at all of it’s children. The same property must be recursively true for all sub-trees in that Binary Tree.
- Min-Heap: In a Min-Heap the key present at the root node must be minimum among the keys present at all of it’s children. The same property must be recursively true for all sub-trees in that Binary Tree.

## :hourglass: Complexity

| Operation     | Average       | Worst case   |
| ------------- | ------------- | ------------ |
| Space         | **O(n)**      | **O(n)**     |
| Search        | **O(n)**  | **O(n)** |
| Insert        | **O(1)**  | **O(log n)** |
| Delete        | **O(log n)**  | **O(log n)** |
| Peek        | **O(1)**  | **O(1)** |


## Operations

1. `Heap(capacity,mx)` - creates a new empty Heap of capacity and if mx true then max heap else min heap.
1. `parent(idx)` - return index of the parent of selected index.
1. `left(idx)` - return index of the left child of selected index.
1. `right(idx)` - return index of the right child of selected index.
1. `insertKey(value)` - add the element to the heap then do bottomUpHeapify.
1. `deleteKey(value)` - delete the element from the heap then do topDownHeapify.
1. `changeKey(idx,value)` - change the value of element at the idx in the heap then do topDownHeapify or bottomUpHeapify according to the type of heap.
1. `getTop()` - return the element at the top of the heap (max/min).
1. `extractTop()` - return the element at the top of the heap (max/min) then remove it from heap.