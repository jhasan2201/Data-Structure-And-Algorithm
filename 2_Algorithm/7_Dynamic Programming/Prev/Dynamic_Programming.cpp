#include "iostream"
#include "vector"
#include "algorithm"
#include "unordered_map"
using namespace std;
//0
int fibonacciNumberSolve(int n){
    if(n==0){
        return 0;
    }
    if(n==1){
        return 1;
    }
    return fibonacciNumberSolve(n-1)+ fibonacciNumberSolve(n-2);
}
int fibonacciNumber(int n){
    return fibonacciNumberSolve(n);
}

//1. Fibonacci number (Memorization)
int fibonacciNumberMemSolve(int n,vector<int> &dp){
    if(n==0){               //base case
        return 0;
    }
    if(n==1){
        return 1;
    }
    if(dp[n]!=-1){           //using memorization (if its value exist just use it)
        return dp[n];
    }
    return dp[n]= fibonacciNumberMemSolve(n-1,dp) + fibonacciNumberMemSolve(n-2,dp);     //store the value :: return value
}
int fibonacciNumberMem(int n){
    vector<int> dp(n+1,-1);
    return fibonacciNumberMemSolve(n,dp);
}

//2. Fibonacci number (Tabulation)
int fibonacciNumberTabSolve(int n){
    vector<int> dp(n+1,0);
    dp[0]=0;
    dp[1]=1;
    for (int i = 2; i <= n; ++i) {
        dp[i] = dp[i-1]+ dp[i-2];
    }
    return dp[n];
}
int fibonacciNumberTab(int n){
    return fibonacciNumberTabSolve(n);
}

//3. Fibonacci number (space optimization)
int fibonacciNumberOpt(int n){
    int firstPrev=1;
    int secondPrev=0;

    if(n==0){
        return 0;
    }

    for (int i = 2; i <= n; ++i) {
        int curr=firstPrev+secondPrev;
        secondPrev=firstPrev;
        firstPrev=curr;
    }
    return firstPrev;
}

//4. Minimum Cost Climbing Stairs (Recursion)
int minCostClimbingStairsSolve(vector<int> &cost,int stair){
    if(stair==0){              //from first stair climbing :: first cost
        return cost[0];
    }
    if(stair==1){
        return cost[1];        //from second stair climbing :: cost[1]
    }
    //every stair have it's own cost + prev(stair-1) or prev(stair-2) cost
    int ans=cost[stair] + min(minCostClimbingStairsSolve(cost,stair-1), minCostClimbingStairsSolve(cost,stair-2));
    return ans;
}
int minCostClimbingStairs(vector<int> &cost){
    int n=cost.size();

    //to reach nth position :: have either from (n-1)th stair or from (n-2)th stair  :: return its minimum [beacuse n-1 th stair have no cost]
    int fromLastStairAns= minCostClimbingStairsSolve(cost,n-1);
    int fromSecondLastStairAns = minCostClimbingStairsSolve(cost,n-2);
    return min(fromLastStairAns,fromSecondLastStairAns);
}

//5. Minimum Cost Climbing Stairs (Memorization)
int minCostClimbingStairsMemSolve(vector<int> &cost,int stair,vector<int> &dp){
    if(stair==0){
        return cost[0];
    }
    if(stair==1){
        return cost[1];
    }
    if(dp[stair]!=-1){
        return dp[stair];
    }

    //every stair have it's own cost + prev(stair-1) or prev(stair-2) cost
    int ans=cost[stair] + min(minCostClimbingStairsMemSolve(cost,stair-1,dp), minCostClimbingStairsMemSolve(cost,stair-2,dp));
    return dp[stair]= ans;
}
int minCostClimbingStairsMem(vector<int> &cost){
    int n=cost.size();
    vector<int> dp(n+1,-1);

    int fromLastStairAns= minCostClimbingStairsMemSolve(cost,n-1,dp);
    int fromSecondLastStairAns= minCostClimbingStairsMemSolve(cost,n-2,dp);
    return min(fromLastStairAns,fromSecondLastStairAns);

}
//6. Minimum Cost Climbing Stairs (Tabulation)

int minCostClimbingStairsTabSolve(vector<int> &cost){
    int n=cost.size();
    vector<int> dp(n+1,-1);
    dp[0]=cost[0];
    dp[1]=cost[1];

    for (int i = 2; i <= n; ++i) {
        dp[i]= cost[i] + min(dp[i-1],dp[i-2]);
    }

    return min(dp[n-1],dp[n-2]);
}
int minCostClimbingStairsTab(vector<int> &cost){
    return minCostClimbingStairsTabSolve(cost);
}

//7. Minimum Cost Climbing Stairs (Space optimization)
int minCostClimbingStairsOptSolve(vector<int> &cost){
    int n=cost.size();

    int secondPrev=cost[0];
    int firstPrev=cost[1];
    int curr=0;

    for (int i = 2; i <= n; ++i) {
        curr=cost[i] + min(secondPrev,firstPrev);
        secondPrev=firstPrev;
        firstPrev=curr;
    }
    return min(curr,secondPrev);
}
int minCostClimbingStairsOpt(vector<int> &cost){
    return minCostClimbingStairsOptSolve(cost);
}

//8. Minimum Number of Coins (Recursion)
int minNumberOfCoinsSolve(vector<int> &coins,int target){
    if(target==0){                      //zero target with zero coin
        return 0;
    }
    if(target<0){                        //negative target :: invalid way :: to calculate minimum :: INT_MAX return
        return INT_MAX;
    }

    int minAns=INT_MAX;                                             //minimum of ans
    for (auto co:coins) {                                          //for each coin  :: call recursively like tree :: with (current target amount - current coin)
        int ans= minNumberOfCoinsSolve(coins,target-co);
        if(ans!=INT_MAX){                                             //if it has a valid way :: if there is a way :: INT_MAX will vanish by a moreThanOrEqualZero value
            minAns=min(minAns, 1 + ans);                            // return tree's child value with (+1) + :: to count way in recursion
                                                                    //(+1) if we sure to use coins[1...coins.size()]{co}  and rest of the amount will fill by (tar-co)
        }
    }
    return minAns;
}
int minNumberOfCoins(vector<int> &coins,int target){
    int ans= minNumberOfCoinsSolve(coins,target);

    if(ans==INT_MAX){                       //if it is not possible to count ways :: like make 1 tk with infinity 2tk coin
        return -1;
    }

    return ans;
}

//9. Minimum Number of Coins (Memorization)
int minNumberOfCoinsMemSolve(vector<int> &coins,int target,vector<int> &dp){
    if(target==0){
        return 0;
    }
    if(target<0){
        return INT_MAX;
    }

    if(dp[target]!=-1){
        return dp[target];
    }

    int miniAns=INT_MAX;
    for (auto co:coins) {
        int ans= minNumberOfCoinsMemSolve(coins,target-co,dp);
        if(ans != INT_MAX){
            miniAns=min(miniAns,1+ans);
        }
    }
    return dp[target]=miniAns;
}
int minNumberOfCoinsMem(vector<int> &coins,int target){
    vector<int> dp(target+1,-1);
    int ans= minNumberOfCoinsMemSolve(coins,target,dp);
    if(ans==INT_MAX){
        return -1;
    }
    return ans;
}

//10. Minimum Number of Coins (Tabulation)

int minNumberOfCoinsTabSolve(vector<int> &coins,int target){
    vector<int> dp(target+1,INT_MAX);             //assume :: every index as invalid
    dp[0]=0;

    for (int tar = 0; tar <= target ; ++tar) {              //make dp array full with 1,2,3....target :: each target can be possible with coins's array
        for (auto co:coins) {
            if(tar-co>=0 && dp[tar-co] != INT_MAX) {        //if tar-co is a valid index and It's value is not INT_MAX
                dp[tar] = min(dp[tar], 1 + dp[tar - co]);     //(+1) if we sure to use coins[1...coins.size()]{co}  and rest of the amount will fill by (tar-co)
            }
        }
    }
    return dp[target];
}
int minNumberOfCoinsTab(vector<int> &coins,int target){
    int ans= minNumberOfCoinsTabSolve(coins,target);
    if(ans==INT_MAX){
        return -1;
    }
    return ans;
}

//minimum coin change :: space optimization is not possible

//11. Maximum Sum of Non-Adjacent Elements (Recursion)
int maxNonAdjacentSumSolve(vector<int> &nums,int index){

    if(index<0){           //invalid index :: return 0
        return 0;
    }
    if(index==0){                //reach first element and it can be made by first number element
        return nums[index];
    }

    int include= nums[index] + maxNonAdjacentSumSolve(nums,index-2);  //if we take :: take this number and skip the next iteration :: because next element is adjacent
    int exclude = 0 + maxNonAdjacentSumSolve(nums,index-1);             //if we don't take :: go to next iteration  :: no restriction here
    return max(include,exclude);                 //return it's maximum
}
int maxNonAdjacentSum(vector<int> &nums){
    int n=nums.size();
    return maxNonAdjacentSumSolve(nums,n-1);
}

//12. Maximum Sum of Non-Adjacent Elements (Memorization)

int maxNonAdjacentSumMemSolve(vector<int> &nums,int index,vector<int> &dp){
    if(index<0){
        return 0;
    }
    if(index==0){
        return nums[index];
    }

    if(dp[index]!=-1){
        return dp[index];
    }

    int include= nums[index] + maxNonAdjacentSumMemSolve(nums,index-2,dp);
    int exclude= 0+ maxNonAdjacentSumMemSolve(nums,index-1,dp);

    return dp[index]=max(include,exclude);
}
int maxNonAdjacentSumMem(vector<int> &nums){
    int n=nums.size();
    vector<int> dp(n,-1);
    return maxNonAdjacentSumMemSolve(nums,n-1,dp);
}

//13. Maximum Sum of Non-Adjacent Elements (Tabulation)

int maxNonAdjacentSumTabSolve(vector<int> &nums){
    int n=nums.size();
    vector<int> dp(n,0);

    dp[0]=nums[0];
    dp[1]=max(nums[0],nums[1]);
    for (int i = 2; i < n; ++i) {
        int include= nums[i] + dp[i-2];
        int exclude= 0 +       dp[i-1];
        dp[i]=max(include,exclude);
    }
    return dp[n-1];
}
int maxNonAdjacentSumTab(vector<int> &nums){
    return maxNonAdjacentSumTabSolve(nums);
}


//14. Maximum Sum of Non-Adjacent Elements (Space optimization)

int maxNonAdjacentSumOptSolve(vector<int> &nums) {
    int n=nums.size();
    int secondPrev=nums[0];
    int firstPrev=max(nums[0],nums[1]);

    for (int i = 2; i < n; ++i) {
        int include= nums[i] + secondPrev;
        int exclude = 0   + firstPrev;

        int current=max(include,exclude);
        secondPrev=firstPrev;
        firstPrev=current;
    }
    return firstPrev;
}
int maxNonAdjacentSumOpt(vector<int> &nums){
    return maxNonAdjacentSumOptSolve(nums);
}

//15. House Robbery Problem (Recursion)

int houseRobberySolve(vector<int> &money,int start,int end){
    if(start>end){                          //invalid index
        return 0;
    }
    if(start==end){                       //if one house:: take it
        return money[start];
    }

    int include = money[end] + houseRobberySolve(money,start,end-2);          //if take :: take this number and skip the next iteration :: because next element is adjacent
    int exclude= 0 + houseRobberySolve(money,start,end-1);                       //if we don't take :: go to next iteration  :: no restriction here

    return max(include,exclude);
}
int houseRobbery(vector<int> &money){
    int n=money.size();
    int firstToSecLast= houseRobberySolve(money,0,n-2);               //first house......(n-1)th house
    int secToLast= houseRobberySolve(money,1,n-1);                     //second house.....nth house
    return max(firstToSecLast,secToLast);

}

//16. House Robbery Problem (Memorization)

int houseRobberyMemSolve(vector<int> &money,int start,int end,vector<int> &dp){
    if(start>end){
        return 0;
    }
    if(start==end){
        return money[start];
    }

    if(dp[end]!=-1){
        return dp[start];
    }

    int include= money[end] + houseRobberyMemSolve(money,start,end-2,dp);       //make first house constant and iterate by end house from end-2.....first :: next element is adjacent
    int exclude=0 + houseRobberyMemSolve(money,start,end-1,dp);                   //make first house constant and iterate by end house from end-1.....first

    return dp[end] = max(include,exclude);
}
int houseRobberyMem(vector<int> &money){
    int n=money.size();
    vector<int> dp(n+1,-1);
    int firstToSecLast= houseRobberyMemSolve(money,0,n-2,dp);
    int secToLast= houseRobberyMemSolve(money,1,n-1,dp);
    return max(firstToSecLast,secToLast);
}

//17. House Robbery Problem (Tabulation)

int houseRobberyTabSolve(vector<int> &money,int start,int end){
    vector<int> dp(end+1,0);

    //first index is depends on start index ::: 0 === (start+0)
    dp[start + 0] = money[start + 0 ];
    dp[start + 1 ]= max(money[start+0],money[start+1]);

    for (int i = start+2; i <= end; ++i) {
        int include= money[i] + dp[i-2];
        int exclude= 0 + dp[i-1];
        dp[i]=max(include,exclude);
    }

    return dp[end];
}
int houseRobberyTab(vector<int> &money){
    int n=money.size();
    int firstToSecLast= houseRobberyTabSolve(money,0,n-2);
    int secToLast= houseRobberyTabSolve(money,1,n-1);
    return max(firstToSecLast,secToLast);
}

//18. House Robbery Problem (Space optimization)

int houseRobberyOptSolve(vector<int> &money,int start,int end){
    int secondPrev=money[start + 0];
    int firstPrev=max(money[start+0],money[start+1]);

    for (int i = start+2; i <= end; ++i) {
        int include= money[i] + secondPrev;
        int exclude = 0 +firstPrev;
        int curr=max(include,exclude);

        secondPrev=firstPrev;
        firstPrev=curr;
    }
    return firstPrev;
}
int houseRobberyOpt(vector<int> &money){
    int n=money.size();
    int firstToSecLast= houseRobberyOptSolve(money,0,n-2);
    int secToLast= houseRobberyOptSolve(money,1,n-1);
    return max(firstToSecLast,secToLast);
}


//19.Cut Rod into Segments of X, Y, Z (Recursion)

int cutRodIntoSegmentSolve(int rodSize,int x,int y,int z){
    if(rodSize==0){               //if rod size is zero
        return 0;
    }
    if(rodSize < 0){               //if less than zero :: return -infinity for ignoring by max function
        return INT_MIN;
    }

    int cutByX= 1 + cutRodIntoSegmentSolve(rodSize-x,x,y,z);     //one choice :: cut by x   :: size decrease by x value
    int cutByY= 1 + cutRodIntoSegmentSolve(rodSize-y,x,y,z);        // y
    int cutByZ= 1 + cutRodIntoSegmentSolve(rodSize-z,x,y,z);         //z

    return max(cutByX,max(cutByY,cutByZ));                           //maximum number of way
}
int cutRodIntoSegment(int rodSize,int x,int y,int z){
    int ans= cutRodIntoSegmentSolve(rodSize,x,y,z);
    if(ans<0) {               //invalid :: for catch
        return 0;
    }
    return ans;
}

//20. Cut Rod into Segments of X, Y, Z (Memorization)

