#include <iostream>

using namespace std;

enum Color { RED, BLACK };

template<typename T>
struct Node {
    T val;
    Color color;
    Node<T> *left, *right, *parent;

    Node<T>(T val ) : val(val), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};
template<typename T>
class RedBlackTree {
private:
    Node<T> *root;

    Node<T> * rotateLeft(Node<T> *&);
    Node<T> * rotateRight(Node<T> *&);
    void fixInsert(Node<T> *&);
    void fixDelete(Node<T> *&);
    Node<T>* search(Node<T> *&,int);
    void inorder(Node<T> *&);
    void transplant(Node<T> *&u, Node<T> *&v);
    Node<T>* minimum(Node<T> *&);

public:
    RedBlackTree<T>() : root(nullptr) {}
    void insert(int);
    void remove(int);
    Node<T>* search(int);
    void print();
};

template<typename T>
Node<T> * RedBlackTree<T>::rotateLeft(Node<T> *&pt) {
    Node<T> *pt_right = pt->right;

    pt->right = pt_right->left;

    if (pt->right != nullptr){
        pt->right->parent = pt;
    }

    pt_right->parent = pt->parent;

    if (pt->parent == nullptr){
        root = pt_right;
    }else if (pt == pt->parent->left){
        pt->parent->left = pt_right;
    }else{
        pt->parent->right = pt_right;
    }

    pt_right->left = pt;
    pt->parent = pt_right;
    return pt_right;
}

template<typename T>
Node<T> * RedBlackTree<T>::rotateRight(Node<T> *&pt) {
    Node<T> *pt_left = pt->left;

    pt->left = pt_left->right;

    if (pt->left != nullptr){
        pt->left->parent = pt;
    }

    pt_left->parent = pt->parent;

    if (pt->parent == nullptr){
        root = pt_left;
    }else if (pt == pt->parent->left){
        pt->parent->left = pt_left;
    }else{
        pt->parent->right = pt_left;
    }

    pt_left->right = pt;
    pt->parent = pt_left;
    return pt_left;
}

template<typename T>
void RedBlackTree<T>::fixInsert(Node<T> *&pt) {
    Node<T> *parent_pt = nullptr;
    Node<T> *grand_parent_pt = nullptr;

    while ((pt != root) && (pt->color != BLACK) &&
           (pt->parent->color == RED)) {
        parent_pt = pt->parent;
        grand_parent_pt = pt->parent->parent;

        if (parent_pt == grand_parent_pt->left) {
            Node<T> *uncle_pt = grand_parent_pt->right;
            if (uncle_pt != nullptr && uncle_pt->color == RED) {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                pt = grand_parent_pt;
            } else {
                if (pt == parent_pt->right) {
                    parent_pt = rotateLeft(parent_pt);
                }

                rotateRight(grand_parent_pt);
                swap(parent_pt->color, grand_parent_pt->color);
                pt = parent_pt;
            }
        } else {
            Node<T> *uncle_pt = grand_parent_pt->left;
            if ((uncle_pt != nullptr) && (uncle_pt->color == RED)) {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                pt = grand_parent_pt;
            } else {
                if (pt == parent_pt->left) {
                    parent_pt = rotateRight(parent_pt);

                }
                rotateLeft(grand_parent_pt);
                swap(parent_pt->color, grand_parent_pt->color);
                pt = parent_pt;
            }
        }
    }

    root->color = BLACK;
}

template<typename T>
void RedBlackTree<T>::insert(int val) {
    Node<T> *pt = new Node<T>(val);

    Node<T> *parent_pt = nullptr;
    Node<T> *current_pt = root;
    while (current_pt != nullptr) {
        parent_pt = current_pt;
        if (val < current_pt->val){
            current_pt = current_pt->left;
        }else{
            current_pt = current_pt->right;
        }
    }

    pt->parent = parent_pt;
    if (parent_pt == nullptr){
        root = pt;
    }else if (val < parent_pt->val){
        parent_pt->left = pt;
    }else{
        parent_pt->right = pt;
    }

    fixInsert(pt);
}

template<typename T>
Node<T>* RedBlackTree<T>::search(Node<T> *&x, int val) {
    if (x == nullptr || x->val == val){
        return x;
    }

    if (x->val < val){
        return search(x->right, val);
    }

    return search(x->left, val);
}

