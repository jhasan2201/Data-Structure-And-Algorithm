#include "iostream"
#include "vector"
using namespace std;

//1.implementation of the factorial function.

int factorial(int n){
    if(n==0){                     //base::0 factorial is 1
        return 1;
    }
    return n * factorial(n-1);        // n * f(n-1)
}

//2.to calculate the power of x (x^y)

double power(double x,double y){
    if(y==0){
        return 1;
    }
    if(y>0){                           // if power positive
        return x* power(x,y-1);                          //x * f(y-1)
    }
    if(y<0){                          //if power is negative
        return  1/x * power(x,y+1) ;                    // (1/x) * f(y+1)
    }
}

//3.to print the n th Fibonacci number

int nthFibonacciNumber(int n){
    if(n==0){                          //oth fibonacci is 0
        return 0;
    }
    if(n==1){                          //1st fibonacci is 1
        return 1;
    }
    return nthFibonacciNumber(n-1) + nthFibonacciNumber(n-2);                          //f(i) = f(i-1) + f(i-2)
}

//4.  check if a given string is a palindrome or not

bool checkPalindrome(string str,int start,int end){
    if(start>end){                          //if false doesn't execute:: its palindome
        return true;
    }
    if(str[start]!=str[end]){                          //first and last element is not equal :: false
        return false;
    }

    return checkPalindrome(str,start+1,end-1);                          // f(start+1, end-1)
}

//5. to print the even numbers in a given range.

void printEven(int a,int b){
    if(a>b){                          //a is increasing
        return;
    }
    if(a%2==0){                          //if current a is even:: print
        cout<<a<<" ";
    }
    printEven(a+1,b);                          // f(a+1)
}
void printEven2(int a,int b){
    if(a>b){                          //b is decreasing
        return;
    }
    printEven(a,b-1);                          //b is going through a  and print while returning call
    if(b%2==0){                          //if even::
        cout<<b<<" ";
    }
}

//6. print an array of size n in given order.

void printArr(int *arr,int n){
    if(n==0){                          //if size is zero
        return;
    }

    cout<<arr[0]<<" ";                          //print array's first element
    printArr(arr+1,n-1);                          // f(arr+1,size--)
}
void printArr(int *arr,int i,int n){

    if(i==n){                          //if index is equal size
        return;
    }

    cout<<arr[i]<<" ";                          //print ith element
    printArr(arr,i+1,n);                          // f(arr+1)
}

//7.print an array of size n in reverse order

void printArrRev(int *arr,int n){
    if(n==0){
        return;
    }

    printArrRev(arr+1,n-1);
    cout<<arr[0]<<" ";
}
void printArrRev(int *arr,int i,int n){
    if(i==n){
        return;
    }
    printArrRev(arr,i+1,n);
    cout<<arr[i]<<" ";
}

//8.  find the sum of the elements of an array of size n
int sumOfArray(int *arr,int n){
    if(n==0){
        return 0;
    }
    return arr[0] + sumOfArray(arr+1,n-1);
}
int sumOfArray(int *arr,int i,int n){
    if(i==n){
        return 0;
    }
    return arr[i] + sumOfArray(arr,i+1,n);
}

//9.find the products of the elements of an array of size n

int productOfArray(int *arr,int n){
    if(n==0){
        return 1;
    }
    return arr[0] * productOfArray(arr+1,n-1);
}
int productOfArray(int *arr,int i,int n){
    if(i==n){
        return 1;
    }
    return arr[i] * productOfArray(arr,i+1,n);
}

//10.find the maximum of the elements of an array of size n

int maxOfArr(int *arr,int n){
    if(n==1){
        return arr[0];
    }
    return max(arr[0], maxOfArr(arr+1,n-1));
}
int maxOfArr(int *arr,int i,int n){
    if(i==n-1){
        return arr[i];
    }
    return max(arr[i], maxOfArr(arr,i+1,n));
}

//11.find the minimum of the elements of an array of size n

int minOfArr(int *arr,int n){
    if(n==1){
        return arr[0];
    }
    return min(arr[0], minOfArr(arr+1,n-1));
}
int minOfArr(int *arr,int i,int n){
    if(i==n-1){
        return arr[i];
    }
    return min(arr[i], minOfArr(arr,i+1,n));
}

//12. find the average of the elements of an array of size n
double findAvg(int *arr,int n){
    if(n==0){
        return 0;
    }
    return ((n-1)* findAvg(arr,n-1) +arr[n-1])/n;
}

//13.print the odd/even numbers of an array of n integers
void printArrEven(int *arr,int n){
    if(n==0){
        return;
    }
    if(arr[0]%2==0){
        cout<<arr[0]<<" ";
    }
    printArrEven(arr+1,n-1);
}