int cutRodIntoSegmentMemSolve(int rodSize,int x,int y,int z,vector<int> dp){
    if(rodSize==0){
        return 0;
    }
    if(rodSize<0){
        return INT_MIN;
    }

    if(dp[rodSize]!=-1){
        return dp[rodSize];
    }

    int cutByX= 1 + cutRodIntoSegmentMemSolve(rodSize-x,x,y,z,dp);
    int cutByY= 1 + cutRodIntoSegmentMemSolve(rodSize-y,x,y,z,dp);
    int cutByZ= 1 + cutRodIntoSegmentMemSolve(rodSize-z,x,y,z,dp);

    return dp[rodSize]=max(cutByX,max(cutByY,cutByZ));
}
int cutRodIntoSegmentMem(int rodSize,int x,int y,int z){
    vector<int> dp(rodSize+1,-1);
    int ans= cutRodIntoSegmentMemSolve(rodSize,x,y,z,dp);
    if(ans<0){               //invalid :: for catch
        return 0;
    }
    return ans;
}

//21. Cut Rod into Segments of X, Y, Z (Tabulation)

int cutRodIntoSegmentTabSolve(int rodSize,int x,int y,int z){
    vector<int> dp(rodSize+1,INT_MIN);
    dp[0]=0;

    for (int rodeS = 1; rodeS <= rodSize ; ++rodeS) {
        if(rodeS-x >= 0) {
            dp[rodeS] = max(dp[rodeS], 1 + dp[rodeS - x]);
        }
        if(rodeS-y >= 0) {
            dp[rodeS] = max(dp[rodeS], 1 + dp[rodeS - y]);
        }
        if(rodeS-z >= 0) {
            dp[rodeS] = max(dp[rodeS], 1 + dp[rodeS - z]);
        }
    }
    return dp[rodSize];
}
int cutRodIntoSegmentTab(int rodSize,int x,int y,int z){
    int ans= cutRodIntoSegmentTabSolve(rodSize,x,y,z);
    if(ans<0){               //invalid :: for catch
        return 0;
    }
    return ans;
}

//23. Count derangements (Recursion)
int countDeRangementsSolve(int n){
      //problem is :: if there is n empty space and you have to organize n number

    if(n==1){              //1 value can't define a way to stand else his position
        return 0;
    }
    if(n==2){                //two value can exchange their position in one way
        return 1;
    }
    return (n-1) * (countDeRangementsSolve(n-1) + countDeRangementsSolve(n-2));   //(n-1)* :: 0th position value can move ith position  by (n-1) way
                                                                                       //possibility 1:: remaining (n-2) [excluding 0th and ith position] value can move (n-2) position  :: subproblem(n-2)
                                                                                    //possibility 2:: if any value don't want to move his index's position with subProblem of (n-1) element :: subproblem(n-1)
}
int countDeRangements(int n){
    return countDeRangementsSolve(n);
}

//24. Count derangements (Memorization)
int countDeRangementsMemSolve(int n,vector<int> &dp){
    if(n==1){
        return 0;
    }
    if(n==2){
        return 1;
    }

    if(dp[n]!=-1){
        return dp[n];
    }

    return dp[n]=(n-1) * (countDeRangementsMemSolve(n-1,dp) + countDeRangementsMemSolve(n-2,dp));
}
int countDeRangementsMem(int n){
    vector<int> dp(n+1,-1);
    return countDeRangementsMemSolve(n,dp);
}


//25. Count derangements (Tabulation)
int countDeRangementsTabSolve(int n){
    vector<int> dp(n+1,0);
    dp[1]=0;
    dp[2]=1;
    for (int i = 3; i <= n; ++i) {
        dp[i]=(i-1) * (dp[i-1] + dp[i-2]);
    }
    return dp[n];
}

int countDeRangementsTab(int n){
    return countDeRangementsTabSolve(n);
}

//26. Count derangements (Space optimization)
int countDeRangementsOptSolve(int n){
    int secondPrev=0;
    int firstPrev=1;
    for (int i = 3; i <= n; ++i) {
        int curr= (i-1)* (firstPrev + secondPrev);
        secondPrev=firstPrev;
        firstPrev=curr;
    }
    return firstPrev;
}
int countDeRangementsOpt(int n){
    return countDeRangementsOptSolve(n);
}
long long int countDerangementsOpt(int n){
    long long int secondPrev=0;
    long long int firstPrev=1;

    for (int i = 3; i <= n; ++i) {
        long long int curr= (i-1) *(firstPrev+secondPrev);
        secondPrev=firstPrev;
        firstPrev=curr;
    }
    return firstPrev;
}


//27. Painting Fence Algorithm (Recursion)
int numberOfWaysSolve(int post,int color){
    if(post==1){
        return color;
    }
    if(post==2){
        return color + (color*(color-1));
    }

    return (color-1)* numberOfWaysSolve(post-2,color) + (color-1)* numberOfWaysSolve(post-2,color);
}
int numberOfWays(int post,int color){
    return numberOfWaysSolve(post,color);
}

//28. Painting Fence Algorithm (Memorization)
int numberOfWaysMemSolve(int post,int color, vector<int> &dp){
    if(post==1){
        return color;
    }
    if(post==2){
        return color + (color*(color-1));
    }

    if(dp[post] != -1){
        return dp[post];
    }

    return dp[post]= (color-1)* numberOfWaysMemSolve(post-2,color,dp) + (color-1)* numberOfWaysMemSolve(post-1,color,dp);
}
int numberOfWaysMem(int post,int color){
    vector<int> dp(post+1,-1);
    return numberOfWaysMemSolve(post,color,dp);
}
//29. Painting Fence Algorithm (Tabulation)
int numberOfWaysTabSolve(int post,int color){
    vector<int> dp(post+1,0);
    dp[1]=color;
    dp[2]= color + color*(color-1);
    for (int i = 3; i <= post ; ++i) {
        dp[i]= (color-1)*dp[i-2] + (color-1)*dp[i-1];
    }
    return dp[post];
}
int numberOfWaysTab(int post,int color){
    return numberOfWaysTabSolve(post,color);
}

//30. Painting Fence Algorithm (Space optimization)
int numberOfWaysOptSolve(int post,int color){
    int secondPrev=color;
    int firstPrev=color + (color*(color-1));
    for (int i = 3; i <= post; ++i) {
        int curr=(color-1)*secondPrev + (color-1)*firstPrev;
        secondPrev=firstPrev;
        firstPrev=curr;
    }
    return firstPrev;
}
int numberOfWaysOpt(int post,int color){
    return numberOfWaysOptSolve(post,color);
}

//31. KnapSack Problem (Recursion)
int knapsackSolve(vector<int> &weight,vector<int> &value,int item,int capacity){
    if(item==0){                                   //traverse form last to first of the (value or wight) array :: base
        if(weight[0] <= capacity){                      //if last element is under capacity :: take it
            return value[0];
        }
        else{
            return 0;
        }
    }

    int include=0;

    if(weight[item] <= capacity){                               //include one time ::: if element is under capacity
        include =value[item] + knapsackSolve(weight,value,item-1,capacity-weight[item]);    //include value added and capacity decrease  //capacity -> capacity-=weight[item] (in include)
    }

    int exclude= 0 + knapsackSolve(weight,value,item-1,capacity);         //exclude one time :: skip this iteration

    int ans=max(include,exclude);                                                                   //return maximum value's knapsack (between include and exclude)
    return ans;
}
int knapsack(vector<int> weight,vector<int> value,int items,int maxWeight){
    return knapsackSolve(weight,value,items-1,maxWeight);         //item-1 :: for indexing
}

//32. KnapSack Problem (Memorization)
int knapsackMemSolve(vector<int> &weight,vector<int> &value,int index,int capacity,vector<vector<int>> &dp){
    if(index==0){
        if(weight[0] <= capacity){         //0 is index
            return value[0];
        }
        else{
            return 0;
        }
    }

    if(dp[index][capacity] != -1){                                  //index -> n-1....0 no item
        return dp[index][capacity];
    }

    int include=0;
    if(weight[index]<=capacity){
        include= value[index] + knapsackMemSolve(weight,value,index-1,capacity-weight[index],dp);

    }

    int exclude =0 + knapsackMemSolve(weight,value,index-1,capacity,dp);

    dp[index][capacity]= max(include,exclude);

    return dp[index][capacity];
}
int knapsackMem(vector<int> weight,vector<int> value,int items,int maxWeight){
    vector<vector<int>> dp(items,vector<int>(maxWeight+1,-1));               // dpArr[items-wise][0....capacity] = {-1}


    return knapsackMemSolve(weight,value,items-1,maxWeight,dp);

}

//33. KnapSack Problem (Tabulation)
int knapsackTabSolve(vector<int> &value,vector<int> &weight,int items,int capacity) {
    vector<vector<int>> dp(items, vector<int>(capacity + 1, 0));
    for (int w = weight[0]; w <= capacity; ++w) {                          //fill 2d vector :: for zero item one (itemIndex 0)
        if (weight[0] <= capacity) {                                            //if the item is under capacity
            dp[0][w] = value[0];                                                    //push it into oth row (for one item)
        } else {
            dp[0][w] = 0;                                                            //push none
        }
    }

    for (int index = 1; index < items; ++index) {                         //iterate itemIndex one-by-one for (1....item-1) [itemIndex]
        for (int w = 0; w <= capacity; ++w) {                               //for each item :: iterate for each weight (0....weightOfCapacity)
            int include = 0;

            if (weight[index] <= w) {
                include = value[index] + dp[index - 1][w - weight[index]];                 //cumulative cost ::prev cost = [ (itemIndex-1 th row) and ( weight-costOfCurrItem) ] + current cost
            }

            int exclude = 0 + dp[index - 1][w];                                            //cumulative cost ::prev cost + 0

            dp[index][w] = max(exclude, include);
        }
    }
    return dp[items - 1][capacity];                             //total cost :: cumulative cost for last itemIndex th row and capacity col th value

}
int knapsackTab(vector<int> value, vector<int> weight, int n, int maxWeight) {
    return knapsackTabSolve(value, weight, n-1, maxWeight);
}

//34. KnapSack Problem (Space optimization - two vector)
int knapsackOptSolve(vector<int> value,vector<int> weight,int items,int capacity){
    vector<int> prev(capacity+1,0);                //previous item info
    vector<int> curr(capacity+1,0);                 //current item info

    for (int w = weight[0]; w <= capacity ; ++w) {            //for first item
        if(weight[0] <= capacity){
            prev[w]=value[0];                                   //if take:: weightTh index :: assign value
        }
        else{
            prev[w]=0;
        }
    }

    for (int index = 1; index < items ; ++index) {
        for (int w = 0; w <= capacity; ++w) {
            int include=0;

            if(weight[index] <= w){
                include= value[index] + prev[w- weight[index]];                   //concern about weight
            }

            int exclude = 0 + prev[w];

            curr[w]= max(include,exclude);
        }
        prev=curr;                                       //exchange previous to current
    }
    return prev[capacity];
}
int knapsackOpt(vector<int> value,vector<int> weight,int n,int maxWeight){
    return knapsackOptSolve(weight,value,n,maxWeight);
}

//35. KnapSack Problem (More Space optimization - one vector)
int knapsackOptSolve2(vector<int> value,vector<int> weight,int items,int capacity){
    vector<int> curr(capacity+1,0);

    for (int w = weight[0]; w <= capacity ; ++w) {
        if(weight[0] <= capacity){
            curr[w]=value[0];
        }
        else{
            curr[w]=0;
        }
    }

    for (int index = 1; index < items ; ++index) {
        for (int w = capacity; w >= 0; --w) {
            int include=0;

            if(weight[index] <= w){
                include= value[index] + curr[w- weight[index]];
            }

            int exclude = 0 + curr[w];

            curr[w]= max(include,exclude);
        }
    }
    return curr[capacity];
}
int knapsackOpt2(vector<int> value,vector<int> weight,int n,int maxWeight){
    return knapsackOptSolve(weight,value,n,maxWeight);
}

//36. Combination Sum (Recursion)
int findWayCombinationSumSolve(vector<int> &number,int target){
    if(target<0){              //if target is less zero :: there is no way to make target full-fill
        return 0;
    }
    if(target==0){           //target zero can make one way
        return 1;
    }

    int countNumberOfWays=0;              //total way
    for (auto num:number) {                //iterate for each number of array
        countNumberOfWays+= findWayCombinationSumSolve(number,target-num);    //target is decreasing after each number added
    }
    return countNumberOfWays;
}
int findWayCombinationSum(vector<int> &number,int tar){
    return findWayCombinationSumSolve(number,tar);
}

//37. Combination Sum (Memorization)
int findWayCombinationSumMemSolve(vector<int> &number,int target,vector<int> &dp){
    if(target<0){
        return 0;
    }
    if(target==0){
        return 1;
    }

    if(dp[target]!=-1){
        return dp[target];
    }

    int countNumberOfWays=0;
    for (auto num:number) {
        countNumberOfWays+= findWayCombinationSumMemSolve(number,target-num,dp);
    }
    return dp[target]=countNumberOfWays;
}
int findWayCombinationSumMem(vector<int> &number,int tar){
    vector<int> dp(tar+1,-1);
    return findWayCombinationSumMemSolve(number,tar,dp);
}

//38. Combination Sum (Tabulation)
int findWayCombinationSumTabSolve(vector<int> &number,int target){
    vector<int> dp(target+1,0);
    dp[0]=1;

    for (int tar = 1; tar <= target ; ++tar) {               //traversing target :: 1.....target
        int countNumberOfWays=0;
        for (auto num:number) {                   //traversing on number vector
            if(tar-num>=0) {
                countNumberOfWays += dp[tar - num];
            }
        }
        dp[tar]=countNumberOfWays;
    }
    return dp[target];
}
int findWayCombinationSumTab(vector<int> &number,int tar){
    return findWayCombinationSumTabSolve(number,tar);
}

//39. Perfect Squares Problem (Recursion)

int minimumSquaresSolve(int n){
    if(n==0){                  //zero can't make any addition of square of number
        return 0;
    }

    int minimumCounter= n;        //maximum can be possible by n
    for (int i = 1; i*i <= n ; ++i) {           //check  by 1^2, 2^2, 3^2, 4^2.....i^2 <=n
        minimumCounter=min(minimumCounter,1+ minimumSquaresSolve(n - i*i));  //1 plus ::count for each step
    }                                                                               //decrease n by i^2 every time
    return minimumCounter;
}
int minimumSquares(int n){
    return minimumSquaresSolve(n);
}

//40. Perfect Squares Problem (Memorization)

int minimumSquaresMemSolve(int n,vector<int> &dp){
    if(n==0){
        return 0;
    }

    if(dp[n]!=-1){
        return dp[n];
    }

    int minimumCounter= n;
    for (int i = 1; i*i <= n; ++i) {
        minimumCounter=min(minimumCounter,1+ minimumSquaresMemSolve(n- i*i,dp));
    }

    return dp[n]=minimumCounter;

}
int minimumSquaresMem(int n){
    vector<int> dp(n+1,-1);
    return minimumSquaresMemSolve(n,dp);
}

//41. Perfect Squares Problem (Tabulation)
int minimumSquaresTabSolve(int n){
    vector<int> dp(n+1,INT_MAX);

    dp[0]=0;

    for (int i = 1; i <= n; ++i) {               //iterate 1....n
        for (int j = 1; j*j <= n; ++j) {             //for each iterate :: check by 1^2, 2^2, 3^2, 4^2.....i^2 <=n
            if(i - j*j >=0) {
                dp[i] = min(dp[i],1+ dp[i - j*j]);
            }
        }
    }
    return dp[n];
}
int minimumSquaresTab(int n){
    return minimumSquaresTabSolve(n);
}

//42. Perfect Cube Problem (Recursion)
int minimumCubeSolve(int n){
    if(n==0){                  //zero can't make any addition of square of number
        return 0;
    }

    int minimumCounter= n;        //maximum can be possible by n
    for (int i = 1; i*i*i <= n ; ++i) {           //check  by 1^3, 2^3, 3^3, 4^3.....i^3 <=n
        minimumCounter=min(minimumCounter,1+ minimumSquaresSolve(n - i*i*i));  //1 plus ::count for each step
    }                                                                               //decrease n by i^3 every time
    return minimumCounter;
}
int minimumCube(int n){
    return minimumCubeSolve(n);
}

