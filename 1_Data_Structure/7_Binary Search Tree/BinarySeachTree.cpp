#include "iostream"
#include "vector"
#include "stack"

using namespace std;
class Node{
public:
    int data;
    Node *left;
    Node *right;
    Node *parent;
    Node(int num){
        data=num;
        left=NULL;
        right=NULL;
        parent=NULL;
    }
};

//1. Preorder print
void preorderPrint(Node *root){
    if(root==NULL){
        return;
    }
    cout<<root->data<<" ";
    preorderPrint(root->left);      //traverse left root
    preorderPrint(root->right);     //traverse right root
}

//2. Inorder print
void inorderPrint(Node *root){
    if(root==NULL){
        return;
    }
    inorderPrint(root->left);       //traverse left root
    cout<<root->data<<" ";
    inorderPrint(root->right);      //traverse right root
}

//3. Postorder print
void postorderPrint(Node *root){
    if(root==NULL){
        return;
    }
    postorderPrint(root->left);     //traverse left root
    postorderPrint(root->right);    //traverse right root
    cout<<root->data<<" ";
}

//4. Insert in BST
Node* insertInBST(Node *root,int data){
    if(root==NULL){                       //if root at leaf level ::
        return new Node(data);
    }

    Node *temp=NULL;
    if(data< root->data){
        temp= insertInBST(root->left,data);
        root->left=temp;
        temp->parent=root;
    }
    else{
        temp= insertInBST(root->right,data);
        root->right=temp;
        temp->parent=root;
    }
    return root;
}

//5. Search in BST
Node* seachInBST(Node *root,int srch){
    if(root==NULL){
        return NULL;
    }
    if(root->data==srch){          //if found
        return root;
    }
    if(srch < root->data){                           //if less:: search in left subtree
        return seachInBST(root->left,srch);
    }
    return seachInBST(root->right,srch);        //if greater:: search in left subtree
}

//6. Minimum of the tree
Node* minFinder(Node *root){
    while (root->left!=NULL){             //traverser :: leftmost element :: to find min
        root=root->left;
    }
    return root;
}

//7. Maximum of the tree
Node* maxFinder(Node *root){
    while (root->right!=NULL){           //traverser :: rightmost element :: to find max
        root=root->right;
    }
    return root;
}

//8. Delete from BST

Node* deleteFromBST(Node *root,int del){
    if(del < root->data){                                       //if less:: left traverse
        root->left= deleteFromBST(root->left,del);
    }
    else if(del > root->data){                                      //if greater:: right traverse
        root->right= deleteFromBST(root->right,del);
    }
    else{                                                       //if found::
        if(root->left==NULL){                               //if node have only right child
            Node *temp=root->right;                             //keep right child by temp
            free(root);
            return temp;                                           //return rest of the left subtree
        }
        else if(root->right==NULL){                             //if node have only left child
            Node *temp=root->left;                                  //keep right child by temp
            free(root);
            return temp;                                        //return rest of the right subtree
        }
        else{                                                   //node have left and right child
           Node *temp= minFinder(root->right);
            root->data=temp->data;
            root->right= deleteFromBST(root->right,temp->data);
        }
    }
    return root;
}

//9. Construct BST from Preorder Array
Node* constructBSTPreorderArr(int preArr[],int *preIdx,int element,int minVal,int maxVal,int n){
    if(*preIdx > n){           //array size bound :: return NULL
        return NULL;
    }

    Node *root=NULL;
    if(element>minVal && element<maxVal){              //if false :: doest not maintain BST rules (node must be less than minVal and greater than maxVal)
        root=new Node(element);                     // creating node
        (*preIdx)=(*preIdx)+1;                              //increasing index
        if((*preIdx) < n){                                                                                      //If index less than size::
            root->left= constructBSTPreorderArr(preArr,preIdx,preArr[*preIdx],minVal,element,n);  //construct (min <--> element)
        }
        if((*preIdx) <n){
            root->right= constructBSTPreorderArr(preArr,preIdx,preArr[*preIdx],element,maxVal,n);   //construct (element<-->max)
        }
    }
    return root;
}