template<typename T>
Node<T>* RedBlackTree<T>::search(int val) {
    return search(root, val);
}

template<typename T>
void RedBlackTree<T>::inorder(Node<T> *&x) {
    if (x == nullptr){
        return;
    }

    inorder(x->left);
    cout << x->val << " ";
    inorder(x->right);
}

template<typename T>
void RedBlackTree<T>::print() {
    inorder(root);
    cout << endl;
}

template<typename T>
void RedBlackTree<T>::remove(int val) {
    Node<T> *z = search(root, val);
    if (z == nullptr) return;
    Node<T> *y = z;
    Node<T> *x;
    Color originalColor = y->color;

    if (z->left == nullptr && z->right == nullptr){
        x = z;
    } else if (z->left == nullptr) {
        x = z->right;
        transplant(z, z->right);
    } else if (z->right == nullptr) {
        x = z->left;
        transplant(z, z->left);
    } else {
        y = minimum(z->right);
        swap(z->val, y->val);
        originalColor = y->color;
        z = y;
        x = y->right;
        transplant(y, y->right);
    }
    if (originalColor == BLACK) {
        fixDelete(x);
    }

    if (z->left == nullptr && z->right == nullptr){
        if (z == z->parent->left){
            z->parent->left = nullptr;
        } else {
            z->parent->right = nullptr;
        }
    }
    delete z;
}

template<typename T>
void RedBlackTree<T>::fixDelete(Node<T> *&pt) {
    if (pt == nullptr){
        return;
    }

    while (pt != root && pt->color == BLACK) {
        if (pt == pt->parent->left) {
            Node<T> *sibling = pt->parent->right;
            if (sibling->color == RED) {
                sibling->color = BLACK;
                pt->parent->color = RED;
                rotateLeft(pt->parent);
                sibling = pt->parent->right;
            }

            if ((!sibling->left || sibling->left->color == BLACK) &&
                (!sibling->right || sibling->right->color == BLACK)) {
                sibling->color = RED;
                pt = pt->parent;
            } else {
                if (sibling->left->color == RED) {
                    sibling->left->color = BLACK;
                    sibling->color = RED;
                    rotateRight(sibling);
                    sibling = pt->parent->right;
                }

                sibling->color = pt->parent->color;
                pt->parent->color = BLACK;
                sibling->right->color = BLACK;
                rotateLeft(pt->parent);
                pt = root;
            }
        } else {
            Node<T> *sibling = pt->parent->left;
            if (sibling->color == RED) {
                sibling->color = BLACK;
                pt->parent->color = RED;
                rotateRight(pt->parent);
                sibling = pt->parent->left;
            }

            if ((!sibling->right || sibling->right->color == BLACK) &&
                (!sibling->left || sibling->left->color == BLACK)) {
                sibling->color = RED;
                pt = pt->parent;
            } else {
                if (sibling->right->color == RED) {
                    sibling->right->color = BLACK;
                    sibling->color = RED;
                    rotateLeft(sibling);
                    sibling = pt->parent->left;
                }

                sibling->color = pt->parent->color;
                pt->parent->color = BLACK;
                sibling->left->color = BLACK;
                rotateRight(pt->parent);
                pt = root;
            }
        }
    }
    pt->color = BLACK;
}

template<typename T>
void RedBlackTree<T>::transplant(Node<T> *&u, Node<T> *&v) {
    if (u->parent == nullptr){
        root = v;
    }else if (u == u->parent->left){
        u->parent->left = v;
    }else{
        u->parent->right = v;
    }

    if (v != nullptr){
        v->parent = u->parent;
    }
}

template<typename T>
Node<T>* RedBlackTree<T>::minimum(Node<T> *&x) {
    while (x->left != nullptr){
        x = x->left;
    }

    return x;
}





int main() {
    RedBlackTree<int> rbt;

    rbt.insert(7);
    rbt.insert(6);
    rbt.insert(5);
    rbt.insert(4);
    rbt.insert(3);
    rbt.insert(2);
    rbt.insert(1);

    rbt.print();

    rbt.remove(7);
    rbt.remove(5);
    rbt.remove(1);

    rbt.print();

    return 0;
}