//43. Minimum Cost for Tickets (Recursion)
int minCostTicketsSolve(int noOfDays,vector<int> &days,vector<int> &cost,int index){
    if(index >= noOfDays){                                  //index travesing from 1....365 :: if it is more than noOfDays you have to stay
        return 0;
    }

    int oneDayPass = cost[0] + minCostTicketsSolve(noOfDays,days,cost,index+1);    //one day pass :: cost for that day and recursive call for (index+1)

    int i;
    //like :: for(int i=0;days[i]<7;i++)
    for (i= index; (i < noOfDays) && (days[i] < days[index] +7)  ; ++i);                      //seven day pass :: i move forward for 7 days (from index)
    int sevenDayPass= cost[1] + minCostTicketsSolve(noOfDays,days,cost,i);          //cost for seven days and recursive call for next for (index+7)

    for (i= index; (i < noOfDays) && (days[i] < days[index] +30)  ; ++i);                       //thirty day pass :: i move forward for 30 days (from index)
    int thirtyDayPass= cost[2] + minCostTicketsSolve(noOfDays,days,cost,i);             //cost for thirty days and recursive call for next for (index+30)

    return min(oneDayPass,min(sevenDayPass,thirtyDayPass));                                //get the minimum cost

}
int minCostTickets(int noOfDays,vector<int> &days,vector<int> &cost){
    return minCostTicketsSolve(noOfDays,days,cost,0);
}

//44. Minimum Cost for Tickets (Memorization)
int minCostTicketsMemSolve(int noOfDays,vector<int> &days,vector<int> &cost,int index,vector<int> &dp){
    if(index >= noOfDays){
        return 0;
    }

    if(dp[index] != -1){
        return dp[index];
    }

    int oneDayPass= cost[0] + minCostTicketsMemSolve(noOfDays,days,cost,index+1,dp);

    int i;
    for ( i = index; (i < noOfDays) && (days[i] < days[index] +7); ++i);
    int sevenDayPass= cost[1] + minCostTicketsMemSolve(noOfDays,days,cost,i,dp);

    for ( i = index; (i < noOfDays) && (days[i] < days[index] +30); ++i);
    int thirtyDayPass= cost[2] + minCostTicketsMemSolve(noOfDays,days,cost,i,dp);

    dp[index]= min(oneDayPass,min(sevenDayPass,thirtyDayPass));
    return dp[index];
}
int minCostTicketsMem(int noOfDays,vector<int> &days,vector<int> &cost){
    vector<int> dp(noOfDays+1,-1);
    return minCostTicketsMemSolve(noOfDays,days,cost,0,dp);
}

//45. Minimum Cost for Tickets (Tabulation)
int minCostTicketsTabSolve(int noOfDays,vector<int> &days,vector<int> &cost){
    vector<int> dp(noOfDays+1,INT_MAX);
    dp[noOfDays]=0;                                              //zero day stay cost 0

    for (int index = noOfDays-1; index >=0 ; --index) {
        int oneDayPass= cost[0] + dp[index+1];

        int i;
        for (i = 0; (i < noOfDays) && (days[i] < days[index]+7); ++i);
        int sevenDayPass=cost[1] + dp[i];

        for (i = 0; (i < noOfDays) && (days[i] < days[index]+30); ++i);
        int thirtyDayPass=cost[2] + dp[i];

        dp[index] =min(oneDayPass,min(sevenDayPass,thirtyDayPass));
    }
    return dp[0];
}
int minCostTicketsTab(int noOfDays,vector<int> &days,vector<int> &cost){
    return minCostTicketsTabSolve(noOfDays,days,cost);
}

//46. Minimum Cost for Tickets (Space optimization)  [unsolved]
int minCostTicketsOpt(int noOfDays,vector<int> &days,vector<int> &cost){

}

//47. Largest Square area in Matrix (Recursion)
int maxSquareInMatSolve(int i,int j,vector<vector<int>> &mat,int &maxi){
    if(i>=mat.size() || j>=mat[0].size()){                      //matrix out-of-bound
        return 0;
    }

    int rightSize= maxSquareInMatSolve(i,j+1,mat,maxi);      //same-row and next-col
    int diagonalSize= maxSquareInMatSolve(i+1,j+1,mat,maxi);   //next-row and next-col
    int downSize= maxSquareInMatSolve(i+1,j,mat,maxi);      //next-col and same row

    if(mat[i][j] == 1){                                        //if element is 1
        int ans= 1+ min(rightSize,min(diagonalSize,downSize));    //+1 for the current 1 and minimum (of the right,Diagonal and Down maximum space)
        maxi=max(maxi,ans);
        return ans;
    }
    else{
        return 0;
    }
}
int maxSquareInMat(int n,int m,vector<vector<int>> mat){
    int maxi=0;                                     //to calculate maximum space in the array
    maxSquareInMatSolve(0,0,mat,maxi);
    return maxi;

}

//48. Largest Square area in Matrix (Memorization)
int maxSquareInMatMemSolve(int i,int j,vector<vector<int>> mat,int &maxi,vector<vector<int>> &dp){
    if(i>=mat.size() || j>=mat[0].size()){
        return 0;
    }

    if(dp[i][j] != -1){
        return dp[i][j];
    }

    int rightSize= maxSquareInMatMemSolve(i,j+1,mat,maxi,dp);
    int diagonalSize= maxSquareInMatMemSolve(i+1,j+1,mat,maxi,dp);
    int downSize= maxSquareInMatMemSolve(i+1,j,mat,maxi,dp);

    if(mat[i][j]==1){
        dp[i][j]=1 + min(rightSize,max(diagonalSize,downSize));
        maxi=max(maxi,dp[i][j]);
        return dp[i][j];
    }
    else{
        return dp[i][j]=0;
    }
}
int maxSquareInMatMem(int n,int m,vector<vector<int>> mat){
    int maxi=0;
    vector<vector<int>> dp(n,vector<int>(m,-1));
    maxSquareInMatMemSolve(0,0,mat,maxi,dp);
    return maxi;
}

//49. Largest Square area in Matrix (Tabulation)
int maxSquareInMatTabSolve(vector<vector<int>> mat,int &maxi){
    int row=mat.size();                  //get row-size
    int col=mat[0].size();              //get col-size
    vector<vector<int>> dp(row+1 ,vector<int>(col+1,0));    //row+1 to safe i+1 call
    for (int i = row-1; i >=0 ; --i) {
        for (int j = col-1; j >=0 ; --j) {
            int rightSize=dp[i][j+1];
            int diagonalSize=dp[i+1][j+1];
            int downSize=dp[i+1][j];

            if(mat[i][j]==1){
                dp[i][j] = 1+ min(rightSize,min(diagonalSize,downSize));
                maxi=max(maxi,dp[i][j]);
            }
            else{
                dp[i][j]=0;
            }
        }
    }
    return dp[0][0];             //return unnecessary statement (we need only maxi)
}
int maxSquareInMatTab(int n,int m,vector<vector<int>> mat){
    int maxi=0;
    maxSquareInMatTabSolve(mat,maxi);
    return maxi;
}

//50. Largest Square area in Matrix (Space optimization)
int maxSquareInMatOptSolve(vector<vector<int>> mat,int &maxi) {
    int row=mat.size();
    int col=mat[0].size();
    vector<int> curr(col+1,0);         //dp[i][x]===curr[x]      and  dp[i+1][x]===next[x]
    vector<int> next(col+1,0);
    for (int i = row-1; i >=0 ; --i) {
        for (int j = col-1; j >=0 ; --j) {
            int rightSize=curr[i+1];
            int diagonalSize=next[i+1];
            int downSize=curr[i];

            if(mat[i][j]==1){
                curr[j]=1+ min(rightSize,min(diagonalSize,downSize));
                maxi=max(maxi,curr[j]);
            }
            else{
                curr[j]=0;
            }
        }
        next=curr;
    }
    return next[0];                   //return unnecessary statement (we need only maxi)
}
int maxSquareInMatOpt(int n,int m,vector<vector<int>> mat){
    int maxi=0;
    maxSquareInMatOptSolve(mat,maxi);
    return maxi;
}

//51. Min Score Triangulation of Polygon (Recursion)
int minScoreTriangulationSolve(vector<int>& val,int i,int j){
    if(i+1==j){                       //if there is only two adjacent :: triangle isn't possible to make
        return 0;
    }

    int mini=INT_MAX;                       //to count minimum possible multiplication of weight
    for (int k = i+1; k < j ; ++k) {             //kth vertex is traversing from i+1 to j-1
        mini=min(mini, val[i]*val[j]*val[k] + minScoreTriangulationSolve(val,i,k) + minScoreTriangulationSolve(val,k,j));
                                                        //value of vertex[i]*vertex[j]*vertex[k] and recursion call :: from i----k  and k----j
    }
    return mini;
}
int minScoreTriangulation(vector<int>& values){
    int n=values.size();
    return minScoreTriangulationSolve(values,0,n-1);
}

//52. Min Score Triangulation of Polygon (Memorization)
int minScoreTriangulationMemSolve(vector<int>& val,int i,int j,vector<vector<int>> &dp){
    if(i+1==j){
        return 0;
    }

    if(dp[i][j] != -1){
        return dp[i][j];
    }

    int mini=INT_MAX;
    for (int k = i+1; k < j; ++k) {
        mini=min(mini, val[i]*val[j]*val[k] + minScoreTriangulationMemSolve(val,i,k,dp) + minScoreTriangulationMemSolve(val,k,j,dp));
    }
    dp[i][j]=mini;
    return dp[i][j];
}
int minScoreTriangulationMem(vector<int>& values){
    int n=values.size();
    vector<vector<int>> dp(n,vector<int>(n,-1));
    return minScoreTriangulationMemSolve(values,0,n-1,dp);
}

//53. Min Score Triangulation of Polygon (Tabulation)
int minScoreTriangulationTabSolve(vector<int>& val){
    int n=val.size();
    vector<vector<int>> dp(n,vector<int>(n,0));

    for (int i = n-1; i >=0 ; --i) {                   //i --> last to first
        for (int j = i+2; j < n; ++j) {                  //j---->  from  i+2 (for make a triangle) to n
            int mini=INT_MAX;

            for (int k = i+1; k <j ; ++k) {
                mini=min(mini, val[i]*val[j]*val[k] + dp[i][k] + dp[k][j]);
            }
            dp[i][j]=mini;
        }
    }
    return dp[0][n-1];
}
int minScoreTriangulationTab(vector<int>& values){
    return minScoreTriangulationTabSolve(values);
}


//54. Minimum Sideways Jump (Recursion)
int minSideJumpsSolve(vector<int>& obstacles,int currLane,int currPos) {
    int n=obstacles.size()-1;              //last index :: size-1
    if(currPos == n){                      //reach in the last index(destination) :: no sideJump needed
        return 0;
    }

    if(obstacles[currPos+1] != currLane){                                     //if inFrontPosition :: there is no obstacle
        return minSideJumpsSolve(obstacles,currLane,currPos+1);       //increment current position
    }
    else{                                                                        //if inFrontPosition :: there is an obstacle
        //sideWay jump
        int mini=INT_MAX;                                                           //to find minimum side jump
        for (int i = 1; i <= 3; ++i) {                                                //checking from 1 to 3 lane :: for side jump
            if(currLane!=i && obstacles[currPos] != i){                                 //if jump lane is not mineLane   and  there is not any obstacle in jumpArea(iTh lane)
                mini=min(mini,1+ minSideJumpsSolve(obstacles,i,currPos));     // (1+) is for count no number of jump
            }
        }
        return mini;
    }
}
int minSideJumps(vector<int>& obstacles) {
    return minSideJumpsSolve(obstacles,2,0);
}

//55. Minimum Sideways Jump (Memorization)
int minSideJumpsMemSolve(vector<int>& obstacles,int currLane,int currPos,vector<vector<int>> &dp) {
    int n=obstacles.size()-1;
    if(currPos == n){
        return 0;
    }

    if(dp[currLane][currPos]!=-1){
        return dp[currLane][currPos];
    }

    if(obstacles[currPos+1] != currLane){
        return minSideJumpsMemSolve(obstacles,currLane,currPos+1,dp);
    }
    else{
        int mini=INT_MAX;
        for (int i = 1; i <= 3 ; ++i) {
            if(currLane !=i && obstacles[currPos] != i){
                mini=min(mini,1 + minSideJumpsMemSolve(obstacles,i,currPos,dp));
            }
        }
        dp[currLane][currPos]=mini;
        return dp[currLane][currPos];
    }

}
int minSideJumpsMem(vector<int>& obstacles) {
    vector<vector<int>> dp(4,vector<int>(obstacles.size(),-1));
    return minSideJumpsMemSolve(obstacles,2,0,dp);
}

//56. Minimum Sideways Jump (Tabulation)
int minSideJumpsTabSolve(vector<int>& obstacles) {
    int n=obstacles.size()-1;
    vector<vector<int>> dp(4,vector<int>(obstacles.size(),INT_MAX));

    //counting from last to first

    dp[0][n]=0;            //if we reach in last position :: there is no way to comeFromNextPosition
    dp[1][n]=0;
    dp[2][n]=0;
    dp[3][n]=0;

    for (int currPos = n-1; currPos >=0 ; --currPos) {
        for (int currLane = 1; currLane <=3 ; ++currLane) {
            if(obstacles[currPos+1] != currLane){                       //if there is no obstacle in next position
                dp[currLane][currPos]=dp[currLane][currPos+1];          //its currPosition will become comeFromNextPosition
            }
            else{                                                   //if there is obstacle in next position :: does not comeFromNextPosition ::
                int mini=INT_MAX;
                for (int i = 1; i <= 3 ; ++i) {
                    if(currLane != i && obstacles[currPos] != i) {
                        mini = min(mini, 1 + dp[i][currPos + 1]);          //calculating by next position from currPos
                    }
                }
                dp[currLane][currPos]=mini;
            }
        }
    }
    return min(dp[2][0],min(1+dp[1][0] , 1+dp[3][0]));               //middle way :: first lane + 1 jump :: 3rd lane + 1 jump    (1 jump to reach first lane)

}
int minSideJumpsTab(vector<int>& obstacles) {
    return minSideJumpsTabSolve(obstacles);
}

//57. Minimum Sideways Jump (Space optimization)
int minSideJumpsOptSolve(vector<int>& obstacles) {
    int n=obstacles.size()-1;

    vector<int> curr(4,INT_MAX);                //for currPos vector of 4 lane
    vector<int> next(4,INT_MAX);                  // for currPos+1 vector of 4 lane

    next[0]=0;
    next[1]=0;
    next[2]=0;
    next[3]=0;

    for (int currPos = n-1; currPos >=0 ; --currPos) {
        for (int currLane = 1; currLane <= 3 ; ++currLane) {
            if(obstacles[currPos+1] != currLane){
                curr[currLane]=next[currLane];
            }
            else{
                int mini=INT_MAX;
                for (int i = 1; i <= 3 ; ++i) {
                    if(currLane != i && obstacles[currPos] != i){
                        mini=min(mini, 1+next[i]);
                    }
                }
                curr[currLane]=mini;
            }
        }
        next=curr;
    }
    return min(next[2] , min(1+next[1] , 1+next[3]));               //middle way :: first lane + 1 jump :: 3rd lane + 1 jump    (1 jump to reach first lane)
}
int minSideJumpsOpt(vector<int>& obstacles) {
    return minSideJumpsOptSolve(obstacles);
}

