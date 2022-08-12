#include <iostream>

using namespace std;

template<class T>
void Swap(T& e1,T& e2){
    T temp = e1;
    e1 = e2;
    e2 = temp;
}

template<class T>
T GetMax(T* arr,int n){
    T mx = arr[0];
    for (int i = 1; i < n; ++i) {
        if(arr[i]>mx){
            mx = arr[i];
        }
    }
    return mx;
}

template<class T>
class Sorter{
public:
    virtual void sort(T* arr,int n){};
};

// Time Complexity ⌛
// Worst -> O(n^2)
// Average -> θ(n^2)
// Best -> Ω(n)
// Space Complexity 💾
// Worst -> O(1)
template<class T>
class InsertionSort : public Sorter<T> {
public:
    void sort(T* arr,int n){
        for (int i = 1; i < n; ++i) {
            T temp = arr[i];
            int j;
            for (j = i; j > 0 && arr[j-1]>temp; --j) {
                arr[j]=arr[j-1];
            }
            arr[j] = temp;
        }
    };
};

// Time Complexity ⌛
// Worst -> O(n^2)
// Average -> θ(n^2)
// Best -> Ω(n^2)
// Space Complexity 💾
// Worst -> O(1)
template<class T>
class SelectionSort : public Sorter<T> {
public:
    void sort(T* arr,int n){
        for (int i = 0; i < n; ++i) {
            T mn = arr[i];
            int idx = i;
            for (int j = i; j < n; ++j) {
                if(arr[j]<mn){
                    mn = arr[j];
                    idx = j;
                }
            }
            Swap(arr[i],arr[idx]);
        }
    };
};

// Time Complexity ⌛
// Worst -> O(n^2)
// Average -> θ(n^2)
// Best -> Ω(n)
// Space Complexity 💾
// Worst -> O(1)
template<class T>
class BubbleSort : public Sorter<T> {
public:
    void sort(T* arr,int n){
        for (int i = 0; i < n-1; ++i) {
            for (int j = 0; j < n-1-i; ++j) {
                if(arr[j]>arr[j+1]){
                    Swap(arr[j],arr[j+1]);
                }
            }
        }
    };
};

// Time Complexity ⌛
// Worst -> O(n*(log(n)^2))
// Average -> θ(n*(log(n)^2))
// Best -> Ω(n*log(n))
// Space Complexity 💾
// Worst -> O(1)
template<class T>
class ShellSort : public Sorter<T> {
public:
    void sort(T* arr,int n){
        int gap = n/2;
        while(gap>0){
            for (int i = gap; i < n; ++i) {
                for (int j = i; j >= gap && arr[j-gap]>arr[j]; j-=gap) {
                    Swap(arr[j],arr[j-gap]);
                }
            }
            gap/=2;
        }
    };
};

// Time Complexity ⌛
// Worst -> O(n+k)
// Average -> θ(n+k)
// Best -> Ω(n+k)
// Space Complexity 💾
// Worst -> O(k)
template<class T>
class CountSort : public Sorter<T> {
public:
    void sort(T* arr,int n){
        int mx = GetMax(arr,n);mx++;
        int tmp[n];
        int *cum = new int[mx];

        for (int i = 0; i < n; ++i) {
            tmp[i]=arr[i];
        }

        for (int i = 0; i < mx; ++i) {
            cum[i]=0;
        }

        for (int i = 0; i < n; ++i) {
            cum[tmp[i]]++;
        }

        for (int i = 1; i < mx; ++i) {
            cum[i]+=cum[i-1];
        }

        for (int i = n-1; i >= 0; --i) {
            arr[--cum[tmp[i]]] =tmp[i];
        }
    };
};

// Time Complexity ⌛
// Worst -> O(n*k)
// Average -> θ(n*k)
// Best -> Ω(n*k)
// Space Complexity 💾
// Worst -> O(k)
template<class T>
class RadixSort : public Sorter<T> {
public:
    void sort(T* arr,int n){
        int mx = GetMax(arr,n);
        int tmp[n];

        for (int exp = 1; mx/exp>0; exp*=10) {
            for (int i = 0; i < n; ++i) {
                tmp[i]=arr[i];
            }

            int cum[10] = {0};

            for (int i = 0; i < n; ++i) {
                cum[(tmp[i]/exp)%10]++;
            }

            for (int i = 1; i < 10; ++i) {
                cum[i]+=cum[i-1];
            }

            for (int i = n-1; i >= 0; --i) {
                arr[--cum[(tmp[i]/exp)%10]] =tmp[i];
            }
        }
    };
};

