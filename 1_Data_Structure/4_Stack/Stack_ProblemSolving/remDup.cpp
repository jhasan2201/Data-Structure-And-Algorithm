#include "iostream"
#include "stack"
using namespace std;
string removeDuplicates(string s) {
    stack<char> st;
    for (int i = s.length()-1; i >=0 ; --i) {
        if(st.empty()){
            st.push(s[i]);
        }
        else if(!st.empty() && st.top()!=s[i]){
            st.push(s[i]);
        }
        else{
            st.pop();
        }
    }
    string ans;
    while (!st.empty()){
        ans+=st.top();
        st.pop();
    }
    return ans;
}
int main(){
    string str1;
    cin>>str1;
    cout<<removeDuplicates(str1)<<endl;
}