#include "iostream"
#include "unordered_map"
#include "list"
#include "vector"
#include "queue"
#include "stack"
#include "algorithm"
#include "set"

using namespace std;

void printVectorOfVector(vector<vector<int>> &vvAns){
    for (auto i:vvAns) {
        for (auto j:i) {
            cout<<j<<" ";
        }
        cout<<endl;
    }
}
void printVector(vector<int> &vAns){
    for (auto x:vAns) {
        cout<<x<<" ";
    }
    cout<<endl;
}

class Graph{
public:
    unordered_map<int, list<int>> adjList;
    vector<vector<int>> edges;

    //1. Add Edge
    void addEdge(int from,int to,bool direction){
        adjList[from].push_back(to);
        if(!direction){                          //if undirected to--from
            adjList[to].push_back(from);
        }
        adjList[to];

        vector<int> edge;
        edge.push_back(from);
        edge.push_back(to);
        edges.push_back(edge);
    }

    //2. Print Adjacency List
    void printAdjList(){
        for (auto i:adjList) {       //iterate :: maps first element
            cout<<i.first<<" --> ";
            for (auto j:i.second) {           //iterate corresponding to first element's set
                cout<<j<<" ";
            }
            cout<<endl;
        }
    }


};

class WeiGraph{
public:
    vector<vector<int>> edges;
    unordered_map<int, list<pair<int,int>>> adjList;

    //3. Add Edge weighted graph
    void addEdge(int from,int to,int weight,bool direction){
        vector<int> edge;
        edge.push_back(from);
        edge.push_back(to);
        edge.push_back(weight);
        edges.push_back(edge);


        adjList[from].push_back(make_pair(to,weight));        //make a pair of :: to and weight
        //adjList's from-th element contain a list of pair<to,weight>
        adjList[to];
        if(!direction){
            adjList[to].push_back(make_pair(from,weight));     //make a pair of :: from and weight
            //adjList's to-th element contain a list of pair<from,weight>
        }
    }


    //4. Print adjacency list of weighted graph
    void printAdjList(){
        for (auto i:adjList) {
            cout<<i.first<<" --> ";                           //first element of unordered_map
            for (auto j:i.second) {               //contain list of pair
                cout<<"["<<j.first<<","<<j.second<<"] ";    //pair firstElement ::to    secondElement::weight
            }
            cout<<endl;
        }
    }
};

vector<vector<int>> prepareAdjMatrix(){
    int v,e;
    cout<<"Vertex:";
    cin>>v;
    cout<<"Edges:";
    cin>>e;
    vector<vector<int>> adjMatrix(v,vector<int>(v,INT_MAX));
    for (int i = 0; i < e; ++i) {
        int from,to,weight;
        cout<<"From :: To:: Weight :";
        cin>>from,to,weight;
        adjMatrix[from][to]=weight;
    }
    return adjMatrix;
}
void printAdjMatrix(vector<vector<int>> &adjMatrix){
    for (int i = 0; i < adjMatrix.size(); ++i) {
        for (int j = 0; j < adjMatrix.size(); ++j) {
            cout<<adjMatrix[i][j]<<" ";
        }
        cout<<endl;
    }
}


//5. BFS
void bfs(unordered_map<int, list<int>> &adjList,unordered_map<int,bool> &visited,vector<int> &components,int source){
    queue<int> q;
    q.push(source);                 //push base in the queue
    visited[source] = true;              //make it is visited
    components.push_back(source);

    while (!q.empty()){
        int frontNode = q.front();;            //take element from queue
        q.pop();

        for (auto neighbur:adjList[frontNode]) {      //take its neighbour elements
            if(!visited[neighbur]){                        //if its not visited :: push it into the queue
                q.push(neighbur);
                visited[neighbur] = true;                   //make it as visited
                components.push_back(neighbur);        //push it as a visited
            }
        }
    }
}
vector<vector<int>> BFS(unordered_map<int, list<int>> &adjList){
    vector<vector<int>> visitedSeq;
    unordered_map<int,bool> visited;
    for (auto node:adjList) {                      //iterate all node as a base one by one (for disconnected components )
        if(!visited[node.first]){                                          //if base is not visited :: call bfs
            vector<int> components;
            bfs(adjList,visited,components,node.first);
            visitedSeq.push_back(components);
        }

    }
    return visitedSeq;
}

//6. DFS
void dfs(unordered_map<int, list<int>> &adjList,unordered_map<int,bool> &visited,vector<int> &components,int source){
    stack<int> st;
    st.push(source);
    visited[source] = true;
    components.push_back(source);

    while (!st.empty()){
        int topNode = st.top();                         //take topElement from stack
        st.pop();

        for (auto neighbur:adjList[topNode]) {
            if(!visited[neighbur]){
                st.push(neighbur);
                visited[neighbur] = true;
                components.push_back(neighbur);
            }
        }
    }
}
vector<vector<int>> DFS(unordered_map<int, list<int>> &adjList){
    vector<vector<int>> visitedSeq;
    unordered_map<int,bool> visited;
    for (auto node:adjList) {                      //iterate all node as a base one by one (for disconnected components )
        if(!visited[node.first]){                                          //if base is not visited :: call bfs
            vector<int> components;
            dfs(adjList,visited,components,node.first);
            visitedSeq.push_back(components);
        }

    }
    return visitedSeq;
}


//7. DFS (using recursion)

