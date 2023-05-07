#include <iostream>

using namespace std;

struct Interval
{
    int low;
    int high;
};

struct Node
{
    Interval interval{};
    int max;
    Node *left, *right, *parent;
    Node(int low, int high)
    {
        interval.low = low;
        interval.high = high;
        max = high;
        left = right = parent = nullptr;
    }
};

/* A class that is used to store the intervals that are found in the search. */
class DynamicArray
{
public:
    DynamicArray() : sz(0), cap(1)
    {
        data = new Node *[cap];
    }

    ~DynamicArray()
    {
        delete[] data;
    }

    /**
     * If the array is full, double the capacity of the array and copy the old elements into the new
     * array
     */
    void push(Node *element)
    {
        if (sz == cap)
        {
            cap *= 2;
            Node **newData = new Node *[cap];
            for (int i = 0; i < sz; i++)
            {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }
        data[sz++] = element;
    }

    /**
     * Returns the node at the given index.
     */
    Node *operator[](int index) const
    {
        return data[index];
    }

    /**
     * It clears the array.
     */
    void clear()
    {
        sz = 0;
        cap = 1;
        delete[] data;
        data = new Node *[cap];
    }

    /**
     * Prints the intervals in the tree.
     */
    void print() const
    {
        if (sz == 0)
        {
            cout << "No intervals found" << endl;
        }
        else
        {
            cout << "Intervals found: \n";
            for (int i = 0; i < sz; i++)
            {
                cout << data[i]->interval.low << " " << data[i]->interval.high << endl;
            }
        }
        cout << endl;
    }

    /**
     * It returns the size of the array.
     */
    int size() const
    {
        return sz;
    }

private:
    Node **data;
    int sz;
    int cap;
};

class IntervalTree
{
private:
    Node *root;
    Node *insert(Node *root, Node *node);
    Node *searchExactInterival(Node *root, int low, int high);
    void deleteNode(Node *node);
    Node *overlapSearch(Node *root, int low, int high);
    void updateMax(Node *node);
    void inorder(Node *root);

public:
    IntervalTree()
    {
        root = nullptr;
    }
    void InsertInterval(int low, int high);
    void DeleteInterval(int low, int high);
    DynamicArray SearchInterval(int low, int high);
    void inorder();
};

/**
 * Insert a new interval into the tree, and update the max value of all the nodes on the path from the
 * root to the newly inserted node
 */
void IntervalTree::InsertInterval(int low, int high)
{
    Node *node = new Node(low, high);
    root = insert(root, node);
    updateMax(node);
}

/**
 * It searches for all the intervals that overlap with the given interval and returns them in a
 * DynamicArray.
 */
DynamicArray IntervalTree::SearchInterval(int low, int high)
{
    DynamicArray arr;
    if (low > high)
    {
        return arr;
    }
    Node *node = overlapSearch(root, low, high);
    while (node != nullptr)
    {
        arr.push(new Node(node->interval.low, node->interval.high));
        deleteNode(node);
        node = overlapSearch(root, low, high);
    };
    for (int i = 0; i < arr.size(); i++)
    {
        InsertInterval(arr[i]->interval.low, arr[i]->interval.high);
    }
    return arr;
}

/**
 * 1. Find the node to be deleted.
 * 2. If the node is a leaf node, delete it.
 * 3. If the node has one child, delete it and replace it with its child.
 * 4. If the node has two children, replace it with its inorder successor, and delete the inorder
 * successor
 */
void IntervalTree::DeleteInterval(int low, int high)
{
    Node *node = searchExactInterival(root, low, high);
    if (node == nullptr)
    {
        cout << "No such interval" << endl;
        return;
    }
    deleteNode(node);
}

/**
 * If the node to be inserted has a lower low value than the root, then insert it in the left subtree,
 * otherwise insert it in the right subtree
 */
Node *IntervalTree::insert(Node *root, Node *node)
{
    if (root == nullptr)
    {
        return node;
    }
    if (node->interval.low < root->interval.low)
    {
        root->left = insert(root->left, node);
        root->left->parent = root;
    }
    else
    {
        root->right = insert(root->right, node);
        root->right->parent = root;
    }
    return root;
}

/**
 * If the root is null or the root's interval is equal to the given interval, return the root.
 * Otherwise, if the root's interval is greater than the given interval, search the left subtree.
 * Otherwise, search the right subtree
 */
Node *IntervalTree::searchExactInterival(Node *root, int low, int high)
{
    if (root == nullptr || (root->interval.low == low && root->interval.high == high))
    {
        return root;
    }
    if (root->interval.low > low)
    {
        return searchExactInterival(root->left, low, high);
    }
    return searchExactInterival(root->right, low, high);
}

/**
 * If the node to be deleted has no children, delete it. If it has one child, replace it with its
 * child. If it has two children, replace it with its in-order successor
 */
void IntervalTree::deleteNode(Node *node)
{
    Node *parent = node->parent;
    if (node->left == nullptr && node->right == nullptr)
    {
        if (node->parent == nullptr)
        {
            root = nullptr;
        }
        else if (node->parent->left == node)
        {
            node->parent->left = nullptr;
        }
        else
        {
            node->parent->right = nullptr;
        }
        delete node;
    }
    else if (node->left == nullptr)
    {
        if (node->parent == nullptr)
        {
            root = node->right;
            node->right->parent = nullptr;
        }
        else if (node->parent->left == node)
        {
            node->parent->left = node->right;
            node->parent->left->parent = node->parent;
        }
        else
        {
            node->parent->right = node->right;
            node->parent->right->parent = node->parent;
        }
        delete node;
    }
    else if (node->right == nullptr)
    {
        if (node->parent == nullptr)
        {
            root = node->left;
            node->left->parent = nullptr;
        }
        else if (node->parent->left == node)
        {
            node->parent->left = node->left;
            node->parent->left->parent = node->parent;
        }
        else
        {
            node->parent->right = node->left;
            node->parent->right->parent = node->parent;
        }
        delete node;
    }
    else
    {
        Node *temp = node->right;
        while (temp->left != nullptr)
        {
            temp = temp->left;
        }
        node->interval.low = temp->interval.low;
        node->interval.high = temp->interval.high;
        updateMax(temp);
        deleteNode(temp);
        return;
    }
    updateMax(parent);
}

/**
 * If the max of the node is less than the max of the left child or the max of the right child, then
 * update the max of the node to the max of the left child or the max of the right child
 */
void IntervalTree::updateMax(Node *node)
{
    if (node == nullptr)
    {
        return;
    }
    int max = node->interval.high;
    if (node->left != nullptr && max < node->left->max)
    {
        max = node->left->max;
    }
    if (node->right != nullptr && max < node->right->max)
    {
        max = node->right->max;
    }
    node->max = max;
    updateMax(node->parent);
}

/**
 * If the current node overlaps with the given interval, return the current node. Otherwise, recur for
 * the left and right children
 */
Node *IntervalTree::overlapSearch(Node *root, int low, int high)
{
    if (root == nullptr)
    {
        return nullptr;
    }
    if (root->interval.low <= low && root->interval.high >= high)
    {
        return root;
    }
    if (root->left != nullptr && root->left->max >= low)
    {
        return overlapSearch(root->left, low, high);
    }
    return overlapSearch(root->right, low, high);
}

/**
 * It calls the private inorder function, passing it the root of the tree
 */
void IntervalTree::inorder()
{
    cout << "Inorder of the tree: \n";
    inorder(root);
    cout << endl;
}

/**
 * If the root is null, return. Otherwise, recursively call inorder on the left subtree, print the
 * root, and recursively call inorder on the right subtree
 */
void IntervalTree::inorder(Node *root)
{
    if (root == nullptr)
    {
        return;
    }
    inorder(root->left);
    cout << root->interval.low << " " << root->interval.high << endl;
    inorder(root->right);
}

int main()
{
    IntervalTree tree1;
    tree1.InsertInterval(15, 20);
    tree1.InsertInterval(10, 30);
    tree1.InsertInterval(17, 19);
    tree1.InsertInterval(5, 20);
    tree1.InsertInterval(12, 15);
    tree1.InsertInterval(30, 40);
    DynamicArray arr1 = tree1.SearchInterval(6, 7);
    arr1.print();
    cout << endl;

    return 0;
}
