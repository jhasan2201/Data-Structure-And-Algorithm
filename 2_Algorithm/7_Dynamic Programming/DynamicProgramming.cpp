#include "iostream"
#include "vector"
#include "algorithm"

using namespace std;

//1. Fibonacci number (Memorization)
int fibonacciSol(int n,vector<int> &dp){
    if(n==0){
        return 0;
    }
    if(n==1){
        return 1;
    }

    if(dp[n]!=-1){
        return dp[n];
    }

    return dp[n]= fibonacciSol(n-1,dp) + fibonacciSol(n-2,dp);
}
int fibonacciMem(int n){
    vector<int> dp(n+1,-1);
    return fibonacciSol(n,dp);
}

//2. Fibonacci number (Tabulation)
int fibonacciTab(int n){
    vector<int> dp(n+1,-1);

    dp[0]=0;
    dp[1]=1;

    for (int i = 2; i <= n; ++i) {
        dp[i]=dp[i-1]+dp[i-2];
    }

    return dp[n];
}
//3. Fibonacci number (space optimization)
int fibonacciOpt(int n){
   // vector<int> dp(n+1,-1);

    int secondPrev=0;
    int firstPrev=1;

    for (int i = 2; i <= n; ++i) {
        int curr=firstPrev+secondPrev;
        secondPrev=firstPrev;
        firstPrev=curr;
    }

    return firstPrev;
}

//4. Minimum Cost Climbing Stairs (Recursion)
int minCostClimbingStairSol(vector<int> &cost,int stair){
    if(stair==0){
        return cost[0];
    }
    if(stair==1){
        return cost[1];
    }
    int oneStairJump=cost[stair] + minCostClimbingStairSol(cost,stair-1);
    int twoStairJump= cost[stair] + minCostClimbingStairSol(cost,stair-2);
    return min(oneStairJump,twoStairJump);
}
int minCostClimbingStair(vector<int> &cost){
    int n=cost.size();

    int fromLastStair= minCostClimbingStairSol(cost,n-1);
    int fromSecLastStair= minCostClimbingStairSol(cost,n-2);
    return min(fromLastStair,fromSecLastStair);
}

//5. Minimum Cost Climbing Stairs (Memorization)
int minCostClimbingStairMemSol(vector<int> &cost,int stair,vector<int> &dp){
    if(stair==0){
        return cost[0];
    }
    if(stair==1){
        return cost[1];
    }

    if(dp[stair]!=-1){
        return dp[stair];
    }

    int oneStairJump=cost[stair] + minCostClimbingStairMemSol(cost,stair-1,dp);
    int twoStairJump= cost[stair] + minCostClimbingStairMemSol(cost,stair-2,dp);
    return dp[stair]= min(oneStairJump,twoStairJump);
}
int minCostClimbingStairMem(vector<int> &cost){
    int n=cost.size();

    vector<int> dp(n+1,-1);

    int fromLastStair= minCostClimbingStairMemSol(cost,n-1,dp);
    int fromSecLastStair= minCostClimbingStairMemSol(cost,n-2,dp);
    return min(fromLastStair,fromSecLastStair);
}
//6. Minimum Cost Climbing Stairs (Tabulation)
int minCostClimbingStairTab(vector<int> &cost){
    int n=cost.size();

    vector<int> dp(n+1,-1);


    dp[0]=cost[0];
    dp[1]=cost[1];

    for (int stair = 2; stair <= n; ++stair) {
        int oneStairJump=cost[stair] + dp[stair-1];
        int twoStairJump= cost[stair] + dp[stair-2];
        dp[stair]= min(oneStairJump,twoStairJump);
    }

    return min(dp[n-1],dp[n-2]);
}
//7. Minimum Cost Climbing Stairs (Space optimization)
int minCostClimbingStairOpt(vector<int> &cost){
    int n=cost.size();

   // vector<int> dp(n+1,-1);


    int secondPrev=cost[0];
    int firstPrev=cost[1];

    int curr=0;
    for (int stair = 2; stair <= n; ++stair) {
        int oneStairJump=cost[stair] + firstPrev;
        int twoStairJump= cost[stair] + secondPrev;
        curr= min(oneStairJump,twoStairJump);
        secondPrev=firstPrev;
        firstPrev=curr;
    }

    return min(secondPrev,curr);
}

//8. Minimum Number of Coins (Recursion)
int minNumberCoins(vector<int> &coins,int target){
    if(target==0){
        return 0;
    }
    if(target<0){
        return INT_MAX;
    }

    int miniCoin=INT_MAX;
    for (auto co:coins) {
        int ans= minNumberCoins(coins,target-co);

        if(ans!=INT_MAX){
            miniCoin=min(miniCoin, 1 + ans);
        }
    }
    return miniCoin;
}

//9. Minimum Number of Coins (Memorization)
int minNumberCoinsMemSol(vector<int> &coins,int target,vector<int> &dp){
    if(target==0){
        return 0;
    }
    if(target<0){
        return INT_MAX;
    }

    if(dp[target]!=-1){
        return dp[target];
    }
    int miniCoin=INT_MAX;
    for (auto co:coins) {
        int ans= minNumberCoinsMemSol(coins,target-co,dp);

        if(ans!=INT_MAX){
            miniCoin=min(miniCoin, 1 + ans);
        }
    }
    return dp[target]= miniCoin;
}
int minNumberCoinsMem(vector<int> &coins,int target){
    vector<int> dp(target+1,-1);
    return minNumberCoinsMemSol(coins,target,dp);
}
//10. Minimum Number of Coins (Tabulation)
int minNumberCoinsTab(vector<int> &coins,int target){
    vector<int> dp(target+1,INT_MAX);

    dp[0]=0;
    for (int tar = 1; tar <= target ; ++tar) {
        int miniCoin=INT_MAX;
        for (auto co:coins) {
            int ans=0;
            if(tar-co>=0) {
                ans = dp[tar - co];
            }

            if(ans!=INT_MAX){
                miniCoin=min(miniCoin, 1 + ans);
            }
        }
        dp[tar]= miniCoin;
    }

    return dp[target];
}

//11. Maximum Sum of Non-Adjacent Elements (Recursion)

int maxSumNonAdjElementSol(vector<int> &nums,int index){
    if(index<0){
        return 0;
    }
    if(index==0){
        return nums[0];
    }
    int include = nums[index] + maxSumNonAdjElementSol(nums,index-2);
    int exclude = 0 + maxSumNonAdjElementSol(nums,index-1);
    return max(include,exclude);
}
int maxSumNonAdjElement(vector<int> &nums){
    int n=nums.size();
    return maxSumNonAdjElementSol(nums,n-1);
}
//12. Maximum Sum of Non-Adjacent Elements (Memorization)
int maxSumNonAdjElementMemSol(vector<int> &nums,int index,vector<int> &dp){
    if(index<0){
        return 0;
    }
    if(index==0){
        return nums[0];
    }

    if(dp[index]!=-1){
        return dp[index];
    }

    int include = nums[index] + maxSumNonAdjElementMemSol(nums,index-2,dp);
    int exclude = 0 + maxSumNonAdjElementMemSol(nums,index-1,dp);
    return dp[index]= max(include,exclude);
}
int maxSumNonAdjElementMem(vector<int> &nums){
    int n=nums.size();

    vector<int> dp(n+1,-1);

    return maxSumNonAdjElementMemSol(nums,n-1,dp);
}
//13. Maximum Sum of Non-Adjacent Elements (Tabulation)
int maxSumNonAdjElementTab(vector<int> &nums){
    int n=nums.size();

    vector<int> dp(n+1,-1);


    dp[0]=nums[0];
    dp[1]=max(nums[0],nums[1]);

    for (int index = 2; index <= n; ++index) {
        int include = nums[index] + dp[index-2];
        int exclude = 0 + dp[index-1];
        dp[index]= max(include,exclude);
    }

    return dp[n-1];
}

//14. Maximum Sum of Non-Adjacent Elements (Space optimization)
int maxSumNonAdjElementOpt(vector<int> &nums){
    int n=nums.size();

    //vector<int> dp(n+1,-1);


    int secondPrev=nums[0];
    int firstPrev=max(nums[0],nums[1]);

    for (int index = 2; index <= n; ++index) {
        int include = nums[index] + secondPrev;
        int exclude = 0 + firstPrev;
        int curr= max(include,exclude);
        secondPrev=firstPrev;
        firstPrev=curr;
    }

    return firstPrev;
}