//14. print the prime numbers of an array of n integers
bool isPrime(int n,int i){
    if(i==n){
        return true;
    }
    if(n%i==0){
        return false;
    }
    return isPrime(n,i+1);
}
void printPrimeNumber(int *arr,int n){
    if(n==0){
        return;
    }
    if(isPrime(arr[0],2)){
        cout<<arr[0]<<" ";
    }
    printPrimeNumber(arr+1,n-1);
}
void printPrimeNumber(int *arr,int i,int n){
    if(i==n){
        return;
    }
    if(isPrime(arr[i],2)){
        cout<<arr[i]<<" ";
    }
    printPrimeNumber(arr,i+1,n);
}

//15. count the odd/even numbers of an array of n integers

int countOddNumber(int *arr,int n){
    int count=0;
    if(n==0){
        return 0;
    }

    if(arr[0]%2==0){
        count=0;
    }
    else{
        count =1;
    }

    return count + countOddNumber(arr+1,n-1);
}
int countEvenNumber(int *arr,int i,int n){
    int count=0;
    if(i==n){
        return 0;
    }

    if(arr[i]%2==0){
        count=1;
    }
    else{
        count =0;
    }

    return count + countEvenNumber(arr,i+1,n);
}

//16.  count the prime numbers of an array of n integers

int countPrimeNumber(int *arr,int n){
    int count=0;

    if(n==0){
        return 0;
    }

    if(isPrime(arr[0],2)){
        count=1;
    }
    else{
        count=0;
    }

    return count + countPrimeNumber(arr+1,n-1);
}
int countPrimeNumber(int *arr,int i,int n){
    int count=0;

    if(i==n){
        return 0;
    }

    if(isPrime(arr[i],2)){
        count=1;
    }
    else{
        count=0;
    }

    return count + countPrimeNumber(arr,i+1,n);
}

//17.find the maximum of a 2d array.

//18. count the prime numbers of a given 2d array.

//19. linear sum  (1 + 2 + 3 + ⋯)
void linearSeries(int n){
    if(n==0){
        return;
    }
    linearSeries(n-1);
    cout<<n<<" + ";
}
int linearSeriesSum(int n){
    if(n==0){
        return 0;
    }
    return n + linearSeriesSum(n-1);
}

//20. Square sum (1^2 + 2^2 + 3^2 + ⋯)

void squareSeries(int n){
    if(n==0){
        return;
    }
    squareSeries(n-1);
    cout<<n*n<<" + ";
}

int squareSeriesSum(int n){
    if(n==0){
        return 0;
    }
    return n*n + squareSeriesSum(n-1);
}

//21. 1∗3 + 2∗5 + 3∗7 + 4∗9 + ⋯

void series3(int n){
    if(n==0){
        return;
    }
    series3(n-1);
    cout<<n<<"*"<<(2*n -1)<<" + ";
}
int series3Sum(int n){
    if(n==0){
        return 0;
    }
    return n*(2*n -1) + series3Sum(n-1);
}

//22. 2∗3 + 4∗5 + 8∗7 + 16∗9 + ⋯

void series4(int n){
    if(n==0){
        return;
    }
    series4(n-1);

    cout<<power(2,n)<<"*"<<(2*n +1)<<" + ";
}

int series4Sum(int n){
    if(n==0){
        return 0;
    }

    return (power(2,n)*(2*n +1)) + series4Sum(n-1);
}

//23. 2∗3∗4 + 4∗5∗3 + 8∗7∗2 + 16∗9∗1 + ⋯

//24. the GCD of x and y

int findGCD(int larger,int smaller){            //not position sensitive
    if(smaller==0){
        return larger;
    }
    return findGCD(smaller,larger%smaller);
}

//25. find the LCM of x and y
int findLCM(int x,int y){
    static int multiOfSmall=0;

    multiOfSmall+=min(x,y);

    if(multiOfSmall % x == 0 && multiOfSmall % y == 0){
        return multiOfSmall;
    }

    return findLCM(x,y);
}

//26. count the number of digits of an integer.

int countDigit(int n){

    if(n==0){
        return 0;
    }

    return  countDigit(n/10) ;
}

//27. find the sum of digits of an integer.

int sumOfDigit(int n){
    if(n==0){
        return 0;
    }
    return n%10 + sumOfDigit(n/10);
}

//28. check if a given positive integer is a palindrome or not

int reverseNumberDigit(int n,int sum){
    if(n==0){
        return sum;
    }
    sum = sum*10 + n%10;
    return reverseNumberDigit(n/10,sum);
}

bool checkPalindrome(int n){
    if(n== reverseNumberDigit(n,0)){
        return true;
    }
    return false;
}

//29.print all subsets of a set of n elements.

void allSubsetsSolve(vector<int> &arr,int index,vector<int> subSet, vector<vector<int>> &ans){
    if(index>=arr.size()){
        ans.push_back(subSet);
        return;
    }

    allSubsetsSolve(arr,index+1,subSet,ans);

    int element =arr[index];
    subSet.push_back(element);
    allSubsetsSolve(arr,index+1,subSet,ans);
}

vector<vector<int>> allSubsets(vector<int> &arr){
    vector<vector<int>> ans;
    vector<int> subSet;
    allSubsetsSolve(arr,0,subSet,ans);
    return ans;
}

