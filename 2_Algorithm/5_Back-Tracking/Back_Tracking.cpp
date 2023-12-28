#include "iostream"
#include "vector"
using namespace std;

//1. Rat in maze

bool isSafe(int newX,int newY,vector<vector<bool>> &visited,vector<vector<int>> &arr,int n){
    if(newX>=0 && newY>=0 && newX<n && newY<n && !visited[newX][newY] && arr[newX][newY]==1){
        return true;
    }
    return false;
}
void solveMaze(int x,int y,vector<vector<int>> &arr,int n,vector<string> &ans,vector<vector<bool>> &visited,string path){
    if(x==n-1 && y==n-1){
        ans.push_back(path);
        return;
    }

    visited[x][y]= true;

    //down
    if(isSafe(x+1,y,visited,arr,n)){
        visited[x][y]= true;
        solveMaze(x+1,y,arr,n,ans,visited,path+"D");
    }

    //Left
    if(isSafe(x,y-1,visited,arr,n)){
        visited[x][y]= true;
        solveMaze(x,y-1,arr,n,ans,visited,path+"L");
    }

    //Right
    if(isSafe(x,y+1,visited,arr,n)){
        visited[x][y]= true;
        solveMaze(x,y+1,arr,n,ans,visited,path+"R");
    }

    //Up
    if(isSafe(x-1,y,visited,arr,n)){
        visited[x][y]= true;
        solveMaze(x-1,y,arr,n,ans,visited,path+"U");
    }

    visited[x][y]= false;

}
vector<string > searchMaze(vector<vector<int>> &arr,int n){
    vector<string > ans;
    vector<vector<bool>> visited(n,vector<bool> (n, false));
    string path= "";
    if(arr[0][0]==0){
        return ans;
    }
    solveMaze(0,0,arr,n,ans,visited,path);
    return ans;
}


//2. N-Queen problem
bool isSafe(int row,int col,vector<vector<int>> &board,int n){
    int x=row;
    int y=col;

    while (y>=0){
        if(board[x][y]==1){
            return false;
        }
        y--;
    }
    x=row;
    y=col;

    while (x>=0 & y>=0){
        if(board[x][y]==1){
            return false;
        }
        y--;
        x--;
    }

    x=row;
    y=col;
    while (x>=0 & y>=0){
        if(board[x][y]==1){
            return false;
        }
        y--;
        x++;
    }
    return true;
}
void addSolution(vector<vector<int>> &ans,vector<vector<int>> &board,int n){

    vector<int> temp;
    for (int i = 0; i < n; ++i) {

        for (int j = 0; j < n; ++j) {
            temp.push_back(board[i][j]);
        }
    }
    ans.push_back(temp);
}
void solveNQueen(int col,vector<vector<int>> &ans,vector<vector<int>> &board,int n){
    if(col == n){
        addSolution(ans,board,n);
        return;
    }

    for(int row=0;row<n;row++){
        if(isSafe(row,col,board,n)){
            board[row][col]=1;
            solveNQueen(col+1,ans,board,n);
            board[row][col]=0;
        }
    }

}
vector<vector<int>> nQueen(int n){
    vector<vector<int>> board(n,vector<int>(n, 0));
    vector<vector<int>> ans;

    solveNQueen(n,ans,board,n);

    return ans;
}


//3. Sudoku solver
bool isSafeSudoku(int row,int col,vector<vector<int>> &board,int value){
    for (int i = 0; i < board.size(); ++i) {
        if(board[row][i] == value ){              //check row-wise
            return false;
        }
        if(board[i][col] == value){             //check col-wise
            return false;
        }

        if(board[3*(row/3) + (i/3)][3*(col/3) + (i%3)]  == value){       //check diagonal-wise (formula)
            return false;
        }
    }
    return true;            //every test case pass :: return true
}
bool solveSudoku(vector<vector<int>> &board){
    int n=board.size();                     //size of the board (9)

    for (int i = 0; i < n; ++i) {                        //iterate row-by-row
        for (int j = 0; j < n; ++j) {                        //iterate col-by-col
            if(board[i][j]==0){                                 //if sudoku table empty space (denotes by 0)
                for(int val=0;val<=9;val++){                        //check by number 1 to 9  :: one by one
                    if(isSafeSudoku(i,j,board,val)){        //if the place is safe for the particular value from 1 to 9
                        board[i][j]=val;                                    //insert into the gap by the number

                        bool ifPsblToSolvce = solveSudoku(board);         //check :: if is it possible
                        if(ifPsblToSolvce){                 //if possible to solve :: stop checking by value and exit from the function with true
                            return true;
                        }
                        else{                              //if not possible :: back-track and check (remove value from the gap and insert zero)
                            board[i][j]=0;                              //and again check from the next value  to   9
                        }
                    }
                }
                return false;                       //if true doesn't  occure :: it is impossible to solve and return false
            }
        }
    }
    return true;        //if there is no gap into the board :: return true
}
void sudoku(vector<vector<int>> &sudukoBoard){
    solveSudoku(sudukoBoard);        //make a sudoku solve
}

int main(){
    int data,data2,data3,choice;
    cout<<"choice:";
    cin>>choice;
    while (choice){
        switch (choice) {
            case 1:{
                vector<vector<int>> arr={
                        {1,0,0,0},
                        {1,1,0,0},
                        {1,1,0,0},
                        {0,1,1,1}
                };
                vector<string> seq= searchMaze(arr,4);
                for (auto x:seq) {
                    cout<<x<<endl;
                }
                break;
            }
            case 2: {
                vector<vector<int>> boardStatus = nQueen(4);
            }
            case 3:{
                vector<vector<int>> sudokuTable={
                        {3, 0, 6, 5 ,0 ,8 ,4 ,0, 0},
                        {5, 2, 0, 0, 0, 0, 0 ,0 ,0},
                        {0, 8 ,7, 0, 0, 0 ,0, 3, 1},
                        {0, 0, 3, 0, 1 ,0 ,0, 8 ,0},
                        {9, 0 ,0 ,8, 6 ,3, 0, 0, 5},
                        {0 ,5 ,0, 0, 9, 0 ,6 ,0, 0},
                        {1 ,3, 0, 0, 0, 0, 2, 5, 0},
                        {0 ,0 ,0 ,0, 0 ,0, 0, 7 ,4},
                        {0, 0, 5, 2 ,0, 6, 3 ,0, 0},
                };
                sudoku(sudokuTable);
                for (auto x:sudokuTable) {
                    for (auto y:x) {
                        cout<<y<<" ";
                    }
                    cout<<endl;
                }
                break;
            }
            default:{
                cout<<"Invalid selection"<<endl;
            }
        }
        cout<<"choice:";
        cin>>choice;
    }
}