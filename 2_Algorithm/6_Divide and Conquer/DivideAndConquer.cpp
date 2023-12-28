#include "iostream"
#include "vector"

using namespace std;

//1. Maximum subarray sum

int crossingSum(vector<int> &arr,int start,int mid,int end){

    int leftMax=INT_MIN;
    int sum=0;
    for (int i = mid; i >=start ; --i) {
        sum+=arr[i];
        leftMax=max(leftMax,sum);
    }

    sum=0;
    int rightMax=INT_MIN;
    for (int i = mid+1; i <= end ; ++i) {
        sum+=arr[i];
        rightMax=max(rightMax,sum);
    }
    return leftMax+rightMax;
}

int maxSumSubarray(vector<int> &arr,int start,int end){
    if(start==end){
        return arr[start];
    }

    int mid=(start+end)/2;
    int leftMaxSum= maxSumSubarray(arr,start,mid);
    int rightMaxSum= maxSumSubarray(arr,mid+1,end);
    int crossingMaxSum= crossingSum(arr,start,mid,end);
    return max(leftMaxSum,max(rightMaxSum,crossingMaxSum));
}

//2. Majority element

int countFreqency(vector<int> &arr,int key){
    int count =0;
    for (auto ele:arr) {
        if(ele==key){
            count++;
        }
    }
    return count;
}

int majorityElement(vector<int> &arr,int start,int end){
    if(start==end){
        return arr[start];
    }

    int mid=(start+end)/2;
    int leftMajority= majorityElement(arr,start,mid);
    int rightMajority= majorityElement(arr,mid+1,end);

    if(leftMajority==rightMajority){
        return leftMajority;
    }

    int leftMojorityFrq= countFreqency(arr,leftMajority);
    int rightMajorityFrq= countFreqency(arr,rightMajority);

    if(leftMojorityFrq > (end-start+1)/2){
        return leftMajority;
    }
    if(rightMajorityFrq > (end-start+1)/2){
        return rightMajority;
    }
    return -1;
}

//3. Find minimum-maximum in array
void minMaxFind(vector<int> &arr,int start,int end,int &smallest,int &largest){
    if(start==end){
        smallest=min(smallest,arr[start]);
        largest=max(largest,arr[start]);
        return;
    }

    int mid=(start+end)/2;
    minMaxFind(arr,start,mid,smallest,largest);
    minMaxFind(arr,mid+1,end,smallest,largest);
}

//4. kth largest element

//5. Find the count of even numbers in an array
int countEvenNumber(vector<int> &nums,int start,int end){
    if(start==end){
        if(nums[start]%2==0){
            return 1;
        }
        else{
            return 0;
        }
    }

    int mid=(start+end)/2;
    int leftEvenCount= countEvenNumber(nums,start,mid);
    int rightEvenCount= countEvenNumber(nums,mid+1,end);
    return leftEvenCount+rightEvenCount;
}
//6. to print the odd numbers of an array of n integers.
void printOddNumber(vector<int> &nums,int start,int end){
    if(start==end){
        if(nums[start]%2!=0){
            cout<<nums[start]<<" ";
        }
        return;
    }

    int mid=(start+end)/2;
    printOddNumber(nums,start,mid);
    printOddNumber(nums,mid+1,end);
}
//7. to calculate the sum of an array of n integers.
int sumOfNumber(vector<int> &nums,int start,int end){
    if(start==end){
        return nums[start];
    }

    int mid=(start+end)/2;
    int leftSum= sumOfNumber(nums,start,mid);
    int rightSum= sumOfNumber(nums,mid+1,end);
    return leftSum+rightSum;
}

//8. to calculate the sum of the even numbers of an array of n integers.
int sumOfEvenNumber(vector<int> &nums,int start,int end){
    if(start==end){
        if(nums[start]%2==0)
            return nums[start];
        else
            return 0;
    }

    int mid=(start+end)/2;
    int leftSum= sumOfEvenNumber(nums,start,mid);
    int rightSum= sumOfEvenNumber(nums,mid+1,end);
    return leftSum+rightSum;
}

