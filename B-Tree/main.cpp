#include <iostream>
using namespace std;

template <typename T>
struct Node {
    int m,n;
    T *keys;
    Node<T> **children;
    bool leaf;
    Node(int m, bool leaf){
        this->m = m;
        this->n = 0;
        this->leaf = leaf;
        keys = new T[m];
        children = new Node<T>*[m+1];
    }
};

template <typename T>
class BTree {
    Node<T> *root;
    int m;
    void insert(Node<T> *x,T k);
    void insertNonFull(Node<T> *x,T k);
    void splitChild(Node<T> *lft, int x, Node<T> *newNode);
    void traverse(Node<T> *x);
    void remove(Node<T> *x, T k);
    void removeNonLeaf(Node<T> *x, T k);
    void removeLeaf(Node<T> *x, T k);
    void merge(Node<T> *x, int i);
    void borrow(Node<T> *x, int i);
    void borrowFromPrev(Node<T> *x, int i);
    void borrowFromNext(Node<T> *x, int i);
    T getPred(Node<T> *x, int i);
    T getSucc(Node<T> *x, int i);
    void search(Node<T> *x, T k);



public:
    BTree(int m){
        root = nullptr;
        this->m = m;
    }
    void insert(T k){
        insert(root,k);
    };
    void traverse();

    void remove(T k){
        remove(root,k);
    };
    void search(T k){
        search(root,k);
    };
};

template<typename T>
void BTree<T>::insert(Node<T> *x, T k) {
    if (root == nullptr){
        root = new Node<T>(m,true);
        root->keys[0] = k;
        root->n = 1;
    } else {
        insertNonFull(root,k);
        if (root->n == m){
            Node<T> *newNode = new Node<T>(m,false);
            newNode->children[0] = root;
            splitChild(root,0,newNode);
            root = newNode;
        }
    }
}
template<typename T>
void BTree<T>::insertNonFull(Node<T> *x, T k) {
    int i = x->n -1;
    if (x->leaf){
        while (i>=0 && x->keys[i] > k){
            x->keys[i+1] = x->keys[i];
            i--;
        }
        x->keys[i+1] = k;
        x->n++;
    }else{
        while (i>=0 && x->keys[i] > k){
            i--;
        }
        insertNonFull(x->children[i+1],k);
        if(x->children[i+1]->n == m){
            splitChild(x->children[i+1],i+1,x);
        }
    }
}

template<typename T>
void BTree<T>::splitChild(Node<T> *lft, int x, Node<T> *newNode){
    Node<T>* rht = new Node<T>(m, lft->leaf);
    rht->n = (m/2) ;
    for (int i = 0; i < rht->n; ++i) {
        rht->keys[i] = lft->keys[rht->n+1+i];
    }
    if (lft->leaf == false){
        for (int i = 0; i < rht->n+1; ++i) {
            rht->children[i] = lft->children[rht->n+1+i];
        }
    }
    lft->n = (m/2) ;
    for (int i = newNode->n ; i > x ; --i) {
        newNode->children[i+1] = newNode->children[i];
    }
    newNode->children[x+1] = rht;

    for (int i = newNode->n-1; i >= x ; --i) {
        newNode->keys[i+1] = newNode->keys[i];
    }
    newNode->keys[x] = lft->keys[lft->n];
    newNode->n++;
}

template<typename T>
void BTree<T>::traverse() {
    traverse(root);
    cout<<endl;
}

template<typename T>
void BTree<T>::traverse(Node<T> *x) {
    int i;
    for (i = 0; i < x->n; i++)
    {
        if (x->leaf == false)
            traverse(x->children[i]);
        cout << x->keys[i] << " ";
    }

    if (x->leaf == false){
        traverse(x->children[i]);
    }
}

template<typename T>
void BTree<T>::remove(Node<T> *x, T k) {
    int i = 0;
    while (i < x->n && k > x->keys[i]){
        i++;
    }
    if (i < x->n && k == x->keys[i]){
        if (x->leaf){
            removeLeaf(x,k);
        }else{
            removeNonLeaf(x,k);
        }
    }else{
        if (x->leaf){
            cout<<"Key not found"<<endl;
            return;
        }
        bool flag = (i == x->n);
        if (x->children[i]->n < (m/2)){
            borrow(x,i);
        }
        if (flag && i > x->n){
            remove(x->children[i-1],k);
        }else{
            remove(x->children[i],k);
        }
    }
}

template<typename T>
void BTree<T>::removeNonLeaf(Node<T> *x, T k) {
    int i = 0;
    while (i < x->n && k > x->keys[i]){
        i++;
    }
    if (x->children[i]->n >= (m/2)){
        T pred = getPred(x,i);
        x->keys[i] = pred;
        remove(x->children[i],pred);
    }else if (x->children[i+1]->n >= (m/2)){
        T succ = getSucc(x,i);
        x->keys[i] = succ;
        remove(x->children[i+1],succ);
    }else{
        merge(x,i);
        remove(x->children[i],k);
    }
}