//15. House Robbery Problem (Recursion)
int hourseRobberySol(vector<int> &money,int start,int end){
    if(start>end){
        return 0;
    }
    if(start==end){
        return money[end];
    }
    int include=money[end] + hourseRobberySol(money,start,end-2);
    int exclude = 0 + hourseRobberySol(money,start,end-1);
    return max(include,exclude);
}
int hourseRobbery(vector<int> &money){
    int n=money.size();
    int firstToSecLast= hourseRobberySol(money,0,n-2);
    int secToLast= hourseRobberySol(money,1,n-1);
    return max(firstToSecLast,secToLast);
}
//16. House Robbery Problem (Memorization)
int hourseRobberyMemSol(vector<int> &money,int start,int end,vector<int> &dp){
    if(start>end){
        return 0;
    }
    if(start==end){
        return money[end];
    }

    if(dp[end]!=-1){
        return dp[end];
    }

    int include=money[end] + hourseRobberyMemSol(money,start,end-2,dp);
    int exclude = 0 + hourseRobberyMemSol(money,start,end-1,dp);
    return dp[end]= max(include,exclude);
}
int hourseRobberyMem(vector<int> &money){
    int n=money.size();

    vector<int> dp(n+1,-1);

    int firstToSecLast= hourseRobberyMemSol(money,0,n-2,dp);
    int secToLast= hourseRobberyMemSol(money,1,n-1,dp);
    return max(firstToSecLast,secToLast);
}
//17. House Robbery Problem (Tabulation)
int hourseRobberyTabSol(vector<int> &money,int start,int end){
    vector<int> dp(end+1,-1);

    dp[start+0]=money[start+0];
    dp[start+1]=max(money[start+0],money[start+1]);

    for (int i =start+2; i <= end; ++i) {
        int include=money[i] + dp[i-2];
        int exclude = 0 + dp[i-1];
        dp[i]= max(include,exclude);
    }
    return dp[end];
}
int hourseRobberyTab(vector<int> &money){
    int n=money.size();
    int firstToSecLast= hourseRobberyTabSol(money,0,n-2);
    int secToLast= hourseRobberyTabSol(money,1,n-1);
    return max(firstToSecLast,secToLast);
}
//18. House Robbery Problem (Space optimization)
int hourseRobberyOptSol(vector<int> &money,int start,int end){
    //vector<int> dp(end+1,-1);

    int secondPrev=money[start+0];
    int firstPrev=max(money[start+0],money[start+1]);

    for (int i =start+2; i <= end; ++i) {
        int include=money[i] + secondPrev;
        int exclude = 0 + firstPrev;
        int curr= max(include,exclude);
        secondPrev=firstPrev;
        firstPrev=curr;
    }
    return firstPrev;
}
int hourseRobberyOpt(vector<int> &money){
    int n=money.size();
    int firstToSecLast= hourseRobberyTabSol(money,0,n-2);
    int secToLast= hourseRobberyTabSol(money,1,n-1);
    return max(firstToSecLast,secToLast);
}

//19. Cut Rod into Segments of X, Y, Z (Recursion)
int cutRodSegment(int target,int x,int y,int z){
    if(target<0){
        return INT_MIN;
    }
    if(target==0){
        return 0;
    }
    int cutByX=1 + cutRodSegment(target-x,x,y,z);
    int cutByY=1 + cutRodSegment(target-y,x,y,z);
    int cutByZ=1 + cutRodSegment(target-z,x,y,z);
    return max(cutByX,max(cutByY,cutByZ));
}

//20. Cut Rod into Segments of X, Y, Z (Memorization)
int cutRodSegmentMemSol(int target,int x,int y,int z,vector<int> dp){
    if(target<0){
        return INT_MIN;
    }
    if(target==0){
        return 0;
    }

    if(dp[target]!=-1){
        return dp[target];
    }

    int cutByX=1 + cutRodSegmentMemSol(target-x,x,y,z,dp);
    int cutByY=1 + cutRodSegmentMemSol(target-y,x,y,z,dp);
    int cutByZ=1 + cutRodSegmentMemSol(target-z,x,y,z,dp);
    return dp[target]=  max(cutByX,max(cutByY,cutByZ));
}
int cutRodSegmentMem(int target,int x,int y,int z){
    vector<int> dp(target+1,-1);
    return cutRodSegmentMemSol(target,x,y,z,dp);
}

//21. Cut Rod into Segments of X, Y, Z (Tabulation)
int cutRodSegmentTab(int target,int x,int y,int z){
    vector<int> dp(target+1,INT_MIN);

    dp[0]=0;
    for (int tar = 1; tar <= target ; ++tar) {

        int cutByX=0;
        if(tar-x>=0)
            cutByX=1 + dp[tar-x];

        int cutByY=0;
        if(tar-y>=0)
            cutByY=1 + dp[tar-y];

        int cutByZ=0;
        if(tar-z>=0)
            cutByZ=1 + dp[tar-z];

        dp[tar]=  max(cutByX,max(cutByY,cutByZ));
    }
    return dp[target];
}

//23. Count derangements (Recursion)  (ith index doesn't stay at ith position --> how may combination?)
int countDerangement(int n){
    if(n==1){
        return 0;
    }
    if(n==2){
        return 1;
    }
    return (n-1)*(countDerangement(n-1)+ countDerangement(n-2));
}
//24. Count derangements (Memorization)
int countDerangementMemSol(int n,vector<int> &dp){
    if(n==1){
        return 0;
    }
    if(n==2){
        return 1;
    }

    if(dp[n]!=-1){
        return dp[n];
    }

    return dp[n]= (n-1)*(countDerangementMemSol(n-1,dp)+ countDerangementMemSol(n-2,dp));
}
int countDerangementMem(int n){
    vector<int> dp(n+1,-1);
    return countDerangementMemSol(n,dp);
}
//25. Count derangements (Tabulation)

int countDerangementTab(int n){
    vector<int> dp(n+1,-1);

    dp[1]=0;
    dp[2]=1;

    for (int i = 3; i <= n; ++i) {
        dp[i]=(i-1)*(dp[i-1]+dp[i-2]);
    }
    return dp[n];
}
//26. Count derangements (Space optimization)
int countDerangementOpt(int n){
    //vector<int> dp(n+1,-1);

    int secondPrev=0;
    int firstPrev=1;

    for (int i = 3; i <= n; ++i) {
        int curr=(i-1)*(firstPrev+secondPrev);
        secondPrev=firstPrev;
        firstPrev=curr;
    }
    return firstPrev;
}

//27. Painting Fence Algorithm (Recursion)
//28. Painting Fence Algorithm (Memorization)
//29. Painting Fence Algorithm (Tabulation)
//30. Painting Fence Algorithm (Space optimization)

//31. KnapSack Problem (Recursion)
int knapSackSol(vector<int> &weight,vector<int> &value,int capacity,int index){

    if(index<0){
        return 0;
    }

    int include=0;
    if(weight[index]<=capacity)
    include=value[index] + knapSackSol(weight,value,capacity-weight[index],index-1);

    int exclude=0 + knapSackSol(weight,value,capacity,index-1);
    return max(include,exclude);
}
int knapSack(vector<int> &weight,vector<int> &value,int capacity){
    int n=weight.size();
    return knapSackSol(weight,value,capacity,n-1);
}
//32. KnapSack Problem (Memorization)
int knapSackMemSol(vector<int> &weight,vector<int> &value,int capacity,int index,vector<vector<int>> &dp){

    if(index<0){
        return 0;
    }

    if(dp[index][capacity]!=-1){
        return dp[index][capacity];
    }

    int include=0;
    if(weight[index]<=capacity)
        include=value[index] + knapSackMemSol(weight,value,capacity-weight[index],index-1,dp);

    int exclude=0 + knapSackMemSol(weight,value,capacity,index-1,dp);
    return dp[index][capacity]= max(include,exclude);
}
int knapSackMem(vector<int> &weight,vector<int> &value,int capacity){
    int n=weight.size();

    vector<vector<int>> dp(n+1,vector<int>(capacity+1,-1));

    return knapSackMemSol(weight,value,capacity,n-1,dp);
}


//33. KnapSack Problem (Tabulation)

int knapSackTab(vector<int> &weight,vector<int> &value,int capacity){
    int n=weight.size();

    vector<vector<int>> dp(n+1,vector<int>(capacity+1,0));

    for (int cap = weight[0]; cap <= capacity ; ++cap) {
        if(weight[0]<=capacity){
            dp[0][cap]=value[0];
        }
    }

    for (int index = 1; index <= n ; ++index) {
        for (int cap = 0; cap <= capacity; ++cap) {
            int include=0;
            if(weight[index]<=cap)
                include=value[index] + dp[index-1][cap-weight[index]];

            int exclude=0 + dp[index-1][cap];
            dp[index][cap]= max(include,exclude);
        }
    }

    return dp[n-1][capacity];
}
//34. KnapSack Problem (Space optimization - two vector)
int knapSackOpt(vector<int> &weight,vector<int> &value,int capacity){
    int n=weight.size();

    //vector<vector<int>> dp(n+1,vector<int>(capacity+1,0));
    vector<int> curr(capacity+1,0);
    vector<int> prev(capacity+1,0);

    for (int cap = weight[0]; cap <= capacity ; ++cap) {
        if(weight[0]<=capacity){
            prev[cap]=value[0];
        }
    }

    for (int index = 1; index < n ; ++index) {
        for (int cap = 0; cap <= capacity; ++cap) {
            int include=0;
            if(weight[index]<=cap)
                include=value[index] + prev[cap-weight[index]];

            int exclude=0 + prev[cap];
            curr[cap]= max(include,exclude);
        }
        prev=curr;
    }

    return prev[capacity];
}
//35. KnapSack Problem (More Space optimization - one vector)
int knapSackOpt2(vector<int> &weight,vector<int> &value,int capacity){
    int n=weight.size();

    //vector<vector<int>> dp(n+1,vector<int>(capacity+1,0));
    vector<int> curr(capacity+1,0);
   // vector<int> prev(capacity+1,0);

    for (int cap = weight[0]; cap <= capacity ; ++cap) {
        if(weight[0]<=capacity){
            curr[cap]=value[0];
        }
    }

    for (int index = 1; index < n ; ++index) {
        for (int cap = capacity; cap >=0 ; --cap) {
            int include=0;
            if(weight[index]<=cap)
                include=value[index] + curr[cap-weight[index]];

            int exclude=0 + curr[cap];
            curr[cap]= max(include,exclude);
        }
    }

    return curr[capacity];
}

