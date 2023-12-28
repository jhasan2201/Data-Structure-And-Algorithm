#include "iostream"
#include "stack"
using namespace std;
string makeGood(string s) {
    stack<char> st;
    for (int i = s.length()-1; i >=0 ; i--) {

        if(!st.empty() && (st.top()==s[i]-32)){
            st.pop();
        }
        else if(!st.empty() && (st.top()==s[i]+32)){
            st.pop();
        }
        else{
            st.push(s[i]);
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
    cout<<makeGood("s")<<endl;
}
