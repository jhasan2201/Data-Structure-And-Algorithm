#include "iostream"
#include "vector"
#include "stack"

using namespace std;
int minOperations(vector<string> &logs) {
    stack<int> st;
    for (string x:logs) {
        if(x=="./");
        else if(x=="../"){
            if(!st.empty()) {
                st.pop();
            }
        }
        else{
            st.push(1);
        }
    }
    return st.size();
}
int main(){
    vector<string> vt={"./","ho3/","tl8/"};
    cout<<minOperations(vt);
}