//36. Combination Sum (Recursion)
int combinationSum(vector<int> &nums,int target){
    if(target<0){
        return 0;
    }
    if(target==0){
        return 1;
    }

    int noOfWay=0;
    for (auto num:nums) {
        noOfWay+= combinationSum(nums,target-num);
    }
    return noOfWay;
}
//37. Combination Sum (Memorization)
int combinationSumMemSol(vector<int> &nums,int target,vector<int> &dp){
    if(target<0){
        return 0;
    }
    if(target==0){
        return 1;
    }

    if(dp[target]!=-1){
        return dp[target];
    }

    int noOfWay=0;
    for (auto num:nums) {
        noOfWay+= combinationSumMemSol(nums,target-num,dp);
    }
    return noOfWay;
}
int combinationSumMem(vector<int> &nums,int target){
    vector<int> dp(target+1,-1);
    return dp[target]= combinationSumMemSol(nums,target,dp);
}
//38. Combination Sum (Tabulation)

int combinationSumTab(vector<int> &nums,int target){
    vector<int> dp(target+1,0);

    dp[0]=1;
    for (int tar = 1; tar <= target; ++tar) {
        int noOfWay=0;
        for (auto num:nums) {
            if(tar-num>=0)
                noOfWay+= dp[tar-num];
        }
        dp[tar]= noOfWay;
    }

    return dp[target];
}

//39. Perfect Squares Problem (Recursion)
int minPerfectSquare(int n){
    if(n<=0){
        return 0;
    }

    int miniSquareNumber=n;
    for (int i = 1; i*i <= n; ++i) {
        miniSquareNumber=min(miniSquareNumber, 1+ minPerfectSquare(n - i*i) );
    }
    return miniSquareNumber;
}
//40. Perfect Squares Problem (Memorization)
int minPerfectSquareMemSol(int n,vector<int> &dp){
    if(n<=0){
        return 0;
    }

    if(dp[n]!=-1){
        return dp[n];
    }

    int miniSquareNumber=n;
    for (int i = 1; i*i <= n; ++i) {
        miniSquareNumber=min(miniSquareNumber, 1+ minPerfectSquareMemSol(n - i*i,dp));
    }
    return dp[n]= miniSquareNumber;
}
int minPerfectSquareMem(int n){
    vector<int> dp(n+1,-1);
    return minPerfectSquareMemSol(n,dp);
}
//41. Perfect Squares Problem (Tabulation)
int minPerfectSquareTab(int n){
    vector<int> dp(n+1,0);

    for (int k = 1; k <= n; ++k) {
        int miniSquareNumber=k;
        for (int i = 1; i*i <= k; ++i) {
            if(k-i*i>=0)
                miniSquareNumber=min(miniSquareNumber, 1+ dp[k-i*i]);
        }
        dp[k]= miniSquareNumber;
    }


    return dp[n];
}
//42. Perfect Cube Problem (Recursion)
int minPerfectCube(int n){
    if(n<=0){
        return 0;
    }

    int minCubeNumber=n;
    for (int i = 1; i*i*i <= n; ++i) {
        minCubeNumber=min(minCubeNumber,1 + minPerfectCube(n-i*i*i));
    }
    return minCubeNumber;
}


//43. Minimum Cost for Tickets (Recursion)
int minCostReservationSol(vector<int> &bookingDays,vector<int> &passCost,int noOfDays,int index){
    if(index>=noOfDays){
        return 0;
    }

    int oneDayPass = passCost[0] + minCostReservationSol(bookingDays,passCost,noOfDays,index+1);

    int i=0;
    for (i = index; (i < noOfDays) && (bookingDays[i]<bookingDays[index]+7); ++i);
    int sevenDayPass=passCost[1] + minCostReservationSol(bookingDays,passCost,noOfDays,i);

    for (i = index; (i < noOfDays) && (bookingDays[i]<bookingDays[index]+30); ++i);
    int thirtyDayPass=passCost[2] + minCostReservationSol(bookingDays,passCost,noOfDays,i);

    return min(oneDayPass,min(sevenDayPass,thirtyDayPass));
}
int minCostReservation(vector<int> &bookingDays,vector<int> &passCost){
    int noOfDays=bookingDays.size();
    return minCostReservationSol(bookingDays,passCost,noOfDays,0);
}

//44. Minimum Cost for Tickets (Memorization)
int minCostReservationMemSol(vector<int> &bookingDays,vector<int> &passCost,int noOfDays,int index,vector<int> &dp){
    if(index>=noOfDays){
        return 0;
    }

    if(dp[index]!=-1){
        return dp[index];
    }

    int oneDayPass = passCost[0] + minCostReservationMemSol(bookingDays,passCost,noOfDays,index+1,dp);

    int i=0;
    for (i = index; (i < noOfDays) && (bookingDays[i]<bookingDays[index]+7); ++i);
    int sevenDayPass=passCost[1] + minCostReservationMemSol(bookingDays,passCost,noOfDays,i,dp);

    for (i = index; (i < noOfDays) && (bookingDays[i]<bookingDays[index]+30); ++i);
    int thirtyDayPass=passCost[2] + minCostReservationMemSol(bookingDays,passCost,noOfDays,i,dp);

    return dp[index]= min(oneDayPass,min(sevenDayPass,thirtyDayPass));
}
int minCostReservationMem(vector<int> &bookingDays,vector<int> &passCost){
    int noOfDays=bookingDays.size();

    vector<int> dp(noOfDays+1,-1);

    return minCostReservationMemSol(bookingDays,passCost,noOfDays,0,dp);
}

//45. Minimum Cost for Tickets (Tabulation)
int minCostReservationTab(vector<int> &bookingDays,vector<int> &passCost){
    int noOfDays=bookingDays.size();

    vector<int> dp(noOfDays+1,0);

    for (int index = noOfDays-1; index >=0 ; --index) {
        int oneDayPass = passCost[0] + dp[index+1];

        int i=0;
        for (i = index; (i < noOfDays) && (bookingDays[i]<bookingDays[index]+7); ++i);
        int sevenDayPass=passCost[1] + dp[i];

        for (i = index; (i < noOfDays) && (bookingDays[i]<bookingDays[index]+30); ++i);
        int thirtyDayPass=passCost[2] + dp[i];

        dp[index]= min(oneDayPass,min(sevenDayPass,thirtyDayPass));
    }
    return dp[0];
}
//46. Minimum Cost for Tickets (Space optimization)  [unsolved]


//47. Largest Square area in Matrix (Recursion)
int largestSquareAreaMatSol(vector<vector<int>> &matrix,int i,int j,int &maxSizeSq){
    if(i>=matrix.size() || j>=matrix[0].size()){
        return 0;
    }

    int rightMove= largestSquareAreaMatSol(matrix,i,j+1,maxSizeSq);
    int bottomMove= largestSquareAreaMatSol(matrix,i+1,j,maxSizeSq);
    int diagonalMove= largestSquareAreaMatSol(matrix,i+1,j+1,maxSizeSq);

    if(matrix[i][j]==1){
        int ans= 1 + min(rightMove,min(bottomMove,diagonalMove));
        maxSizeSq=max(maxSizeSq,ans);
        return ans;
    }
    else{
        return 0;
    }

}
int largestSquareAreaMat(vector<vector<int>> &matrix){
    int maxSizeSquare=0;
    largestSquareAreaMatSol(matrix,0,0,maxSizeSquare);
    return maxSizeSquare;
}

//48. Largest Square area in Matrix (Memorization)
int largestSquareAreaMatMemSol(vector<vector<int>> &matrix,int i,int j,int &maxSizeSq,vector<vector<int>> &dp){
    if(i>=matrix.size() || j>=matrix[0].size()){
        return 0;
    }

    if(dp[i][j]!=-1){
        return dp[i][j];
    }

    int rightMove= largestSquareAreaMatMemSol(matrix,i,j+1,maxSizeSq,dp);
    int bottomMove= largestSquareAreaMatMemSol(matrix,i+1,j,maxSizeSq,dp);
    int diagonalMove= largestSquareAreaMatMemSol(matrix,i+1,j+1,maxSizeSq,dp);

    if(matrix[i][j]==1){
        int ans= 1 + min(rightMove,min(bottomMove,diagonalMove));
        maxSizeSq=max(maxSizeSq,ans);
        return dp[i][j]= ans;
    }
    else{
        return dp[i][j]= 0;
    }
}
int largestSquareAreaMatMem(vector<vector<int>> &matrix){
    int maxSizeSquare=0;

    int row=matrix.size();
    int col=matrix[0].size();
    vector<vector<int>> dp(row+1,vector<int>(col+1,-1));

    largestSquareAreaMatMemSol(matrix,0,0,maxSizeSquare,dp);
    return maxSizeSquare;
}

