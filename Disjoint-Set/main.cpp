#include <iostream>

using namespace std;

class Node {
public:
    int rank,parent;
    Node(int parent, int rank) {
        this->parent = parent;
        this->rank = rank;
    }
    Node() {
        this->parent = -1;
        this->rank = 0;
    }
};

class DisjointSet {
private:
    int n;
    Node *children;
public:
    DisjointSet(int n) {
        this->children = new Node[n + 1];
        this->n = n;
        makeSet();
    }
    void makeSet() {
        for (int i = 0; i <= n; i++) {
            children[i] = Node(i, 1);
        }
    }
    int find(int x) {
        if (children[x].parent != x) {
            return find(children[x].parent);
        }
        return children[x].parent;
    }
    void Union(int x, int y) {
        int xset = find(x);
        int yset = find(y);
        if (xset != yset) {
            if(children[xset].rank < children[yset].rank){
                children[xset].parent = yset;
                children[yset].rank += children[xset].rank;
            }else {
                children[yset].parent = xset;
                children[xset].rank += children[yset].rank;
            }
        } else {
            cout << "Already in the same set" << endl;
        }
    }

};

int main() {
    DisjointSet ds(5);
    ds.Union(1, 2);
    ds.Union(2, 3);
    ds.Union(4, 5);
    ds.Union(3, 5);
    cout << ds.find(1) << endl;
    cout << ds.find(2) << endl;
    cout << ds.find(3) << endl;
    cout << ds.find(4) << endl;
    cout << ds.find(5) << endl;
    return 0;
}