void dfsRecursion(unordered_map<int, list<int>> &adjList,unordered_map<int,bool> &visited,vector<int> &component,int source){
    component.push_back(source);                  //push base in the component
    visited[source] = true;

    for (auto neighbour:adjList[source]) {
        if(!visited[neighbour]){
            dfsRecursion(adjList,visited,component,neighbour);
        }
    }
}
vector<vector<int>> DFSrecursion(unordered_map<int, list<int>> &adjList){
    vector<vector<int>> visitedSeq;
    unordered_map<int,bool> visited;
    for (auto node:adjList) {
        if(!visited[node.first]){
            vector<int> component;                                          //every node works as a component
            dfsRecursion(adjList,visited,component,node.first);     //call dfs for it
            visitedSeq.push_back(component);
        }
    }
    return visitedSeq;                      //return visited sequence
}

//8. Check cycle (BFS)

bool checkCycleBFSSolve(unordered_map<int, list<int>> &adjList,unordered_map<int,bool> &visited,int source){

    unordered_map<int,int> parent;          //track every node's parent  <son,parent>

    queue<int> q;
    q.push(source);                     //push source in queue
    visited[source] = true;              //make it as visited
    parent[source]=-1;                 //source node have not any parent :: -1 assign

    while (!q.empty()){
        int frontNode=q.front();            //take element one by one
        q.pop();

        for (auto neighbour:adjList[frontNode]) {                   //traverse all neighbour(adjacent) of frontNode
            if(!visited[neighbour]){                                      //if adjacent is not visited :: make it as visited and <son: adjacent, parent: frontNode>
                q.push(neighbour);                          //Insert into queue
                visited[neighbour] = true;
                parent[neighbour]=frontNode;
            }
            else if(parent[frontNode]!=neighbour){          //{if adjacent are already visited} and {it is not parent of that adjacent}
                return true;
            }
        }
    }
    return false;
}
bool checkCycleBFS(unordered_map<int, list<int>> &adjList){
    unordered_map<int,bool> visited;
    for (auto node:adjList) {
        if(!visited[node.first]) {
            if (checkCycleBFSSolve(adjList, visited, node.first)) {            //If there is a cycle :: return true
                return true;
            }
        }
    }
    return false;

}

//9. Check cycle (DFS)

bool checkCycleDFSSolve(unordered_map<int, list<int>> &adjList,unordered_map<int,bool> &visited,int parent,int source){
    visited[source] = true;                              //make source node as visited

    for (auto neighbour:adjList[source]) {                  //traverse all adjacent of source node
        if(!visited[neighbour]){                                   //if adjacent is not visited
            bool cycle= checkCycleDFSSolve(adjList,visited,source,neighbour);         //recursively call DFS-function  :: {node: adjacent} and {parent: node}
            if(cycle){
                return true;
            }
        }
        else if(parent != neighbour){                   //if adjacent is visited and is not child of parent  :: cycle has
            return true;
        }
    }
    return false;                                   //not found any cycle

}
bool checkCycleDFS(unordered_map<int, list<int>> &adjList){
    unordered_map<int,bool> visited;
    for (auto node:adjList) {                             //node is:: i and parent of source node is:: -1
        if(!visited[node.first]){
            if(checkCycleDFSSolve(adjList,visited,-1,node.first)){      //if there is a cycle :: return true
                return true;
            }
        }
    }
    return false;
}

//10. Check cycle in Directed Graph (DFS)
bool checkCycleDirectedDFSSolve(unordered_map<int, list<int>> &adjList,unordered_map<int,bool> &visited,unordered_map<int,bool> &dfsVisited,int source){
    visited[source] = true;
    dfsVisited[source] = true;                      //if call DFS-function :: make dfsVisited as true

    for (auto neighbour:adjList[source]) {
        if(!visited[neighbour]){                                                                //if adjacent is not visited
            bool cycle =  checkCycleDirectedDFSSolve(adjList,visited, dfsVisited,neighbour);    //recursively call DFS-function  :: {node: adjacent} and {parent: node}
            if(cycle){
                return true;
            }
        }
        else if(dfsVisited[neighbour]){                      //if the {neighbour node is visited} and {its dfsvisited[neighbour] is true}  :: cycle have
            return true;
        }
    }
    dfsVisited[source]= false;              //if the {neighbour node is visited} and {its dfsvisited[neighbour] is false}  :: make dfsVisited[source] as false(untrue)
    return false;
}
bool checkCycleDirectedDFS(unordered_map<int, list<int>> &adjList){
    unordered_map<int,bool> visited;
    unordered_map<int,bool> dfsVisited;
    for (auto node:adjList) {
        if(!visited[node.first]){
            bool cycle= checkCycleDirectedDFSSolve(adjList,visited,dfsVisited,node.first);
            if(cycle){
                return true;
            }
        }
    }
    return false;
}


//11. Check cycle in Directed Graph (BFS && Kahn's Algorithm)

bool checkCycleDirectedBFSKhansAlgo(unordered_map<int, list<int>> &adjList){
    unordered_map<int,int> indegree;                    //indegree map
    for (auto node:adjList) {            //find all indegree
        indegree[node.first];
        for (auto adj:node.second) {
            indegree[adj]++;
        }
    }

    queue<int> q;
    for (auto i:indegree) {              //take all vertex
        if(i.second==0){                           //if any vertex indegree is 0 :: push it into queue
            q.push(i.first);
        }
    }

    int count=0;
    while (!q.empty()){
        int frontNode=q.front();            //take element from queue
        q.pop();

        count++;

        for (auto neighbour:adjList[frontNode]) {       //traverse its neighbour
            indegree[neighbour]--;                         //decrease their indegree
            if(indegree[neighbour]==0){                      //if any neighbour's indegree is 0 :: push it into queue
                q.push(neighbour);
            }
        }
    }

    if(count==adjList.size()){
        return false;
    }
    return true;
}

