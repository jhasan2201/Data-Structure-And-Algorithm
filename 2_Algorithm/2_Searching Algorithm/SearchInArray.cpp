#include "iostream"
using namespace std;
void insertArray(int arr[],int n){
    for (int i = 0; i < n; ++i) {
        cin>>arr[i];
    }
}
void printArray(int arr[],int n){
    for (int i = 0; i < n; ++i) {
        cout<<arr[i]<<" ";
    }
}
int linearSearch(int arr[],int n,int srch){
    for (int i = 0; i < n; ++i) {
        if(arr[i]==srch){
            return i;
        }
    }
    return -1;
}
int binarySearch(int arr[],int n,int srch){
    int start=0,end=n;
    while (start<=end){
        int mid=(start+end)/2;
        if(arr[mid]==srch){      //if found
            return mid;
        }
        else if(arr[mid]<srch){    //go to left of the mid   (ignore right)
            end=mid-1;
        }
        else{                       //go to right of the mid   (ignore left)
            start=mid+1;
        }
    }
    return -1;

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
                cout<<"Search:";
                cin>>data;
                int idx=linearSearch(arr,n,data);
                if(idx==-1){
                    cout<<"Not found"<<endl;
                }else{
                    cout<<"Found at "<<idx<<endl;
                }
                break;
            }
            case 4:{
                cout<<"Seach:";
                cin>>data;
                int idx=binarySearch(arr,n,data);
                if(idx==-1){
                    cout<<"Not found"<<endl;
                }else{
                    cout<<"Found at "<<idx<<endl;
                }
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