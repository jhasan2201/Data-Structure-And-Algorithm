#include "iostream"
using namespace std;

int getBit(int n,int pos){
    return ((n & (1<<pos))!=0);
}
int setBit(int n,int pos){
    return (n | (1<<pos));
}
int clearBit(int n,int pos){
    int mask=~(1<<pos);
    return (n & mask);
 }
int updateBit(int n,int pos,int value){
    int mask=~(1<<pos);
    n = n & mask;
    return (n | (value<<pos));
}
bool isPowerOf2(int n){
    return (n && !(n & n-1));
}
int numberOfOnes(int n){
    int count=0;
    while (n){
        n = n & (n-1);
        count++;
    }
    return count;
}
void subSets(int arr[],int n){
    for (int i = 0; i < (1<<n); i++) {
        for (int j = 0; j < n; ++j) {
            if( i & (1<<j)){
                cout<<arr[j]<<" ";
            }
        }
        cout<<endl;
    }
}
int oneUniqueFinder(int arr[],int n){
    int xorSum=0;
    for (int i = 0; i < n; ++i) {
        xorSum = xorSum^arr[i];
    }
    return xorSum;
}
void twoUniqueFinder(int arr[],int n){
    int xorSum=0;
    for (int i = 0; i < n; ++i) {
        xorSum=xorSum^arr[i];
    }
    int tempXor=xorSum;
    int setbits=0,pos=0;
    while (setbits!=1){
        setbits =xorSum&1;
        pos++;
        xorSum =xorSum >> 1;
    }
    int newXor=0;
    for (int i = 0; i < n; ++i) {
        if(getBit(arr[i],pos-1)){
            newXor=newXor^arr[i];
        }
    }
    cout<<newXor<<endl;
    cout<<(newXor^tempXor)<<endl;
}
int oneUniqIntripleRepeatation(int arr[],int n){
    int result=0;
    for (int i = 0; i <64 ; ++i) {
        int sum=0;
        for (int j = 0; j < n; ++j) {
            if(getBit(arr[j],i)){
                sum++;
            }
        }
        if(sum%3!=0){
            result= setBit(result,i);
        }
    }
    return result;
}

int main(){
    int choice;
    cout<<"Choice:";
    cin>>choice;
    while (choice){
        switch (choice) {
            case 1:{
                cout<<getBit(5,2)<<endl;
                break;
            }
            case 2:{
                cout<<setBit(5,1)<<endl;
                break;
            }
            case 3:{
                cout<<clearBit(5,2)<<endl;
                break;
            }
            case 4:{
                cout<<updateBit(5,1,1)<<endl;
                break;
            }
            case 5:{
                cout<<isPowerOf2(16)<<endl;
                break;
            }
            case 6:{
                cout<<numberOfOnes(7)<<endl;
                break;
            }
            case 7:{
                int arr[3]={1,2,3,};
                cout<<"Subsets"<<endl;
                subSets(arr,3);
                break;
            }
            case 8:{
                int xorFindArr[7]={1,2,3,4,1,2,3};
                cout<<oneUniqueFinder(xorFindArr,7)<<endl;
                break;
            }
            case 9:{
                int xorFindArr2[8]={1,2,3,5,6,1,2,3};
                twoUniqueFinder(xorFindArr2,8);
                break;
            }
            case 10:{
                int threeRepeat[10]={1,2,3,4,1,2,3,1,2,3};
                cout<<oneUniqIntripleRepeatation(threeRepeat,10)<<endl;
                break;
            }
        }

        cout<<"Choice:";
        cin>>choice;
    }
}


