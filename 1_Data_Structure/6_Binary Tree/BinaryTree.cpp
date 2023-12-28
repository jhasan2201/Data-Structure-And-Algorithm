#include "iostream"
#include "queue"
using namespace std;
class Node{
public:
    int data;
    Node *left;
    Node *right;
    Node(int num){
        data=num;
        left=NULL;
        right=NULL;
    }
};

//1. Preorder print of tree
void preorderPrint(Node *root){
    if(root==NULL){
        return;
    }
    cout<<root->data<<" ";
    preorderPrint(root->left);      //traverse left root
    preorderPrint(root->right);     //traverse right root
}

//2. Inorder print of tree
void inorderPrint(Node *root){
    if(root==NULL){
        return;
    }
    inorderPrint(root->left);       //traverse left root
    cout<<root->data<<" ";
    inorderPrint(root->right);      //traverse right root
}

//3. Postorder print of tree
void postorderPrint(Node *root){
    if(root==NULL){
        return;
    }
    postorderPrint(root->left);     //traverse left root
    postorderPrint(root->right);    //traverse right root
    cout<<root->data<<" ";
}

//4. Build tree from preorder and inorder array
int searchFromInorderArr(int inorder[],int start,int end,int key){
    for (int i = start; i <=end ; ++i) {        //linear search
        if(inorder[i]==key){
            return i;
        }
    }
    return -1;
}
Node* buildTreePreInorderArr(int preArr[],int inArr[],int start,int end){
    if(start>end){          //base case:: out of the array
        return NULL;
    }
    static int i=0;         //get element from preorder array
    int curr=preArr[i];
    i++;

    Node *temp=new Node(curr);      //create node

    if(start==end){            //leaf node:: return node to the back
        return temp;
    }

    int pos= searchFromInorderArr(inArr,start,end,curr);    //get index from inorder array
    temp->left= buildTreePreInorderArr(preArr,inArr,start,pos-1);   //build left subtree
    temp->right= buildTreePreInorderArr(preArr,inArr,pos+1,end);    //build right subtree
    return temp;
}

//5. Build tree from postorder and inorder array
Node* buildTreePostInorderArr(int postArr[],int inArr[],int start,int end){
    if(start>end){                      //base case:: out of the array
        return NULL;
    }
    static int i=end;                   //get element from reverse postorder array
    int curr=postArr[i];
    i--;

    Node *temp=new Node(curr);      //create node

    if(start==end){                     //leaf node:: return node to the back
        return temp;
    }

    int pos= searchFromInorderArr(inArr,start,end,curr);        //get index from inorder array

    temp->right= buildTreePostInorderArr(postArr,inArr,pos+1,end);      //build right subtree
    temp->left= buildTreePostInorderArr(postArr,inArr,start,pos-1);     //build left subtree
    return temp;
}

//6. Count no of nodes
int countNodes(Node *root){
    if(root==NULL){                 //base:: go back
        return 0;
    }
    return countNodes(root->left)+ countNodes(root->right)+1;   //1 for root
}

//7. Calculate height of tree
int calHeight(Node *root){
    if(root==NULL){                 //base::
        return 0;
    }
    int leftHeight= calHeight(root->left);       //get leftHeight
    int rightHeight= calHeight(root->right);     //get rightHeight
    return max(leftHeight,rightHeight)+1;                //1 for root
}

//8. Level order print of tree
void levelOrderPrint(Node *root){
    if(root==NULL){
        return;
    }
    queue<Node*> q;
    q.push(root);                  //push root:: q
    q.push(NULL);                 //after finishing level push a NULL
    while (!q.empty()){
        Node *temp=q.front();       //get node from queue
        q.pop();

        if(temp!=NULL){             //if temp if not NULL print data
            cout<<temp->data<<" ";
            if(temp->left!=NULL){           //temp have left subtree :: push it into queue
                q.push(temp->left);
            }
            if(temp->right!=NULL){          //temp have right subtree :: push it into queue
                q.push(temp->right);
            }
        }
        else if(!q.empty()){                //after finishing level :: push a NULL
            q.push(NULL);
        }
    }

}

//9. Print Kth level
void printAtKthLevel(Node *root,int k){
    if(root==NULL){
        return;
    }
    int level=0;
    queue<Node*> q;
    q.push(root);
    q.push(NULL);
    while (!q.empty()){
        Node *temp=q.front();
        q.pop();

        if(temp!=NULL){
            if(level==k){
                cout<<temp->data<<" ";
            }
            if(temp->left!=NULL){
                q.push(temp->left);
            }
            if(temp->right!=NULL){
                q.push(temp->right);
            }
        }
        else if(!q.empty()){
            q.push(NULL);
            level++;
        }
    }

}

