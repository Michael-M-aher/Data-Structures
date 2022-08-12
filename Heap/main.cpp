#include <iostream>
using namespace std;

template<class T>
class Heap{
private:
    bool mx;
    T *arr;
    int cap;
    int size;
    void bottomUpHeapify(int i){
        while(i!=0&& mx?(arr[parent(i)] < arr[i]):(arr[parent(i)] > arr[i]) ){
            swap(arr[parent(i)],arr[i]);
            i = parent(i);
        }
    }
    void topDownHeapify(int i){
        int lft = left(i),rht = right(i);
        int elem = i;
        if(lft<size && (mx?arr[lft]>arr[i]:arr[lft]<arr[i])){
            elem = lft;
        }
        if(rht<size && (mx?arr[rht]>arr[elem]:arr[rht]<arr[elem])){
            elem = rht;
        }
        if(elem != i){
            swap(arr[elem],arr[i]);
            topDownHeapify(elem);
        }
    }
    void cpy(T *arr1,T *arr2,int arrLen){
        for (int i = 0; i < arrLen; ++i) {
            arr2[i]=arr1[i];
        }
    }
    void buildHeap(T *arr, int i,int n){
        for (int j = parent(i); j >=0 ; --j) {
            topDownHeapify(j);
        }
    }
public:
    Heap(){
        this->cap = 10;
        this->size = 0;
        this->mx = true;
        this->arr = new T[cap];
    };
    Heap(bool mx){
        this->cap = 10;
        this->size = 0;
        this->mx = mx;
        this->arr = new T[cap];
    };
    Heap(int cap,bool mx){
        this->cap = cap;
        this->size = 0;
        this->mx = mx;
        this->arr = new T[cap];
    };
    int parent(int idx){
        return (idx-1)/2;
    };
    int left(int idx){
        return (2*idx+1);
    };
    int right(int idx){
        return (2*idx+2);
    };
    void insertKey(T k){
        if(size==cap){
            T *temp = new T[cap];
            cpy(arr,temp,size);
            delete[] arr;
            cap *=2;
            arr = new T[cap];
            cpy(temp,arr,size);
            delete[] temp;
        }
        arr[size]=k;
        bottomUpHeapify(size);
        size++;
    };
    void deleteKey(int i){
        if(size == 1||i == size-1){
            size--;
            return;
        }
        size--;
        swap(arr[i],arr[size]);
        topDownHeapify(i);
    };
    void changeKey(int i, T new_val){
        T old = arr[i];
        arr[i]=new_val;
        if(mx){
            if(new_val>old){
                bottomUpHeapify(i);
            }else{
                topDownHeapify(i);
            }
        }else{
            if(new_val>old){
                topDownHeapify(i);
            }else{
                bottomUpHeapify(i);
            }
        }
    };
    T getTop() {
        return arr[0];
    }
    T extractTop(){
        T temp = arr[0];
        deleteKey(0);
        return temp;
    }

};

int main() {
    //min heap
    Heap<int> h(11, false);
    h.insertKey(3);
    h.insertKey(2);
    h.deleteKey(1);
    h.insertKey(15);
    h.insertKey(5);
    h.insertKey(4);
    h.insertKey(45);
    cout << h.extractTop() << " ";
    cout << h.getTop() << " ";
    h.changeKey(2, 1);
    cout << h.getTop()<<"\n";
    //max heap
    Heap<int> h1(11, true);
    h1.insertKey(80);
    h1.insertKey(72);
    h1.insertKey(79);
    h1.insertKey(45);
    h1.insertKey(58);
    cout << h1.extractTop() << " ";
    cout << h1.getTop() << " ";
    h1.changeKey(2, 82);
    cout << h1.getTop();
    return 0;
}