//49. Largest Square area in Matrix (Tabulation)
int largestSquareAreaMatTab(vector<vector<int>> &matrix){
    int maxSizeSq=0;

    int row=matrix.size();
    int col=matrix[0].size();
    vector<vector<int>> dp(row+1,vector<int>(col+1,0));

    for (int i = row-1; i >=0; --i) {
        for (int j = col-1; j >=0 ; --j) {
            int rightMove= dp[i][j+1];
            int bottomMove= dp[i+1][j];
            int diagonalMove= dp[i+1][j+1];

            if(matrix[i][j]==1){
                int ans= 1 + min(rightMove,min(bottomMove,diagonalMove));
                maxSizeSq=max(maxSizeSq,ans);
                dp[i][j]= ans;
            }
            else{
                dp[i][j]= 0;
            }
        }
    }

    return maxSizeSq;
}

//50. Largest Square area in Matrix (Space optimization)
int largestSquareAreaMatOpt(vector<vector<int>> &matrix){
    int maxSizeSq=0;

    int row=matrix.size();
    int col=matrix[0].size();
    //vector<vector<int>> dp(row+1,vector<int>(col+1,0));
    vector<int> curr(col+1,0);
    vector<int> next(col+1,0);

    for (int i = row-1; i >=0; --i) {
        for (int j = col-1; j >=0 ; --j) {
            int rightMove= curr[j+1];
            int bottomMove= next[j];
            int diagonalMove= next[j+1];

            if(matrix[i][j]==1){
                int ans= 1 + min(rightMove,min(bottomMove,diagonalMove));
                maxSizeSq=max(maxSizeSq,ans);
                curr[j]= ans;
            }
            else{
                curr[j]= 0;
            }
        }
        next=curr;
    }

    return maxSizeSq;
}

//51. Min Score Triangulation of Polygon (Recursion)
int minScoreTriPolySol(vector<int> &poly,int start,int end){
    if(start+1==end){
        return 0;
    }

    int miniTriangulation=INT_MAX;
    for (int k = start+1; k <= end-1 ; ++k) {
        miniTriangulation=min(miniTriangulation, poly[start]*poly[end]*poly[k] +
                minScoreTriPolySol(poly,start,k) + minScoreTriPolySol(poly,k,end));
    }
    return miniTriangulation;
}
int minScoreTriangulationPoly(vector<int> &polynomial){
    int n=polynomial.size();
    return minScoreTriPolySol(polynomial,0,n-1);
}

//52. Min Score Triangulation of Polygon (Memorization)
int minScoreTriPolyMemSol(vector<int> &poly,int start,int end,vector<vector<int>> &dp){
    if(start+1==end){
        return 0;
    }

    if(dp[start][end]!=-1){
        return dp[start][end];
    }

    int miniTriangulation=INT_MAX;
    for (int k = start+1; k <= end-1 ; ++k) {
        miniTriangulation=min(miniTriangulation, poly[start]*poly[end]*poly[k] +
                                                 minScoreTriPolyMemSol(poly,start,k,dp) + minScoreTriPolyMemSol(poly,k,end,dp));
    }
    return dp[start][end]= miniTriangulation;
}
int minScoreTriangulationPolyMem(vector<int> &polynomial){
    int n=polynomial.size();

    vector<vector<int>> dp(n+1,vector<int>(n+1,-1));

    return minScoreTriPolyMemSol(polynomial,0,n-1,dp);
}

//53. Min Score Triangulation of Polygon (Tabulation)
int minScoreTriangulationPolyTab(vector<int> &polynomial){
    int n=polynomial.size();

    vector<vector<int>> dp(n+1,vector<int>(n+1,0));

    for (int start = n-1; start >=0 ; --start) {
        for (int end = start+2; end < n; ++end) {
            int miniTriangulation=INT_MAX;
            for (int k = start+1; k <= end-1 ; ++k) {
                miniTriangulation=min(miniTriangulation, polynomial[start]*polynomial[end]*polynomial[k] +
                          dp[start][k] + dp[k][end]);
            }
            dp[start][end]= miniTriangulation;
        }
    }
    return dp[0][n-1];
}

//54. Minimum Sideways Jump (Recursion)
int sideWayJumpSol(vector<int> &obstacle,int currLane,int currPos){
    if(currPos==obstacle.size()){
        return 0;
    }

    if(currLane != obstacle[currPos+1]){
        return sideWayJumpSol(obstacle,currLane,currPos+1);
    }
    else{
        int miniJump=INT_MAX;
        for (int lane = 1; lane <= 3; ++lane) {
            if(lane!=currLane && lane!=obstacle[currPos]){
                miniJump=min(miniJump,1 + sideWayJumpSol(obstacle,lane,currPos));
            }
        }
        return miniJump;
    }

}
int sideWayJump(vector<int> &obstacle){
    return sideWayJumpSol(obstacle,2,0);
}

//55. Minimum Sideways Jump (Memorization)
int sideWayJumpMemSol(vector<int> &obstacle,int currLane,int currPos,vector<vector<int>> &dp){
    if(currPos==obstacle.size()){
        return 0;
    }

    if(dp[currLane][currPos]!=-1){
        return dp[currLane][currPos];
    }

    if(currLane != obstacle[currPos+1]){
        return dp[currLane][currPos]= sideWayJumpMemSol(obstacle,currLane,currPos+1,dp);
    }
    else{
        int miniJump=INT_MAX;
        for (int lane = 1; lane <= 3; ++lane) {
            if(lane!=currLane && lane!=obstacle[currPos]){
                miniJump=min(miniJump,1 + sideWayJumpMemSol(obstacle,lane,currPos+1,dp));
            }
        }
        return dp[currLane][currPos]= miniJump;
    }

}
int sideWayJumpMem(vector<int> &obstacle){
    int n=obstacle.size();

    vector<vector<int>> dp(4,vector<int>(n+1,-1));

    return sideWayJumpMemSol(obstacle,2,0,dp);
}

//56. Minimum Sideways Jump (Tabulation)
int sideWayJumpTab(vector<int> &obstacle){
    int n=obstacle.size();

    vector<vector<int>> dp(4,vector<int>(n+1,INT_MAX));

    dp[0][n]=0;
    dp[1][n]=0;
    dp[2][n]=0;
    dp[3][n]=0;


    for (int currPos = n-1; currPos >=0 ; --currPos) {
        for (int currLane = 1; currLane <= 3; ++currLane) {
            if(currLane != obstacle[currPos+1]){
                dp[currLane][currPos]= dp[currLane][currPos+1];
            }
            else{
                int miniJump=INT_MAX;
                for (int lane = 1; lane <= 3; ++lane) {
                    if(lane!=currLane && lane!=obstacle[currPos]){
                        miniJump=min(miniJump,1 + dp[lane][currPos+1]);
                    }
                }
                dp[currLane][currPos]= miniJump;
            }
        }
    }
    return min(dp[2][0], min(1+dp[1][0],1+dp[3][0]));
}
//57. Minimum Sideways Jump (Space optimization)
int sideWayJumpOpt(vector<int> &obstacle){
    int n=obstacle.size();

    //vector<vector<int>> dp(4,vector<int>(n+1,INT_MAX));
    vector<int> curr(4,INT_MAX);
    vector<int> next(4,INT_MAX);

    next[0]=0;
    next[1]=0;
    next[2]=0;
    next[3]=0;


    for (int currPos = n-1; currPos >=0 ; --currPos) {
        for (int currLane = 1; currLane <= 3; ++currLane) {
            if(currLane != obstacle[currPos+1]){
                curr[currLane]= next[currLane];
            }
            else{
                int miniJump=INT_MAX;
                for (int lane = 1; lane <= 3; ++lane) {
                    if(lane!=currLane && lane!=obstacle[currPos]){
                        miniJump=min(miniJump,1 + next[lane]);
                    }
                }
                curr[currLane]= miniJump;
            }
        }
        next=curr;
    }
    return min(next[2], min(1+next[1],1+next[3]));
}


//58. Reducing Dishes (Recursion)
//59. Reducing Dishes (Memorization)
//60. Reducing Dishes (Tabulation)
//61. Reducing Dishes (Space optimization)


//62. Longest Increasing Subsequence (Recursion)
int longestIncreasingSubsequenceSol(vector<int> &nums,int prevIndex,int index){

    if(index==nums.size()){
        return 0;
    }

    int include=0;

    if(prevIndex==-1 || nums[index]>nums[prevIndex])
        include=1 + longestIncreasingSubsequenceSol(nums,index,index+1);

    int exclude=0 + longestIncreasingSubsequenceSol(nums,prevIndex,index+1);
    return max(include,exclude);
}

int longestIncreasingSubsequence(vector<int> &nums){
    return longestIncreasingSubsequenceSol(nums,-1,0);
}

//63. Longest Increasing Subsequence (Memorization)
int longestIncreasingSubsequenceMemSol(vector<int> &nums,int prevIndex,int index,vector<vector<int>> &dp){

    if(index==nums.size()){
        return 0;
    }

    if(dp[index][prevIndex+1]!=-1){
        return dp[index][prevIndex+1];
    }

    int include=0;

    if(prevIndex==-1 || nums[index]>nums[prevIndex])
        include=1 + longestIncreasingSubsequenceMemSol(nums,index,index+1,dp);

    int exclude=0 + longestIncreasingSubsequenceMemSol(nums,prevIndex,index+1,dp);
    return dp[index][prevIndex+1]= max(include,exclude);
}