//12. Topological Sort (using DFS)

void topologicalSortDFS(unordered_map<int, list<int>> &adjList,unordered_map<int,bool> &visited,stack<int> &st,int source){
    visited[source]= true;

    for (auto neighbour:adjList[source]) {
        if(!visited[neighbour]){
            topologicalSortDFS(adjList,visited,st,neighbour);
        }
    }
    st.push(source);
}

vector<int> topologicalSort(unordered_map<int, list<int>> &adjList){
    unordered_map<int,bool> visited;
    stack<int> st;
    for (auto node:adjList) {
        if(!visited[node.first]){
            topologicalSortDFS(adjList,visited,st,node.first);
        }
    }

    vector<int> topoSorted;
    while (!st.empty()){
        topoSorted.push_back(st.top());
        st.pop();
    }
    return topoSorted;
}

//13. Topological Sort (Kahn's Algorithm)

vector<int> topologicalSortKhansAlgo(unordered_map<int, list<int>> &adjList){
    unordered_map<int,int> indegree;
    for (auto node:adjList) {
        indegree[node.first];
        for (auto adj:node.second) {
            indegree[adj]++;
        }
    }

    queue<int> q;
    for (auto i:indegree) {
        if(i.second==0){
            q.push(i.first);
        }
    }

    vector<int> topoSortedList;
    while (!q.empty()){
        int frontNode=q.front();
        q.pop();

        topoSortedList.push_back(frontNode);                    //insert into topological sorted list

        for (auto neighbour:adjList[frontNode]) {
            indegree[neighbour]--;
            if(indegree[neighbour]==0){
                q.push(neighbour);
            }
        }
    }

    return topoSortedList;                      //return :: topologically sorted list
}

//14. Shortest path in undirected graph

vector<int> shortedPathUndirectedGph(unordered_map<int, list<int>> &adjList,int src,int dest){
    unordered_map<int,bool> visited;                 //make a visited
    unordered_map<int,int> parent;                   //map its parent list

    queue<int> q;
    q.push(src);                       //push source into queue
    visited[src] = true;                  //make it is visited
    parent[src] = -1;                      //make source parent as -1

    while (!q.empty()){
        int frontNode=q.front();             //take element from queue
        q.pop();

        for (auto neighbour:adjList[frontNode]) {        //traverse its adjacent
            if(!visited[neighbour]){                       //if it is not visited::
                q.push(neighbour);                           //push it into queue
                visited[neighbour] = true;                     //make it visited
                parent[neighbour] = frontNode;                   //make frontNode as a parent of adjacent
            }
        }
    }

    vector<int> shortestPath;
    int currNode=dest;
    shortestPath.push_back(currNode);            //insert destination::  into shortest path
    while (currNode!=src){                  //while it comes to source :: traverse
        currNode=parent[currNode];            //currentNode will come parent of present node
        shortestPath.push_back(currNode);        //insert into shortest path
    }
    reverse(shortestPath.begin(), shortestPath.end());       //reverse :: make vector from source to destination
    return shortestPath;
}

//15. Shortest path distance in undirected graph
int shortedPathDistacneUndirGph(unordered_map<int, list<int>> &adjList,int src,int dest){
    unordered_map<int,bool> visited;                 //make a visited
    unordered_map<int,int> parent;                   //map its parent list

    queue<int> q;
    q.push(src);                       //push source into queue
    visited[src] = true;                  //make it is visited
    parent[src] = -1;                      //make source parent as -1

    while (!q.empty()){
        int frontNode=q.front();             //take element from queue
        q.pop();

        for (auto neighbour:adjList[frontNode]) {        //traverse its adjacent
            if(!visited[neighbour]){                       //if it is not visited::
                q.push(neighbour);                           //push it into queue
                visited[neighbour] = true;                      //make it visited
                parent[neighbour] = frontNode;                   //make frontNode as a parent of adjacent
            }
        }
    }


    int currNode=dest;
    int distance=0;
    while (currNode!=src){                 //while it comes to source :: traverse
        currNode=parent[currNode];            //currentNode will come parent of present node
        distance++;
    }

    return distance;
}


//16. Shortest distance form source to all node (weighted DAG)
void shortDistDFS(unordered_map<int, list<pair<int,int>>> &adjList,unordered_map<int,bool> &visited,stack<int> &st,int source){
    visited[source] = true;                                      //make visited of base(source) as true
    for (auto neighbour:adjList[source]) {          //traverse it's neighbour(pair of node and weight)
        if(!visited[neighbour.first]){                               //if its node(first of pair) is not visited
            shortDistDFS(adjList,visited,st,neighbour.first);     //recursively traver traverse its neighbour
        }
    }
    st.push(source);                                     //make dfs order(topologically) into the stack
}

unordered_map<int,int> shortestDistanceFromSrcToAll(unordered_map<int, list<pair<int,int>>> &adjList,int src){
    unordered_map<int,bool> visited;
    stack<int> st;                               //for getting topological sorted list into the stack

    for (auto node:adjList) {
        if(!visited[node.first]){                              //if adjList member is not visited  :: call dfs for base(source)
            shortDistDFS(adjList,visited,st,node.first);
        }
    }

    unordered_map<int,int> distance;               //distance calculate vector from (source node) to (rest of the node)
    for (auto node:adjList) {
        distance[node.first] = INT_MAX;           //make vector full of infinity(INT_MAX) value
    }

    distance[src]=0;                             //distance to source is zero

    while (!st.empty()){
        int topVal=st.top();                     //getting element from topologically sorted stack one by one as :: topNode
        st.pop();
        if(distance[topVal]!=INT_MAX){                   //if distance between source to topNode is not infinity
            for (auto neighbour:adjList[topVal]) {                  //get topNode's neighbour
                distance[neighbour.first] = min(distance[neighbour.first],distance[topVal] + neighbour.second);      //if sum of[distance of topNode(as parent)] and [weight of neighbour] is less than [distance of neighbour]
                //[distance of neighbour] will become sum of [distance of topNode(as parent)] and [weight of neighbour]
            }
        }
    }
    return distance;         //return :: distance vector
}


