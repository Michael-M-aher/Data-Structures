
# Doubly Linked List

## Brief
It is type of linked list in which every node contains some data and two pointers one to the next node of the same data type and other to the previous node of the same data type. The node contains two pointers one to the next node means that the node stores the address of the next node in the sequence and other to the previous node means that the node stores the address of the previous node in the sequence. 

## :hourglass: Complexity

| Operation     | Average       | Worst case   |
| ------------- | ------------- | ------------ |
| Space         | **O(1)**      | **O(1)**     |
| Access        | **O(n)**  | **O(n)** |
| Insert at head        | **O(1)**  | **O(1)** |
| Insert at tail        | **O(1)**  | **O(1)** |
| Search        | **O(n)**  | **O(n)** |
| Remove at head        | **O(1)**  | **O(1)** |
| Remove in middle        | **O(n)**  | **O(n)** |
| Remove at tail        | **O(1)**  | **O(1)** |


## Operations

1. `list()` - creates a new empty Doubly Linked List.
1. `list(value, size)` - creates a new Doubly Linked List with size and value specified.
1. `push_front(value)` - inserts a new element into the front of the list.
1. `push_back(value)` - inserts a new element into the back of the list.
1. `insert(iterator, value)` - inserts a new element into the iterator location in the list.
1. `pop_front()` - delete the element at the front of the list.
1. `pop_back()` - delete the element at the back of the list.
1. `Remove(iterator)` - delete the element at the iterator location in the list.
1. `search(value)` - returns iterator location with the value specified.
1. `clear()` - clear the list.
1. `size()` - return the size of the list.
1. `front()` - return the element at the front of the list.
1. `back()` - return the element at the back of the list.
1. `begin()` - returns iterator of the first element in the list.
1. `end()` - returns iterator of the end of the list.
1. `rbegin()` - returns iterator of the last element in the list.
1. `rend()` - returns iterator of the beginning of the list.
1. `list<type>::iterator()` - creates a new iterator.
1. `iterator ++,+=,--,-=,==,!=` - all operations can be applied to the iterator.
