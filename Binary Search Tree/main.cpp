#include <iostream>
#include <queue>
using namespace std;

template<class T>
class BSTNode{
public:
    T value;
    int height;
    BSTNode *left,*right;
    BSTNode(T v): value(v), left(nullptr), right(nullptr),height(0){}
};

template<class T>
class BST{
private:
    BSTNode<T>* parent;
    BSTNode<T>* insRec(BSTNode<T> *current, T val){
        if(current == nullptr){
            return new BSTNode<T>(val);
        }
        if (val < current->value){
            current->left = insRec(current->left, val);
        }else if(val > current->value){
            current->right = insRec(current->right, val);
        }else{
            cout << val << " already in the tree\n";
            return current;
        }
        updateHeight(current);
        return current;
    }
    BSTNode<T>* delRec(BSTNode<T> *current,T val){
        if(current->value == val){
            BSTNode<T>* tmp;
            if(current->left == nullptr){
                tmp = current->right;
                delete current;
                return tmp;
            }else if(current->right == nullptr){
                tmp = current->left;
                delete current;
                return tmp;
            }else{
                BSTNode<T>* prev;
                prev=current;
                tmp = current->right;
                while(tmp->left != nullptr){
                    prev = tmp;
                    tmp = tmp->left;
                }
                current->value = tmp->value;
                if(prev==current){
                    current->right = tmp->right;
                }else{
                    prev->left = tmp->right;
                }
                delete tmp;
            }
        }else if (val < current->value){
            current->left = delRec(current->left, val);
        }else{
            current->right = delRec(current->right, val);
        }
        updateHeight(current);
        return current;
    }
    BSTNode<T>* findRec(BSTNode<T> *current,T val){
        if(current->value == val){
            return current;
        }else if (val < current->value&&current->left){
            return findRec(current->left, val);
        }else if (val > current->value&&current->right){
            return findRec(current->right, val);
        }
        return nullptr;
    }
    void printRangeRec(BSTNode<T>* node, int start, int end){
        if(!node){
            return;
        }
        if(node->value>start){
            printRangeRec(node->left, start, end);
        }
        if(node->value>=start&&node->value<=end){
            cout<<node->value<<" ";
        }
        if(node->value<end){
            printRangeRec(node->right, start, end);
        }
    }
    bool static subTreeRec(BSTNode<T>* t1, BSTNode<T>*t2){
        if(!t1&&!t2){
            return true;
        }else if(!t1||!t2||t1->value!= t2->value){
            return false;
        }
        return subTreeRec(t1->left,t2->left)&&subTreeRec(t1->right,t2->right);
    }
    void updateHeight(BSTNode<T>* node){
        node->height = 1+max((node->left)?node->left->height:0,(node->right)?node->right->height:0);
    }

public:
    BST<T>(){ parent = nullptr;}
    BSTNode<T>* getParent(){return parent;}

    void Insert(T val){
        parent = insRec(parent, val);
    }
    void Delete(T val){
        parent = delRec(parent,val);
    }
    BSTNode<T>* Find(T val){
        return findRec(parent,val);
    }
    bool isBalance(){
        int lft=0,rht=0;
        if(parent->left)
            lft=parent->left->height;
        if(parent->right)
            rht=parent->right->height;
        int balance = lft-rht;
        return (balance>=-1&&balance<=1);
    }
    bool static isSubTree(BST* t1, BST* t2){
        if(t1->Find(t2->parent->value)){
            BSTNode<T>* start = t1->Find(t2->parent->value);
            return subTreeRec(start, t2->parent);
        } else{
            return false;
        }
    }
    void printRange(int start,int end){
        printRangeRec(parent, start, end);
        cout<<endl;
    }
    void preorder(BSTNode<T> *n){
        if(n== nullptr){
            return;
        }
        cout<<n->value<<" ";
        preorder(n->left);
        preorder(n->right);
    }
    void inorder(BSTNode<T> *n){
        if(n== nullptr){
            return;
        }
        inorder(n->left);
        cout<<n->value<<" ";
        inorder(n->right);
    }
    void postorder(BSTNode<T> *n){
        if(n== nullptr){
            return;
        }
        postorder(n->left);
        postorder(n->right);
        cout<<n->value<<" ";
    }
    void breadthFirst(){
        queue<BSTNode<T>*> q;
        q.push(parent);
        while(!q.empty()){
            if(q.front()->left!= nullptr){
                q.push(q.front()->left);
            }
            if(q.front()->right!= nullptr){
                q.push(q.front()->right);
            }
            cout<<q.front()->value<<" ";
            q.pop();
        }
        cout<<endl;
    }

};

