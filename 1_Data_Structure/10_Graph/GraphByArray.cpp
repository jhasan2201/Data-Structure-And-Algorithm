#include "iostream"
#include "vector"
#include "queue"
#include "stack"
#include "cstring"
#define V 8
#define E 10
using namespace std;

void printAdjacencyList(vector<int> adjList[],int v){
    for (int i = 0; i < v; ++i) {
        cout<<i<<"-->";
        for (int x:adjList[i]) {
            cout<<x<<" ";
        }
        cout<<endl;
    }
}
void printAdjacencyMatrix(vector<int> adjList[],int v){
    int adjMat[v][v];
    memset(adjMat,0, sizeof(adjMat));
    for (int i = 0; i < v; ++i) {
        for (int x:adjList[i]) {
            adjMat[i][x]=1;
        }
    }
    for (int i = 0; i < v; ++i) {
        for (int j = 0; j < v; ++j) {
            cout<<adjMat[i][j]<<" ";
        }
        cout<<endl;
    }
}
void BFS(vector<int>vertex[],int v,int source){
    bool visited[V]= {false};
    queue<int> q;
    q.push(source);

    vector<int> visitedSequence;
    while (!q.empty()){
        int curr=q.front();
        q.pop();

        if(visited[curr]== true){
            continue;
        }
        visited[curr]= true;
        visitedSequence.push_back(curr);

        vector<int> temp=vertex[curr];
        for(int x: temp){
            if(visited[x]== false){
                q.push(x);
            }
        }
    }

    for (int it:visitedSequence) {
        cout<<it<<" ";
    }
    cout<<endl;

}
void DFS(vector<int>vertex[],int v,int source){
    bool visited[V]={false};
    stack<int> st;
    st.push(source);

    vector<int> visitingSequence;

    while (!st.empty()){
        int curr=st.top();
        st.pop();

        if(visited[curr]== true){
            continue;
        }
        visited[curr]= true;
        visitingSequence.push_back(curr);

        vector<int> temp=vertex[curr];

        for (int x:temp) {
            if(visited[x]== false){
                st.push(x);
            }
        }
    }

    for (int it:visitingSequence) {
        cout<<it<<" ";
    }
    cout<<endl;

}
int main(){
    int input[E+1][V]={
            {8 ,9},
            {0 ,1},
            {0, 2},
            {0, 7},
            {1, 4},
            {2, 3},
            {2, 4},
            {3, 5},
            {3, 6},
            {6, 7}
    };
//    int v,e;
//    cout<<"Vertex:";
//    cin>>v;
//    cout<<"Edges:";
//    cin>>e;

    vector<int> adjList[V];

    for (int i = 0; i < E; ++i) {
//        int from,to;
//        cin>>from>>to;
        adjList[input[i+1][0]].push_back(input[i+1][1]);
        adjList[input[i+1][1]].push_back(input[i+1][0]);
    }

    int data,choice;
    cout<<"Choice:";
    cin>>choice;
    while (choice){
        switch (choice) {
            case 1:{
                printAdjacencyList(adjList,V);
                cout<<endl;
                break;
            }
            case 2:{
                printAdjacencyMatrix(adjList,V);
                cout<<endl;
                break;

            }
            case 3:{
                cout<<"Base:";
                cin>>data;
                BFS(adjList,V,data);
                cout<<endl;
                break;
            }
            case 4:{
                cout<<"Base:";
                cin>>data;
                DFS(adjList,V,data);
                cout<<endl;
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