//30. print all subsequences of a string
void allSubsequeneceSolve(string str,int index, string subSeq,vector<string> &ans){
    if(index>=str.length()){
        ans.push_back(subSeq);
        return;
    }

    allSubsequeneceSolve(str,index+1,subSeq,ans);

    char element=str[index];
    subSeq.push_back(element);
    allSubsequeneceSolve(str,index+1,subSeq,ans);

}

vector<string> allSubsequenece(string str){
    vector<string> ans;
    string subSeq;
    allSubsequeneceSolve(str,0,subSeq,ans);
    return ans;
}

//31. binary search in a sorted array

bool binarySearch(int *arr,int start,int end,int key){
    if(start>end){
        return false;
    }

    int mid= (start + end )/2;
    if(arr[mid]==key){
        return true;
    }

    if(arr[mid]>key){
        return binarySearch(arr,start,mid-1,key);
    }
    else{
        return binarySearch(arr,mid+1,end,key);
    }
}

int main(){

    int choice,data,data2,data3;
    cout<<"Choice:";
    cin>>choice;
    while (choice){
        int arr[5]={5,7,12,3,6};
        switch (choice) {
            case 1:{
                cout<<factorial(5)<<endl;
                break;
            }
            case 2:{
                cout<<power(5,-3)<<endl;
                break;
            }
            case 3:{
                cout<<nthFibonacciNumber(6)<<endl;
                break;
            }
            case 4:{
                string str ="asdfgfdsa";
                cout<<checkPalindrome(str,0,str.size()-1)<<endl;
                break;
            }
            case 5:{
              //  printEven(1,9);
                printEven2(1,9);

                cout<<endl;
                break;
            }
            case 6:{
           //     printArr(arr,5);
                printArr(arr,0,5);
                cout<<endl;
                break;
            }
            case 7:{
               // printArrRev(arr,5);
                printArrRev(arr,0,5);
                cout<<endl;
                break;
            }
            case 8:{
              //  cout<<sumOfArray(arr,5)<<endl;
              cout<<sumOfArray(arr,0,5)<<endl;
                break;
            }
            case 9:{
            //    cout<<productOfArray(arr,5)<<endl;
            cout<<productOfArray(arr,0,5)<<endl;
                break;
            }
            case 10:{
            //    cout<<maxOfArr(arr,5)<<endl;
                cout<<maxOfArr(arr,0,5)<<endl;
                break;

            }
            case 11:{
                //    cout<<minOfArr(arr,5)<<endl;
                cout<<minOfArr(arr,0,5)<<endl;
                break;

            }
            case 12:{
                cout<<findAvg(arr,5);
            }
            case 13:{
                printArrEven(arr,5);
                cout<<endl;
                break;
            }
            case 14:{
                printPrimeNumber(arr,5);
              //  printPrimeNumber(arr,0,5);
                cout<<endl;
                break;
            }
            case 15:{
                //cout<<countOddNumber(arr,5)<<endl;
                cout<<countEvenNumber(arr,0,5)<<endl;
                break;
            }
            case 16:{
             //   cout<<countPrimeNumber(arr,5)<<endl;
                cout<<countPrimeNumber(arr,0,5)<<endl;
                break;
            }
            case 17:{
                break;
            }
            case 18:{
                break;
            }
            case 19:{
                linearSeries(11);
                cout<<endl;
                cout<<"Sum:"<<linearSeriesSum(11)<<endl;
                break;
            }
            case 20:{
                squareSeries(6);
                cout<<endl;
                cout<<"Sum:"<<squareSeriesSum(6)<<endl;
                break;
            }
            case 21:{
                series3(4);
                cout<<endl<<"Sum:"<<series3Sum(4)<<endl;
                break;
            }
            case 22:{
                series4(4);
                cout<<endl<<"Sum:"<<series4Sum(4)<<endl;
                break;
            }
            case 23:{
                break;
            }
            case 24:{
                cout<<"GCD:"<<findGCD(24,36)<<endl;
                break;
            }
            case 25:{
                cout<<"LCM:"<<findLCM(8,6)<<endl;
                break;
            }
            case 26:{
                cout<<countDigit(25619)<<endl;
                break;
            }
            case 27:{
                cout<<sumOfDigit(45215)<<endl;
                break;
            }
            case 28:{

              cout<<checkPalindrome(45654)<<endl;
                break;
            }
            case 29:{
                vector<int> arr={4,5,6};
                vector<vector<int>> subSets= allSubsets(arr);
                for (auto i:subSets) {
                    for (auto j:i) {
                        cout<<j<<" ";
                    }
                    cout<<endl;
                }
                break;
            }
            case 30:{
                vector<string> ans= allSubsequenece("cse");
                for (auto x:ans) {
                    cout<<x<<endl;
                }
                break;
            }
            case 31:{
                int arrr[8]={4,5,6,5,6,9,3,8};
                cout<<binarySearch(arrr,0,8,6)<<endl;
                break;
            }

        }
        cout<<"Choice:";
        cin>>choice;
    }
}