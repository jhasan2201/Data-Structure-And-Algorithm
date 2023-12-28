#include "iostream"

using namespace std;

//Max Heap
class MaxHeap{
public:
    int arr[100];
    int size;
    MaxHeap(){
        arr[0]=-1;
        size=0;
    }

    //2. Insert in heap
    void insert(int val){
        size++;
        int index=size;
        arr[index]=val;                          //add at last of the CBT(complete binary tree)

        while (index>1){
            int parent=index/2;              //get index of parent::
            if(arr[parent] < arr[index]) {            //check if is it greater than his parent
                swap(arr[parent], arr[index]);     //true:: swap and it's index become his parent index
                index = parent;
            }
            else{                        //false :: maxHeap rules maintain :: exit
                return;
            }
        }
    }

    //1. Print heap
    void printHeap(){
        for (int i = 1; i <=size ; ++i) {
            cout<<arr[i]<<" ";
        }
    }

    //3. Delete from heap
    void deleteFromHeap(){
        if(size==0){
            cout<<"Nothing to delete"<<endl;
            return;
        }

        arr[1]=arr[size];              //assign last element to first position
        size--;                       //ignore last element

        int i=1;                     //count from first
        while (i<size){             //till last
            int leftIndex=2*i;         //get left child index
            int rightIndex=2*i+1;         //get right child index

            if(leftIndex<size && arr[i]<arr[leftIndex]){          //check array-out-of-bound and if parent is less than leftchild :: swap them
                swap(arr[i],arr[leftIndex]);
                i=leftIndex;                                         //jump to the left child position
            }
            else if(rightIndex<size && arr[i]<arr[rightIndex]){     //check array-out-of-bound and if parent is less than rightchild :: swap them
                swap(arr[i],arr[rightIndex]);
                i=rightIndex;                                           //jump to the right child position
            }
            else{
                return;
            }
        }
    }
};


//4. Make a heap from array
void maxHeapify(int arr[],int n,int i){
    int largestIndex=i;       //get i as largestIndex
    int leftIndex=2*i;       //its left
    int rightIndex=2*i+1;    //its right

    if(leftIndex<=n && arr[largestIndex]<arr[leftIndex]){      //if left child is greater than parent
        largestIndex=leftIndex;                               //largestIndex --> left child index
    }
    if(rightIndex<=n && arr[largestIndex]<arr[rightIndex]){      //if right child is greater than parent
        largestIndex=rightIndex;                                //largestIndex --> right child index
    }

    if(largestIndex != i){                    //if any change occur
        swap(arr[largestIndex],arr[i]);
        maxHeapify(arr,n,largestIndex);     //check its child recursively
    }
}
void makeMaxHeap(int arr[],int n){
    for (int i = n/2; i >0 ; --i) {    //for ignoring leaf element  --  leaf element belong to from {n/2 to n}
        maxHeapify(arr,n,i);
    }
}

//5. Heap sort of the array
void heapSort(int arr[],int n){
    int size=n-1;
    while (size > 1){                     //array traverse :: last to first(2nd index)
        swap(arr[size],arr[1]);      //swap :: last element to first
        size--;                             //make first last element(max value of array) out of consider

        maxHeapify(arr,size,1);         //take first element to its correct position(heapify)
    }
}
void printHeap(int arr[],int n){
    for (int i = 1; i < n; ++i) {
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

//Min Heap
class MinHeap{
public:
    int arr[100];
    int size;
    MinHeap(){
        arr[0]=-1;
        size=0;
    }

    //7. Insert in heap
    void insert(int val){
        size++;
        int index=size;
        arr[index]=val;

        while (index>1){
            int parent=index/2;
            if(arr[parent]>arr[index]){
                swap(arr[parent],arr[index]);
                index=parent;
            }
            else{
                return;
            }
        }
    }

    //6. Print heap
    void printHeap(){
        for (int i = 1; i <=size ; ++i) {
            cout<<arr[i]<<" ";
        }
        cout<<endl;
    }

    //8. Delete from heap
    void deleteFromHeap(){
        if(size==0){
            cout<<"Nothing to delete"<<endl;
            return;
        }

        arr[1]=arr[size];
        size--;

        int i=1;
        while (i<size){
            int leftIndex=2*i;
            int rightIndex=2*i +1;
            if(leftIndex<size && arr[i]>arr[leftIndex]){
                swap(arr[i],arr[leftIndex]);
                i=leftIndex;
            }
            else if(rightIndex<size && arr[i]>arr[rightIndex]){
                swap(arr[i],arr[rightIndex]);
                i=rightIndex;
            }
            else{
                return;
            }
        }
    }
};

//9. Make a heap from array
void minHeapify(int arr[],int n,int i){
    int smallestIndex=i;
    int leftIndex=2*i;
    int rightIndex=2*i+1;

    if(leftIndex<n && arr[smallestIndex]>arr[leftIndex]){
        smallestIndex=leftIndex;
    }
    if(rightIndex<n && arr[smallestIndex]>arr[rightIndex]){
        smallestIndex=rightIndex;
    }

    if(smallestIndex != i){
        swap(arr[smallestIndex],arr[i]);
        minHeapify(arr,n,smallestIndex);
    }
}
void makeMinHeap(int arr[],int n){
    for (int i = n/2; i > 0; --i) {
        minHeapify(arr,n,i);
    }
}

//10. Heap sort of the array
void minHeapSort(int arr[],int n){
    int size=n-1;
    while (size>1){
        swap(arr[size],arr[1]);
        size--;

        minHeapify(arr,size,1);
    }
}



int main(){


    MaxHeap h;
    h.insert(6);
    h.insert(10);
    h.insert(9);
    h.insert(5);
    h.insert(12);
    h.insert(1);

    MinHeap mh;
    mh.insert(10);
    mh.insert(5);
    mh.insert(12);
    mh.insert(1);
    mh.insert(6);
    mh.insert(9);


    int data,choice;
    cout<<"Choice:";
    cin>>choice;
    while (choice){
        int n=11;
       // int arr[12]={-1,45,96,28,36,89,46,102,56,3,99,5};
       int arr[11]={-1,33,21,35,78,12,5,10,66,29,9};
        switch (choice) {
            case 1:{
                h.printHeap();
                break;
            }
            case 2:{
                cout<<"Data:";
                cin>>data;
                h.insert(data);
                break;
            }
            case 3:{
                h.deleteFromHeap();
                break;
            }
            case 4:{

                makeMaxHeap(arr,n);
                printHeap(arr,n);
                break;
            }
            case 5:{
                makeMaxHeap(arr,n);
                heapSort(arr,n);
                printHeap(arr,n);
                break;
            }
            case 6:{
                mh.printHeap();
                break;
            }
            case 7:{
                cout<<"Data:";
                cin>>data;
                mh.insert(data);
                break;
            }
            case 8:{
                mh.deleteFromHeap();
                break;
            }
            case 9:{
                makeMinHeap(arr,n);
                printHeap(arr,n);
                break;
            }
            case 10:{
                makeMinHeap(arr,n);
                minHeapSort(arr,n);
                printHeap(arr,n);
                break;
            }




            default:{
                cout<<"invalid selection"<<endl;
            }
        }
        cout<<"Choice:";
        cin>>choice;
    }

}