//10. Check BST is valid or not
bool checkValidBST(Node *root,Node *minNode,Node *maxNode){
    if(root==NULL){                                       // empty tree is valanced
        return true;
    }
    if(minNode!=NULL && root->data <= minNode->data){       //if root data is greater than minNode
        return false;
    }
    if(maxNode!=NULL && root->data >= maxNode->data){       //if root data is less than maxNode
        return false;
    }

    bool leftValidity= checkValidBST(root->left,minNode,root);     //check validity for left tree::(min<--->key)
    bool rightValidity= checkValidBST(root->right,root,maxNode);    //check validity for right tree::(key<--->max)
    return leftValidity && rightValidity;
}

//11. Build BST from sorted array
Node* buildBSTFromSortedArr(int sortedArr[],int start,int end){         //problem
    if(start>end){
        return NULL;
    }
    int mid=(start+end)/2;
    Node *root=new Node(sortedArr[mid]);
    root->left- buildBSTFromSortedArr(sortedArr,start,mid-1);
    root->right= buildBSTFromSortedArr(sortedArr,mid+1,end);
    return root;
}

//12. Tree Successor
Node* treeSuccessor(Node *root,int base){
    Node *temp= seachInBST(root,base);
    if(temp->right!=NULL){                          //if right child have
        return minFinder(temp->right);           //return::  right subtree's minimum
    }

    Node *prnt=temp->parent;
    while (prnt!=NULL && temp==prnt->right){            //searching first right turn from the bottom
        temp=prnt;
        prnt=prnt->parent;
    }
    return prnt;
}

//13. Tree Predecessor
Node* treePredecessor(Node *root,int base){
    Node *temp= seachInBST(root,base);
    if(temp->left!=NULL){
        return maxFinder(temp->left);
    }
    Node *prnt=temp->parent;
    while (prnt!=NULL && temp==prnt->left){
        temp=prnt;
        prnt=prnt->parent;
    }
    return prnt;
}


//14. Construct all possible tree between two number
vector<Node*> constructAllPossibleTrees(int start, int end){
    vector<Node*> trees;              //create an array(vector) of trees

    if(start>end){                              //base:: after finishing of creating a tree
        trees.push_back(NULL);                                  //push a NULL and return it
        return trees;
    }

    for (int i = start; i <= end; ++i) {
        vector<Node*> leftSubtrees= constructAllPossibleTrees(start,i-1);       //create ith nodes's left subtree (start --- i-1)
        vector<Node*> rightSubtrees= constructAllPossibleTrees(i+1,end);        //create ith nodes's right subtree (i+1 --- end)

        for (int j = 0; j < leftSubtrees.size(); ++j) {                           //left subtree traverse
            Node *ithLeftSubtree=leftSubtrees[j];                           //keep ith nodes's left subtree
            for (int k = 0; k < rightSubtrees.size(); ++k) {                     //right subtree traverse
                Node *ithRightSubtree=rightSubtrees[k];                    //keep ith nodes's right subtree

                Node *ithNode=new Node(i);                            //create ith node
                ithNode->left=ithLeftSubtree;                              //attach leftsubtree
                ithNode->right=ithRightSubtree;                            //attach rightsubtree

                trees.push_back(ithNode);                                //push it to the trees array(vector)
            }
        }
    }
    return trees;
}

//15. Zig zag traversal
void zigzagTraversal(Node *root){
    if(root==NULL){              //base::
        return;
    }

    stack<Node*> currLevel;
    stack<Node*> nextLevel;
    bool leftToRight= true;        //left to right traverse

    currLevel.push(root);

    while (!currLevel.empty()){
        Node *temp=currLevel.top();
        currLevel.pop();

        if(temp!=NULL) {
            cout << temp->data << " ";

            if (leftToRight == true) {                      //left to right traverse::
                if (temp->left != NULL) {                          //push left subtree first
                    nextLevel.push(temp->left);
                }
                if (temp->right != NULL) {                        //push right subtree secondly
                    nextLevel.push(temp->right);
                }
            } else {                                         //right to left traverse::
                if (temp->right != NULL) {                          //push right subtree first
                    nextLevel.push(temp->right);
                }
                if (temp->left != NULL) {                            //push left subtree secondly
                    nextLevel.push(temp->left);
                }
            }
        }
        if (currLevel.empty()) {                             //after finishing a level
            leftToRight = !leftToRight;                     //leftToRight=false   and swap two stack
            swap(currLevel, nextLevel);
        }
    }
}

