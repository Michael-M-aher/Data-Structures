# Trie

![Trie](https://upload.wikimedia.org/wikipedia/commons/thumb/b/be/Trie_example.svg/1920px-Trie_example.svg.png)

## Brief
A Trie, also called Prefix Tree, is a tree-like data structure that is used to store a dynamic set or associative array. It is particularly efficient for finding and manipulating keys that share a common prefix.

## :hourglass: Complexity

| Operation     | Average       | Worst case   |
| ------------- | ------------- | ------------ |
| Space         | **O(n)**      | **O(n)**     |
| Search        | **O(m)**      | **O(m)**     |
| Insert        | **O(m)**      | **O(m)**     |
| Delete        | **O(m)**      | **O(m)**     |

Where `m` is the length of the key.

## Operations

1. `TrieNode()` - creates a new empty Trie node.
2. `insert(key)` - inserts a new key into the Trie.
3. `search(key)` - searches for the key in the Trie.