int main() {
    BST<int> t,t1,t2,t3,t4,t5,t6,t7;
    t.Insert(10);
    t.Insert(11);
    t.Insert(5);
    t.Insert(3);
    t.Insert(7);
    t.Insert(6);
    t.Insert(8);
    t.Insert(9);
    t.Delete(11);
    BSTNode<int> *n2 = t.Find(7);
    cout<<"node is found and its left child is "<<n2->left->value<<" and its right child is "<<n2->right->value<<endl;
    cout<<"Preorder traversal of the constructed BST is: ";
    t.preorder(t.getParent());
    cout<<"\nInorder traversal of the constructed BST is: ";
    t.inorder(t.getParent());
    cout<<"\nPostorder traversal of the constructed BST is: ";
    t.postorder(t.getParent());
    cout<<"\nBreadth First Traversal of the constructed BST is: ";
    t.breadthFirst();
    cout<<"\ntest print range:\n";
    t1.Insert(5);
    t1.Insert(3);
    t1.Insert(7);
    t1.Insert(2);
    t1.Insert(4);
    t1.Insert(9);
    t1.Insert(1);
    t1.Insert(8);
    t1.Insert(10);
    t1.printRange(3,7);
    t1.printRange(6,6);
    t1.printRange(1,4);
    t1.printRange(2,2);
    t1.printRange(8,15);

    t2.Insert(5);
    t2.Insert(3);
    t2.Insert(7);
    t2.Insert(2);
    t2.Insert(4);
    t2.Insert(9);
    t2.Insert(1);
    t2.Insert(8);
    t2.Insert(10);

    t3.Insert(9);
    t3.Insert(8);
    t3.Insert(10);
    t4.Insert(3);
    t4.Insert(2);
    t4.Insert(4);
    t4.Insert(1);

    t5.Insert(20);
    t5.Insert(10);
    t5.Insert(30);
    t5.Insert(8);
    t5.Insert(12);
    t5.Insert(23);
    t5.Insert(28);
    t5.Insert(3);
    t5.Insert(9);
    t5.Insert(22);
    t5.Insert(24);
    t5.Insert(27);
    t5.Insert(29);
    t5.Insert(2);


    t6.Insert(10);
    t6.Insert(12);
    t6.Insert(8);
    t6.Insert(3);
    t6.Insert(9);
    t6.Insert(2);

    t7.Insert(6);
    t7.Insert(2);

    cout<<"\ntest isBalance:\n";
    if(t.isBalance()){
        cout<<"tree is balanced\n";
    }
    else{
        cout<<"tree is not balanced\n";
    }
    if(t1.isBalance()){
        cout<<"tree is balanced\n";
    }
    else{
        cout<<"tree is not balanced\n";
    }
    if(t2.isBalance()){
        cout<<"tree is balanced\n";
    }
    else{
        cout<<"tree is not balanced\n";
    }
    if(t3.isBalance()){
        cout<<"tree is balanced\n";
    }
    else{
        cout<<"tree is not balanced\n";
    }
    if(t5.isBalance()){
        cout<<"tree is balanced\n";
    }
    else{
        cout<<"tree is not balanced\n";
    }

    cout<<"\ntest isSubTree:\n";
    if(BST<int>::isSubTree(&t2, &t3)){
        cout<<"tree is subtree\n";
    }
    else{
        cout<<"tree is not subtree\n";
    }
    if(BST<int>::isSubTree(&t2, &t4)){
        cout<<"tree is subtree\n";
    }
    else{
        cout<<"tree is not subtree\n";
    }
    t4.Delete(1);
    if(BST<int>::isSubTree(&t2, &t4)){
        cout<<"tree is subtree\n";
    }
    else{
        cout<<"tree is not subtree\n";
    }
    if(BST<int>::isSubTree(&t5, &t6)){
        cout<<"tree is subtree\n";
    }
    else{
        cout<<"tree is not subtree\n";
    }
    if(BST<int>::isSubTree(&t5, &t7)){
        cout<<"tree is subtree\n";
    }
    else{
        cout<<"tree is not subtree\n";
    }

    return 0;
}