//17.  Shortest distance form source to all node (weighted) (Dijkstra Algorithm)
unordered_map<int,int> dijkstraAlgoShortPathDistance(unordered_map<int, list<pair<int,int>>> &adjList,int src){
    unordered_map<int,int> distance;               //distance calculate vector from (source node) to (rest of the node)
    for (auto node:adjList) {
        distance[node.first]=INT_MAX;              //make vector full of infinity(INT_MAX) value
    }

    distance[src]=0;                             //distance to source is zero

    set<pair<int,int>> setOfPair;                     //create a set of pair<distance From Source, value of node>
    setOfPair.insert(make_pair(0,src));        //distance:: source to source is 0  ,value:: source

    while (!setOfPair.empty()){                             //until setOfPair(sop) is empty
        auto topNode=*(setOfPair.begin());       //get pair with minimum distance from source in set(return minimum)
        setOfPair.erase(setOfPair.begin());

        int topNodeDistance = topNode.first;             //pair's distance
        int topNodeVal=topNode.second;          //pair's node value

        for (auto neighbour:adjList[topNodeVal]) {                  //tarverse it's adjacent
            if(topNodeDistance + neighbour.second < distance[neighbour.first]){          //if sum of[distance of topNode(as parent)] and [weight of neighbour] is less than [distance of neighbour]

                auto prevRecord = setOfPair.find(make_pair(distance[neighbour.first],neighbour.first)); //if a copy of neighbour is already exist in the setOfPair :: catch in the record
                if(prevRecord!=setOfPair.end()){                    //if record exist
                    setOfPair.erase(prevRecord);           //remove from the setOfPair
                }

                distance[neighbour.first] = topNodeDistance + neighbour.second;        //update neighbour's distance with sum of it's minimum value
                setOfPair.insert(make_pair(distance[neighbour.first],neighbour.first));      //insert into the setOfPair with updated distance value
            }
        }
    }
    return distance;         //return distance vevtor
}


//18. Shortest path in weighted graph with negative edge (Bellmon Ford Algorithm)

int bellmonFordShortestPath(vector<vector<int>> &edges,int vertex,int src,int dest){
    vector<int> distance(vertex+1,INT_MAX);
    distance[src]=0;

    for (int i = 0; i < vertex; ++i) {                 //Do the work for n timers ::
        for (int j = 0; j < edges.size(); ++j) {           //get [from and to and weight]  edge-by-edge
            int from=edges[j][0];
            int to=edges[j][1];
            int weight = edges[j][2];


            if(distance[from]!=INT_MAX && (distance[from] + weight < distance[to])){   //if summation of( distance of from and weight)  is less than distance of to
                distance[to] = distance[from] + weight;                                           //assign the minimum distance (better way to move)
            }
        }
    }

    bool flag= false;
    for (int j = 0; j < edges.size(); ++j) {           //Do the same work another time ::
        int from=edges[j][0];
        int to=edges[j][1];
        int weight = edges[j][2];


        if(distance[from]!=INT_MAX && (distance[from] + weight < distance[to])){
            //distance[to] = distance[from] + weight;
            flag= true;                                                 //if any change occur :: there is a negative cycle (meaning infinity cycle)
            break;
        }
    }
    if(!flag){                           //if flag is false
        return distance[dest];
    }
    return -1;                                  //true

}


//19. Floyd-Warshal Shortest path between all node of pair

void floydWarshalShortestPath(vector<vector<int>> &adjMatrix){
    int vertex=adjMatrix.size();
    for (int k = 0; k < vertex; ++k) {
        for (int i = 0; i < vertex; ++i) {
            for (int j = 0; j < vertex; ++j) {
                if(adjMatrix[i][k]!=INT_MAX && adjMatrix[k][j]!=INT_MAX)
                    adjMatrix[i][j] = min(adjMatrix[i][j],adjMatrix[i][k]+adjMatrix[k][j]);
            }
        }
    }
}



//20. Minimum Spanning Tree (Prim's Algorithm)

vector<pair<pair<int,int>,int>> MSTbyPrimsAlgo(unordered_map<int, list<pair<int,int>>> &adjList){
    int vertex=adjList.size();

    vector<int> key(vertex+1,INT_MAX);         //for calculation of weight
    vector<bool> mst(vertex+1, false);         //for tracking all node as true in mst
    vector<int> parent(vertex+1,-1);        //track their parent
    //parent is -1

    key[1]=0;                       //let start from 0th node ::   weight is 0



    for (int i = 1; i < vertex; ++i) {                //traverse for every node
        int minikey=INT_MAX;                        //mini:: INT_MAX
        int from;                                  //for a edge::   from--->to

        for (int ver = 1; ver <= vertex; ++ver) {             //finding minimum from the key vector(if it will be minimum, mst is false for that vertex)
            if(key[ver]<minikey && !mst[ver]){
                minikey=key[ver];                        //mini is minimumKeyValue
                from=ver;                              //from:: is the vertex for minimumKeyValue
            }
        }

        mst[from] =true;                  //mst will become true for that vertex

        for (auto neighbour:adjList[from]) {       //traverse it's neighbour pair
            int to=neighbour.first;                        //to:: from's   neighbour           :: neighbour <to,weight>
            int weight = neighbour.second;                     //weight of (from-->to)

            if(!mst[to] && weight<key[to]){            //weight of neighbour is less than  minimumKeyValue of neighbour
                parent[to]=from;                               //parent of neighbour is from
                key[to]=weight;                               //keyValue of neighbour is weight of (from-->to)
            }
        }

    }

    vector<pair<pair<int,int>,int>> ans;               //convert into from--to--weight format
    for (int i = 2; i <= vertex ; ++i) {
        ans.push_back({{parent[i],i},key[i]});
    }
    return ans;

}

