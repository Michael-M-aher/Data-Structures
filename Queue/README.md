
# Queue

## Brief
A Queue is a linear structure which follows a particular order in which the operations are performed. The order is First In First Out (FIFO)  or LILO(Last In Last Out).

## :hourglass: Complexity

| Operation     | Average       | Worst case   |
| ------------- | ------------- | ------------ |
| Space         | **O(n)**      | **O(n)**     |
| enqueue        | **O(1)**  | **O(n)** |
| dequeue        | **O(1)**  | **O(1)** |


## Operations

1. `Queue()` - creates a new empty Queue.
1. `push(value)` - inserts a new element to the back of the queue.
1. `pop()` - delete the element at the front of the queue.
1. `empty()` - check if the queue is empty.
1. `clear()` - clear the queue.
1. `size()` - return the size of the queue.
1. `back()` - return the element at the back of the queue.
1. `front()` - return the element at the front of the queue.