int longestIncreasingSubsequenceMem(vector<int> &nums){

    int n=nums.size();
    vector<vector<int>> dp(n+1,vector<int>(n+1,-1));

    return longestIncreasingSubsequenceMemSol(nums,-1,0,dp);
}

//64. Longest Increasing Subsequence (Tabulation)
int longestIncreasingSubsequenceTab(vector<int> &nums){

    int n=nums.size();
    vector<vector<int>> dp(n+1,vector<int>(n+1,0));

    for (int index = n-1; index >=0 ; --index) {
        for (int prevIndex = index-1; prevIndex >=-1; --prevIndex) {
            int include=0;

            if(prevIndex==-1 || nums[index]>nums[prevIndex])
                include=1 + dp[index+1][index+1];

            int exclude=0 + dp[index+1][prevIndex+1];
            dp[index][prevIndex+1]= max(include,exclude);
        }
    }
    return dp[0][-1+1];
}
//65. Longest Increasing Subsequence (Space optimization)
int longestIncreasingSubsequenceOpt(vector<int> &nums){

    int n=nums.size();
    //vector<vector<int>> dp(n+1,vector<int>(n+1,0));
    vector<int> curr(n+1,0);
    vector<int> next(n+1,0);

    for (int index = n-1; index >=0 ; --index) {
        for (int prevIndex = index-1; prevIndex >=-1; --prevIndex) {
            int include=0;

            if(prevIndex==-1 || nums[index]>nums[prevIndex])
                include=1 + next[index+1];

            int exclude=0 + next[prevIndex+1];
            curr[prevIndex+1]= max(include,exclude);
        }
        next=curr;
    }
    return next[-1+1];
}


//66. Longest Increasing Subsequence (DP + BinarySearch)
int longestIncreasingSubsequenceBinSrc(vector<int> &nums){
    vector<int> ans;
    ans.push_back(nums[0]);

    for (int i = 1; i < nums.size(); ++i) {
        if(nums[i]>ans.back()){
            ans.push_back(nums[i]);
        }
        else{
            int index= lower_bound(ans.begin(), ans.end(),nums[i])-ans.begin();
            ans[index]=nums[i];
        }
    }
    return ans.size();
}

//67. Russian Doll (DP + BinarySearch)
struct Env{
    int width;
    int height;
    Env(int width,int height){
        this->width=width;
        this->height=height;
    }
};
bool cmp(Env ev1,Env ev2){
    if(ev1.width==ev2.width){
        return ev1.height<ev2.height;
    }
    return ev1.width<ev2.width;
}
int russianDollBinSrcDP(vector<vector<int>> &envelops){
    vector<Env> listEv;
    for (auto env:envelops) {
        listEv.push_back(Env(env[0],env[1]));
    }
    sort(listEv.begin(), listEv.end(), cmp);

    vector<int> heightList;
    for (auto env:listEv) {
        heightList.push_back(env.height);
    }

    if(heightList.size()==0){
        return 0;
    }

    vector<int> ans;
    ans.push_back(heightList[0]);

    for (int i = 1; i < heightList.size(); ++i) {
        if(heightList[i] > ans.back()){
            ans.push_back(heightList[i]);
        }
        else{
            int index= lower_bound(ans.begin(), ans.end(),heightList[i])-ans.begin();
            ans[index]=heightList[i];
        }
    }
    return ans.size();
}

//68. Maximum Height by Stacking Cuboid (Tabulation)

bool checkSafe(vector<vector<int>> &cuboids,int prevIndex,int currIndex){
    if(cuboids[currIndex][0] <= cuboids[prevIndex][0] && cuboids[currIndex][1] <= cuboids[prevIndex][1] &&
            cuboids[currIndex][2] <= cuboids[prevIndex][2]){
        return true;
    }
    return false;
}

int maxCuboidHeightSol(vector<vector<int>> &cuboids,int prevIndex,int index){
    if(index==cuboids.size()){
        return 0;
    }

    int include=0;

    if(prevIndex==-1 || checkSafe(cuboids,index,prevIndex))
        include=cuboids[index][2] + maxCuboidHeightSol(cuboids,index+1,index+1);

    int exclude=0 + maxCuboidHeightSol(cuboids,prevIndex+1,index+1);
    return max(include,exclude);
}
int maxCuboidHeight(vector<vector<int>> cuboids){
    for (auto &arr:cuboids) {
        sort(arr.begin(), arr.end());
    }
    sort(cuboids.begin(), cuboids.end());
    return maxCuboidHeightSol(cuboids,-1,0);
}

//Memorization
int maxCuboidHeightMemSol(vector<vector<int>> &cuboids,int prevIndex,int index, vector<vector<int>> &dp){
    if(index==cuboids.size()){
        return 0;
    }

    if(dp[index][prevIndex+1]!=-1){
        return dp[index][prevIndex+1];
    }

    int include=0;

    if(prevIndex==-1 || checkSafe(cuboids,index,prevIndex))
        include=cuboids[index][2] + maxCuboidHeightMemSol(cuboids,index+1,index+1,dp);

    int exclude=0 + maxCuboidHeightMemSol(cuboids,prevIndex+1,index+1,dp);
    return dp[index][prevIndex+1]= max(include,exclude);
}
int maxCuboidHeightMem(vector<vector<int>> cuboids){
    for (auto &arr:cuboids) {
        sort(arr.begin(), arr.end());
    }
    sort(cuboids.begin(), cuboids.end());

    int n=cuboids.size();
    vector<vector<int>> dp(n+1,vector<int>(n+1,-1));

    return maxCuboidHeightMemSol(cuboids,-1,0,dp);
}

//Tabulation

int maxCuboidHeightTab(vector<vector<int>> cuboids){
    for (auto &arr:cuboids) {
        sort(arr.begin(), arr.end());
    }
    sort(cuboids.begin(), cuboids.end());

    int n=cuboids.size();
    vector<vector<int>> dp(n+1,vector<int>(n+1,0));

    for (int index = n-1; index >=0 ; --index) {
        for (int prevIndex = index-1; prevIndex >=-1 ; --prevIndex) {
            int include=0;

            if(prevIndex==-1 || checkSafe(cuboids,index,prevIndex))
                include=cuboids[index][2] + dp[index+1][index+1];

            int exclude=0 + dp[index+1][prevIndex+1];
            dp[index][prevIndex+1]= max(include,exclude);
        }
    }

    return dp[0][0];
}

//Space-optimization
int maxCuboidHeightOpt(vector<vector<int>> cuboids){
    for (auto &arr:cuboids) {
        sort(arr.begin(), arr.end());
    }
    sort(cuboids.begin(), cuboids.end());

    int n=cuboids.size();
   // vector<vector<int>> dp(n+1,vector<int>(n+1,0));
   vector<int> curr(n+1,0);
   vector<int> next(n+1,0);

    for (int index = n-1; index >=0 ; --index) {
        for (int prevIndex = index-1; prevIndex >=-1 ; --prevIndex) {
            int include=0;

            if(prevIndex==-1 || checkSafe(cuboids,index,prevIndex))
                include=cuboids[index][2] + next[index+1];

            int exclude=0 + next[prevIndex+1];
            curr[prevIndex+1]= max(include,exclude);
        }
        next=curr;
    }

    return next[0];
}

//69. Pizza with 3n size (Recursion)

int maxPizzaSliceSol(vector<int> &slices,int index,int noOfSlices){
    if(index>=slices.size() || noOfSlices==0){
        return 0;
    }

    int include=slices[index] + maxPizzaSliceSol(slices,index+2,noOfSlices-1);
    int exclude= 0 + maxPizzaSliceSol(slices,index+1,noOfSlices);
    return max(include,exclude);
}
int maxPizzaSlice(vector<int> &slices){
    int noOfSlice=slices.size();
    int firstToSecLast= maxPizzaSliceSol(slices,0,noOfSlice/3);
    int secToLast = maxPizzaSliceSol(slices,noOfSlice-1,noOfSlice/3);
    return max(firstToSecLast,secToLast);
}

//70. Pizza with 3n size (Memorization)
int maxPizzaSliceMemSol(vector<int> &slices,int index,int noOfSlices,vector<vector<int>> dp){
    if(index>=slices.size() || noOfSlices==0){
        return 0;
    }

    if(dp[index][noOfSlices]!=-1){
        return dp[index][noOfSlices];
    }

    int include =slices[index] + maxPizzaSliceMemSol(slices,index+2,noOfSlices-1,dp);
    int exclude= 0 + maxPizzaSliceMemSol(slices,index+1,noOfSlices,dp);
    return dp[index][noOfSlices]= max(include,exclude);
}
int maxPizzaSliceMem(vector<int> &slices){
    int noOfSlice=slices.size();

    vector<vector<int>> dp(noOfSlice+1,vector<int>(noOfSlice/3+1,-1));

    int firstToSecLast= maxPizzaSliceMemSol(slices,0,noOfSlice/3,dp);
    int secToLast = maxPizzaSliceMemSol(slices,noOfSlice-1,noOfSlice/3,dp);
    return max(firstToSecLast,secToLast);
}
//71. Pizza with 3n size (Tabulation)
int maxPizzaSliceTab(vector<int> &slices){
//    int totalSlice=slices.size();
//
//    vector<vector<int>> dp1(totalSlice+2,vector<int>(totalSlice/3+2,0));
//    for (int index = totalSlice-2; index >=0 ; --index) {
//        for (int noOfSlices = 0; noOfSlices <= totalSlice/3 ; ++noOfSlices) {
//            int include =slices[index] + dp1[index+2][noOfSlices-1];
//            int exclude= 0 + dp1[index+1][noOfSlices];
//            dp1[index][noOfSlices]= max(include,exclude);
//        }
//    }
//
//    int firstToSecLast =dp1[0][totalSlice/3];
//
//    vector<vector<int>> dp2(totalSlice+2,vector<int>(totalSlice/3+2,0));
//    for (int index = totalSlice-1; index >=0 ; --index) {
//        for (int noOfSlices = 0; noOfSlices <= totalSlice/3 ; ++noOfSlices) {
//            int include =slices[index] + dp2[index+2][noOfSlices-1];
//            int exclude= 0 + dp2[index+1][noOfSlices];
//            dp2[index][noOfSlices]= max(include,exclude);
//        }
//    }
//
//    int secToLast =dp2[1][totalSlice/3];
//    return max(firstToSecLast,secToLast);

}
//72. Pizza with 3n size (Space optimization)