//21. Minimum Spanning Tree (Kruskal Algorithm) (disjoint set)

void makeSet(vector<int> &parent,vector<int> &rank,int v){
    for (int i = 0; i <= v; ++i) {
        parent[i]=i;                      //initially parent of each value is himself
        rank[i]=0;                        //rank is zero
    }
}

int findParent(vector<int> &parent,int node){
    if(parent[node]==node){                   //base :  recursive traverse ends until root(captain) is found :: value's parent is himself
        return node;                          //return his own value
    }
    return parent[node]= findParent(parent,parent[node]);       //get him parent value   and direct connect to root
}

void unionSet(int u,int v,vector<int> &parent,vector<int> &rank){
    u= findParent(parent,u);                //find one value's parent as u
    v= findParent(parent,v);                 //find another value's parent as v
    if(rank[u]<rank[v]){                      //change parent of minimum ranked value  (by more ranked value)
        parent[u]=v;
    }
    else if(rank[v]<rank[u]){
        parent[v]=u;
    }
    else{                    //if both are same  :: change parent any of them by another(here it is maximum) :: and increase another one's rank
        parent[u]=v;            //also, parent[v]=u;  rank[u]++;
        (rank[v])++;
    }
}

bool cmp(vector<int> &p1,vector<int> &p2){        //comparator for sorting in descending order by weight
    return p1[2] < p2[2];
}

vector<pair<pair<int,int>,int>> MSTbyKruskalAlgo(vector<vector<int>> &edges,int vertex){
    sort(edges.begin(), edges.end(), cmp);           //sort edges's list in descending order by weight

    vector<int> parent(vertex);             //vector for tracking very vertex's parent
    vector<int> rank(vertex);               //vector for tracking rank of every vertex

    makeSet(parent,rank,vertex);          //make these vector initialize

                    //for calculation minimum weight of the spanning tree

    vector<pair<pair<int,int>,int>> ans;


    for (int i = 0; i < edges.size(); ++i) {            //traverse every edge's one by one
        int u= findParent(parent,edges[i][0]);      //find from's parent
        int v= findParent(parent,edges[i][1]);       //find to's parent

        int weight = edges[i][2];                 //weight of every edge




        if(u!=v){                             //if parent of from and parent of to doesn't match ::
            unionSet(u,v,parent,rank);        //Do union of u and v
            ans.push_back({{u, v}, weight});                  //sum it's weight
        }
        //if match:: ignore step
    }
    return ans;
}





//22. Finding Bridge

void findingBridgeDFS(unordered_map<int,list<int>> &adjList,unordered_map<int,bool> &visited,vector<int> &disc,vector<int> &low,vector<vector<int>> &bridges,int &timer,int parent,int source){
    visited[source] = true;                  //make node's visited as true
    disc[source] = low[source] = timer++;          //firstly :: discovery time and lowest discovery time both are (time++) {incremented value of time}

    for (auto neighbour:adjList[source]) {                     //traverse it's neighbour
        if(neighbour==parent){                                 //in backtracking time :: if neighbour is parent :: skip step
            continue;
        }

        if(!visited[neighbour]){                                                     //if neighbour is not visited
            findingBridgeDFS(adjList,visited,disc,low,bridges,timer,source,neighbour);    //call dfs for neighbour
            low[source] = min(low[source],low[neighbour]);                      //came back from recursive call :: lowestDiscoveryTime will update by minimum of(lowestDiscoveryTime of neighbour , lowestDiscoveryTime)
            //because:: it is possible to this node's neighbour(child) have back-edge(another way to reach) :: so get lowest discovery time from its neighbour
            if(low[neighbour] > disc[source]){                          //if lowestDiscoveryTime of neighbour is greater than discovery time  :: there is a bridge  ::
                vector<int> oneBridge;
                oneBridge.push_back(source);                         //between node and neighbour  :: make a vector of edge
                oneBridge.push_back(neighbour);
                bridges.push_back(oneBridge);                      //push it into the result
            }
        }
        else{                                                   //if neighbour is visited :: there is possibility of having back-edge(another way to reach that node)
            low[source] = min(low[source],disc[neighbour]);            //if back-edge have:: lowestDiscoveryTime will become minimum of (discovery time of neighbour, lowestDiscoveryTime)
        }
    }

}

vector<vector<int>> findingBridge(unordered_map<int,list<int>> &adjList){
    int vertex=adjList.size();

    vector<int> disc(vertex,-1);    //for counting vertex's discovery time
    //initially discovery time is -1
    vector<int> low(vertex,-1);     //for counting vertex's lowest discovery time
    //lowest discovery time is -1
    unordered_map<int,bool> visited;     //track vertex is visited

    vector<vector<int>> bridges;             //vector is bridge (edges)
    int timer=0;                          //starting timer from 0

    for (auto node:adjList) {
        if(!visited[node.first]){                                               //if not visited  :: do dfs
            findingBridgeDFS(adjList,visited,disc,low,bridges,timer,-1,node.first);
            //starting node's parent -1
        }
    }
    return bridges;
}

