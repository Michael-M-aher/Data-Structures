#include <iostream>
#include <queue>
using namespace std;

template<class T>
struct BSTNode{
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
        return Balance(current);
    }
    BSTNode<T>* delRec(BSTNode<T> *current,T val){
        if(current->value == val){
            BSTNode<T>* tmp = current;
            if(current->left == nullptr){
                current = current->right;
                return current;
            }else if(current->right == nullptr){
                current = current->left;
                return current;
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
            }
            delete tmp;
        }else if (val < current->value){
            current->left = delRec(current->left, val);
        }else{
            current->right = delRec(current->right, val);
        }
        updateHeight(current);
        return Balance(current);
    }
    BSTNode<T>* findRec(BSTNode<T> *current,T val){
        if(current->value == val){
            return current;
        }else if (val < current->value){
            return findRec(current->left, val);
        }else{
            return findRec(current->right, val);
        }
    }

    void updateHeight(BSTNode<T>* node){
        node->height = 1+max((node->left)?node->left->height:0,(node->right)?node->right->height:0);
    }
    int getBalance(BSTNode<T>* node){
        int lft=0,rht=0;
        if(node->left)
            lft=node->left->height;
        if(node->right)
            rht=node->right->height;
        return (lft-rht);
    }

    BSTNode<T>* Balance(BSTNode<T>* node){
        int balance = getBalance(node);
        if(balance > 1 && getBalance(node->left) >= 0){
            return rightRotate(node);
        }
        if(balance > 1 && getBalance(node->left) < 0){
            node->left= leftRotate(node->left);
            return rightRotate(node);
        }
        if(balance < -1 && getBalance(node->right) <= 0){
            return leftRotate(node);
        }
        if(balance < -1 && getBalance(node->right) > 0){
            node->right= rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

public:
    BST<T>(){parent = nullptr;}
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

    BSTNode<T>* leftRotate(BSTNode<T>* node){
        BSTNode<T>* rht = node->right;
        node->right = rht->left;
        rht->left = node;
        updateHeight(rht);
        updateHeight(node);
        return rht;
    }
    BSTNode<T>* rightRotate(BSTNode<T>* node){
        BSTNode<T>* lft = node->left;
        node->left = lft->right;
        lft->right = node;
        updateHeight(lft);
        updateHeight(node);
        return lft;
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
    void levelprint(){
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

    }
};

int main() {
    BST<int> t;
    t.Insert(9);
    t.Insert(10);
    t.Insert(5);
    t.Insert(3);
    t.Insert(7);
    t.Insert(6);
    t.Insert(8);
    t.Delete(9);
    t.Delete(10);
    t.Delete(8);
//    t.Delete(5);
//    BSTNode<int> *n2 = t.Find(7);
//    cout<<n2->left->value;
    t.preorder(t.getParent());
    cout<<endl;
    t.inorder(t.getParent());
    cout<<endl;
    t.postorder(t.getParent());
    cout<<endl;
    t.levelprint();
    return 0;
}
