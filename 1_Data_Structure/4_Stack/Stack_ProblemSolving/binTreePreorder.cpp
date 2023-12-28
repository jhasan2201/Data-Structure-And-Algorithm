#include "iostream"
#include "vector"
using namespace std;
class TreeNode{
public:
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int num){
        val=num;
        left=NULL;
        right=NULL;
    }
};
int main(){

}
void preorder(TreeNode *root,vector<int> &ans){
    if(root==NULL){
        return;
    }
    ans.push_back(root->val);
    preorder(root->left,ans);
    preorder(root->right,ans);

}
vector<int> preorderTraversal(TreeNode* root) {
    vector<int> ans;
    preorder(root,ans);
    return ans;
}