//23. Finding Articulation Point

void findingArticulationPointDFS(unordered_map<int,list<int>> &adjList,unordered_map<int,bool> &visited,vector<int> &disc,vector<int> &low,vector<bool> &articulationPoint,int &timer,int parent,int source){
    visited[source] = true;

    disc[source] = low[source] = timer++;

    int child=0;

    for (auto neighbour:adjList[source]) {
        if(neighbour==parent){
            continue;
        }

        if(!visited[neighbour]){
            findingArticulationPointDFS(adjList,visited,disc,low,articulationPoint,timer,source,neighbour);
            low[source] = min(low[source] , low[neighbour]);

            if(low[neighbour] >= disc[source] && parent!=-1){                           //if lowestDiscoverTime of neighbour is greater than or equal discoveryTime of node  && this is not parent(starting index)
                articulationPoint[source]= true;                  //this point is discovery node :: make it true
            }

            child++;                           //counting child of parent(starting node)

        }
        else{
            low[source] = min(low[source] , disc[neighbour]);
        }
    }

    if(parent!=-1 && child>1){                      //if parent has more than one child :: this also a articulation point
        articulationPoint[source]= true;
    }
}

vector<bool> findingArticulationPoint(unordered_map<int,list<int>> &adjList){
    int vertex = adjList.size();
    vector<int> disc(vertex,-1);
    vector<int> low(vertex,-1);

    unordered_map<int,bool> visited;

    vector<bool> articulationPoint(vertex, false);
    int timer=0;

    for (auto node:adjList) {
        if(!visited[node.first]){
            findingArticulationPointDFS(adjList,visited,disc,low,articulationPoint,timer,-1,node.first);
        }
    }
    return articulationPoint;

}

//24. Number of Strongly Connected Components (Kosaraju Algorithm)

void strongConCompoKosarajuDFS(unordered_map<int,list<int>> &adjList,unordered_map<int,bool> &visited,stack<int> &st,int source){
    visited[source] = true;                                    //make as visited
    for (auto neighbour:adjList[source]) {                        //traverse it's neighbour
        if(!visited[neighbour]){                                    //if not visited
            strongConCompoKosarajuDFS(adjList,visited,st,neighbour);              //call dfs for neighbour and get topological order sort
        }
    }
    st.push(source);                                     //into the stack
}

void strongConCompoKosarajuRevDFS(unordered_map<int,list<int>> &adjList,unordered_map<int,bool> &visited,int source){
    visited[source] = true;                           //make as visited
    for (auto neighbour:adjList[source]) {            //traverse it's neighbour
        if(!visited[neighbour]){                          //if not visited
            strongConCompoKosarajuRevDFS(adjList,visited,neighbour);       //call dfs for neighbour
        }
    }
}

int stronglyConnectedComponentsKosaraju(unordered_map<int,list<int>> &adjList){
    unordered_map<int,bool> visited;
    stack<int> st;
    for (auto node:adjList) {
        if(!visited[node.first]){
            strongConCompoKosarajuDFS(adjList,visited,st,node.first);     //get topological order into the stack
        }
    }

    unordered_map<int,list<int>> revAdjList;           //change every direction of directed graph


    for (auto node:adjList) {
        visited[node.first]= false;                            //make visited false again
        revAdjList[node.first];
        for (auto neighbour:node.second) {          //traverse neighbour
            revAdjList[neighbour].push_back(node.first);       //neighbour's adjacent is current node
        }
    }



    int componentNumber=0;           //for counting components
    while (!st.empty()){               //until stack is empty
        int topNode=st.top();           //take element from topologically sorted stack
        st.pop();

        if(!visited[topNode]){
            componentNumber++;                                 //increasing components number
            strongConCompoKosarajuRevDFS(revAdjList,visited,topNode);   //reverserDFS (dfs without stack) for transposeDirectedGraph
        }
    }
    return componentNumber;                  //return it
}

//25. Strongly Connected Components List (Kosaraju Algorithm)


void strongConCompoListKosarajuRevDFS(unordered_map<int,list<int>> &adjList,unordered_map<int,bool> &visited,vector<int> &oneComponent,int source){
    visited[source] = true;
    oneComponent.push_back(source);                     //insert into a component

    for (auto neighbour:adjList[source]) {
        if(!visited[neighbour]){
            strongConCompoListKosarajuRevDFS(adjList,visited,oneComponent,neighbour);
        }
    }
}

vector<vector<int>> stronglyConnectedComponentsListKosaraju(unordered_map<int,list<int>> &adjList){
    unordered_map<int,bool> visited;
    stack<int> st;
    for (auto node:adjList) {
        if(!visited[node.first]){
            strongConCompoKosarajuDFS(adjList,visited,st,node.first);     //get topological order into the stack
        }
    }

    unordered_map<int,list<int>> revAdjList;           //change every direction of directed graph


    for (auto node:adjList) {
        visited[node.first]= false;                            //make visited false again
        revAdjList[node.first];
        for (auto neighbour:node.second) {          //traverse neighbour
            revAdjList[neighbour].push_back(node.first);       //neighbour's adjacent is current node
        }
    }



    vector<vector<int>> components;                             //vector of strongly connected components

    while (!st.empty()){               //until stack is empty
        int topNode=st.top();           //take element from topologically sorted stack
        st.pop();

        if(!visited[topNode]){
            vector<int> oneComponent;                  //for a single strongly connected component
            strongConCompoListKosarajuRevDFS(revAdjList,visited,oneComponent,topNode);      //reverserDFS (dfs without stack) for transposeDirectedGraph
            components.push_back(oneComponent);           //make a list of strongly connected components
        }
    }
    return components;
}