//10. Sum of Kth level
int sumAtKthLevel(Node *root,int k){
    if(root==NULL){
        return 0;
    }
    int level=0,sum=0;
    queue<Node*> q;
    q.push(root);
    q.push(NULL);
    while (!q.empty()){
        Node *temp=q.front();
        q.pop();

        if(temp!=NULL){
            if(level==k){
                sum+=temp->data;
            }
            if(temp->left!=NULL){
                q.push(temp->left);
            }
            if(temp->right!=NULL){
                q.push(temp->right);
            }
        }
        else if(!q.empty()){
            q.push(NULL);
            level++;
        }
    }
    return sum;
}

//11. Every node with sum of its subtree
void sumOfAllSubTree(Node *root){
    if(root==NULL){
        return;
    }
    sumOfAllSubTree(root->left);        //staring from bottom (sequence doesnt matter)
    sumOfAllSubTree(root->right);

    if(root->left!=NULL){                   //if node have left subtree :: add to its parent
        (root->data)+=(root->left->data);
    }
    if(root->right!=NULL){                  //if node have right subtree :: add to its parent
        (root->data)+=(root->right->data);
    }
}

//12. Check the tree is balanced
bool checkIsBalanced(Node *root){
    if(root==NULL){                     //no node :: balanced
        return true;
    }
    if(checkIsBalanced(root->left)== false){        //if any moment it become false :: tree is not balanced
        return false;
    }
    if(checkIsBalanced(root->right)== false){
        return false;
    }

    int leftHeight=0,rightHeight=0;
    leftHeight= calHeight(root->left);      //get left Height
    rightHeight= calHeight(root->right);    //get right Height
    if(abs(leftHeight-rightHeight)<=1){         //if balanced::
        return true;
    }
    return false;
}

//13. Check the tree is balanced (with pointer pass)
bool checkIsBalanced(Node *root,int *height){
    if(root==NULL){
        return true;
    }
    int leftHeiPtr=0,rightHeiPtr=0;
    if(checkIsBalanced(root->left,&leftHeiPtr)== false){         //if any time left subtree is not balanced so the whole tree is not balanced
        return false;
    }
    if(checkIsBalanced(root->right,&rightHeiPtr)== false){
        return false;
    }
    *height=max(leftHeiPtr,rightHeiPtr)+1;                  //find height
    if(abs(leftHeiPtr-rightHeiPtr)<=1){                    //diff between left and right tree is <=1
        return true;
    }
    else {
        return false;
    }
}

//14. Right view of the tree
void rightViewOfTree(Node *root){
    if(root==NULL){
        return;
    }
    queue<Node*> q;
    q.push(root);
    while (!q.empty()){

        int widthOfEachLevel=q.size();                  //width of each level

        for (int i = 0; i < widthOfEachLevel; ++i) {
            Node *temp=q.front();
            q.pop();

            if(i==widthOfEachLevel-1){              //if right most node in a particular level
                cout<<temp->data<<" ";
            }
            if(temp->left!=NULL){                   //if node have left subtree push them
                q.push(temp->left);
            }
            if(temp->right!=NULL){                  //if node have right subtree push them
                q.push(temp->right);
            }
        }
    }
}

//15. Left view of the tree
void leftViewOfTree(Node *root){
    if(root==NULL){
        return;
    }
    queue<Node*> q;
    q.push(root);

    while (!q.empty()){
        int widthOfEachLevel=q.size();

        for (int i = 0; i < widthOfEachLevel; ++i) {
            Node *temp=q.front();
            q.pop();

            if(i==0){
                cout<<temp->data<<" ";
            }
            if(temp->left!=NULL){
                q.push(temp->left);
            }
            if(temp->right!=NULL){
                q.push(temp->right);
            }
        }
    }
}

//16. Calculate Diameter (maximum distance towards two node)
int calDiameter(Node *root){
    if(root==NULL){
        return 0;
    }
    int leftDiameter= calDiameter(root->left);             //calculate left diameter
    int rightDiameter= calDiameter(root->right);            //calculate right diameter

    int diameterByRoot= calHeight(root->left)+ calHeight(root->right)+1;        //diameter goes through root is left and right hight and (1 for root)

    return max(diameterByRoot, max(leftDiameter,rightDiameter));
}