// Time Complexity ⌛
// Worst -> O(n*log(n))
// Average -> θ(n*log(n))
// Best -> Ω(n*log(n))
// Space Complexity 💾
// Worst -> O(n)
template<class T>
class MergeSort : public Sorter<T> {
private:
    void MergRec(T*arr , int lft, int rht){
        if(lft==rht){
            return;
        }
        int mid = (lft+rht)/2;
        MergRec(arr,lft,mid);
        MergRec(arr,mid+1,rht);
        Merge(arr , lft, mid, rht);
    }
    void Merge(T*arr , int lft, int mid, int rht){
        int n1 = mid - lft + 1;
        int n2 = rht - mid;
        T arrL[n1],arrR[n2];
        for (int i = 0; i < n1; ++i) {
            arrL[i]=arr[lft+i];
        }
        for (int i = 0; i < n2; ++i) {
            arrR[i]=arr[mid+i+1];
        }
        int l = 0,r = 0,i=lft;
        while(l<n1&&r<n2){
            if(arrL[l]<arrR[r]){
                arr[i++]=arrL[l++];
            }else{
                arr[i++]=arrR[r++];
            }
        }

        while(l<n1){
            arr[i++]=arrL[l++];
        }

        while(r<n2){
            arr[i++]=arrR[r++];
        }
    }
public:
    void sort(T* arr,int n){
        MergRec(arr,0,n-1);
    };
};

// Time Complexity ⌛
// Worst -> O(n^2)
// Average -> θ(n*log(n))
// Best -> Ω(n*log(n))
// Space Complexity 💾
// Worst -> O(log(n))
template<class T>
class QuickSort : public Sorter<T> {
private:
    // Pivot is the last element of array
    void QuickRec(T* arr,int lft,int rht){
        if(lft>rht){
            return;
        }
        int piv = rht;
        int i =lft-1,j=lft;
        while(j<piv){
            if(arr[j]<arr[piv]){
                Swap(arr[++i],arr[j++]);
            }else{
                j++;
            }
        }
        Swap(arr[++i],arr[piv]);
        QuickRec(arr,lft,i-1);
        QuickRec(arr,i+1,rht);
    }

    // Pivot is the middle element of array
//    void QuickRec(T* arr,int lft,int rht){
//        int piv = (lft+rht)/2;
//        int i = lft,j=rht;
//        while (i<=j){
//            while (arr[i] < arr[piv])
//                i++;
//            while (arr[j] > arr[piv])
//                j--;
//            if (i <= j) {
//                Swap(arr[i++],arr[j--]);
//            }
//        }
//        if(lft<j){
//            QuickRec(arr,lft,j);
//        }
//        if(i<rht){
//            QuickRec(arr,i,rht);
//        }
//    }

public:
    void sort(T* arr,int n){
        QuickRec(arr,0,n-1);
    };
};

// Time Complexity ⌛
// Worst -> O(n*log(n))
// Average -> θ(n*log(n))
// Best -> Ω(n*log(n))
// Space Complexity 💾
// Worst -> O(1)
template<class T>
class HeapSort : public Sorter<T> {
private:
    int parent(int idx){
        return (idx-1)/2;
    };
    int left(int idx){
        return (2*idx+1);
    };
    int right(int idx){
        return (2*idx+2);
    };
    void MaxHeapify(T *arr, int i, int n){
        int lft = left(i),rht = right(i);
        int elem = i;
        if(lft<n && arr[lft]>arr[i]){
            elem = lft;
        }
        if(rht<n &&arr[rht]>arr[elem]){
            elem = rht;
        }
        if(elem != i){
            swap(arr[elem],arr[i]);
            MaxHeapify(arr,elem,n);
        }
    }
    void BuildHeap(T *arr, int n){
        for (int j = parent(n); j >=0 ; --j) {
            MaxHeapify(arr, j, n);
        }
    }
public:
    void sort(T* arr,int n){
        BuildHeap(arr, n);
        int s = n;
        while(s--){
            swap(arr[0],arr[s]);
            MaxHeapify(arr,0,s);
        }
    };
};

int main() {
    int x[11]={6,4,3,5,2,1,10,8,9,7,0};
//    int x[9]={1,12,5,26,7,14,3,7,2};
//    int x[10]={1,2,3,4,5,6,7,8,9,10};
    Sorter<int>* s;
    s = new HeapSort<int>;
    s->sort(x,11);
    for (auto i:x) {
        cout<<i<<" ";
    }
    return 0;
}
