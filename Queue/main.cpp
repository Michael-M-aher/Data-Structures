#include <iostream>
using namespace std;
template<class T>
struct slNode{
    T info;
    slNode<T>* next;
    slNode(T info, slNode<T>* Ptr = NULL){
        this->info=info;
        this->next=Ptr;
    }
};

template<class T>
class Queue{
private:
    slNode<T> *head,*tail;
    int Size;
public:
    Queue(){
        head=tail=NULL;
        Size = 0;
    }
    void push(T info){
        slNode<T> *tmp = new slNode<T>(info);
        if(!head){
            head=tail=tmp;
        }else{
            tail->next=tmp;
            tail = tmp;
        }
        Size++;
    }
    void pop(){
        slNode<T> *tmp = head;
        if(head==tail){
            head = tail = NULL;
        }else{
            head = head->next;
        }
        delete tmp;
        Size--;
    }
    T& front(){
        return head->info;
    }
    T& back(){
        return tail->info;
    }
    bool empty(){
        return Size==0;
    }
    int size(){
        return Size;
    }
    void clear(){
        slNode<T> *tmp;
        while(head!=NULL){
            tmp = head;
            head = head->next;
            delete tmp;
        }
    }
    ~Queue(){
        clear();
    }
};

int main() {
    Queue<int> s;
    s.push(5);
    s.push(4);
    s.push(3);
    s.push(8);
    s.pop();
    cout<<s.front()<<endl;
    cout<<s.back()<<endl;
    cout<<s.size()<<endl;
    return 0;
}