int main(){

    Graph undiretedGraph1;
    undiretedGraph1.addEdge(0,1, false);
    undiretedGraph1.addEdge(0,2, false);
    undiretedGraph1.addEdge(0,7, false);
    undiretedGraph1.addEdge(1,4, false);
    undiretedGraph1.addEdge(2,4, false);
    undiretedGraph1.addEdge(2,3, false);
    undiretedGraph1.addEdge(7,6, false);
    undiretedGraph1.addEdge(3,5, false);
    undiretedGraph1.addEdge(3,6, false);


    Graph directedGraph1;
    directedGraph1.addEdge(1,0, true);
    directedGraph1.addEdge(2,1, true);
    directedGraph1.addEdge(0,2, true);
    directedGraph1.addEdge(0,3, true);
    directedGraph1.addEdge(3,4, true);
    directedGraph1.addEdge(4,0, true);


    Graph disconnectedGraph;
    disconnectedGraph.addEdge(0,1, false);
    disconnectedGraph.addEdge(0,2, false);
    disconnectedGraph.addEdge(1,2, false);
    disconnectedGraph.addEdge(1,3, false);
    disconnectedGraph.addEdge(2,3, false);
    disconnectedGraph.addEdge(4,5, false);
    disconnectedGraph.addEdge(4,6, false);


    Graph undirectedGraph2;
    undirectedGraph2.addEdge(4,1, false);
    undirectedGraph2.addEdge(4,2, false);
    undirectedGraph2.addEdge(4,3, false);
    undirectedGraph2.addEdge(4,5, false);
    undirectedGraph2.addEdge(5,6, false);

    Graph directedAcyclicGraph;
    directedAcyclicGraph.addEdge(1,2, true);
    directedAcyclicGraph.addEdge(1,3, true);
    directedAcyclicGraph.addEdge(2,4, true);
    directedAcyclicGraph.addEdge(2,5, true);
    directedAcyclicGraph.addEdge(3,6, true);
    directedAcyclicGraph.addEdge(4,7, true);
    directedAcyclicGraph.addEdge(5,7, true);
    directedAcyclicGraph.addEdge(6,5, true);
    directedAcyclicGraph.addEdge(6,7, true);
//
//
    WeiGraph weightedDirectedAcyclicGraph;
    weightedDirectedAcyclicGraph.addEdge(0,1,5, true);
    weightedDirectedAcyclicGraph.addEdge(0,2,3, true);
    weightedDirectedAcyclicGraph.addEdge(1,2,2, true);
    weightedDirectedAcyclicGraph.addEdge(1,3,6, true);
    weightedDirectedAcyclicGraph.addEdge(2,3,7, true);
    weightedDirectedAcyclicGraph.addEdge(3,4,-1, true);
    weightedDirectedAcyclicGraph.addEdge(2,4,4, true);
    weightedDirectedAcyclicGraph.addEdge(2,5,2, true);
    weightedDirectedAcyclicGraph.addEdge(4,5,-2, true);
//
    WeiGraph weightedGraph1;
    weightedGraph1.addEdge(2,1,3,false);
    weightedGraph1.addEdge(2,0,1,false);
    weightedGraph1.addEdge(1,0,7,false);
    weightedGraph1.addEdge(1,4,1,false);
    weightedGraph1.addEdge(1,3,5,false);
    weightedGraph1.addEdge(0,3,2,false);
    weightedGraph1.addEdge(3,4,7,false);

    WeiGraph weightedGraph2NegativeEdge;
    weightedGraph2NegativeEdge.addEdge(1,2,4,true);
    weightedGraph2NegativeEdge.addEdge(1,3,3,true);
    weightedGraph2NegativeEdge.addEdge(2,4,7,true);
    weightedGraph2NegativeEdge.addEdge(3,4,-2,true);

    WeiGraph weightedGraph3NegativeCycle;
    weightedGraph3NegativeCycle.addEdge(0,2,-2, true);
    weightedGraph3NegativeCycle.addEdge(2,3,2, true);
    weightedGraph3NegativeCycle.addEdge(3,1,-1, true);
    weightedGraph3NegativeCycle.addEdge(1,2,-3, true);
    weightedGraph3NegativeCycle.addEdge(1,0,4, true);


    WeiGraph weightedGraph4;
    weightedGraph4.addEdge(5,4,9, false);
    weightedGraph4.addEdge(5,1,4, false);
    weightedGraph4.addEdge(4,1,1, false);
    weightedGraph4.addEdge(4,3,5, false);
    weightedGraph4.addEdge(1,2,2, false);
    weightedGraph4.addEdge(4,2,3, false);
    weightedGraph4.addEdge(3,2,3, false);
    weightedGraph4.addEdge(3,6,8, false);
    weightedGraph4.addEdge(2,6,7, false);



    Graph bridgeGraph;
    bridgeGraph.addEdge(0,1, false);
    bridgeGraph.addEdge(0,2, false);
    bridgeGraph.addEdge(1,2, false);
    bridgeGraph.addEdge(2,5, false);
    bridgeGraph.addEdge(2,3, false);
    bridgeGraph.addEdge(3,4, false);
    bridgeGraph.addEdge(5,6, false);
    bridgeGraph.addEdge(6,7, false);
    bridgeGraph.addEdge(7,8, false);
    bridgeGraph.addEdge(5,8, false);

    Graph stronglyConnComponents;
    stronglyConnComponents.addEdge(3,0,true);
    stronglyConnComponents.addEdge(0,1,true);
    stronglyConnComponents.addEdge(1,2,true);
    stronglyConnComponents.addEdge(2,3,true);
    stronglyConnComponents.addEdge(2,4,true);
    stronglyConnComponents.addEdge(4,5,true);
    stronglyConnComponents.addEdge(5,6,true);
    stronglyConnComponents.addEdge(6,4,true);
    stronglyConnComponents.addEdge(6,7,true);



    unordered_map<int,int> umap;
    vector<int> v;
    vector<vector<int>> vv;
    int choice,data1,data2,data3,data4;
    bool select;
    cout<<"Choice:";
    cin>>choice;
    while (choice){
        switch (choice) {
            case 1:{
                cout<<"From:";
                cin>>data1;
                cout<<"To:";
                cin>>data2;
                cout<<"Direction:(0==undirected || 1==directed)";
                cin>>select;
                undiretedGraph1.addEdge(data1,data2,select);
                break;
            }
            case 2:{
                undiretedGraph1.printAdjList();
                cout<<endl;
                break;
            }
            case 3:{
                cout<<"From:";
                cin>>data1;
                cout<<"To:";
                cin>>data2;
                cout<<"Weight:";
                cin>>data3;
                cout<<"Direction:(0==undirected || 1==directed)";
                cin>>select;
                weightedGraph1.addEdge(data1,data2,data3,select);
                break;
            }
            case 4:{
                weightedGraph1.printAdjList();
                cout<<endl;
                break;
            }
            case 5:{
                vv= BFS(undiretedGraph1.adjList);
                printVectorOfVector(vv);
                break;
            }
            case 6:{
                vv= DFS(undiretedGraph1.adjList);
                printVectorOfVector(vv);
                break;
            }
            case 7:{
                vv= DFSrecursion(disconnectedGraph.adjList);
                printVectorOfVector(vv);
                break;
            }
            case 8:{
                cout<<checkCycleBFS(undirectedGraph2.adjList)<<endl;
                break;
            }
            case 9:{
                cout<<checkCycleDFS(undiretedGraph1.adjList)<<endl;
                cout<<checkCycleDFS(undirectedGraph2.adjList)<<endl;
                break;
            }
            case 10:{
                cout<<checkCycleDirectedDFS(directedGraph1.adjList)<<endl;
                cout<<checkCycleDirectedDFS(directedAcyclicGraph.adjList)<<endl;
                break;
            }
            case 11:{
                cout<<checkCycleDirectedBFSKhansAlgo(directedGraph1.adjList)<<endl;
                cout<<checkCycleDirectedBFSKhansAlgo(directedAcyclicGraph.adjList)<<endl;
                break;
            }
            case 12:{
                v= topologicalSort(directedAcyclicGraph.adjList);
                printVector(v);
                break;
            }
            case 13:{
                v= topologicalSortKhansAlgo(directedAcyclicGraph.adjList);
                printVector(v);
                break;
            }
            case 14:{
                v= shortedPathUndirectedGph(undiretedGraph1.adjList,2,6);
                printVector(v);
                break;
            }
            case 15:{
               cout<<shortedPathDistacneUndirGph(undiretedGraph1.adjList,2,7)<<endl;
                break;
            }
            case 16:{
                umap= shortestDistanceFromSrcToAll(weightedDirectedAcyclicGraph.adjList,0);
                for (auto mapEle:umap) {
                    cout<<mapEle.first<<" -> "<<mapEle.second<<endl;
                }
                break;
            }
            case 17:{
                umap= dijkstraAlgoShortPathDistance(weightedGraph1.adjList,0);
                for (auto mapEle:umap) {
                    cout<<mapEle.first<<" -> "<<mapEle.second<<endl;
                }
                break;
            }


            case 18:{
                cout<<bellmonFordShortestPath(weightedGraph2NegativeEdge.edges,4,1,4)<<endl;
                cout<<bellmonFordShortestPath(weightedGraph3NegativeCycle.edges,4,0,2)<<endl;
                break;
            }

            case 19:{
                vector<vector<int>> adjMat=
                        {
                                {0,3,INT_MAX,7},
                                {8,0,2,INT_MAX},
                                {5,INT_MAX,0,1},
                                {2,INT_MAX,INT_MAX,0}
                        };
                floydWarshalShortestPath(adjMat);
                printAdjMatrix(adjMat);
                break;
                break;
            }

            case 20:{
                vector<pair<pair<int,int>,int>> ans= MSTbyPrimsAlgo(weightedGraph4.adjList);
                for (auto x:ans) {
                    cout<<x.first.first<<" "<<x.first.second<<" "<<x.second<<endl;
                }
                break;
            }
            case 21:{
                vector<pair<pair<int,int>,int>> ans= MSTbyKruskalAlgo(weightedGraph4.edges,6);
                for (auto x:ans) {
                    cout<<x.first.first<<" "<<x.first.second<<" "<<x.second<<endl;
                }
                break;
            }
            case 22:{
                vv= findingBridge(bridgeGraph.adjList);
                printVectorOfVector(vv);
                break;
            }
            case 23:{
                vector<bool> artiPoint=findingArticulationPoint(bridgeGraph.adjList);
                for (int i = 0; i < artiPoint.size(); ++i) {
                    if(artiPoint[i]){
                        cout<<i<<" ";
                    }
                }cout<<endl;
                break;
            }
            case 24:{
                cout<<stronglyConnectedComponentsKosaraju(stronglyConnComponents.adjList)<<endl;
                break;
            }
            case 25:{
                vv= stronglyConnectedComponentsListKosaraju(stronglyConnComponents.adjList);
                printVectorOfVector(vv);
                break;
            }


        }
        cout<<"Choice:";
        cin>>choice;
    }
}