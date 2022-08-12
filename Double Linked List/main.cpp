#include <iostream>
using namespace std;

template <class T>
struct dlNode{
    T info;
    dlNode<T> *prev, *next;
    dlNode(T info, dlNode<T>* prv = NULL, dlNode<T>* nxt = NULL){
        this->info=info;
        this->prev=prv;
        this->next=nxt;
    }
};

template<class T>
class list{
private:
    dlNode<T> *head, *tail;
    int Size;
public:
    class iterator{
    private:
        dlNode<T> *nodePtr;
    public:
        iterator(dlNode<T> *p = NULL){
            nodePtr = p;
        }
        dlNode<T>* getnodePtr(){
            return nodePtr;
        };
        iterator operator++(int num){
            iterator tmp = *this;
            nodePtr = nodePtr->next;
            return tmp;
        }
        iterator operator++(){
            nodePtr = nodePtr->next;
            return *this;
        }
        iterator operator--(int num){
            iterator tmp = *this;
            nodePtr = nodePtr->prev;
            return tmp;
        }
        iterator operator--(){
            nodePtr = nodePtr->prev;
            return *this;
        }
        iterator operator+=(int num){
            iterator *tmp = this;
            while (num--){
                nodePtr = nodePtr->next;
            }
            return *this;
        }
        iterator operator-=(int num){
            iterator *tmp = this;
            while (num--){
                nodePtr = nodePtr->prev;
            }
            return *this;
        }
        T& operator*(){
            return nodePtr->info;
        }
        bool operator==(const iterator& Node){
            return (nodePtr == Node.nodePtr);
        }
        bool operator!=(const iterator& Node){
            return (nodePtr != Node.nodePtr);
        }
    };

    list(){
        head = tail = NULL;
        Size = 0;
    }

    ~list(){
        //deallocate();
    }

    list(T info, int initial_size){
        head = tail = NULL;
        for (int i = 0; i < initial_size; ++i) {
            push_back(info);
        }
    }

    list<T>& operator =(const list<T>& another_list){
        if(this != &another_list){
            clear();
            dlNode<T> *tmp = another_list.head;
            while(tmp != NULL){
                push_back(tmp->info);
                tmp = tmp->next;
            }
        }
        return *this;
    }
    void push_front(T info){
        dlNode<T> *Ptr = new dlNode<T>(info);
        if(!head){
            head = tail = Ptr;
        }else{
            head->prev=Ptr;
            Ptr->next=head;
            head=Ptr;
        }
        Size++;
    }
    void push_back(T info){
        dlNode<T> *Ptr = new dlNode<T>(info);
        if(!head){
            head = tail = Ptr;
        }else{
            Ptr->prev=tail;
            tail->next=Ptr;
            tail=Ptr;
        }
        Size++;
    }
    void insert(iterator loc, T info){
        if (loc.getnodePtr()==tail){
            push_back(info);
        }else{
            dlNode<T> *Node = new dlNode<T>(info);
            loc.getnodePtr()->prev->next = Node;
            Node->prev = loc.getnodePtr()->prev;
            Node->next = loc.getnodePtr();
            loc.getnodePtr()->prev = Node;
            Size++;
        }
    }
    void pop_front(){
        dlNode<T>* Ptr=head;
        if(head==tail){
            head=tail=NULL;
        }else{
            head=head->next;
            head->prev=NULL;
        }
        delete Ptr;
        Size--;
    }
    void pop_back(){
        dlNode<T>* Ptr = tail;
        if(head==tail){
            head=tail=NULL;
        }else{
            tail = tail->prev;
            tail->next = NULL;
        }
        delete Ptr;
        Size--;
    }
    iterator remove(iterator loc){
        dlNode<T>* Ptr = loc.getnodePtr()->prev;
        if (loc.getnodePtr()==tail){
            pop_back();
        }else{
            Ptr->next=loc.getnodePtr()->next;
            loc.getnodePtr()->next->prev = Ptr;
            Size--;
        }
        delete loc.getnodePtr();
        return iterator(Ptr);
    }
    iterator search(T info){
        dlNode<T>* Ptr = head;
        while(Ptr&&Ptr->info!=info){
            Ptr = Ptr->next;
        }
        return iterator(Ptr);
    }

    void clear(){
        dlNode<T> *tmp;
        while(head != NULL){
            tmp = head;
            head = head->next;
            delete tmp;
        }
        Size = 0;
    }

    int size(){
        return Size;
    }
    T front(){
        return head->info;
    }
    T back(){
        return tail->info;
    }
    iterator begin(){
        return iterator(head);
    }
    iterator end(){
        return iterator(tail->next);
    }
    iterator rbegin(){
        return iterator(tail);
    }
    iterator rend(){
        dlNode<T> tmp(0,NULL,head);
        return iterator(tmp);
    }
    template<class T2>
    friend ostream& operator<<(ostream&, list<T2>);
};
template<class T2>
ostream &operator<<(ostream &out, list<T2> lst) {
    auto it = lst.begin();
    while(it != lst.end()){
        out<<*it<<" ";
        it++;
    }
    out<<"\n";
    return out;
}




int main()
{
    list<int> intList1;
    intList1.push_back(2);
    intList1.push_back(5);
    intList1.push_back(8);
    intList1.push_back(3);
    intList1.push_back(1);
    intList1.push_back(9);
    intList1.push_back(5);
    cout<<"list #1 : ";
    cout<<intList1;
    cout<<"size of list #1 : "<<intList1.size()<<endl;
    list<int>::iterator it = intList1.begin();
    it++,it++;
    list<int>::iterator temp=intList1.remove(it);
    cout<<"the value of iterator returned after erase : "<<*temp<<endl;
    cout<<"list #1 after erase : ";
    cout<<intList1;
    cout<<"size of list #1 after erase : "<<intList1.size()<<endl;
    list<int> intList2(10, 5); //list #2 with initial size
    cout<<"list #2 : ";
    cout<<intList2;
    intList2=intList1;
    cout<<"list #2 after copy values of list 1: ";
    cout<<intList2;
    it=intList2.begin();
    it+=2; //to insert in list #2 in position 3
    intList2.insert(it,11);
    cout<<"list #2 after inserting value '11' : ";
    cout<<intList2;
    cout<<"size of list #2 : "<<intList2.size()<<endl;
    return 0;
//    list<int> intList1;
//    intList1.push_back(2);
//    intList1.push_back(5);
//    intList1.push_back(8);
//    intList1.push_back(3);
//    intList1.push_back(1);
//    intList1.push_back(9);
//    intList1.push_back(5);
//    cout<<"list #1 : ";
//    cout<<intList1;
//    list<int>::iterator it = intList1.begin();
//    it++;
//    cout<<*++it<<endl;
//    it = intList1.remove(it);
//    cout<<*it<<endl;
//    intList1.pop_back();
//    intList1.push_back(7);
//    intList1.push_front(2);
//
//    cout<<"list #1 : ";
//    cout<<intList1;
//    list<int> t(5,3);
//    t = intList1;
//    cout<<"list #1 : ";
//    cout<<t;
//    return 0;
}