//16. Is two tree are same (Identical)
bool isIdentical(Node *root1,Node *root2){
    if(root1==NULL && root2==NULL){                             //true:: No node tree
        return true;
    }
    else if(root1==NULL || root2==NULL){                        //false:: one tree have ended but another is not
        return false;
    }
    else{
        bool cond1= (root1->data==root2->data);                       //if both BST node equal
        bool cond2= isIdentical(root1->left,root2->left);    //compare leftSubTree
        bool cond3= isIdentical(root1->right,root2->right);         //compare rightSubTree

        if(cond1 && cond2 && cond3){            //true:: all condition satisfy
            return true;
        }
        return false;
    }

}

//17. Largest BST in Binary tree
struct Info{
    int size;
    int maxi;
    int mini;
    int ans;
    bool isBST;
};
Info largestBSTinBT(Node *root){
    if(root==NULL){                                                        //no node binary tree
        return {0,INT_MIN,INT_MAX,0, true};
    }
    if(root->left==NULL && root->right==NULL){                                  //leaf node of BT is the BST
        return {1,root->data,root->data,1, true};
    }

    Info leftInfo= largestBSTinBT(root->left);                      //left subtree info
    Info rightInfo= largestBSTinBT(root->right);                    //right subtree info

    Info curr;
    curr.size=(1+ leftInfo.size + rightInfo.size);                      //1 for curr + leftSubtree size + rightSubTree size

    if(leftInfo.isBST && rightInfo.isBST && (leftInfo.maxi<root->data) && (rightInfo.mini>root->data)){     //if curr is BST {(leftSubtree && rightSubTree)==BST}
        curr.mini=min(root->data,min(leftInfo.mini,rightInfo.mini));                              //minimum among (curr and leftSubTree and rightSubtree)
        curr.maxi= max(root->data, max(leftInfo.maxi,rightInfo.maxi));                          //maximum among (curr and leftSubTree and rightSubtree)

        curr.ans=curr.size;                             //ans is updated by current size(itself +leftSubtree + rightSubtree )
        curr.isBST= true;                                       //it's a BST
        return curr;
    }
    //if it doesn't follow BST rules
    curr.ans= max(leftInfo.ans,rightInfo.ans);
    curr.isBST= false;
    return curr;
}

//18. Restore BST
void swap(int *a,int *b){     //swap two pointers value
    int temp=*a;
    *a=*b;
    *b=temp;
}
void calcPointer(Node *root,Node **first,Node **mid,Node **last,Node **prev){
    if(root==NULL){
        return;
    }
    calcPointer(root->left,first,mid,last,prev);          //like inorder traversal:: for root->left
    if(*prev!=NULL && (root->data < (*prev)->data)){             //if inorder sequence violate
        if(!(*first)){                      //first==NULL
            *first=*prev;                       //first is the before place where violate occur
            *mid=root;                              //mid is the place where violate occur
        }
        else{                                   //first!=NULL   (for a distance violation:: case1)
            *last=root;
        }
    }
    *prev=root;
    calcPointer(root->right,first,mid,last,prev);       //like inorder traversal:: for root->right
}
void restoreBST(Node *root){
    Node *first,*mid,*last,*prev;
    first=NULL;
    mid=NULL;
    last=NULL;
    prev=NULL;

    calcPointer(root,&first,&mid,&last,&prev);

    if((first && last)!=NULL){                            //inorder:: 1 3 5 11 12   ---> 1 (12) 5 11 (3)       {first=12  mid=5 last=3}
        swap(&(first->data),&(last->data));                 //swap first-last
    }
    else if((first && mid)!=NULL){                        //inorder:: 1 3 5 11 12   ---> 1 (5) (3) 11 12        {first=5  mid=3 last=NULL}
        swap(&(first->data),&(mid->data));                  //swap first-mid
    }
}