//58. Reducing Dishes (Recursion)
int maxSatisfactionSolve(vector<int> &satisfaction,int index,int time){
    if(index==satisfaction.size()){
        return 0;
    }

    int include=satisfaction[index] * (time+1) + maxSatisfactionSolve(satisfaction,index+1,time+1);    //ans+=satis[index]*(time+1)  :: call for index++ and time++
    int exclude= 0 + maxSatisfactionSolve(satisfaction,index+1,time);                                       //ans+=0         :: call for index++ and time remain same

    return max(include,exclude);
}
int maxSatisfaction(vector<int> &satisfaction){
    sort(satisfaction.begin(), satisfaction.end());           //sort ascending order
    return maxSatisfactionSolve(satisfaction,0,0);
}

//59. Reducing Dishes (Memorization)
int maxSatisfactionMemSolve(vector<int> &satisfaction,int index,int time,vector<vector<int>> &dp){
    if(index==satisfaction.size()){
        return 0;
    }

    if(dp[index][time] != -1){
        return dp[index][time];
    }

    int include=satisfaction[index]*(time+1) + maxSatisfactionMemSolve(satisfaction,index+1,time+1,dp);
    int exclude= 0 + maxSatisfactionMemSolve(satisfaction,index+1,time,dp);
    return dp[index][time]=max(include,exclude);
}
int maxSatisfactionMem(vector<int> &satisfaction){
    sort(satisfaction.begin(), satisfaction.end());

    int n=satisfaction.size();
    vector<vector<int>> dp(n+1,vector<int>(n+1,-1));
    return maxSatisfactionMemSolve(satisfaction,0,0,dp);
}

//60. Reducing Dishes (Tabulation)
int maxSatisfactionTabSolve(vector<int> &satisfaction){
    int n=satisfaction.size();
    vector<vector<int>> dp(n+1,vector<int>(n+1,0));

    for (int index = n-1; index >=0 ; --index) {                               //index traversing from last to first
        for (int time = index; time >=0 ; --time) {                               //time traverse (from index) to 0
            int include =satisfaction[index]*(time+1) + dp[index+1][time+1];       //index++ and time++
            int exclude=0 +dp[index+1][time];                                       //index++

            dp[index][time]=max(include,exclude);
        }
    }

    return dp[0][0];
}
int maxSatisfactionTab(vector<int> &satisfaction){
    sort(satisfaction.begin(), satisfaction.end());
    return maxSatisfactionTabSolve(satisfaction);
}

//61. Reducing Dishes (Space optimization)
int maxSatisfactionOptSolve(vector<int> &satisfaction){
    int n=satisfaction.size();
    vector<int> curr(n+1);          //for curr===dp[index]
    vector<int> next(n+1);         //for next===dp[index+1]

    for (int index = n-1; index >=0 ; --index) {
        for (int time = index; time >=0 ; --time) {
            int include= satisfaction[index]*(time+1) + next[time+1];
            int exclude= 0 + next[time];

            curr[time] =max(include,exclude);
        }
        next=curr;
    }

    return next[0];
}
int maxSatisfactionOpt(vector<int> &satisfaction){
    sort(satisfaction.begin(), satisfaction.end());
    return maxSatisfactionOptSolve(satisfaction);
}

//62. Longest Increasing Subsequence (Recursion)
int longestSubsequenceSolve(int n,int arr[],int curr,int prev){
    if(curr==n){
        return 0;
    }

    int include=0;
    if(prev==-1 || arr[curr] > arr[prev]){                                   //if element is first element(prev==-1)  or current element is greater than previous element
         include=1 + longestSubsequenceSolve(n,arr,curr+1,curr);    //include it and count (+1)  :: curr++ and prev=curr
    }
    int exclude= 0 + longestSubsequenceSolve(n,arr,curr+1,prev);       //exclude it and count (+0)    ;; curr++ and prev remain same

    return max(include,exclude);                                      //return maximum of include exclude
}
int longestSubsequence(int n,int arr[]){
    return longestSubsequenceSolve(n,arr,0,-1);                   //curr :: 0....(n-1)        prev:: -1.....(n-1)
}

//63. Longest Increasing Subsequence (Memorization)
int longestSubsequenceMemSolve(int n,int arr[],int curr,int prev,vector<vector<int>> &dp){
    if(curr==n){
        return 0;
    }

    if(dp[curr][prev+1]!=-1){                     //dp[prev+1] :: because 0 index contains -1 and    (n+1)th index contains  (nth) index value
        return dp[curr][prev+1];
    }

    int include=0;
    if(prev==-1 || arr[curr] > arr[prev]){
        include=1 + longestSubsequenceSolve(n,arr,curr+1,curr);
    }
    int exclude= 0 + longestSubsequenceSolve(n,arr,curr+1,prev);

    return dp[curr][prev+1]= max(include,exclude);
}
int longestSubsequenceMem(int n,int a[]){
    vector<vector<int>> dp(n, vector<int>(n+1,-1));
    return longestSubsequenceMemSolve(n,a,0,-1,dp);

}

//64. Longest Increasing Subsequence (Tabulation)
int longestSubsequenceTabSolve(int n,int arr[],int curr,int prev){
    vector<vector<int>> dp(n+1,vector<int>(n+1,0));        //for containing -1 :: we need n+1 space ::

    for (int curr = n-1; curr >=0 ; --curr) {                   //traversing from end   (n-1)....0
        for (int prev = curr-1; prev >= -1 ; --prev) {          //                      (n-1)...-1
            int include=0;
            if(prev==-1 || arr[curr] > arr[prev]){             //dp[prev+1]
                include = 1 + dp[curr+1][curr+1];
            }
            int exclude = 0 + dp[curr+1][prev+1];

            dp[curr][prev+1] =max(include,exclude);
        }
    }
    return dp[0][0];
}
int longestSubsequenceTab(int n,int a[]){
    return longestSubsequenceTabSolve(n,a,0,-1);
}

//65. Longest Increasing Subsequence (Space optimization)
int longestSubsequenceOptSolve(int n,int arr[],int curr,int prev){
    vector<int> currRow(n+1,0);               //dp[curr] === currRow
    vector<int> nextRow(n+1,0);               //dp[curr+1] === nextRow

    for (int curr = n-1; curr >=0 ; --curr) {
        for (int prev = curr-1; prev >= -1 ; --prev) {
            int include=0;
            if(prev==-1 || arr[curr] > arr[prev]){
                include = 1 + nextRow[curr+1];
            }
            int exclude = 0 + nextRow[prev+1];

            currRow[prev+1] =max(include,exclude);
        }
        nextRow=currRow;                           //currRow will become change after iteration
    }
    return nextRow[0];                            //nextRow first index is ans
}
int longestSubsequenceOpt(int n,int a[]){
    return longestSubsequenceOptSolve(n,a,0,-1);
}

//66.Longest Increasing Subsequence (DP + BinarySearch)
int longestSubsequenceDpBsSolve(int n,int arr[]){
    if(n==0){
        return 0;
    }

    vector<int> ans;
    ans.push_back(arr[0]);                //first element will push without any condition
    for (int i = 1; i < n; ++i) {             //second to last element
        if(arr[i] > ans.back()){              //if current element is greter than last element of ans vector :: push it
            ans.push_back(arr[i]);
        }
        else{
            int index= lower_bound(ans.begin(), ans.end(),arr[i]) - ans.begin();     //to get immediate greater value's index :: get memory address - first element address
            ans[index]=arr[i];              //re-assign into that index by the current value (we just need the size of ans vector so overlap value doesn't matter)
        }
    }
    return ans.size();

}
int longestSubsequenceDpBs(int n,int a[]){
    return longestSubsequenceDpBsSolve(n,a);
}


//67. Russian Doll
struct Env{
    int width;
    int height;
    Env(int width,int height){
        this->width=width;
        this->height=height;
    }
};
bool comp(Env ob1,Env ob2){
    if(ob1.width==ob2.width){
        return ob1.height > ob2.height;
    }
    return ob1.width < ob2.width;
}

int maxEnvelopsSolve(vector<vector<int>> &envelopes){
    vector<Env> arr;
    for (auto x:envelopes) {
        Env obj(x[0],x[1]);
        arr.push_back(obj);
    }
    sort(arr.begin(), arr.end(),comp);         //get ascending by width and descending by height(if width is equal)

    int n=envelopes.size();
    int heightArr[n];                          //to get array of height
    for (int i = 0; i < n; ++i) {
        heightArr[i]=arr[i].height;
    }


 //   return longestSubsequenceDpBs(envelopes.size(),heightArr);

    //operate:: longest Subsequence by DP and Binary search of heightArr
    if(n==0){
        return 0;
    }

    vector<int> ans;
    ans.push_back(heightArr[0]);

    for (int i = 1; i < n; ++i) {
        if(heightArr[i] > ans.back()){
            ans.push_back(heightArr[i]);
        }
        else{
            int index= lower_bound(ans.begin(), ans.end(),heightArr[i]) - ans.begin();
            ans[index]=heightArr[i];
        }
    }
    return ans.size();


}
int maxEnvelops(vector<vector<int>> &envelopes){
    return maxEnvelopsSolve(envelopes);
}

//68. Maximum Height by Stacking Cuboid (DP + BinarySearch)
bool check(vector<int> base,vector<int> newBox){
    if(newBox[0]<=base[0] &&newBox[1]<=base[1] && newBox[2]<=base[2]){
        return true;
    }
    else{
        return false;
    }
}
int maxCuboidsHeightTabSolve(int n,vector<vector<int>> &cuboids){
    vector<int> currRow(n+1,0);               //dp[curr] === currRow
    vector<int> nextRow(n+1,0);               //dp[curr+1] === nextRow

    for (int curr = n-1; curr >=0 ; --curr) {
        for (int prev = curr-1; prev >= -1 ; --prev) {
            int include=0;
            if(prev==-1 || check(cuboids[curr] , cuboids[prev])){
                include = cuboids[curr][2] + nextRow[curr+1];
            }
            int exclude = 0 + nextRow[prev+1];

            currRow[prev+1] =max(include,exclude);
        }
        nextRow=currRow;                           //currRow will become change after iteration
    }
    return nextRow[0];                            //nextRow first index is ans
}
int maxCuboidsHeightTab(vector<vector<int>> &cuboids){
    for (auto &arr:cuboids) {
        sort(arr.begin(), arr.end());
    }

    sort(cuboids.begin(), cuboids.end());
    return maxCuboidsHeightTabSolve(cuboids.size(),cuboids);
}


//69. Pizza with 3n size (Recursion)
int maxPizzaSlicesSolve(int index,int endIndex,vector<int> &slices,int noOfSlice){
    if(noOfSlice==0 || index>=slices.size()){
        return 0;
    }

    int include=slices[index] + maxPizzaSlicesSolve(index+2,endIndex,slices,noOfSlice-1);       //skip next slice (call by index+2) and decreased by one slice
    int exclude= 0 + maxPizzaSlicesSolve(index+1,endIndex,slices,noOfSlice);
    return max(include,exclude);

}
int maxPizzaSlices(vector<int> &slices){
    int k=slices.size();
    int case1= maxPizzaSlicesSolve(0,k-2,slices,k/3);          //for firstToSecondLast
    int case2= maxPizzaSlicesSolve(1,k-1,slices,k/3);          //for secondToLast
    return max(case1,case2);
}

//70. Pizza with 3n size (Memorization)
int maxPizzaSlicesMemSolve(int index,int endIndex,vector<int> &slices,int noOfSlice,vector<vector<int>> &dp){
    if(noOfSlice==0 || index>=slices.size()){
        return 0;
    }

    if(dp[index][noOfSlice] !=-1){
        return dp[index][noOfSlice];
    }

    int include=slices[index] + maxPizzaSlicesMemSolve(index+2,endIndex,slices,noOfSlice-1,dp);
    int exclude= 0 + maxPizzaSlicesMemSolve(index+1,endIndex,slices,noOfSlice,dp);
    return dp[index][noOfSlice]= max(include,exclude);
}
int maxPizzaSlicesMem(vector<int> &slices){
    int k=slices.size();

    vector<vector<int>> dp1(k,vector<int>(k,-1));
    int case1= maxPizzaSlicesMemSolve(0,k-2,slices,k/3,dp1);

    vector<vector<int>> dp2(k,vector<int>(k,-1));
    int case2= maxPizzaSlicesMemSolve(1,k-1,slices,k/3,dp2);
    return max(case1,case2);
}


//71. Pizza with 3n size (Tabulation)
int maxPizzaSlicesTabSolve(vector<int> &slices){
    int k=slices.size();
    vector<vector<int>> dp1(k+2,vector<int>(k+2,0));
    for (int index = k-2; index >=0 ; --index) {
        for (int noOfSlice = 1; noOfSlice <= k/3 ; ++noOfSlice) {
            int include=slices[index] + dp1[index+2][noOfSlice-1];
            int exclude= 0 + dp1[index+1][noOfSlice];
            dp1[index][noOfSlice]= max(include,exclude);
        }
    }
    int case1=dp1[0][k/3];



    vector<vector<int>> dp2(k+2,vector<int>(k+2,0));
    for (int index = k-1; index >=0 ; --index) {
        for (int noOfSlice = 1; noOfSlice <= k/3 ; ++noOfSlice) {
            int include=slices[index] + dp2[index+2][noOfSlice-1];
            int exclude= 0 + dp2[index+1][noOfSlice];
            dp2[index][noOfSlice]= max(include,exclude);
        }
    }
    int case2=dp2[1][k/3];

    return max(case1,case2);
}
int maxPizzaSlicesTab(vector<int> &slices){
    return maxPizzaSlicesTabSolve(slices);
}

//72. Pizza with 3n size (Space optimization)
int maxPizzaSlicesOptSolve(vector<int> &slices){
    int k=slices.size();
    vector<int> prev1(k+2,0);
    vector<int> curr1(k+2,0);
    vector<int> next1(k+2,0);

    for (int index = k-2; index >=0 ; --index) {
        for (int noOfSlice = 1; noOfSlice <= k/3 ; ++noOfSlice) {
            int include=slices[index] + next1[noOfSlice-1];
            int exclude= 0 + curr1[noOfSlice];
            prev1[noOfSlice]= max(include,exclude);
        }
        next1=curr1;
        curr1=prev1;
    }
    int case1=curr1[k/3];


    vector<int> prev2(k+2,0);
    vector<int> curr2(k+2,0);
    vector<int> next2(k+2,0);

    for (int index = k-1; index >=0 ; --index) {
        for (int noOfSlice = 1; noOfSlice <= k/3 ; ++noOfSlice) {
            int include=slices[index] + next2[noOfSlice-1];
            int exclude= 0 + curr2[noOfSlice];
            prev2[noOfSlice]= max(include,exclude);
        }

        next2=curr2;
        curr2=prev2;
    }
    int case2=curr2[k/3];

    return max(case1,case2);
}
int maxPizzaSlicesOpt(vector<int> &slices){
    return maxPizzaSlicesOptSolve(slices);
}

//73. Number of Dice Rolls with Target Sum (Recursion)
long noOfDiceRollsSolve(int dice,int face,int target){
    if(target < 0){
        return 0;
    }
    if(dice==0 && target!=0){
        return 0;
    }
    if(target==0 && dice!=0){             //there is not 0 type face
        return 0;
    }
    if(dice==0 && target==0){            //one way :: nothing to do
        return 1;
    }

    long ans=0;
    for (int i = 1; i <=face; ++i) {
        ans = ans + noOfDiceRollsSolve(dice-1,face,target-i);
    }
    return ans;

}
long noOfDiceRolls(int dice,int face,int target){
    return noOfDiceRollsSolve(dice,face,target);

}