//-------------------------------------------------------------------------






//73. Number of Dice Rolls with Target Sum (Recursion)

int diceRollTargetSol(int noOfFace,int dice,int target){

    if(target<0){
        return 0;
    }
    if(dice==0 && target!=0){
        return 0;
    }
    if(dice!=0 && target==0){
        return 0;
    }


    if(dice==0 && target==0){
        return 1;
    }

    int ans=0;
    for (int face =1 ; face <=noOfFace ; ++face) {
        ans+= diceRollTargetSol(noOfFace,dice-1,target-face);
    }
    return ans;
}

int diceRollTarget(int face,int dice,int target){
    return diceRollTargetSol(face,dice,target);
}

//74. Number of Dice Rolls with Target Sum (Memorization)
int diceRollTargetMemSol(int noOfFace,int dice,int target,vector<vector<int>> &dp){

    if(target<0){
        return 0;
    }
    if(dice==0 && target!=0){
        return 0;
    }
    if(dice!=0 && target==0){
        return 0;
    }

    if(dice==0 && target==0){
        return 1;
    }

    if(dp[dice][target]!=-1){
        return dp[dice][target];
    }

    int ans=0;
    for (int face =1 ; face <=noOfFace ; ++face) {
        ans+= diceRollTargetMemSol(noOfFace,dice-1,target-face,dp);
    }
    return dp[dice][target]= ans;
}

int diceRollTargetMem(int face,int dice,int target){

    vector<vector<int>> dp(dice+1,vector<int>(target+1,-1));
    return diceRollTargetMemSol(face,dice,target,dp);
}


//75. Number of Dice Rolls with Target Sum (Tabulation)
int diceRollTargetTab(int noOfFace,int noOfDice,int target){
    vector<vector<int>> dp(noOfDice+1,vector<int>(target+1,0));

    dp[0][0]=1;

    for (int dice = 1; dice <=noOfDice ; ++dice) {
        for (int tar = 1; tar <= target ; ++tar) {
            int ans=0;
            for (int face =1 ; face <=noOfFace ; ++face) {
                if(tar-face>=0)
                    ans+= dp[dice-1][tar-face];
            }
            dp[dice][tar]= ans;
        }
    }

    return dp[noOfDice][target];

}

//76. Number of Dice Rolls with Target Sum (Space optimization)
int diceRollTargetOpt(int noOfFace,int noOfDice,int target){
    //vector<vector<int>> dp(noOfDice+1,vector<int>(target+1,0));
    vector<int> curr(target+1,0);
    vector<int> prev(target+1,0);

    prev[0]=1;

    for (int dice = 1; dice <=noOfDice ; ++dice) {
        for (int tar = 1; tar <= target ; ++tar) {
            int ans=0;
            for (int face =1 ; face <=noOfFace ; ++face) {
                if(tar-face>=0)
                    ans+= prev[tar-face];
            }
            curr[tar]= ans;
        }
        prev=curr;
    }

    return curr[target];

}

//77. Partition Equal Subset Sum (Recursion)
bool partitionEqualSol(vector<int> &nums,int index,int target){
    if(target<0){
        return false;
    }
    if(index==nums.size()){
        return false;
    }
    if(target==0){
        return true;
    }


    bool include= nums[index] + partitionEqualSol(nums,index+1,target-nums[index]);
    bool exclude = 0 + partitionEqualSol(nums,index+1,target);
    return include || exclude;
}

bool partitionEqual(vector<int> &nums){
    int sum=0;
    for (auto x:nums) {
        sum+=x;
    }
    if(sum&1){
        return false;
    }
    int target=sum/2;
    return partitionEqualSol(nums,0,target);

}

//78. Partition Equal Subset Sum (Memorization)
bool partitionEqualMemSol(vector<int> &nums,int index,int target,vector<vector<int>> &dp){
    if(target<0){
        return false;
    }
    if(index==nums.size()){
        return false;
    }
    if(target==0){
        return true;
    }

    if(dp[index][target]!=-1){
        return dp[index][target];
    }

    bool include= nums[index] + partitionEqualMemSol(nums,index+1,target-nums[index],dp);
    bool exclude = 0 + partitionEqualMemSol(nums,index+1,target,dp);
    return dp[index][target]= include || exclude;
}

bool partitionEqualMem(vector<int> &nums){
    int sum=0;
    for (auto x:nums) {
        sum+=x;
    }
    if(sum&1){
        return false;
    }
    int target=sum/2;

    int n=nums.size();
    vector<vector<int>> dp(n+1,vector<int>(target+1,-1));

    return partitionEqualMemSol(nums,0,target,dp);

}

//79. Partition Equal Subset Sum (Tabulation)
bool partitionEqualTab(vector<int> &nums){
    int sum=0;
    for (auto x:nums) {
        sum+=x;
    }
    if(sum&1){
        return false;
    }
    int target=sum/2;

    int n=nums.size();
    vector<vector<bool>> dp(n+1,vector<bool>(target+1, false));

    for (int i = 0; i <= n; ++i) {
        dp[i][0]= true;
    }

    for (int index = n-1; index >=0 ; --index) {
        for (int tar = 0; tar <= target ; ++tar) {

            bool include= false;
            if(tar-nums[index]>=0)
                include= nums[index] + dp[index+1][tar-nums[index]];

            bool exclude = 0 + dp[index+1][tar];
            dp[index][tar]= include || exclude;
        }
    }
    return dp[0][target];

}

//80. Partition Equal Subset Sum (Space optimization)
bool partitionEqualOpt(vector<int> &nums){
    int sum=0;
    for (auto x:nums) {
        sum+=x;
    }
    if(sum&1){
        return false;
    }
    int target=sum/2;

    int n=nums.size();
    //vector<vector<bool>> dp(n+1,vector<bool>(target+1, false));
    vector<bool> curr(target+1, false);
    vector<bool> next(target+1, false);

    curr[0]= true;
    next[0]= true;

    for (int index = n-1; index >=0 ; --index) {
        for (int tar = 0; tar <= target ; ++tar) {

            bool include= false;
            if(tar-nums[index]>=0)
                include= nums[index] + next[tar-nums[index]];

            bool exclude = 0 + next[tar];
            curr[tar]= include || exclude;
        }
        next=curr;
    }
    return next[target];

}

//81. Minimum Swap to Make Sequence Increasing (Recursion)

int minSwapSeqIncSol(vector<int> &nums1,vector<int> &nums2,int index,bool swapped){

    if(index==nums1.size()){
        return 0;
    }

    int prev1=nums1[index-1];
    int prev2=nums2[index-1];

    if(swapped){
        swap(prev1,prev2);
    }

    int doSwap=INT_MAX;
    if(prev2 < nums1[index] && prev1 < nums2[index]){
        doSwap = 1 + minSwapSeqIncSol(nums1,nums2,index+1, true);
    }

    int noSwap=INT_MAX;
    if(prev1 < nums1[index] && prev2 < nums2[index]){
        noSwap= 0 + minSwapSeqIncSol(nums1,nums2,index+1, false);
    }

    return min(doSwap,noSwap);
}

int minSwapSeqInc(vector<int> &nums1,vector<int> &nums2){
    nums1.insert(nums1.begin(),-1);
    nums2.insert(nums2.begin(),-1);

    return minSwapSeqIncSol(nums1,nums2,1, false);
}


//82. Minimum Swap to Make Sequence Increasing (Memorization)

int minSwapSeqIncMemSol(vector<int> &nums1,vector<int> &nums2,int index,int swapped,vector<vector<int>> &dp){

    if(index==nums1.size()){
        return 0;
    }

    if(dp[index][swapped]!=-1){
        return dp[index][swapped];
    }

    int prev1=nums1[index-1];
    int prev2=nums2[index-1];

    if(swapped){
        swap(prev1,prev2);
    }

    int doSwap=INT_MAX;
    if(prev2 < nums1[index] && prev1 < nums2[index]){
        doSwap = 1 + minSwapSeqIncMemSol(nums1,nums2,index+1, 1,dp);
    }

    int noSwap=INT_MAX;
    if(prev1 < nums1[index] && prev2 < nums2[index]){
        noSwap= 0 + minSwapSeqIncMemSol(nums1,nums2,index+1, 0,dp);
    }

    return dp[index][swapped]= min(doSwap,noSwap);
}