template<typename T>
void BTree<T>::removeLeaf(Node<T> *x, T k) {
    int i = 0;
    while (i < x->n && k > x->keys[i]){
        i++;
    }
    for (int j = i+1; j < x->n; ++j) {
        x->keys[j-1] = x->keys[j];
    }
    x->n--;
}

template<typename T>
T BTree<T>::getPred(Node<T> *x, int i) {
    Node<T> *cur = x->children[i];
    while (!cur->leaf){
        cur = cur->children[cur->n];
    }
    return cur->keys[cur->n-1];
}

template<typename T>
T BTree<T>::getSucc(Node<T> *x, int i) {
    Node<T> *cur = x->children[i+1];
    while (!cur->leaf){
        cur = cur->children[0];
    }
    return cur->keys[0];
}

template<typename T>
void BTree<T>::borrow(Node<T> *x, int i) {
    if (i != 0 && x->children[i-1]->n >= (m/2)){
        borrowFromPrev(x,i);
    }else if (i != x->n && x->children[i+1]->n >= (m/2)){
        borrowFromNext(x,i);
    }else{
        if (i != x->n){
            merge(x,i);
        }else{
            merge(x,i-1);
        }
    }
}

template<typename T>
void BTree<T>::borrowFromPrev(Node<T> *x, int i) {
    Node<T> *child = x->children[i];
    Node<T> *sibling = x->children[i-1];
    for (int j = child->n-1; j >= 0; --j) {
        child->keys[j+1] = child->keys[j];
    }
    if (!child->leaf){
        for (int j = child->n; j >= 0; --j) {
            child->children[j+1] = child->children[j];
        }
    }
    child->keys[0] = x->keys[i-1];
    if (!child->leaf){
        child->children[0] = sibling->children[sibling->n];
    }
    x->keys[i-1] = sibling->keys[sibling->n-1];
    child->n++;
    sibling->n--;
}

template<typename T>
void BTree<T>::borrowFromNext(Node<T> *x, int i) {
    Node<T> *child = x->children[i];
    Node<T> *sibling = x->children[i+1];
    child->keys[child->n] = x->keys[i];
    if (!child->leaf){
        child->children[child->n+1] = sibling->children[0];
    }
    x->keys[i] = sibling->keys[0];
    for (int j = 1; j < sibling->n; ++j) {
        sibling->keys[j-1] = sibling->keys[j];
    }
    if (!sibling->leaf){
        for (int j = 1; j <= sibling->n; ++j) {
            sibling->children[j-1] = sibling->children[j];
        }
    }
    child->n++;
    sibling->n--;
}

template<typename T>
void BTree<T>::merge(Node<T> *x, int i) {
    Node<T> *child = x->children[i];
    Node<T> *sibling = x->children[i+1];
    child->keys[m/2-1] = x->keys[i];
    for (int j = 0; j < sibling->n; ++j) {
        child->keys[m/2+j] = sibling->keys[j];
    }
    if (!child->leaf){
        for (int j = 0; j <= sibling->n; ++j) {
            child->children[m/2+j] = sibling->children[j];
        }
    }
    for (int j = i+1; j < x->n; ++j) {
        x->keys[j-1] = x->keys[j];
    }
    for (int j = i+2; j <= x->n; ++j) {
        x->children[j-1] = x->children[j];
    }
    child->n += sibling->n+1;
    x->n--;
    delete(sibling);
}

template<typename T>
void BTree<T>::search(Node<T> *x, T k) {
    int i = 0;
    while (i < x->n && k > x->keys[i]){
        i++;
    }
    if (x->keys[i] == k){
        cout << "Found " << k << endl;
    }else if (x->leaf){
        cout << "Not Found " << k << endl;
    }else{
        search(x->children[i],k);
    }
}


int main() {
//    BTree<int> t(5); // A B-Tree of order 5
//    t.insert(10);
//    t.insert(20);
//    t.insert(5);
//    t.insert(6);
//    t.insert(12);
//    t.insert(30);
//    t.insert(7);
//    t.insert(17);
    BTree<char> t(5); // A B-Tree of order 5
    t.insert('g');
    t.insert('i');
    t.insert('b');
    t.insert('j');
    t.insert('c');
    t.insert('a');
    t.insert('k');
    t.insert('e');
    t.insert('d');
    t.insert('s');
    t.insert('t');
    t.remove('e');
    t.remove('k');

    cout << "Traversal of the constructed tree is ";
    t.traverse();

    return 0;
}