//74. Number of Dice Rolls with Target Sum (Memorization)
long noOfDiceRollsMemSolve(int dice,int face,int target,vector<vector<long>> &dp){
    if(target < 0){
        return 0;
    }
    if(dice==0 && target!=0){
        return 0;
    }
    if(target==0 && dice!=0){             //there is not 0 type face
        return 0;
    }
    if(dice==0 && target==0){            //one way :: nothing to do
        return 1;
    }

    if(dp[dice][target] != -1){
        return dp[dice][target];
    }

    int ans=0;
    for (int i = 1; i <=face; ++i) {
        ans = ans + noOfDiceRollsMemSolve(dice-1,face,target-i,dp);
    }
    return dp[dice][target] = ans;
}
long noOfDiceRollsMem(int dice,int face,int target){
   vector<vector<long>> dp(dice+1,vector<long>(target+1,-1));
    return noOfDiceRollsMemSolve(dice,face,target,dp);

}

//75. Number of Dice Rolls with Target Sum (Tabulation)
long noOfDiceRollsTabSolve(int dice,int face,int target){
    vector<vector<long>> dp(dice+1,vector<long>(target+1,0));

    dp[0][0]=1;

    for (int dc = 1; dc <= dice; ++dc) {
        for (int tr = 1; tr <= target; ++tr) {

            long ans=0;
            for (int i = 1; i <=face; ++i) {
                if(tr-i >=0) {
                    ans = ans + dp[dc - 1][tr - i];
                }
            }
            dp[dc][tr] = ans;
        }
    }
    return dp[dice][target];
}
long noOfDiceRollsTab(int dice,int face,int target){
    return noOfDiceRollsTabSolve(dice,face,target);
}

//76. Number of Dice Rolls with Target Sum (Space optimization)
long noOfDiceRollsSolveOpt(int dice,int face,int target){
    vector<long> prev(target+1,0);
    vector<long> curr(target+1,0);

    prev[0]=1;

    for (int dc = 1; dc <= dice; ++dc) {
        for (int tr = 1; tr <= target; ++tr) {

            long ans=0;
            for (int i = 1; i <=face; ++i) {
                if(tr-i >=0) {
                    ans = ans + prev[tr - i];
                }
            }
            curr[tr] = ans;
        }
        prev=curr;
    }
    return curr[target];
}
long noOfDiceRollsOpt(int dice,int face,int target){
    return noOfDiceRollsSolveOpt(dice,face,target);
}

//77. Partition Equal Subset Sum (Recursion)
bool equalPartitionSubSumSolve(int n,int *arr,int target,int index){
    if(index >= n){               //array-out-of-bound
        return false;
    }
    if(target < 0){
        return false;
    }
    if(target==0){
        return true;
    }

    bool include= equalPartitionSubSumSolve(n,arr,target-arr[index],index+1);
    bool exclude= equalPartitionSubSumSolve(n,arr,target,index+1);

    return include || exclude;
}
bool equalPartitionSubSum(int n,int *arr){
    int total=0;
    for (int i = 0; i < n; ++i) {
        total+=arr[i];
    }
    if(total & 1){
        return false;
    }

    int target=total/2;
    return equalPartitionSubSumSolve(n,arr,target,0);
}

//78. Partition Equal Subset Sum (Memorization)
bool equalPartitionSubSumMemSolve(int n,int *arr,int target,int index,vector<vector<int>> &dp){
    if(index>=n){
        return false;
    }
    if(target < 0){
        return false;
    }
    if(target==0){
        return true;
    }

    if(dp[index][target] != -1 ){
        return dp[index][target];
    }

    bool include =equalPartitionSubSumMemSolve(n,arr,target-arr[index],index+1,dp);
    bool exclude= equalPartitionSubSumMemSolve(n,arr,target- 0,index+1,dp);

    return dp[index][target]= include or exclude;
}
bool equalPartitionSubSumMem(int n,int *arr){

    int total=0;
    for (int i = 0; i < n; ++i) {
        total+=arr[i];
    }
    if(total & 1){
        return false;
    }

    int target=total/2;

    vector<vector<int>> dp(n,vector<int>(target+1,-1));

    return equalPartitionSubSumMemSolve(n,arr,target,0,dp);
}

//79. Partition Equal Subset Sum (Tabulation)
bool equalPartitionSubSumTabSolve(int n,int *arr,int target){
    vector<vector<bool>> dp(n+1,vector<bool>(target+1, false));

    for (int i = 0; i <= n; ++i) {
        dp[i][0]= true;
    }
    for (int idx = n-1; idx >= 0; --idx) {
        for (int tar = 0; tar <= target ; ++tar) {
            bool include= false;
            if(tar- arr[idx] >=0) {
                include = dp[idx + 1][tar - arr[idx]];
            }
             bool exclude=dp[idx+1][tar- 0];

            dp[idx][tar]=include or exclude ;
        }
    }
    return dp[0][target];
}
bool equalPartitionSubSumTab(int n,int *arr){
    int total=0;
    for (int i = 0; i < n; ++i) {
        total+=arr[i];
    }
    if(total & 1){
        return false;
    }

    int target=total/2;
    return equalPartitionSubSumTabSolve(n,arr,target);
}

//80. Partition Equal Subset Sum (Space optimization)
bool equalPartitionSubSumOptSolve(int n,int *arr,int target){
 //   vector<vector<bool>> dp(n+1,vector<bool>(target+1, false));
    vector<bool> curr(target+1, false);
    vector<bool> next(target+1, false);

    curr[0]= true;
    next[0]=true;

    for (int idx = n-1; idx >= 0; --idx) {
        for (int tar = 0; tar <= target ; ++tar) {
            bool include= false;
            if(tar- arr[idx] >=0) {
                include = next[tar - arr[idx]];
            }
            bool exclude=next[tar - 0];

            curr[tar]=include or exclude ;
        }
       next=curr;
    }
    return next[target];
}
bool equalPartitionSubSumOpt(int n,int *arr){
    int total=0;
    for (int i = 0; i < n; ++i) {
        total+=arr[i];
    }
    if(total & 1){
        return false;
    }

    int target=total/2;
    return equalPartitionSubSumOptSolve(n,arr,target);
}


//81. Minimum Swap to Make Sequence Increasing (Recursion)
int makeSeqMinSwapSolve(vector<int> &num1,vector<int> &num2,int index,bool swapped){
    if(index == num1.size()){
        return 0;
    }

    int prevNum1=num1[index-1];
    int prevNum2=num2[index-1];

    if(swapped){
        swap(prevNum1,prevNum2);
    }

    //No swap
    int exclude=INT_MAX;
    if(num1[index]>prevNum1 && num2[index]>prevNum2){
        exclude = makeSeqMinSwapSolve(num1,num2,index+1, false);
    }

    //Swap
    int include=INT_MAX;
    if(num1[index]>prevNum2 && num2[index]>prevNum1) {
        include =1 + makeSeqMinSwapSolve(num1,num2,index+1, true);
    }
    return min(include,exclude);
}
int makeSeqMinSwap(vector<int> &num1,vector<int> &num2){
    num1.insert(num1.begin(),-1);
    num2.insert(num2.begin(),-1);

    bool swapped= false;
    int ans= makeSeqMinSwapSolve(num1,num2,1,swapped);
    if(ans==INT_MIN){
        return -1;
    }
    return ans;
}

//82. Minimum Swap to Make Sequence Increasing (Memorization) [Problem]
int makeSeqMinSwapMemSolve(vector<int> &num1,vector<int> &num2,int index,bool swapped, vector<vector<int>> &dp){
    if(index == num1.size()){
        return 0;
    }

    if(dp[index][swapped] != -1){
        return dp[index][swapped];
    }

    int prevNum1=num1[index-1];
    int prevNum2=num2[index-1];

    if(swapped){
        swap(prevNum1,prevNum2);
    }

    //No swap
    int exclude=INT_MAX;
    if(num1[index]>prevNum1 && num2[index]>prevNum2){
        exclude = makeSeqMinSwapMemSolve(num1,num2,index+1, false,dp);
    }

    //Swap
    int include=INT_MAX;
    if(num1[index]>prevNum2 && num2[index]>prevNum1) {
        include =1 + makeSeqMinSwapMemSolve(num1,num2,index+1, true,dp);
    }
    return dp[index][swapped]= min(include,exclude);

}

int makeSeqMinSwapMem(vector<int> &num1,vector<int> &num2){

    num1.insert(num1.begin(),-1);
    num2.insert(num2.begin(),-1);

    int n=num1.size();
    vector<vector<int>> dp(n,vector<int>(2,-1));

    bool swapped= false;
    int ans= makeSeqMinSwapMemSolve(num1,num2,1,swapped,dp);
    if(ans==INT_MIN){
        return -1;
    }
    return ans;
}

//83. Minimum Swap to Make Sequence Increasing (Tabulation)
int makeSeqMinSwapTabSolve(vector<int> &num1,vector<int> &num2){
    int n=num1.size();
    vector<vector<int>> dp(n+1,vector<int>(2,0));

    for (int index = n-1; index >=1 ; --index) {
        for (int swapped = 1; swapped >= 0 ; --swapped) {
            int prevNum1=num1[index-1];
            int prevNum2=num2[index-1];

            if(swapped){
                swap(prevNum1,prevNum2);
            }

            //No swap
            int exclude=INT_MAX;
            if(num1[index]>prevNum1 && num2[index]>prevNum2){
                exclude = dp[index+1][0];
            }

            //Swap
            int include=INT_MAX;
            if(num1[index]>prevNum2 && num2[index]>prevNum1) {
                include =1 + dp[index+1][1];
            }
            dp[index][swapped]= min(include,exclude);
        }
    }
    return dp[1][0];
}


int makeSeqMinSwapTab(vector<int> &num1,vector<int> &num2){
    num1.insert(num1.begin(),-1);
    num2.insert(num2.begin(),-1);

    int ans= makeSeqMinSwapTabSolve(num1,num2);
    if(ans==INT_MIN){
        return -1;
    }
    return ans;
}

//84. Minimum Swap to Make Sequence Increasing (Space optimization)
int makeSeqMinSwapOptSolve(vector<int> &num1,vector<int> &num2){
    int n=num1.size();

    int swapp=0,noSwapp=0;
    int currSwapp=0,currNoSwapp=0;

    for (int index = n-1; index >=1 ; --index) {
        for (int swapped = 1; swapped >= 0 ; --swapped) {
            int prevNum1=num1[index-1];
            int prevNum2=num2[index-1];

            if(swapped){
                swap(prevNum1,prevNum2);
            }

            //No swap
            int exclude=INT_MAX;
            if(num1[index]>prevNum1 && num2[index]>prevNum2){
                exclude = noSwapp;
            }

            //Swap
            int include=INT_MAX;
            if(num1[index]>prevNum2 && num2[index]>prevNum1) {
                include =1 + swapp;
            }
            if(swapped) {
                currSwapp = min(include, exclude);
            }
            else{
                currNoSwapp=min(include,exclude);
            }

        }
        swapp=currSwapp;
        noSwapp=currNoSwapp;
    }
    return min(swapp,noSwapp);
}

int makeSeqMinSwapOpt(vector<int> &num1,vector<int> &num2){
    num1.insert(num1.begin(),-1);
    num2.insert(num2.begin(),-1);

    int ans= makeSeqMinSwapTabSolve(num1,num2);
    if(ans==INT_MIN){
        return -1;
    }
    return ans;
}


//85. Longest Arithmetic Subsequence (Recursion)
int lengthOfLongestAPSolve(int index,int diff,int *arr){
    if(index<0){         //index:: i....0->stop
        return 0;
    }
    int ans=0;
    for (int j = index-1; j >=0 ; --j) {    //j:: i-1...0->stop
        if(arr[index]-arr[j] == diff){             //if we have solved one case
            ans=max(ans,1+ lengthOfLongestAPSolve(j,diff,arr));  //+1 we have solved one case and rest of the case is for recursion
        }
    }
    return ans;
}
int lengthOfLongestAP(int *arr,int n){
    if(n<=2){             //1 element array have AP size 1 and 2 element have 2 size
        return n;
    }
    int ans=0;
    for (int i = 0; i < n; ++i) {                 //iterate every pair of i
        for (int j = i+1; j < n; ++j) {              // and j
            ans= max(ans,2 + lengthOfLongestAPSolve(i,arr[j]-arr[i],arr));      //+2 we have already included 2 element to find their difference
                                                                    //index:: 0...n-1
        }
    }
    return ans;
}


//86. Longest Arithmetic Subsequence (Memorization)
int lengthOfLongestAPMemSolve(int index,int diff,int *arr,unordered_map<int,int> dp[]){
    if(index<0){
        return 0;
    }

    if(dp[index].count(diff)){
        return dp[index][diff];
    }

    int ans=0;
    for (int j = index-1; j >=0 ; --j) {
        if(arr[index]-arr[j] == diff){
            ans=max(ans,1+ lengthOfLongestAPSolve(j,diff,arr));
        }
    }
    return dp[index][diff]= ans;
}
int lengthOfLongestAPMem(int *arr,int n){
    if(n<=2){
        return n;
    }
    int ans=0;

    unordered_map<int,int> dp[n+1];

    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            ans= max(ans,2 + lengthOfLongestAPSolve(i,arr[j]-arr[i],arr));
        }
    }
    return ans;
}

//87. Longest Arithmetic Subsequence (Tabulation)
int lengthOfLongestAPTabSolve(int *arr,int n){
    if(n<=2){
        return n;
    }

    int ans=0;

    unordered_map<int,int> dp[n+1];

    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            int diff=arr[i] - arr[j];
            int cnt=1;

            if(dp[j].count(diff)){
                cnt=dp[j][diff];
            }
            dp[i][diff]= 1 + cnt;
            ans=max(ans,dp[i][diff]);
        }
    }
    return ans;
}
int lengthOfLongestAPTab(int *arr,int n){
    return lengthOfLongestAPTabSolve(arr,n);
}

//88.  Longest AP with given Difference "d" (Hashmap)
int longestSubsequenceSolve(vector<int>& arr, int difference) {
    unordered_map<int,int> dp;
    int ans=0;

    for (int i = 0; i < arr.size(); ++i) {   //traverse full array one-by-one
        int temp=arr[i] - difference;       //have to find this number like 5-(-2)=7 :: count how many times 5 counted in mapping
        int tempAns=0;

        if(dp.count(temp)){       //search in mapping from the current situation
            tempAns=dp[temp];
        }

        dp[arr[i]]=1+tempAns;         //+1 for subsequence by temp itself and add rest of the occurrence into the mapping :: and update mapping

        ans=max(ans,dp[arr[i]]);     //max of mapping dp
    }
    return ans;
}

int longestSubsequence(vector<int>& arr, int difference) {
    return longestSubsequenceSolve(arr,difference);
}

//89. Unique Binary Search Trees or Catalan Number (Recursion)
int uniqBinaryTreeSolve(int n){
    if(n<=1){
        return 1;
    }
    int ans=0;
    for (int i = 1; i <= n; ++i) {      //every node will be root node
        ans += uniqBinaryTreeSolve(i-1) * uniqBinaryTreeSolve(n-i);
    }
    return ans;
}
int uniqBinaryTree(int n){
    return uniqBinaryTreeSolve(n);
}

//90. Unique Binary Search Trees or Catalan Number (Memorization)
int uniqBinaryTreeMemSolve(int n,vector<int> &dp){
    if(n<=1){
        return 1;
    }

    if(dp[n]!=-1){
        return dp[n];
    }

    int ans=0;
    //i--> no of node
    for (int i = 1; i <= n; ++i) {
        ans += uniqBinaryTreeSolve(i-1) * uniqBinaryTreeSolve(n-i);
    }
    return dp[n]= ans;
}
int uniqBinaryTreeMem(int n){
    vector<int> dp(n+1,-1);
    return uniqBinaryTreeMemSolve(n,dp);
}