int minSwapSeqIncMem(vector<int> &nums1,vector<int> &nums2){
    nums1.insert(nums1.begin(),-1);
    nums2.insert(nums2.begin(),-1);

    int n=nums1.size();
    vector<vector<int>> dp(n+1,vector<int>(2,-1));

    return minSwapSeqIncMemSol(nums1,nums2,1, 0,dp);
}

//83. Minimum Swap to Make Sequence Increasing (Tabulation)

int minSwapSeqIncTab(vector<int> &nums1,vector<int> &nums2){
    nums1.insert(nums1.begin(),-1);
    nums2.insert(nums2.begin(),-1);

    int n=nums1.size();
    vector<vector<int>> dp(n+1,vector<int>(2,INT_MAX));

    dp[n][0]=0;
    dp[n][1]=0;

    for (int index = n-1; index >=1 ; --index) {
        for (int swapped = 1; swapped >=0 ; --swapped) {
            int prev1=nums1[index-1];
            int prev2=nums2[index-1];

            if(swapped){
                swap(prev1,prev2);
            }

            int doSwap=INT_MAX;
            if(prev2 < nums1[index] && prev1 < nums2[index]){
                doSwap = 1 + dp[index+1][1];
            }

            int noSwap=INT_MAX;
            if(prev1 < nums1[index] && prev2 < nums2[index]){
                noSwap= 0 +dp[index+1][0];
            }

            dp[index][swapped]= min(doSwap,noSwap);
        }
    }
    return dp[1][0];
}


//84. Minimum Swap to Make Sequence Increasing (Space optimization)

int minSwapSeqIncOpt(vector<int> &nums1,vector<int> &nums2){
    nums1.insert(nums1.begin(),-1);
    nums2.insert(nums2.begin(),-1);

    int n=nums1.size();
    //vector<vector<int>> dp(n+1,vector<int>(2,INT_MAX));
    vector<int> nextRow(2,INT_MAX);
    vector<int> currRow(2,INT_MAX);

    nextRow[0]=0;
    nextRow[1]=0;

    for (int index = n-1; index >=1 ; --index) {
        for (int swapped = 1; swapped >=0 ; --swapped) {
            int prev1=nums1[index-1];
            int prev2=nums2[index-1];

            if(swapped){
                swap(prev1,prev2);
            }

            int doSwap=INT_MAX;
            if(prev2 < nums1[index] && prev1 < nums2[index]){
                doSwap = 1 + nextRow[1];
            }

            int noSwap=INT_MAX;
            if(prev1 < nums1[index] && prev2 < nums2[index]){
                noSwap= 0 +nextRow[0];
            }

            currRow[swapped]= min(doSwap,noSwap);
        }
        nextRow=currRow;
    }
    return nextRow[0];
}


//85. Longest Arithmetic Subsequence (Recursion)
int lengthOfLongestAPSol(vector<int> &arr,int uptoIndex,int diff){
    if(uptoIndex<0){
        return 0;
    }

    int ans=0;
    for (int i = uptoIndex-1; i >=0 ; --i) {
        if(arr[uptoIndex]-arr[i]==diff){
            ans= 1 + lengthOfLongestAPSol(arr,i,diff);
        }
    }
    return ans;
}

int lengthOfLongestAP(vector<int> &arr){
    if(arr.size()<=2){
        return arr.size();
    }

    int maxAns=0;
    for (int i = 0; i < arr.size(); ++i) {
        for (int j = i+1; j < arr.size(); ++j) {
            maxAns=max(maxAns,2 + lengthOfLongestAPSol(arr,i,arr[j]-arr[i]));
        }
    }
    return maxAns;
}

//86. Longest Arithmetic Subsequence (Memorization)
//int lengthOfLongestAPMemSol(vector<int> &arr,int uptoIndex,int diff){
//    if(uptoIndex<0){
//        return 0;
//    }
//
//    int ans=0;
//    for (int i = uptoIndex-1; i >=0 ; --i) {
//        if(arr[uptoIndex]-arr[i]==diff){
//            ans= 1 + lengthOfLongestAPMemSol(arr,i,diff);
//        }
//    }
//    return ans;
//}
//
//int lengthOfLongestAPMem(vector<int> &arr){
//    if(arr.size()<=2){
//        return arr.size();
//    }
//
//
//
//
//    int maxAns=0;
//    for (int i = 0; i < arr.size(); ++i) {
//        for (int j = i+1; j < arr.size(); ++j) {
//            maxAns=max(maxAns,2 + lengthOfLongestAPMemSol(arr,i,arr[j]-arr[i]));
//        }
//    }
//    return maxAns;
//}


//87. Longest Arithmetic Subsequence (Tabulation)

//88.  Longest AP with given Difference "d" (Hashmap)

//89. Unique Binary Search Trees or Catalan Number (Recursion)
//90. Unique Binary Search Trees or Catalan Number (Memorization)
//91. Unique Binary Search Trees or Catalan Number (Tabulation)

//92. Guess Number Higher or Lower (Recursion)
//93. Guess Number Higher or Lower (Memorization)
//94. Guess Number Higher or Lower (Tabulation)

//95. Minimum Cost Tree From Leaf Values

//96. Buy and Sell Stock [I]

//97. Buy and Sell Stock [II] (Recursion)
//98. Buy and Sell Stock [II] (Memorization)
//99. Buy and Sell Stock [II]  (Tabulation)
//100. Buy and Sell Stock [II] (Space optimization)

//101. Buy and Sell Stock [III] (Recursion)
//102. Buy and Sell Stock [III] (Memorization)
//103. Buy and Sell Stock [III] (Tabulation)
//104. Buy and Sell Stock [III] (Space optimization)

//105. Buy and Sell Stock [IV] (Space optimization + Alternative)
//106. Buy and Sell Stock [IV] (Recursion)
//107. Buy and Sell Stock [IV] (Memorization)
//108. Buy and Sell Stock [IV] (Tabulation)
//109. Buy and Sell Stock [IV] (Space optimization)

//110. Buy and Sell Stock [V] (Space optimization)

//111. Longest Common Subsequence (Recursion)
//112. Longest Common Subsequence (Memorization)
//113. Longest Common Subsequence (Tabulation)
//114. Longest Common Subsequence (Space optimization)

//115. Longest Pelindromic Subsequence (Recursion)
//116. Longest Pelindromic Subsequence (Memorization)
//117. Longest Pelindromic Subsequence (Tabulation)
//118. Longest Pelindromic Subsequence (Space optimization)

//119. Edit Distance (Recursion)
//120. EDIT Distance (Memorization)
//121. EDIT Distance (Tabulation)
//122. EDIT Distance (Space optimization)

