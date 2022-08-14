
# Sorting Algorithm

## Brief
A Sorting Algorithm is used to rearrange a given array or list elements according to a comparison operator on the elements. The comparison operator is used to decide the new order of elements in the respective data structure.

&nbsp;
**Sorting Algorthms:**
- [**Insertion Sort**](https://www.geeksforgeeks.org/insertion-sort/)
- [**Selection Sort**](https://www.geeksforgeeks.org/selection-sort/)
- [**Bubble Sort**](https://www.geeksforgeeks.org/bubble-sort/)
- [**Shell Sort**](https://www.geeksforgeeks.org/shellsort/)
- [**Count Sort**](https://www.geeksforgeeks.org/counting-sort/)
- [**Radix Sort**](https://www.geeksforgeeks.org/radix-sort/)
- [**Merge Sort**](https://www.geeksforgeeks.org/merge-sort/)
- [**Quick Sort**](https://www.geeksforgeeks.org/quick-sort/)
- [**Heap Sort**](https://www.geeksforgeeks.org/heap-sort/)

## :hourglass: Complexity

| Algorithm     | Best case   | Average       | Worst case   | Space     |
| ------------- | ------------- | ------------ | ------------ | ------------ |
| Insertion Sort         | **O(n)**      | **O(n^2)**     | **O(n^2)**     | **O(1)**     |
| Selection Sort         | **O(n^2)**      | **O(n^2)**     | **O(n^2)**     | **O(1)**     |
| Bubble Sort         | **O(n)**      | **O(n^2)**     | **O(n^2)**     | **O(1)**     |
| Shell Sort         | **O(n(log(n))**      | **O(n(log(n)^2))**     | **O(n(log(n)^2))**     | **O(1)**     |
| Count Sort         | **O(n+k)**      | **O(n+k)**     | **O(n+k)**     | **O(k)**     |
| Radix Sort         | **O(n*k)**      | **O(n*k)**     | **O(n*k)**     | **O(k)**     |
| Merge Sort         | **O(n*log(n))**      | **O(n*log(n))**     | **O(n*log(n))**     | **O(n)**     |
| Quick Sort         | **O(n*log(n))**      | **O(n*log(n))**     | **O(n^2)**     | **O(log(n))**     |
| Heap Sort         | **O(n*log(n))**      | **O(n*log(n))**     | **O(n^2)**     | **O(1)**     |


## Operations

1. `Sorter<int>* s` - Creates a new Sorter Pointer.
1. `s = new (Algorithm name)Sort<type>` - Make a new object of selected sorting algorithm to use.
1. `s->sort(array,size)` - Sort the array according to the sorting algorithm specified.
1. `InsertionSort<type>` - Use Insertion Sort algorithm.
1. `SelectionSort<type>` - Use Selection Sort algorithm.
1. `BubbleSort<type>` - Use Bubble Sort algorithm.
1. `ShellSort<type>` - Use Shell Sort algorithm.
1. `CountSort<type>` - Use Count Sort algorithm.
1. `RadixSort<type>` - Use Radix Sort algorithm.
1. `MergeSort<type>` - Use Merge Sort algorithm.
1. `QuickSort<type>` - Use Quick Sort algorithm.
1. `HeapSort<type>` - Use Heap Sort algorithm.