//91. Unique Binary Search Trees or Catalan Number (Tabulation)
int uniqBinaryTreeTabSolve(int n){
    vector<int> dp(n+1,0);
    dp[0] =dp[1] =1;

    //i--> no of node
    for (int i = 2; i <= n; ++i) {
        //j--> root node
        for (int j = 1; j <= i; ++j) {
            dp[i] +=dp[j-1] * dp[i-j];
        }
    }
    return dp[n];
}
int uniqBinaryTreeTab(int n){
    return uniqBinaryTreeTabSolve(n);
}

//92. Guess Number Higher or Lower (Recursion)
int getMoneyAmountSolve(int start,int end) {
    if(start>=end){
        return 0;
    }

    int ans=INT_MAX;
    for (int i = start; i <= end ; ++i) {
        ans=min(ans,i+max(getMoneyAmountSolve(start,i-1), getMoneyAmountSolve(i+1,end)));
    }
    return ans;
}
int getMoneyAmount(int n) {
    return getMoneyAmountSolve(1,n);
}

//93. Guess Number Higher or Lower (Memorization)
int getMoneyAmountMemSolve(int start,int end,vector<vector<int>> &dp) {
    if(start>=end){
        return 0;
    }

    if( dp[start][end] !=-1){
        return  dp[start][end];
    }

    int ans=INT_MAX;
    for (int i = start; i <= end ; ++i) {
        ans=min(ans,i+max(getMoneyAmountMemSolve(start,i-1,dp), getMoneyAmountMemSolve(i+1,end,dp)));
    }
    return dp[start][end] =ans;
}
int getMoneyAmountMem(int n) {
    vector<vector<int>> dp(n+1,vector<int>(n+1,-1));
    return getMoneyAmountMemSolve(1,n,dp);
}


//94. Guess Number Higher or Lower (Tabulation)
int getMoneyAmountTabSolve(int n) {
    vector<vector<int>> dp(n+2,vector<int>(n+2,0));

    for (int start = n; start >=1 ; --start) {
        for (int end = start; end <=n ; ++end) {
            if(start==end){
                continue;
            }
            else{
                int ans=INT_MAX;
                for (int i = start; i <= end ; ++i) {
                    ans=min(ans,i+max(dp[start][i-1], dp[i+1][end]));
                }
                dp[start][end] =ans;
            }
        }
    }
    return dp[1][n];
}
int getMoneyAmountTab(int n) {
    return getMoneyAmountTabSolve(n);
}

//95

//96. Buy and Sell Stock [I]
int maxProfitBuySell(vector<int> &prices){
    int mini = prices[0];
    int profit = 0;
    for (int i = 1; i < prices.size(); ++i) {
        int diff = prices[i] - mini;
        profit = max(profit,diff);
        mini = min(mini,prices[i]);
    }
    return profit;
}

//97. Buy and Sell Stock [II] (Recursion)
int maxProfitBuySell2Solve(vector<int> &prices,int index,bool buy){
    if(index==prices.size()){
        return 0;
    }

    int profit=0;
    if(buy){
        int include= -prices[index] + maxProfitBuySell2Solve(prices,index+1, false);
        int exclude = 0 + maxProfitBuySell2Solve(prices,index+1, true);
        profit =max(include,exclude);
    }
    else{
        int include = prices[index] + maxProfitBuySell2Solve(prices,index+1, true);
        int exclude = 0 + maxProfitBuySell2Solve(prices,index+1, false);
        profit =max(include,exclude);
    }
    return profit;
}
int maxProfitBuySell2(vector<int> &prices){
    return maxProfitBuySell2Solve(prices,0, true);
}

//98. Buy and Sell Stock [II] (Memorization)
int maxProfitBuySell2MemSolve(vector<int> &prices,int index,int buy,vector<vector<int>> &dp){
    if(index>=prices.size()){
        return 0;
    }

    if(dp[index][buy]!=-1){
        return dp[index][buy];
    }

    int profit = 0;
    if(buy){
        int include = -prices[index] + maxProfitBuySell2MemSolve(prices,index+1,0,dp);
        int exclude = 0 + maxProfitBuySell2MemSolve(prices,index+1,1,dp);
        profit = max(include,exclude);
    }
    else{
        int include = prices[index] + maxProfitBuySell2MemSolve(prices,index+1,1,dp);
        int exclude = 0 + maxProfitBuySell2MemSolve(prices,index+1,0,dp);
        profit = max(include,exclude);
    }

    return dp[index][buy] = profit;
}
int maxProfitBuySell2Mem(vector<int> &prices){
    int n=prices.size();
    vector<vector<int>> dp(n+1,vector<int>(2,-1));
    return maxProfitBuySell2MemSolve(prices,0,1,dp);
}

//99. Buy and Sell Stock [II]  (Tabulation)
int maxProfitBuySell2TabSolve(vector<int> &prices){
    int n=prices.size();
    vector<vector<int>> dp(n+1,vector<int>(2,0));

    for (int index = n-1; index >=0 ; --index) {
        for (int buy = 0; buy <= 1; ++buy) {

            int profit = 0;
            if(buy){
                int include = -prices[index] + dp[index+1][0];
                int exclude = 0 + + dp[index+1][1];
                profit = max(include,exclude);
            }
            else{
                int include = prices[index] + + dp[index+1][1];
                int exclude = 0 + + dp[index+1][0];
                profit = max(include,exclude);
            }

            dp[index][buy] = profit;
        }
    }
    return dp[0][1];
}
int maxProfitBuySell2Tab(vector<int> &prices){
    return maxProfitBuySell2TabSolve(prices);
}

//100. Buy and Sell Stock (Space optimization) [II]
int maxProfitBuySell2OptSolve(vector<int> &prices){
    int n=prices.size();
    vector<int> curr(2,0);
    vector<int> next(2,0);

    for (int index = n-1; index >=0 ; --index) {
        for (int buy = 0; buy <= 1; ++buy) {

            int profit = 0;
            if(buy){
                int include = -prices[index] + next[0];
                int exclude = 0 + + next[1];
                profit = max(include,exclude);
            }
            else{
                int include = prices[index] + + next[1];
                int exclude = 0 + + next[0];
                profit = max(include,exclude);
            }

            curr[buy] = profit;
        }
        next=curr;
    }
    return next[1];
}
int maxProfitBuySell2Opt(vector<int> &prices){
    return maxProfitBuySell2OptSolve(prices);
}

//101. Buy and Sell Stock [III] (Recursion)
int maxProfitBuySell3Solve(vector<int> &prices,int index,int buy,int limit){
    if(index==prices.size()){
        return 0;
    }
    if(limit==0){
        return 0;
    }

    int profit=0;
    if(buy){
        int include= -prices[index] + maxProfitBuySell3Solve(prices,index+1, 0,limit);
        int exclude = 0 + maxProfitBuySell3Solve(prices,index+1, 1,limit);
        profit =max(include,exclude);
    }
    else{
        int include = prices[index] + maxProfitBuySell3Solve(prices,index+1, 1,limit-1);
        int exclude = 0 + maxProfitBuySell3Solve(prices,index+1, 0,limit);
        profit =max(include,exclude);
    }
    return profit;
}
int maxProfitBuySell3(vector<int> &prices){
    return maxProfitBuySell3Solve(prices,0,1,2);
}

//102. Buy and Sell Stock [III] (Memorization)
int maxProfitBuySell3MemSolve(vector<int> &prices,int index,int buy,int limit,vector<vector<vector<int>>> &dp){
    if(index==prices.size()){
        return 0;
    }
    if(limit==0){
        return 0;
    }

    if(dp[index][buy][limit]!=-1){
        return dp[index][buy][limit];
    }

    int profit=0;
    if(buy){
        int include= -prices[index] + maxProfitBuySell3MemSolve(prices,index+1, 0,limit,dp);
        int exclude = 0 + maxProfitBuySell3MemSolve(prices,index+1, 1,limit,dp);
        profit =max(include,exclude);
    }
    else{
        int include = prices[index] + maxProfitBuySell3MemSolve(prices,index+1, 1,limit-1,dp);
        int exclude = 0 + maxProfitBuySell3MemSolve(prices,index+1, 0,limit,dp);
        profit =max(include,exclude);
    }
    return dp[index][buy][limit] = profit;
}
int maxProfitBuySell3Mem(vector<int> &prices){
    int n=prices.size();
    vector<vector<vector<int>>> dp(n+1,vector<vector<int>>(2,vector<int>(3,-1)));
    return maxProfitBuySell3MemSolve(prices,0,1,2,dp);
}

//103. Buy and Sell Stock [III] (Tabulation)
int maxProfitBuySell3TabSolve(vector<int> &prices){
    int n=prices.size();
    vector<vector<vector<int>>> dp(n+1,vector<vector<int>>(2,vector<int>(3,0)));

    for (int index = n-1; index >=0 ; --index) {
        for (int buy = 0; buy <= 1; ++buy) {
            for (int limit = 1; limit <= 2; ++limit) {
                int profit=0;
                if(buy){
                    int include= -prices[index] + dp[index+1][0][limit];
                    int exclude = 0 + dp[index+1][1][limit];
                    profit =max(include,exclude);
                }
                else{
                    int include = prices[index] + dp[index+1][ 1][limit-1];
                    int exclude = 0 + dp[index+1][0][limit];
                    profit =max(include,exclude);
                }
                dp[index][buy][limit] = profit;
            }
        }
    }
    return dp[0][1][2];

}
int maxProfitBuySell3Tab(vector<int> &prices){
   return maxProfitBuySell3TabSolve(prices);
}

//104. Buy and Sell Stock [III] (Space optimization)
int maxProfitBuySell3OptSolve(vector<int> &prices){
    int n=prices.size();
 //   vector<vector<vector<int>>> dp(n+1,vector<vector<int>>(2,vector<int>(3,0)));

     vector<vector<int>> curr(2,vector<int>(3,0));
     vector<vector<int>> next(2,vector<int>(3,0));

    for (int index = n-1; index >=0 ; --index) {
        for (int buy = 0; buy <= 1; ++buy) {
            for (int limit = 1; limit <= 2; ++limit) {
                int profit=0;
                if(buy){
                    int include= -prices[index] + next[0][limit];
                    int exclude = 0 + next[1][limit];
                    profit =max(include,exclude);
                }
                else{
                    int include = prices[index] + next[ 1][limit-1];
                    int exclude = 0 + next[0][limit];
                    profit =max(include,exclude);
                }
                curr[buy][limit] = profit;
            }
        }
        next=curr;
    }
    return next[1][2];
}
int maxProfitBuySell3Opt(vector<int> &prices){
    return maxProfitBuySell3OptSolve(prices);
}


//105. Buy and Sell Stock [IV] (Space optimization + Alternative)
int maxProfitBuySell4OptAltSolve(vector<int> &prices,int k){
    int n=prices.size();


    vector<vector<int>> curr(2,vector<int>(k+1,0));
    vector<vector<int>> next(2,vector<int>(k+1,0));

    for (int index = n-1; index >=0 ; --index) {
        for (int buy = 0; buy <= 1; ++buy) {
            for (int limit = 1; limit <= k; ++limit) {
                int profit=0;
                if(buy){
                    int include= -prices[index] + next[0][limit];
                    int exclude = 0 + next[1][limit];
                    profit =max(include,exclude);
                }
                else{
                    int include = prices[index] + next[ 1][limit-1];
                    int exclude = 0 + next[0][limit];
                    profit =max(include,exclude);
                }
                curr[buy][limit] = profit;
            }
        }
        next=curr;
    }
    return next[1][k];
}
int maxProfitBuySell4OptAlt(vector<int> &prices,int k){
    return maxProfitBuySell4OptAltSolve(prices,k);
}

//106. Buy and Sell Stock [IV] (Recursion)
int maxProfitBuySell4Solve(vector<int> &prices,int k,int index,int operationNo){
    if(index==prices.size()){
        return 0;
    }
    if(operationNo==2*k){
        return 0;
    }

    int profit=0;
    if(operationNo%2==0){
        int include= -prices[index] + maxProfitBuySell4Solve(prices,k,index+1,operationNo+1);
        int exclude = 0 + maxProfitBuySell4Solve(prices,k,index+1,operationNo);
        profit =max(include,exclude);
    }
    else{
        int include = prices[index] + maxProfitBuySell4Solve(prices,k,index+1,operationNo+1);
        int exclude = 0 + maxProfitBuySell4Solve(prices,k,index+1,operationNo);
        profit =max(include,exclude);
    }
    return profit;
}
int maxProfitBuySell4(vector<int> &prices,int k){
    return maxProfitBuySell4Solve(prices,k,0,0);
}

//107. Buy and Sell Stock [IV] (Memorization)
int maxProfitBuySell4MemSolve(vector<int> &prices,int k,int index,int operationNo,vector<vector<int>> dp){
    if(index==prices.size()){
        return 0;
    }
    if(operationNo==2*k){
        return 0;
    }

    if(dp[index][operationNo]!=-1){
        return dp[index][operationNo];
    }

    int profit=0;
    if(operationNo%2==0){
        int include= -prices[index] + maxProfitBuySell4MemSolve(prices,k,index+1,operationNo+1,dp);
        int exclude = 0 + maxProfitBuySell4MemSolve(prices,k,index+1,operationNo,dp);
        profit =max(include,exclude);
    }
    else{
        int include = prices[index] + maxProfitBuySell4MemSolve(prices,k,index+1,operationNo+1,dp);
        int exclude = 0 + maxProfitBuySell4MemSolve(prices,k,index+1,operationNo,dp);
        profit =max(include,exclude);
    }
    return dp[index][operationNo]= profit;
}
int maxProfitBuySell4Mem(vector<int> &prices,int k){
    int n=prices.size();
    vector<vector<int>> dp(n+1,vector<int>(2*k,-1));
    return maxProfitBuySell4MemSolve(prices,k,0,0,dp);
}

//108. Buy and Sell Stock [IV] (Tabulation)
int maxProfitBuySell4TabSolve(vector<int> &prices,int k){
    int n=prices.size();
    vector<vector<int>> dp(n+1,vector<int>(2*k,0));
    for (int index = n-1; index >=0 ; --index) {
        for (int operationNo = 0; operationNo <= 2*k; ++operationNo) {
            int profit=0;
            if(operationNo%2==0){
                int include= -prices[index] + dp[index+1][operationNo+1];
                int exclude = 0 + dp[index+1][operationNo];
                profit =max(include,exclude);
            }
            else{
                int include = prices[index] + dp[index+1][operationNo+1];
                int exclude = 0 + dp[index+1][operationNo];
                profit =max(include,exclude);
            }
            dp[index][operationNo]= profit;
        }
    }
    return dp[0][0];

}
int maxProfitBuySell4Tab(vector<int> &prices,int k){
    return maxProfitBuySell4TabSolve(prices,k);
}

//109. Buy and Sell Stock [IV] (Space optimization)
int maxProfitBuySell4OptSolve(vector<int> &prices,int k){
    int n=prices.size();
 //   vector<vector<int>> dp(n+1,vector<int>(2*k,0));
    vector<int> curr(n+1,0);
    vector<int> next(n+1,0);

    for (int index = n-1; index >=0 ; --index) {
        for (int operationNo = 0; operationNo <= 2*k; ++operationNo) {
            int profit=0;
            if(operationNo%2==0){
                int include= -prices[index] + next[operationNo+1];
                int exclude = 0 + next[operationNo];
                profit =max(include,exclude);
            }
            else{
                int include = prices[index] + next[operationNo+1];
                int exclude = 0 + next[operationNo];
                profit =max(include,exclude);
            }
            curr[operationNo]= profit;
        }
        next=curr;
    }
    return next[0];
}
int maxProfitBuySell4Opt(vector<int> &prices,int k){
    return maxProfitBuySell4OptSolve(prices,k);
}