int main(){
    int choice;
    cout<<"Choice:";
    cin>>choice;
    while (choice){
        switch (choice) {
            case 1:{
                cout<<fibonacciMem(6)<<endl;
                break;
            }
            case 2:{
                cout<<fibonacciTab(6)<<endl;
                break;
            }
            case 3:{
                cout<<fibonacciOpt(6)<<endl;
                break;
            }
            case 4:{
                vector<int> cost = { 1, 100, 1, 1, 1, 100, 1, 1, 100, 1 };
                cout<<minCostClimbingStair(cost)<<endl;
                break;
            }
            case 5:{
                vector<int> cost = { 1, 100, 1, 1, 1, 100, 1, 1, 100, 1 };
                cout<<minCostClimbingStairMem(cost)<<endl;
                break;
            }
            case 6:{
                vector<int> cost = { 1, 100, 1, 1, 1, 100, 1, 1, 100, 1 };
                cout<<minCostClimbingStairTab(cost)<<endl;
                break;
            }
            case 7:{
                vector<int> cost = { 1, 100, 1, 1, 1, 100, 1, 1, 100, 1 };
                cout<<minCostClimbingStairOpt(cost)<<endl;
                break;
            }
            case 8:{
                vector<int> coins={1,2,3};
                cout<<minNumberCoins(coins,7)<<endl;
                break;
            }
            case 9:{
                vector<int> coins={1,2,3};
                cout<<minNumberCoinsMem(coins,7)<<endl;
                break;
            }
            case 10:{
                vector<int> coins={1,2,3};
                cout<<minNumberCoinsTab(coins,7)<<endl;
                break;
            }
            case 11:{
                vector<int> nums={1, 2, 3, 1 ,3 ,5, 8, 1, 9};
                cout<<maxSumNonAdjElement(nums)<<endl;
                break;
            }
            case 12:{
                vector<int> nums={1, 2, 3, 1 ,3 ,5, 8, 1, 9};
                cout<<maxSumNonAdjElementMem(nums)<<endl;
                break;
            }
            case 13:{
                vector<int> nums={1, 2, 3, 1 ,3 ,5, 8, 1, 9};
                cout<<maxSumNonAdjElementTab(nums)<<endl;
                break;
            }
            case 14:{
                vector<int> nums={1, 2, 3, 1 ,3 ,5, 8, 1, 9};
                cout<<maxSumNonAdjElementOpt(nums)<<endl;
                break;
            }
            case 15:{
                vector<int> money={1, 5, 1, 2 ,6};
                cout<<hourseRobbery(money)<<endl;
                break;
            }
            case 16:{
                vector<int> money={1, 5, 1, 2 ,6};
                cout<<hourseRobberyMem(money)<<endl;
                break;
            }
            case 17:{
                vector<int> money={1, 5, 1, 2 ,6};
                cout<<hourseRobberyTab(money)<<endl;
                break;
            }
            case 18:{
                vector<int> money={1, 5, 1, 2 ,6};
                cout<<hourseRobberyOpt(money)<<endl;
                break;
            }
            case 19:{
                cout<<cutRodSegment(7,3,2,2)<<endl;
                break;
            }
            case 20:{
                cout<<cutRodSegmentMem(7,3,2,2)<<endl;
                break;
            }
            case 21:{
                cout<<cutRodSegmentTab(7,3,2,2)<<endl;
                break;
            }
            case 23:{
                cout<<countDerangement(4)<<endl;
                break;
            }
            case 24:{
                cout<<countDerangementMem(4)<<endl;
                break;
            }
            case 25:{
                cout<<countDerangementTab(4)<<endl;
                break;
            }
            case 26:{
                cout<<countDerangementOpt(4)<<endl;
                break;
            }


            case 31:{
                vector<int> weight={1, 2, 4, 5};
                vector<int> value={5, 4, 8, 6};
                cout<<knapSack(weight, value,5)<<endl;
                break;
            }
            case 32:{
                vector<int> weight={1, 2, 4, 5};
                vector<int> value={5, 4, 8, 6};
                cout<<knapSackMem(weight, value,5)<<endl;
                break;
            }
            case 33:{
                vector<int> weight={1, 2, 4, 5};
                vector<int> value={5, 4, 8, 6};
                cout<<knapSackTab(weight, value,5)<<endl;
                break;
            }
            case 34:{
                vector<int> weight={1, 2, 4, 5};
                vector<int> value={5, 4, 8, 6};
                cout<<knapSackOpt(weight, value,5)<<endl;
                break;
            }
            case 35:{
                vector<int> weight={1, 2, 4, 5};
                vector<int> value={5, 4, 8, 6};
                cout<<knapSackOpt2(weight, value,5)<<endl;
                break;
            }
            case 36:{
                vector<int> num={1, 2, 5};
                cout<<combinationSum(num,5)<<endl;
                break;
            }
            case 37:{
                vector<int> num={1, 2, 5};
                cout<<combinationSumMem(num,5)<<endl;
                break;
            }
            case 38:{
                vector<int> num={1, 2, 5};
                cout<<combinationSumTab(num,5)<<endl;
                break;
            }
            case 39:{
                cout<<minPerfectSquare(6)<<endl;
                break;
            }
            case 40:{
                cout<<minPerfectSquareMem(6)<<endl;
                break;
            }
            case 41:{
                cout<<minPerfectSquareTab(6)<<endl;
                break;
            }
            case 42:{
                cout<<minPerfectCube(9)<<endl;
                break;
            }
            case 43:{
                vector<int> days={1, 3, 4, 5, 7, 8, 10};
                vector<int> costs={2, 7, 20};
                cout<<minCostReservation(days,costs)<<endl;
                break;
            }
            case 44:{
                vector<int> days={1, 3, 4, 5, 7, 8, 10};
                vector<int> costs={2, 7, 20};
                cout<<minCostReservationMem(days,costs)<<endl;
                break;
            }
            case 45:{
                vector<int> days={1, 3, 4, 5, 7, 8, 10};
                vector<int> costs={2, 7, 20};
                cout<<minCostReservationTab(days,costs)<<endl;
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
                cout<<largestSquareAreaMat(matrix)<<endl;
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
                cout<<largestSquareAreaMatMem(matrix)<<endl;
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
                cout<<largestSquareAreaMatTab(matrix)<<endl;
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
                cout<<largestSquareAreaMatOpt(matrix)<<endl;
                break;
            }
            case 51:{
                vector<int> polygonial={ 1,3,1,4,1,5};
                cout<<minScoreTriangulationPoly(polygonial)<<endl;
                break;
            }
            case 52:{
                vector<int> polygonial={ 1,3,1,4,1,5};
                cout<<minScoreTriangulationPolyMem(polygonial)<<endl;
                break;
            }
            case 53:{
                vector<int> polygonial={ 1,3,1,4,1,5};
                cout<<minScoreTriangulationPolyTab(polygonial)<<endl;
                break;
            }
            case 54:{
                vector<int> obstacle={0,2,1,0,3,0};
                cout<<sideWayJump(obstacle)<<endl;
                break;
            }
            case 55:{
                vector<int> obstacle={0,2,1,0,3,0};
                cout<<sideWayJumpMem(obstacle)<<endl;
                break;
            }
            case 56:{
                vector<int> obstacle={0,2,1,0,3,0};
                cout<<sideWayJumpTab(obstacle)<<endl;
                break;
            }
            case 57:{
                vector<int> obstacle={0,2,1,0,3,0};
                cout<<sideWayJumpOpt(obstacle)<<endl;
                break;
            }


            case 62:{
                vector<int> nums={0,8,4,12,2,10,6,14,1,9,5,13,3,11,7,15};
                cout<<longestIncreasingSubsequence(nums)<<endl;
                break;
            }
            case 63:{
                vector<int> nums={0,8,4,12,2,10,6,14,1,9,5,13,3,11,7,15};
                cout<<longestIncreasingSubsequenceMem(nums)<<endl;
                break;
            }
            case 64:{
                vector<int> nums={0,8,4,12,2,10,6,14,1,9,5,13,3,11,7,15};
                cout<<longestIncreasingSubsequenceTab(nums)<<endl;
                break;
            }
            case 65:{
                vector<int> nums={0,8,4,12,2,10,6,14,1,9,5,13,3,11,7,15};
                cout<<longestIncreasingSubsequenceOpt(nums)<<endl;
                break;
            }
            case 66:{
                vector<int> nums={0,8,4,12,2,10,6,14,1,9,5,13,3,11,7,15};
                cout<<longestIncreasingSubsequenceBinSrc(nums)<<endl;
                break;
            }
            case 67: {
                vector<vector<int>> envelopes = {
                        {5, 4},
                        {6, 4},
                        {6, 7},
                        {2, 3}
                };
                cout << russianDollBinSrcDP(envelopes) << endl;
                break;
            }
            case 68:{
                vector<vector<int>> cuboids={
                        {50,45,20},
                        {95,37,53},
                        {45,23,12}
                };
                cout<<maxCuboidHeight(cuboids)<<endl;
                cout<<maxCuboidHeightMem(cuboids)<<endl;
                cout<<maxCuboidHeightTab(cuboids)<<endl;
                cout<<maxCuboidHeightOpt(cuboids)<<endl;
                break;
            }
            case 69:{
                vector<int> slices={1,2,3,4,5,6};
                cout<<maxPizzaSlice(slices)<<endl;
                break;
            }
            case 70:{
                vector<int> slices={1,2,3,4,5,6};
                cout<<maxPizzaSliceMem(slices)<<endl;
                break;
            }
            case 71:{
                vector<int> slices={1,2,3,4,5,6};
                cout<<maxPizzaSliceTab(slices)<<endl;
                break;
            }


            case 73:{
                cout<<diceRollTarget(6,3,12)<<endl;
                break;
            }
            case 74:{
                cout<<diceRollTargetMem(6,3,12)<<endl;
                break;
            }
            case 75:{
                cout<<diceRollTargetTab(6,3,12)<<endl;
                break;
            }
            case 76:{
                cout<<diceRollTargetOpt(6,3,12)<<endl;
                break;
            }
            case 77:{
                vector<int> nums={1,5,11,5};
                if(partitionEqual(nums)){
                    cout<<"Yes"<<endl;
                }
                else{
                    cout<<"No"<<endl;
                }
                break;
            }
            case 78:{
                vector<int> nums={1,5,11,5};
                if(partitionEqualMem(nums)){
                    cout<<"Yes"<<endl;
                }
                else{
                    cout<<"No"<<endl;
                }
                break;
            }
            case 79:{
                vector<int> nums={1,5,11,5};
                if(partitionEqualTab(nums)){
                    cout<<"Yes"<<endl;
                }
                else{
                    cout<<"No"<<endl;
                }
                break;
            }
            case 80:{
                vector<int> nums={1,5,11,5};
                if(partitionEqualOpt(nums)){
                    cout<<"Yes"<<endl;
                }
                else{
                    cout<<"No"<<endl;
                }
                break;
            }
            case 81:{
                vector<int> num1={1,3,3,4,8};
                vector<int> num2={1,2,4,7,5};
                cout<<minSwapSeqInc(num1,num2)<<endl;
                break;
            }
            case 82:{
                vector<int> num1={1,3,3,4,8};
                vector<int> num2={1,2,4,7,5};
                cout<<minSwapSeqIncMem(num1,num2)<<endl;
                break;
            }
            case 83:{
                vector<int> num1={1,3,3,4,8};
                vector<int> num2={1,2,4,7,5};
                cout<<minSwapSeqIncTab(num1,num2)<<endl;
                break;
            }
            case 84:{
                vector<int> num1={1,3,3,4,8};
                vector<int> num2={1,2,4,7,5};
                cout<<minSwapSeqIncOpt(num1,num2)<<endl;
                break;
            }
            case 85:{
                vector<int> arr={1,7,10,13,14,19};
                cout<<lengthOfLongestAP(arr)<<endl;
                break;
            }



        }
        cout<<"Choice:";
        cin>>choice;
    }
}