//9. calculates the value of X^Y  and prints it
double power(double x,int y){
    if(y==1){
        return x;
    }

    double leftPower=0;
    double rightPower=0;

    if(y>=0){
        if(y%2==0){
            leftPower= power(x,y/2);
            rightPower= power(x,y/2);
        }
        else{
            leftPower= power(x,y/2);
            rightPower= power(x,y/2+1);
        }
    }
    else{
        if(y%2==0){
            leftPower=1/ power(x,-1*y/2);
            rightPower=1/ power(x,-1*y/2);
        }
        else{
            leftPower=1/ power(x,-1*y/2);
            rightPower=1/ power(x,-1*y/2) *1/x;
        }
    }
    return leftPower*rightPower;
}

//10. binary_search
int binarySearch(vector<int> &arr,int key){
    int start=0;
    int end=arr.size();

    while (start<=end){
        int mid=(start+end)/2;
        if(arr[mid]==key){
            return mid;
        }
        else if(arr[mid]<key){
            end=mid-1;
        }
        else{
            start=mid+1;
        }
    }
    return -1;
}
//11. Merge sort

void merge(vector<int> &arr,int start,int mid,int end){
    int size1=mid+1-start;
    int size2=end-mid;

    vector<int> sub1(size1);
    vector<int> sub2(size2);

    for (int i = 0; i < size1; ++i) {
        sub1[i]=arr[start+i];
    }
    for (int i = 0; i < size2; ++i) {
        sub2[i]=arr[mid+1+i];
    }
    int i=0,j=0,k=start;
    while (i<size1 && j<size2){
        if(sub1[i]<sub2[j]){
            arr[k]=sub1[i];
            i++;
            k++;
        }
        else{
            arr[k]=sub2[j];
            j++;
            k++;
        }
    }
    while (i<size1){
        arr[k]=sub1[i];
        i++;
        k++;
    }
    while (j<size2){
        arr[k]=sub2[j];
        j++;
        k++;
    }

}

void mergeSort(vector<int> &arr,int start,int end){
    if(start>=end){
        return;
    }
    int mid=(start+end)/2;
    mergeSort(arr,start,mid);
    mergeSort(arr,mid+1,end);
    merge(arr,start,mid,end);
}

//12. Quick sort

void swap(vector<int> &arr,int onePosition,int toAnother){
    int temp=arr[onePosition];
    arr[onePosition]=arr[toAnother];
    arr[toAnother]=temp;
}

int partition(vector<int> &arr,int start,int end){
    int pivot=arr[end];
    int j=start-1;
    for (int i = start; i <= end ; ++i) {
        if(arr[i]<pivot){
            j++;
            swap(arr,i,j);
        }
    }
    swap(arr,j+1,end);
    return j+1;
}

void quickSort(vector<int> &arr,int start,int end){
    if(start>=end){
        return;
    }
    int pivot= partition(arr,start,end);
    quickSort(arr,start,pivot-1);
    quickSort(arr,pivot+1,end);
}

//13. count_inversion .

int mergeCount(vector<int> &arr,int start,int mid,int end){
    int size1=mid+1-start;
    int size2=end-mid;

    int sub1[size1];
    int sub2[size2];

    for (int i = 0; i < size1; ++i) {
        sub1[i]=arr[start+i];
    }
    for (int i = 0; i < size2; ++i) {
        sub2[i]=arr[mid+1+i];
    }

    int count=0;
    for (int i = 0; i < size1; ++i) {
        for (int j = 0; j < size2; ++j) {
            if(sub1[i]>sub2[j]){
                count++;
            }
        }
    }
    return count;
}

void countInversion(vector<int> &arr,int start,int end,int &inversion){
    if(start>=end){
        return;
    }

    int mid=(start+end)/2;
    countInversion(arr,start,mid,inversion);
    countInversion(arr,mid+1,end,inversion);
    inversion+= mergeCount(arr,start,mid,end);
}

//14. takes N strings from the user and finds the longest common prefix of those strings .