//110. Buy and Sell Stock [V] (Space optimization)
int maxProfitBuySell5OptSolve(vector<int> &prices,int fees){
    int n=prices.size();
    vector<int> curr(2,0);
    vector<int> next(2,0);

    for (int index = n-1; index >=0 ; --index) {
        for (int buy = 0; buy <= 1; ++buy) {

            int profit = 0;
            if(buy){
                int include = -prices[index] + next[0];
                int exclude = 0 + + next[1];
                profit = max(include,exclude);
            }
            else{
                int include = prices[index] + + next[1] - fees;
                int exclude = 0 + + next[0];
                profit = max(include,exclude);
            }

            curr[buy] = profit;
        }
        next=curr;
    }
    return next[1];
}
int maxProfitBuySell5Opt(vector<int> &prices,int fees){
    return maxProfitBuySell5OptSolve(prices,fees);
}

//111. Longest Common Subsequence (Recursion)
int longestCommonSubsequenceSolve(string text1, string text2,int i,int j){
    if(i==text1.length()){
        return 0;
    }
    if(j==text2.length()){
        return 0;
    }

    int ans=0;
    if(text1[i]==text2[j]){
        ans = 1 + longestCommonSubsequenceSolve(text1,text2,i+1,j+1);
    }
    else{
        ans = max(longestCommonSubsequenceSolve(text1,text2,i+1,j),longestCommonSubsequenceSolve(text1,text2,i,j+1));
    }
    return ans;
}
int longestCommonSubsequence(string text1, string text2){
    return longestCommonSubsequenceSolve(text1,text2,0,0);
}

//112. Longest Common Subsequence (Memorization)
int longestCommonSubsequenceMemSolve(string text1, string text2,int i,int j,vector<vector<int>> &dp){
    if(i==text1.length()){
        return 0;
    }
    if(j==text2.length()){
        return 0;
    }

    if(dp[i][j]!=-1){
        return dp[i][j];
    }

    int ans=0;
    if(text1[i]==text2[j]){
        ans = 1 + longestCommonSubsequenceMemSolve(text1,text2,i+1,j+1,dp);
    }
    else{
        ans = max(longestCommonSubsequenceMemSolve(text1,text2,i+1,j,dp),longestCommonSubsequenceMemSolve(text1,text2,i,j+1,dp));
    }
    return dp[i][j] = ans;
}
int longestCommonSubsequenceMem(string text1, string text2){
    vector<vector<int>> dp(text1.length()+1,vector<int>(text2.length()+1,-1));
    return longestCommonSubsequenceMemSolve(text1,text2,0,0,dp);
}

//113. Longest Common Subsequence (Tabulation)
int longestCommonSubsequenceTabSolve(string text1, string text2){
    int n1=text1.length(),n2=text2.length();
    vector<vector<int>> dp(n1+1,vector<int>(n2+1,0));
    for (int i = n1-1; i >=0 ; --i) {
        for (int j = n2-1; j >=0 ; --j) {
            int ans=0;
            if(text1[i]==text2[j]){
                ans = 1 + dp[i+1][j+1];
            }
            else{
                ans = max(dp[i+1][j],dp[i][j+1]);
            }
            dp[i][j] = ans;
        }
    }
    return dp[0][0];
}
int longestCommonSubsequenceTab(string text1, string text2){
    return longestCommonSubsequenceTabSolve(text1,text2);
}

//114. Longest Common Subsequence (Space optimization)
int longestCommonSubsequenceOptSolve(string text1, string text2){
    int n1=text1.length(),n2=text2.length();
   vector<int> curr(n2+1,0);
    vector<int> next(n2+1,0);
    for (int i = n1-1; i >=0 ; --i) {
        for (int j = n2-1; j >=0 ; --j) {
            int ans=0;
            if(text1[i]==text2[j]){
                ans = 1 + next[j+1];
            }
            else{
                ans = max(next[j],curr[j+1]);
            }
            curr[j] = ans;
        }
        next=curr;
    }
    return next[0];
}
int longestCommonSubsequenceOpt(string text1, string text2){
    return longestCommonSubsequenceOptSolve(text1,text2);
}


//115. Longest Pelindromic Subsequence (Recursion)
int pelindromicLongestSubsequenceSolve(string text,string revText,int i,int j){
    if(i==text.length()){
        return 0;
    }
    if(j==revText.length()){
        return 0;
    }

    int ans=0;
    if(text[i]==revText[j]){
        ans = 1 + pelindromicLongestSubsequenceSolve(text,revText,i+1,j+1);
    }
    else{
        ans = max(pelindromicLongestSubsequenceSolve(text,revText,i+1,j),pelindromicLongestSubsequenceSolve(text,revText,i,j+1));
    }
    return ans;
}
int pelindromicLongestSubsequence(string text){
    string revText=text;
    reverse(revText.begin(), revText.end());
    return pelindromicLongestSubsequenceSolve(text,revText,0,0);
}


//116. Longest Pelindromic Subsequence (Memorization)
int pelindromicLongestSubsequenceMemSolve(string text,string revText,int i,int j,vector<vector<int>> &dp){
    if(i==text.length()){
        return 0;
    }
    if(j==revText.length()){
        return 0;
    }

    if(dp[i][j]!=-1){
        return dp[i][j];
    }

    int ans=0;
    if(text[i]==revText[j]){
        ans = 1 + pelindromicLongestSubsequenceMemSolve(text,revText,i+1,j+1,dp);
    }
    else{
        ans = max(pelindromicLongestSubsequenceMemSolve(text,revText,i+1,j,dp),pelindromicLongestSubsequenceMemSolve(text,revText,i,j+1,dp));
    }
    return dp[i][j] =  ans;
}
int pelindromicLongestSubsequenceMem(string text){
    string revText=text;
    reverse(revText.begin(), revText.end());
    vector<vector<int>> dp(text.length()+1,vector<int>(revText.length()+1,-1));
    return pelindromicLongestSubsequenceMemSolve(text,revText,0,0,dp);
}


//117. Longest Pelindromic Subsequence (Tabulation)
int pelindromicLongestSubsequenceTabSolve(string text,string revText){
    int n1=text.length(),n2=revText.length();
    vector<vector<int>> dp(n1+1,vector<int>(n2+1,0));
    for (int i = n1-1; i >=0 ; --i) {
        for (int j = n2-1; j >=0 ; --j) {
            int ans=0;
            if(text[i]==revText[j]){
                ans = 1 + dp[i+1][j+1];
            }
            else{
                ans = max(dp[i+1][j],dp[i][j+1]);
            }
            dp[i][j] = ans;
        }
    }
    return dp[0][0];
}
int pelindromicLongestSubsequenceTab(string text){
    string revText=text;
    reverse(revText.begin(), revText.end());
    return pelindromicLongestSubsequenceTabSolve(text,revText);
}


//118. Longest Pelindromic Subsequence (Space optimization)
int pelindromicLongestSubsequenceOptSolve(string text,string revText){
    int n1=text.length(),n2=revText.length();
    vector<int> curr(n2+1,0);
    vector<int> next(n2+1,0);
    for (int i = n1-1; i >=0 ; --i) {
        for (int j = n2-1; j >=0 ; --j) {
            int ans=0;
            if(text[i]==revText[j]){
                ans = 1 + next[j+1];
            }
            else{
                ans = max(next[j],curr[j+1]);
            }
            curr[j] = ans;
        }
        next=curr;
    }
    return next[0];
}
int pelindromicLongestSubsequenceOpt(string text){
    string revText=text;
    reverse(revText.begin(), revText.end());
    return pelindromicLongestSubsequenceOptSolve(text,revText);
}

//119. Edit Distance (Recursion)

int editDistanceSolve(string text1,string text2,int i,int j){
    if(i==text1.length()){
        return text2.length()-j;
    }
    if(j==text2.length()){
        return text1.length()-i;
    }
    int ans=0;
    if(text1[i]==text2[j]){
        return editDistanceSolve(text1,text2,i+1,j+1);
    }
    else{
        //insert
        int insertAns=1 + editDistanceSolve(text1,text2,i,j+1);
        //delete
        int deleteAns= 1 + editDistanceSolve(text1,text2,i+1,j);
        //replace
        int replaceAns= 1 + editDistanceSolve(text1,text2,i+1,j+1);
        ans = min(insertAns,min(deleteAns,replaceAns));
    }
    return ans;
}
int editDistance(string text1,string text2){
    return editDistanceSolve(text1,text2,0,0);
}

//120. EDIT Distance (Memorization)
int editDistanceMemSolve(string text1,string text2,int i,int j,vector<vector<int>> dp){
    if(i==text1.length()){
        return text2.length()-j;
    }
    if(j==text2.length()){
        return text1.length()-i;
    }

    if(dp[i][j]!=-1){
        return dp[i][j];
    }

    int ans=0;
    if(text1[i]==text2[j]){
        return editDistanceMemSolve(text1,text2,i+1,j+1,dp);
    }
    else{
        //insert
        int insertAns=1 + editDistanceMemSolve(text1,text2,i,j+1,dp);
        //delete
        int deleteAns= 1 + editDistanceMemSolve(text1,text2,i+1,j,dp);
        //replace
        int replaceAns= 1 + editDistanceMemSolve(text1,text2,i+1,j+1,dp);
        ans = min(insertAns,min(deleteAns,replaceAns));
    }
    return dp[i][j]= ans;
}
int editDistanceMem(string text1,string text2){
    int n1=text1.length(),n2=text2.length();
    vector<vector<int>> dp(n1+1,vector<int>(n2+1,-1));
    return editDistanceMemSolve(text1,text2,0,0,dp);
}

//121. EDIT Distance (Tabulation)
int editDistanceTabSolve(string text1,string text2){
    int n1=text1.length(),n2=text2.length();
    vector<vector<int>> dp(n1+1,vector<int>(n2+1,0));
    for (int j = 0; j < n2; ++j) {
        dp[n1][j] = text2.length() - j;
    }
    for (int i = 0; i < n1; ++i) {
        dp[i][n2] = text1.length() - i;
    }
    for (int i = n1-1; i >=0 ; --i) {
        for (int j = n2-1; j >=0 ; --j) {
            int ans=0;
            if(text1[i]==text2[j]){
                ans = dp[i+1][j+1];
            }
            else{
                //insert
                int insertAns=1 + dp[i][j+1];
                //delete
                int deleteAns= 1 + dp[i+1][j];
                //replace
                int replaceAns= 1 + dp[i+1][j+1];
                ans = min(insertAns,min(deleteAns,replaceAns));
            }
            dp[i][j]= ans;
        }
    }
    return dp[0][0];

}
int editDistanceTab(string text1,string text2){
    return editDistanceTabSolve(text1,text2);
}

//122. EDIT Distance (Space optimization)
int editDistanceSolveOpt(string text1,string text2){
    int n1=text1.length(),n2=text2.length();
 //   vector<vector<int>> dp(n1+1,vector<int>(n2+1,-1));
    vector<int> curr(n2+1,0) ;
    vector<int> next(n2+1,0) ;

    for (int j = 0; j < n2; ++j) {
        next[j] = text2.length() - j;
    }

//    for (int i = 0; i < n1; ++i) {
//        dp[i][n2] = text1.length() - i;
//    }

    for (int i = n1-1; i >=0 ; --i) {
        for (int j = n2-1; j >=0 ; --j) {

            //catch --->> base case
            curr[n2] = text1.length()-i;


            int ans=0;
            if(text1[i]==text2[j]){
                ans = next[j+1];
            }
            else{
                //insert
                int insertAns=1 + curr[j+1];
                //delete
                int deleteAns= 1 + next[j];
                //replace
                int replaceAns= 1 + next[j+1];
                ans = min(insertAns,min(deleteAns,replaceAns));
            }
            curr[j]= ans;
        }
        next=curr;
    }
    return next[0];
}
int editDistanceOpt(string text1,string text2){
    if(text1.length()==0){
        return text2.length();
    }
    if(text2.length()==0){
        return text1.length();
    }
    return editDistanceSolveOpt(text1,text2);
}