int main(){
    Node *root=NULL;
    root= insertInBST(root,8);
    root= insertInBST(root,3);
    root= insertInBST(root,10);
    root= insertInBST(root,1);
    root= insertInBST(root,6);
    root= insertInBST(root,14);
    root= insertInBST(root,4);
    root= insertInBST(root,7);
    root= insertInBST(root,13);

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
                cout<<"Node:";
                cin>>data;
                root= insertInBST(root,data);
                cout<<endl;
                break;
            }
            case 5:{
                cout<<"Search:";
                cin>>data;
                cout<<seachInBST(root,data)->data<<endl;
                break;
            }
            case 6:{
                cout<<minFinder(root)<<endl;
                break;
            }
            case 7:{
                cout<<maxFinder(root)<<endl;
                break;
            }
            case 8:{
                cout<<"Delete:";
                cin>>data;
                root= deleteFromBST(root,data);
                cout<<endl;
                break;
            }
            case 9:{
                int preIndex=0;
                int preArray[]={8,3,1,6,4,7,10,14,13};
                Node *root2= constructBSTPreorderArr(preArray,&preIndex,preArray[preIndex],INT_MIN,INT_MAX,9);
                inorderPrint(root2);
                break;
            }
            case 10:{
                if(checkValidBST(root,NULL,NULL)){
                    cout<<"The BST is valid"<<endl;
                }
                else{
                    cout<<"The BST is not valid"<<endl;
                }
                break;
            }
            case 11:{
                int sortArr[]={1,5,8,9,12,36,99,102};
                Node *root2= buildBSTFromSortedArr(sortArr,0,7);
                preorderPrint(root2);
                cout<<endl;
                break;
            }
            case 12:{
                cout<<"Node:";
                cin>>data;
                cout<<treeSuccessor(root,data)->data<<endl;
                break;
            }
            case 13:{
                cout<<"Node:";
                cin>>data;
                cout<<treePredecessor(root,data)->data<<endl;
                break;
            }
            case 14:{
                vector<Node*> totalTrees= constructAllPossibleTrees(1,3);
                for (int i = 0; i < totalTrees.size(); ++i) {
                    cout<<i+1<<":";
                    preorderPrint(totalTrees[i]);
                    cout<<endl;
                }
                break;
            }
            case 15:{
                zigzagTraversal(root);
                cout<<endl;
                break;
            }
            case 16:{

                Node *root2=NULL;
                root2= insertInBST(root2,3);
                root2= insertInBST(root2,6);
                root2= insertInBST(root2,1);
                root2= insertInBST(root2,7);
                root2= insertInBST(root2,8);
                root2= insertInBST(root2,2);
                root2= insertInBST(root2,4);
                root2= insertInBST(root2,8);
                if(isIdentical(root,root2)){
                    cout<<"Two trees are identical"<<endl;
                }else{

                    cout<<"Two trees are not identical"<<endl;
                }
                break;
            }
            case 17:{
                cout<<largestBSTinBT(root).ans<<endl;
                break;
            }
            case 18:{
                //           3
                //          /\
                //        (6)  7
                //        /  /\
                //       1  5  8
                //          /\
                //         4  (2)
                Node *root2=NULL;
                root2=new Node(3);
                root2->left=new Node(6);
                root2->right=new Node(7);
                root2->left->left=new Node(1);
                root2->right->left=new Node(5);
                root2->right->right=new Node(8);
                root2->right->left->left=new Node(4);
                root2->right->left->right=new Node(2);

                //   preorderPrint(root2);
                restoreBST(root2);
                inorderPrint(root2);
                cout<<endl;
                break;
            }

        }
        cout<<"Choice:";
        cin>>choice;
    }
}