//17. Calculate Diameter with pointer
int calDiameter(Node *root,int *height){
    if(root==NULL){
        return 0;
    }

    int leftHeight=0,rightHeight=0;
    int leftDiameter= calDiameter(root->left,&leftHeight);          //calculate left diameter
    int rightDiameter= calDiameter(root->right,&rightHeight);           //calculate right diameter

    int diameterByRoot=leftHeight+rightHeight+1;                //diameter goes through root is left and right hight and (1 for root)
    *height=max(leftHeight,rightHeight)+1;

    return max(diameterByRoot, max(leftDiameter,rightDiameter));
}

//18. Lowest Common Ancestor Finder
Node* lowestCommonAncestor(Node *root,int num1,int num2){
    if(root==NULL){
        return NULL;
    }

    if(root->data==num1 || root->data==num2){       //found one of them as a root
        return root;
    }

    Node *leftFinder= lowestCommonAncestor(root->left,num1,num2);
    Node *rightFinder= lowestCommonAncestor(root->right,num1,num2);

    if(leftFinder!=NULL && rightFinder!=NULL){          //both are root
        return root;
    }
    if(leftFinder==NULL && rightFinder==NULL){          //not found in the whole tree
        return NULL;
    }
    if(leftFinder!=NULL){       //rightFinder is NULL :: both lies in the leftSubTree
        return lowestCommonAncestor(root->left,num1,num2);
    }
    return lowestCommonAncestor(root->right,num1,num2);     //leftFinder is NULL :: both lies in the rightSubTree
}

//19. Distance between node to root
int distancedBetweenRoot(Node *root,int num,int distance){
    if(root==NULL){
        return -1;         //Not found:: return -1
    }

    if(root->data==num){        //if found:: return distance
        return distance;
    }

    int leftDistance= distancedBetweenRoot(root->left,num,distance+1);    //search in leftSubTree
    if(leftDistance!=-1){           //if found in left subtree (not -1)
        return leftDistance;
    }
    return distancedBetweenRoot(root->right,num,distance+1);            //search in rightSubTree
}

//20. Distance between two node
int distanceBetweenTwoNode(Node *root,int num1,int num2){
    Node *lca= lowestCommonAncestor(root,num1,num2);                   //their root is lowestCommonAncestor

    int distance1= distancedBetweenRoot(lca,num1,0);
    int distance2= distancedBetweenRoot(lca,num2,0);
    return distance1+distance2;
}

//21. Print Kth distance node in subtree
void subtreeKthDistanceNodePrint(Node *root,int k){
    if(root==NULL || k<0){          //this is not exist
        return;
    }
    if(k==0){
        cout<<root->data<<" ";
    }
    subtreeKthDistanceNodePrint(root->left,k-1);
    subtreeKthDistanceNodePrint(root->right,k-1);
}

//22. Find node from tree
Node* findNode(Node *root,int num){
    if(root==NULL){
        return NULL;
    }
    if(root->data==num){
        return root;
    }
    Node *leftFinder= findNode(root->left,num);
    if(leftFinder!=NULL){
        return leftFinder;
    }
    return findNode(root->right,num);

}

//23. Print kth distance nodes
int printKthDistanceNode(Node *root,int base,int k){
    if(root==NULL){                                   //Not found:: base
        return -1;
    }
    Node *baseNode= findNode(root,base);        //base number to convert baseNode from tree
    if(root==baseNode){                                //base node is root:: No option for going in Ancestor :: print its subtree node kth dis
        subtreeKthDistanceNodePrint(root,k);
        return 0;
    }

    int leftAncestorDistance= printKthDistanceNode(root->left,base,k);     //Go Left
    if(leftAncestorDistance!=-1){
        if(leftAncestorDistance+1==k){
            cout<<root->data<<" ";
        }
        else{
            subtreeKthDistanceNodePrint(root->right,k-2-leftAncestorDistance);
        }
        return 1+leftAncestorDistance;
    }

    int rightAncestorDistance= printKthDistanceNode(root->right,base,k);
    if(rightAncestorDistance!=-1){
        if(rightAncestorDistance+1==k){
            cout<<root->data<<" ";
        }
        else{
            subtreeKthDistanceNodePrint(root->left,k-2-rightAncestorDistance);
        }
        return 1+rightAncestorDistance;         //doesnt exist in root->left and root->right
    }

    return -1;

}

//24. Sum of all nodes of the tree
int sumOfAllNodeOfTheTree(Node *root){
    if(root==NULL){
        return 0;
    }
    return root->data + sumOfAllNodeOfTheTree(root->left)+ sumOfAllNodeOfTheTree(root->right);      //rootData + leftData + rightData
}