int main(){
    int data,data2,choice;
    cout<<"Choice:";
    cin>>choice;
    while (choice) {
        switch (choice) {
            case 1: {
                cout<<fibonacciNumberMem(6)<<endl;
                break;
            }
            case 2:{
                cout<<fibonacciNumberTab(6)<<endl;
                break;
            }
            case 3:{
                cout<<"Insert n:";
                cin>>data;
                cout<<fibonacciNumberOpt(data)<<endl;
                break;
            }
            case 4:{
                vector<int> cost={1,100,1,1,1,100,1,1,100,1};
                cout<<minCostClimbingStairs(cost)<<endl;
                break;
            }
            case 5:{
                vector<int> cost={1,100,1,1,1,100,1,1,100,1};
                cout<<minCostClimbingStairsMem(cost)<<endl;
                break;
            }
            case 6:{
                vector<int> cost={1,100,1,1,1,100,1,1,100,1};
                cout<<minCostClimbingStairsTab(cost)<<endl;
                break;
            }
            case 7:{
                vector<int> cost={1,100,1,1,1,100,1,1,100,1};
                cout<<minCostClimbingStairsOpt(cost)<<endl;
                break;
            }
            case 8:{
                vector<int> coins={1,2,3};
                cout<<minNumberOfCoins(coins,7)<<endl;
                break;
            }
            case 9:{
                vector<int> coins={1,2,3};
                cout<<minNumberOfCoinsMem(coins,7)<<endl;
                break;
            }
            case 10:{
                vector<int> coins={1,2,3};
                cout<<minNumberOfCoinsTab(coins,7)<<endl;
                break;
            }
            case 11:{
                vector<int> nums={1, 2, 3, 1 ,3 ,5, 8, 1, 9};
                cout<<maxNonAdjacentSum(nums)<<endl;
                break;
            }
            case 12:{
                vector<int> nums={1, 2, 3, 1 ,3 ,5, 8, 1, 9};
                cout<<maxNonAdjacentSumMem(nums)<<endl;
                break;
            }
            case 13:{
                vector<int> nums={1, 2, 3, 1 ,3 ,5, 8, 1, 9};
                cout<<maxNonAdjacentSumTab(nums)<<endl;
                break;
            }
            case 14:{
                vector<int> nums={1, 2, 3, 1 ,3 ,5, 8, 1, 9};
                cout<<maxNonAdjacentSumOpt(nums)<<endl;
                break;
            }
            case 15:{
                vector<int> money={1, 5, 1, 2 ,6};
                cout<<houseRobbery(money)<<endl;
                break;
            }
            case 16:{
                vector<int> money={1, 5, 1, 2 ,6};
                cout<<houseRobberyMem(money)<<endl;
                break;
            }
            case 17:{
                vector<int> money={1, 5, 1, 2 ,6};
                cout<<houseRobberyTab(money)<<endl;
                break;
            }
            case 18:{
                vector<int> money={1, 5, 1, 2 ,6};
                cout<<houseRobberyOpt(money)<<endl;
                break;
            }
            case 19:{
                cout<<cutRodIntoSegment(7,3,2,2)<<endl;
                break;
            }
            case 20:{
                cout<<cutRodIntoSegmentMem(7,3,2,2)<<endl;
                break;
            }
            case 21:{
                cout<<cutRodIntoSegmentTab(7,3,2,2)<<endl;
                break;
            }
            case 22:{
                break;
            }
            case 23:{
                cout<<countDeRangements(4)<<endl;
                break;
            }
            case 24:{
                cout<<countDeRangementsMem(4)<<endl;
                break;
            }
            case 25:{
                cout<<countDerangementsOpt(4)<<endl;
                break;
            }
            case 26:{
                cout<<countDeRangementsOpt(4)<<endl;
                break;
            }
            case 27:{
                cout<<numberOfWays(2,4)<<endl;
                break;
            }
            case 28:{
                cout<<numberOfWaysMem(2,4)<<endl;
                break;
            }
            case 29:{

                cout<<numberOfWaysTab(2,4)<<endl;
                break;
            }
            case 30:{

                cout<<numberOfWaysOpt(2,4)<<endl;
                break;
            }
            case 31:{
                vector<int> weight={1, 2, 4, 5};
                vector<int> value={5, 4, 8, 6};
                cout<<knapsack(weight, value,4,5)<<endl;
                break;
            }
            case 32:{
                vector<int> weight={1, 2, 4, 5};
                vector<int> value={5, 4, 8, 6};
                cout<<knapsackMem(weight, value,4,5)<<endl;
                break;
            }
            case 33:{
                vector<int> weight={1, 2, 4, 5};
                vector<int> value={5, 4, 8, 6};
                cout<<knapsackTab(value,weight ,4,5)<<endl;
                break;
            }
            case 34:{
                vector<int> weight={1, 2, 4, 5};
                vector<int> value={5, 4, 8, 6};
                cout<<knapsackOpt(value,weight ,4,5)<<endl;
                break;
            }
            case 35:{
                vector<int> weight={1, 2, 4, 5};
                vector<int> value={5, 4, 8, 6};
                cout<<knapsackOpt2(value,weight ,4,5)<<endl;
                break;
            }
            case 36:{
                vector<int> num={1, 2, 5};
                cout<<findWayCombinationSum(num,5)<<endl;
                break;
            }
            case 37:{
                vector<int> num={1, 2, 5};
                cout<<findWayCombinationSumMem(num,5)<<endl;
                break;
            }
            case 38:{
                vector<int> num={1, 2, 5};
                cout<<findWayCombinationSumTab(num,5)<<endl;
                break;
            }
            case 39:{
                cout<<minimumSquares(6)<<endl;
                break;
            }
            case 40:{
                cout<<minimumSquaresMem(6)<<endl;
                break;
            }
            case 41:{
                cout<<minimumSquaresTab(6)<<endl;
                break;
            }
            case 42:{
                cout<<minimumCube(9)<<endl;
                break;
            }
            case 43:{
                vector<int> days={1, 3, 4, 5, 7, 8, 10};
                vector<int> costs={2, 7, 20};
                cout<<minCostTickets(7,days,costs)<<endl;
                break;
            }
            case 44:{
                vector<int> days={1, 3, 4, 5, 7, 8, 10};
                vector<int> costs={2, 7, 20};
                cout<<minCostTicketsMem(7,days,costs)<<endl;
                break;
            }
            case 45:{
                vector<int> days={1, 3, 4, 5, 7, 8, 10};
                vector<int> costs={2, 7, 20};
                cout<<minCostTicketsTab(7,days,costs)<<endl;
                break;
            }
            case 46:{
                break;
            }
            case 47:{
                vector<vector<int>> matrix={
                        {1,0,1,1,1},
                        {1,1,1,1,1},
                        {0,0,1,1,1},
                        {1,1,1,0,1},
                        {1,1,0,1,1}
                };
                cout<<maxSquareInMat(5,5,matrix)<<endl;
                break;
            }
            case 48:{
                vector<vector<int>> matrix={
                        {1,0,1,1,1},
                        {1,1,1,1,1},
                        {0,0,1,1,1},
                        {1,1,1,0,1},
                        {1,1,0,1,1}
                };
                cout<<maxSquareInMatMem(5,5,matrix)<<endl;
                break;
            }
            case 49:{
                vector<vector<int>> matrix={
                        {1,0,1,1,1},
                        {1,1,1,1,1},
                        {0,0,1,1,1},
                        {1,1,1,0,1},
                        {1,1,0,1,1}
                };
                cout<<maxSquareInMatTab(5,5,matrix)<<endl;
                break;
            }
            case 50:{
                vector<vector<int>> matrix={
                        {1,0,1,1,1},
                        {1,1,1,1,1},
                        {0,0,1,1,1},
                        {1,1,1,0,1},
                        {1,1,0,1,1}
                };
                cout<<maxSquareInMatOpt(5,5,matrix)<<endl;
                break;
            }
            case 51:{
                vector<int> polygonial={ 1,3,1,4,1,5};{
                    cout<<minScoreTriangulation(polygonial)<<endl;
                    break;
                }
            }
            case 52:{
                vector<int> polygonial={ 1,3,1,4,1,5};{
                    cout<<minScoreTriangulationMem(polygonial)<<endl;
                    break;
                }
            }
            case 53:{
                vector<int> polygonial={ 1,3,1,4,1,5};{
                    cout<<minScoreTriangulationTab(polygonial)<<endl;
                    break;
                }
            }
            case 54:{
                vector<int> obstacle={0,2,1,0,3,0};
                cout<<minSideJumps(obstacle)<<endl;
                break;
            }
            case 55:{
                vector<int> obstacle={0,2,1,0,3,0};
                cout<<minSideJumpsMem(obstacle)<<endl;
                break;
            }
            case 56:{
                vector<int> obstacle={0,2,1,0,3,0};
                cout<<minSideJumpsTab(obstacle)<<endl;
                break;
            }
            case 57:{
                vector<int> obstacle={0,2,1,0,3,0};
                cout<<minSideJumpsOpt(obstacle)<<endl;
                break;
            }
            case 58:{
                vector<int> satisfaction={-1,-8,0,5,-9};
                cout<<maxSatisfaction(satisfaction)<<endl;
                break;
            }
            case 59:{
                vector<int> satisfaction={-1,-8,0,5,-9};
                cout<<maxSatisfactionMem(satisfaction)<<endl;
                break;
            }
            case 60:{
                vector<int> satisfaction={-1,-8,0,5,-9};
                cout<<maxSatisfactionTab(satisfaction)<<endl;
                break;
            }
            case 61:{
                vector<int> satisfaction={-1,-8,0,5,-9};
                cout<<maxSatisfactionOpt(satisfaction)<<endl;
                break;
            }
            case 62:{
                int arr[16]={0,8,4,12,2,10,6,14,1,9,5,13,3,11,7,15};
                cout<<longestSubsequence(16,arr)<<endl;
                break;
            }
            case 63:{
                int arr[16]={0,8,4,12,2,10,6,14,1,9,5,13,3,11,7,15};
                cout<<longestSubsequenceMem(16,arr)<<endl;
                break;
            }
            case 64:{
                int arr[16]={0,8,4,12,2,10,6,14,1,9,5,13,3,11,7,15};
                cout<<longestSubsequenceTab(16,arr)<<endl;
                break;
            }
            case 65:{
                int arr[16]={0,8,4,12,2,10,6,14,1,9,5,13,3,11,7,15};
                cout<<longestSubsequenceOpt(16,arr)<<endl;
                break;
            }
            case 66:{
                int arr[16]={0,8,4,12,2,10,6,14,1,9,5,13,3,11,7,15};
                cout<<longestSubsequenceDpBs(16,arr)<<endl;
                break;
            }
            case 67:{
                vector<vector<int>> envelopes={
                        {5,4},
                        {6,4},
                        {6,7},
                        {2,3}
                };
                cout<<maxEnvelops(envelopes)<<endl;
                break;
            }
            case 68:{
                vector<vector<int>> cuboids={
                        {50,45,20},
                        {95,37,53},
                        {45,23,12}
                };
                cout<<maxCuboidsHeightTab(cuboids)<<endl;
                break;
            }
            case 69:{
                vector<int> slices={1,2,3,4,5,6};
                cout<<maxPizzaSlices(slices)<<endl;
                break;
            }
            case 70:{
                vector<int> slices={1,2,3,4,5,6};
                cout<<maxPizzaSlicesMem(slices)<<endl;
                break;
            }
            case 71:{
                vector<int> slices={1,2,3,4,5,6};
                cout<<maxPizzaSlicesTab(slices)<<endl;
                break;
            }
            case 72:{
                vector<int> slices={1,2,3,4,5,6};
                cout<<maxPizzaSlicesOpt(slices)<<endl;
                break;
            }
            case 73:{
                cout<<noOfDiceRolls(3,6,12)<<endl;
                break;
            }
            case 74:{
                cout<<noOfDiceRollsMem(3,6,12)<<endl;
                break;
            }
            case 75:{
                cout<<noOfDiceRollsTab(3,6,12)<<endl;
                break;
            }
            case 76:{
                cout<<noOfDiceRollsOpt(3,6,12)<<endl;
                break;
            }
            case 77:{
                int arr[4]={1,5,11,5};
                if(equalPartitionSubSum(4,arr)){
                    cout<<"Yes"<<endl;
                }
                else{
                    cout<<"No"<<endl;
                }
                break;
            }
            case 78:{
                int arr[4]={1,5,11,5};
                if(equalPartitionSubSumMem(4,arr)){
                    cout<<"Yes"<<endl;
                }
                else{
                    cout<<"No"<<endl;
                }
                break;
            }
            case 79:{
                int arr[4]={1,5,11,5};
                if(equalPartitionSubSumTab(4,arr)){
                    cout<<"Yes"<<endl;
                }
                else{
                    cout<<"No"<<endl;
                }
                break;
            }
            case 80:{
                int arr[4]={1,5,11,5};
                if(equalPartitionSubSumOpt(4,arr)){
                    cout<<"Yes"<<endl;
                }
                else{
                    cout<<"No"<<endl;
                }
                break;
            }
            case 81:{
                vector<int> num1={1,3,5,4};
                vector<int> num2={1,2,3,7};
//                vector<int> num1={1,3,2,4};
//                vector<int> num2={1,2,3,7};
                cout<<makeSeqMinSwap(num1,num2)<<endl;
                break;
            }
            case 82:{
                vector<int> num1={1,3,5,4};
                vector<int> num2={1,2,3,7};
                cout<<makeSeqMinSwapMem(num1,num2)<<endl;
                break;
            }
            case 83:{
                vector<int> num1={1,3,5,4};
                vector<int> num2={1,2,3,7};
                cout<<makeSeqMinSwapTab(num1,num2)<<endl;
                break;
            }
            case 84:{
                vector<int> num1={1,3,5,4};
                vector<int> num2={1,2,3,7};
                cout<<makeSeqMinSwapOpt(num1,num2)<<endl;
                break;
            }
            case 85:{
                int arr[]={1,7,10,13,14,19};
                cout<<lengthOfLongestAP(arr,6)<<endl;
                break;
            }
            case 86:{
                int arr[]={1,7,10,13,14,19};
                cout<<lengthOfLongestAPMem(arr,6)<<endl;
                break;
            }
            case 87:{
                int arr[]={1,7,10,13,14,19};
                cout<<lengthOfLongestAPTab(arr,6)<<endl;
                break;
            }
            case 88:{
                vector<int> arr= {1,5,7,8,5,3,4,2,1};
                cout<<longestSubsequence(arr,-2)<<endl;
                break;
            }
            case 89:{
                cout<<uniqBinaryTree(3)<<endl;
                break;
            }
            case 90:{
                cout<<uniqBinaryTreeMem(3)<<endl;
                break;
            }
            case 91:{
                cout<<uniqBinaryTreeTab(3)<<endl;
                break;
            }
            case 92:{
                cout<<getMoneyAmount(10)<<endl;
                break;
            }
            case 93:{
                cout<<getMoneyAmountMem(10)<<endl;
                break;
            }
            case 94:{
                cout<<getMoneyAmountTab(10)<<endl;
                break;
            }
            case 95:{
                break;
            }
            case 96:{
                vector<int> prices= {7,1,5,3,6,4};
                cout<<maxProfitBuySell(prices)<<endl;
                break;
            }
            case 97:{
                vector<int> prices= {7,1,5,3,6,4};
                cout<<maxProfitBuySell2(prices)<<endl;
                break;
            }
            case 98:{
                vector<int> prices= {7,1,5,3,6,4};
                cout<<maxProfitBuySell2Mem(prices)<<endl;
                break;
            }
            case 99:{
                vector<int> prices= {7,1,5,3,6,4};
                cout<<maxProfitBuySell2Tab(prices)<<endl;
                break;
            }
            case 100:{
                vector<int> prices= {7,1,5,3,6,4};
                cout<<maxProfitBuySell2Opt(prices)<<endl;
                break;
            }
            case 101:{
                vector<int> prices ={3,3,5,0,0,3,1,4};
                cout<<maxProfitBuySell3(prices)<<endl;
                break;
            }
            case 102:{
                vector<int> prices ={3,3,5,0,0,3,1,4};
                cout<<maxProfitBuySell3Mem(prices)<<endl;
                break;
            }
            case 103:{
                vector<int> prices ={3,3,5,0,0,3,1,4};
                cout<<maxProfitBuySell3Tab(prices)<<endl;
                break;
            }
            case 104:{
                vector<int> prices ={3,3,5,0,0,3,1,4};
                cout<<maxProfitBuySell3Opt(prices)<<endl;
                break;
            }
            case 105:{
                vector<int> prices = {3,2,6,5,0,3};
                cout<<maxProfitBuySell4OptAlt(prices,2)<<endl;
                break;
            }
            case 106:{
                vector<int> prices = {3,2,6,5,0,3};
                cout<<maxProfitBuySell4(prices,2)<<endl;
                break;
            }
            case 107:{
                vector<int> prices = {3,2,6,5,0,3};
                cout<<maxProfitBuySell4Mem(prices,2)<<endl;
                break;
            }
            case 108:{
                vector<int> prices = {3,2,6,5,0,3};
                cout<<maxProfitBuySell4Tab(prices,2)<<endl;
                break;
            }
            case 109:{
                vector<int> prices = {3,2,6,5,0,3};
                cout<<maxProfitBuySell4Opt(prices,2)<<endl;
                break;
            }
            case 110:{
                vector<int> price = {1,3,2,8,4,9};
                cout<<maxProfitBuySell5Opt(price,2)<<endl;
                break;
            }
            case 111:{
               string text1 = "abcde", text2 = "ace";
               cout<<longestCommonSubsequence(text1,text2)<<endl;
                break;
            }
            case 112:{
                string text1 = "abcde", text2 = "ace";
                cout<<longestCommonSubsequenceMem(text1,text2)<<endl;
                break;
            }
            case 113:{
                string text1 = "abcde", text2 = "ace";
                cout<<longestCommonSubsequenceTab(text1,text2)<<endl;
                break;
            }
            case 114:{
                string text1 = "abcde", text2 = "ace";
                cout<<longestCommonSubsequenceOpt(text1,text2)<<endl;
                break;
            }
            case 115:{
                string text="bbbab";
                cout<<pelindromicLongestSubsequence(text)<<endl;
                break;
            }
            case 116:{
                string text="bbbab";
                cout<<pelindromicLongestSubsequenceMem(text)<<endl;
                break;
            }
            case 117:{
                string text="bbbab";
                cout<<pelindromicLongestSubsequenceTab(text)<<endl;
                break;
            }
            case 118:{
                string text="bbbab";
                cout<<pelindromicLongestSubsequenceOpt(text)<<endl;
                break;
            }
            case 119:{
              string word1 = "horse", word2 = "ros";
              cout<<editDistance(word1,word2)<<endl;
                break;
            }
            case 120:{
                string word1 = "horse", word2 = "ros";
                cout<<editDistanceMem(word1,word2)<<endl;
                break;
            }
            case 121:{
                string word1 = "horse", word2 = "ros";
                cout<<editDistanceTab(word1,word2)<<endl;
                break;
            }
            case 122:{
                string word1 = "horse", word2 = "ros";
                cout<<editDistanceOpt(word1,word2)<<endl;
                break;
            }
            default:{
                cout<<"Invalid selection"<<endl;
            }
        }
        cout<<"Choice:";
        cin>>choice;
    }
}
