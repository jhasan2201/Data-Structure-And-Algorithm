#include "iostream"
using namespace std;
//1. Insert Array
void insertArray(int arr[],int n){
    for (int i = 0; i < n; ++i) {
        cin>>arr[i];
    }
}
//2. Print Array
void printArray(int arr[],int n){
    for (int i = 0; i < n; ++i) {
        cout<<arr[i]<<" ";
    }
}

//3. Sorting Array
void sort(int arr[],int n){
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            if(arr[i]>arr[j]){
                swap(arr[i],arr[j]);
            }
        }
    }
}

//4. Insertion Sort
void insertionSort(int arr[],int n){
    for (int i = 0; i < n; ++i) {
        int curr=arr[i];                    //catch the element
        int j=i-1;                          //start traversing from before of curr's distance
        while (arr[j]>curr && j>=0){        //find the appropriate position {curr is greater than its previous value}
            arr[j+1]=arr[j];                //moving element forward
            j--;
        }
        arr[j+1]=curr;                     //jth element is smaller than curr
    }
}

//5. Selection Sort
void selectionSort(int arr[],int n){
    for (int i = 0; i < n-1; ++i) {
        int minVal=arr[i],minIdx=i;       //find minimum and minimum's index from the unsorted array
        for (int j = i+1; j < n; ++j) {
            if(arr[j]<minVal){
                minVal=arr[j];
                minIdx=j;
            }
        }
        arr[minIdx]=arr[i];             //swap minimum of the unsorted part with the current element
        arr[i]=minVal;
    }
}

//6. Bubble Sort
void bubbleSort(int arr[],int n){
    for (int i = 0; i < n-1; ++i) {            //stop second last
        for (int j = 0; j < n-1-i; ++j) {      //decrease ith step in every iteration (unsorted part)
            if(arr[j]>arr[j+1]){
                swap(arr[j],arr[j+1]);     //getting bubble of maximum value
            }
        }
    }
}

//7. Count Sort(problem)
void countSort(int arr[],int n){
    int freq[10]={0};                                   //frequency array
    for (int i = 0; i < n; ++i) {
        (freq[arr[i]])++;                               //count frequency
    }
    for (int i = 1; i < 10; ++i) {
        freq[i]+=freq[i-1];                             //count cumulative frequency
    }
    int output[n];
    for (int i = n-1; i >=0 ; --i) {
        output[--freq[arr[i]]]=arr[i];
    }
    for (int i = 0; i < n; ++i) {
        arr[i]=output[i];
    }
}

//8. Quick Sort
void swap(int arr[],int i,int j){        //swap element by index
    int temp=arr[i];
    arr[i]=arr[j];
    arr[j]=temp;
}
int partition(int arr[],int start,int end){
    int pivot=arr[end];                            //we assume,last element is pivot(an element which's less value belongs to left of the array)
    int j=start-1;                                 //starting from before start
    for (int i = start; i <= end; ++i) {
        if(arr[i]<pivot){                          //if less than pivot inside left side of pivot
            j++;                                   //increment j and insert in the jth index
            swap(arr,i,j);                         //insert
        }
    }
    swap(arr,j+1,end);                        //place pivot(an element which's less value belongs to left of the array)
    return j+1;
}
void quickSort(int arr[],int start,int end){
    if(start>=end){
        return;
    }
    int pi= partition(arr,start,end);           //find partition index
    quickSort(arr,start,pi-1);              //sort left side of partition         (partition is sorted)
    quickSort(arr,pi+1,end);                //sort right side of partition
}

//9. Merge Sort
void merge(int arr[],int start,int mid,int end){
    //(start)-----(mid+1)-----(end+1)
    int s1=(mid+1)-start;
    int s2=end-mid;                            //(end+1)-(mid+1) == end-mid
    int subArr1[s1];
    int subArr2[s2];
    for (int i = 0; i < s1; ++i) {              //distribute array to two sub array
        subArr1[i]=arr[start+i];
    }
    for (int i = 0; i < s2; ++i) {
        subArr2[i]=arr[(mid+1)+i];
    }
    int i=0,j=0,k=start;
    while (i<s1 && j<s2){                      //compare two subarray and insert lesser value
        if(subArr1[i] < subArr2 [j]){
            arr[k]=subArr1[i];
            i++; k++;
        }
        else{
            arr[k]=subArr2[j];
            j++; k++;
        }
    }
    while (i<s1){                        //if subarray2 end :: insert remaining subarray1 element
        arr[k]=subArr1[i];
        i++; k++;
    }
    while (j<s2){                      //if subarray1 end :: insert remaining subarray2 element
        arr[k]=subArr2[j];
        j++; k++;
    }

}
void mergeSort(int arr[],int start,int end){
    if(start>=end){
        return;
    }
    int mid=(start+end)/2;
    mergeSort(arr,start,mid);             //sort start to mid
    mergeSort(arr,mid+1,end);            //sort mid+1 to end
    merge(arr,start,mid,end);                //merge them all subArray
}

//10. Wave Sort
void waveSort(int arr[],int n){
    for (int i = 1; i < n; i+=2) {
        if(arr[i]>arr[i-1]){
            swap(arr,i,i-1);
        }
        if(arr[i]>arr[i+1]  && i<=n-2){
            swap(arr,i,i+1);
        }
    }
}

//11. DNF Sort
void dnfSort(int arr[],int n){
    int low=0,mid=0,high=n-1;
    while (mid<=high){
        if(arr[mid]==0){
            swap(arr,low,mid);
            low++;
            mid++;
        }
        else if(arr[mid]==1){
            mid++;
        }else{
            swap(arr,mid ,high);
            high--;
        }
    }
}

int main(){

    int n;
    cout<<"Size of array:";
    cin>>n;
    int *arr=new int(n);
    int data,choice;
    cout<<"Choice:";
    cin>>choice;
    while (choice){
        switch (choice) {
            case 1:{
                insertArray(arr,n);
                break;
            }
            case 2:{
                printArray(arr,n);
                cout<<endl;
                break;
            }
            case 3:{
                sort(arr,n);
                break;
            }
            case 4:{
                insertionSort(arr,n);
                break;
            }
            case 5:{
                selectionSort(arr,n);
                break;
            }
            case 6:{
                bubbleSort(arr,n);
                break;
            }
            case 7:{
                int countArr[7]={7,5,3,1,5,9,3};
                countSort(countArr,n);
                printArray(countArr,n);
                break;
            }
            case 8:{
                quickSort(arr,0,n-1);
                break;
            }
            case 9:{
                mergeSort(arr,0,n-1);
                break;
            }
            case 10:{
                waveSort(arr,n);
                break;
            }
            case 11:{
              //  dnfSort();

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