//25. Flutten Binary Tree
void flutten(Node *root){
    if(root==NULL || (root->left==NULL && root->right==NULL)){    //base
        return;
    }
    if(root->left!=NULL){
        flutten(root->left);    //make root->left single line

        Node *temp=root->right;      //replacing root's left arm to right
        root->right=root->left;
        root->left=NULL;

        Node *ptr=root->right;    //(starting from roots left chain) is now at right chain
        while (ptr->right!=NULL){
            ptr=ptr->right;
        }
        ptr->right=temp;

    }
    flutten(root->right);      //make root->right single line
}

int main(){
    int n=12;
    int inArr[12]={13, 1, 6, 5, 3, 11, 10, 9, 15, 4, 16, 2};
    int preArr[12]={3, 1, 13, 5, 6, 10, 11, 16, 15, 9, 4, 2};
    int postArr[12]={13, 6, 5, 1, 11, 9, 4, 15, 2, 16, 10, 3};
    Node *root=NULL;
    root=new Node(3);
    root->left=new Node(1);
    root->right=new Node(10);
    root->left->left=new Node(13);
    root->left->right=new Node(5);
    root->right->left=new Node(11);
    root->right->right=new Node(16);
    root->left->right->left=new Node(6);
    root->right->right->left=new Node(15);
    root->right->right->right=new Node(2);
    root->right->right->left->left=new Node(9);
    root->right->right->left->right=new Node(4);

    int data,data2,choice;
    cout<<"Choice:";
    cin>>choice;
    while (choice){
        switch (choice) {
            case 1:{
                preorderPrint(root);
                cout<<endl;
                break;
            }
            case 2:{
                inorderPrint(root);
                cout<<endl;
                break;
            }
            case 3:{
                postorderPrint(root);
                cout<<endl;
                break;
            }
            case 4:{
                root= buildTreePreInorderArr(preArr,inArr,0,n);
                cout<<endl;
                break;
            }
            case 5:{
                root= buildTreePostInorderArr(postArr,inArr,0,n);
                cout<<endl;
                break;
            }
            case 6:{
                cout<<countNodes(root)<<endl;
                break;
            }
            case 7:{
                cout<<calHeight(root)<<endl;
                break;
            }
            case 8:{
                levelOrderPrint(root);
                cout<<endl;
                break;
            }
            case 9:{
                cout<<"Level:";
                cin>>data;
                printAtKthLevel(root,data);
                cout<<endl;
                break;
            }
            case 10:{
                cout<<"Level:";
                cin>>data;
                cout<<sumAtKthLevel(root,data);
                cout<<endl;
                break;
            }
            case 11:{
                sumOfAllSubTree(root);
                break;
            }
            case 12:{
                if(checkIsBalanced(root)){
                    cout<<"The tree is balanced"<<endl;
                }
                else{
                    cout<<"The tree is not balanced"<<endl;
                }
                break;
            }
            case 13:{
                int height=0;
                if(checkIsBalanced(root,&height)){
                    cout<<"The tree is balanced"<<endl;
                }
                else{
                    cout<<"The tree is not balanced"<<endl;
                }
                break;
            }
            case 14:{
                rightViewOfTree(root);
                cout<<endl;
                break;
            }
            case 15:{
                leftViewOfTree(root);
                cout<<endl;
                break;
            }
            case 16:{
                cout<<calDiameter(root)<<endl;
                break;
            }
            case 17:{
                int height=0;
                cout<<calDiameter(root,&height)<<endl;
                break;
            }
            case 18:{
                cout<<"Node 1:";
                cin>>data;
                cout<<"Node 2:";
                cin>>data2;
                cout<<lowestCommonAncestor(root,data,data2)->data<<endl;
                break;

            }
            case 19:{
                cout<<"Node:";
                cin>>data;
                cout<<distancedBetweenRoot(root,data,0)<<endl;
                break;
            }
            case 20:{
                cout<<"Node 1:";
                cin>>data;
                cout<<"Node 2:";
                cin>>data2;
                cout<<distanceBetweenTwoNode(root,data,data2)<<endl;
                break;
            }
            case 21:{
                cout<<"Distance:";
                cin>>data;
                subtreeKthDistanceNodePrint(root,data);
                cout<<endl;
                break;
            }
            case 22:{
                cout<<findNode(root,16)->right->data<<endl;
                break;
            }
            case 23:{
                cout<<"From Node:";
                cin>>data;
                cout<<"Distance:";
                cin>>data2;
                printKthDistanceNode(root,data,data2);
                cout<<endl;
                break;
            }
            case 24:{
                cout<<sumOfAllNodeOfTheTree(root)<<endl;
                break;
            }
            case 25:{
                flutten(root);
                break;
            }

        }
        cout<<"Choice:";
        cin>>choice;
    }

}