string longestPrefix(string word1,string word2){
    int i=0,j=0;
    while (i<word1.length() && j<word2.length()){
        if(word1[i]!=word2[j]){
            break;
        }
        i++;
        j++;
    }
    return word1.substr(0,i);
}

string longestCommonOPrefix(vector<string> &list){
    string commonPrefix=list[0];
    for (auto word:list) {
        commonPrefix= longestPrefix(commonPrefix,word);
    }
    return commonPrefix;
}

//15. takes N two-dimensional points’ coordinates as input, and finds the pair of points that are closest together (according to euclidean distance).
//16. Segregate positive and negative number using merge sort
//17. Count occurrences in the array
int countOccurrence(vector<int> &arr,int start,int end,int key){
    if(start==end){
        if(arr[start]==key){
            return 1;
        }
        else{
            return 0;
        }
    }
    int mid=(start+end)/2;
    int leftOccur= countOccurrence(arr,start,mid,key);
    int rightOccur= countOccurrence(arr,mid+1,end,key);
    return leftOccur+rightOccur;

}

int main(){
    int choice;
    cout<<"Choice:";
    cin>>choice;
    while (choice){
        switch (choice) {
            case 1:{
                vector<int> arr={-2,-3,4,-1,-2,1,5,-3};
                cout<<maxSumSubarray(arr,0,arr.size()-1)<<endl;
                break;
            }
            case 2:{
                vector<int> arr={2,2,1,1,1,2,2};
                cout<<majorityElement(arr,0,arr.size()-1)<<endl;
                break;
            }
            case 3:{
                int smallest=INT_MAX,largest=INT_MIN;
                vector<int> arr={-2,-3,4,-1,-2,1,5,-3};
                minMaxFind(arr,0,arr.size()-1,smallest,largest);
                cout<<smallest<<" "<<largest<<endl;
                break;
            }
            case 5:{
                vector<int> arr={45,8,6,9,38,99,2,6};
                cout<<countEvenNumber(arr,0,arr.size()-1)<<endl;
                break;
                break;
            }
            case 6:{
                vector<int> arr={45,8,6,9,38,99,2,6};
                printOddNumber(arr,0,arr.size()-1);
                cout<<endl;
                break;
            }
            case 7:{
                vector<int> arr={45,8,6,9,38,99,2,6};
                cout<<sumOfNumber(arr,0,arr.size()-1)<<endl;
                break;
            }
            case 8:{
                vector<int> arr={45,8,6,9,38,99,2,6};
                cout<<sumOfEvenNumber(arr,0,arr.size()-1)<<endl;
                break;
            }
            case 9:{
                cout<<power(8,-2)<<endl;
                break;
            }
            case 10:{
                vector<int> arr={45,8,6,9,38,99,2,6};
                cout<<binarySearch(arr,2)<<endl;
                break;
            }
            case 11:{
                vector<int> arr={45,8,6,9,38,99,2,6};
                mergeSort(arr,0,arr.size()-1);
                for (auto x:arr) {
                    cout<<x<<" ";
                }
                cout<<endl;
                break;
            }
            case 12:{
                vector<int> arr={45,8,6,9,38,99,2,6};
                quickSort(arr,0,arr.size()-1);
                for (auto x:arr) {
                    cout<<x<<" ";
                }
                cout<<endl;
                break;
            }
            case 13:{
                vector<int> arr={45,8,6,9,38,99,2,6};
                int inversion=0;
                countInversion(arr,0,arr.size()-1,inversion);
                cout<<inversion<<endl;
                break;
            }
            case 14:{
                vector<string> vStr={
                        "techie delight","tech","techie","technology","technical"
                };
                cout<<longestCommonOPrefix(vStr)<<endl;
                break;
            }

            case 17:{
                vector<int> arr={2,9,5,9,9,4,9,8,9,9};
                cout<<countOccurrence(arr,0,arr.size()-1,9)<<endl;
                break;

            }

        }
        cout<<"Choice:";
        cin>>choice;
    }
}