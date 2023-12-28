#include "iostream"
#include "math.h"
#include "algorithm"
#include "stack"
using namespace std;

//1. Prefix expression evaluate
int prefixExpression(string str){
    stack<int> st;
    for (int i = str.length()-1; i >=0 ; --i) {           //prefix: traversing last to first of the string
        if(str[i]>='0' && str[i]<='9'){                   //if digit push them (string to number)
            st.push(str[i]-'0');
        }
        else{
            int op1=st.top();                            //pop two element from the stack
            st.pop();
            int op2=st.top();
            st.pop();
            switch (str[i]) {                          //if + plum that two elements and push them into stack
                case '+':{
                    st.push(op1+op2);
                    break;
                }
                case '-':{
                    st.push(op1-op2);
                    break;
                }
                case '*':{
                    st.push(op1*op2);
                    break;
                }
                case '/':{
                    st.push(op1/op2);
                    break;
                }
                case '^':{
                    st.push(pow(op1,op2));
                    break;
                }
            }
        }
    }
    return st.top();                                     //return the ans
}

//2. Postfix expression evaluate
int postfixExpression(string str) {

    stack<int> st;

    for (int i = 0; i < str.length(); ++i) {             //postfix: traversing first to last of the string
        if (str[i] >= '0' && str[i] <= '9') {           //if digit push them (string to number)
            st.push(str[i] - '0');
        } else {
            int op2 = st.top();        //[op1 and op2 exchange]    pop two element from the stack
            st.pop();
            int op1 = st.top();
            st.pop();
            switch (str[i]) {                        //if + plum that two elements and push them into stack
                case '+': {
                    st.push(op1 + op2);
                    break;
                }
                case '-': {
                    st.push(op1 - op2);
                    break;
                }
                case '*': {
                    st.push(op1 * op2);
                    break;
                }
                case '/': {
                    st.push(op1 / op2);
                    break;
                }
                case '^': {
                    st.push(pow(op1, op2));
                    break;
                }
            }
        }
    }
    return st.top();                              //return the ans
}

//3. Infix to prefix
int pref(char c){                             //preference of the operator
    if(c=='^'){
        return 3;
    }else if(c=='*' || c=='/'){
        return 2;
    }
    else if(c=='+' || c=='-'){
        return 1;
    }
    else{
        return -1;
    }
}
string infixToPrefix(string str){
    reverse(str.begin(), str.end());                           //reverse string
    stack<char> cSt;
    string resStr;
    for (int i = 0; i < str.length(); ++i) {
        if((str[i]>='a' && str[i]<='z') || (str[i]>='A' && str[i]<='Z')){      //if operand just print
            resStr+=str[i];
        }
        else if(str[i]==')'){                                                  //push to stack
            cSt.push(str[i]);
        }
        else if(str[i]=='('){                                      //pop from stack and print until '(' is found
            while (cSt.top()!=')'  &&  !cSt.empty()){
                resStr+=cSt.top();
                cSt.pop();
            }
            if(!cSt.empty()){
                cSt.pop();
            }
        }
        else{
            while (!cSt.empty() && pref(cSt.top()) >= pref(str[i])){        //if operator pop from stack
                resStr+=cSt.top();                                          //until an operator with less precedence is found
                cSt.pop();
            }
            cSt.push(str[i]);
        }
    }
    while (!cSt.empty()){
        resStr+=cSt.top();
        cSt.pop();
    }
    reverse(resStr.begin(), resStr.end());                     //again reverse resStr
    return resStr;
}

//4. Infix to postfix
string infixToPostfix(string str){
    stack<char> cSt;
    string resStr;
    for (int i = 0; i < str.length(); ++i) {
        if((str[i]>='a' && str[i]<='z') || (str[i]>='A' && str[i]<='Z')){
            resStr+=str[i];                             //if operand just print
        }
        else if(str[i]=='(')                           //push to stack
        {
            cSt.push(str[i]);
        }
        else if(str[i]==')'){                         //pop from stack and print until '(' is found
            while (cSt.top()!='(' && !cSt.empty()){
                resStr+=cSt.top();
                cSt.pop();
            }
            if(!cSt.empty()){
                cSt.pop();
            }
        }
        else{
            while (!cSt.empty() && ( pref(cSt.top()) >= pref(str[i])) ){   //if operator pop from stack
                resStr+=cSt.top();                             //until an operator with less precedence is found
                cSt.pop();
            }
            cSt.push(str[i]);
        }
    }
    while (!cSt.empty()){
        resStr+=cSt.top();
        cSt.pop();
    }
    return resStr;
}

//5. Valid parenthesis
bool validParenthesis(string str){
    stack<char> st;
    for (int i = 0; i < str.length(); ++i) {
        if(str[i]=='(' ||str[i]=='{' ||str[i]=='['){
            st.push(str[i]);
        }else{
            if(st.empty()){
                return false;
            }
            switch (str[i]) {
                case ')':{
                    if(st.top()=='('){
                        st.pop();
                    }else{
                        return false;
                    }
                    break;
                }
                case '}':{
                    if(st.top()=='{'){
                        st.pop();
                    }else{
                        return false;
                    }
                    break;
                }
                case ']':{
                    if(st.top()=='['){
                        st.pop();
                    }else{
                        return false;
                    }
                    break;
                }
            }
        }
    }
    if(!st.empty()){
        return false;
    }
    return true;
}

int main(){
    string prefStr= "-+7*45+20";
    string postStr="46+2/5*7+";
    string infStr="(a-b/c)*(a/k-l)";
    int choice;
    cout<<"Insert choice:";
    cin>>choice;
    while (choice){
        switch (choice) {
            case 1:{
                cout<<prefixExpression(prefStr)<<endl;
                break;
            }
            case 2:{
                cout<<postfixExpression(postStr)<<endl;
                break;
            }
            case 3:{
                cout<<infixToPrefix(infStr)<<endl;
                break;
            }
            case 4:{
                cout<<infixToPostfix(infStr)<<endl;
                break;
            }
            case 5:{
                if(validParenthesis("((({[()(){}]})))]")){
                    cout<<"Parenthesis is valid"<<endl;
                }else{
                    cout<<"Parenthesis is not valid"<<endl;
                }
                break;
            }

        }
        cout<<endl<<"Insert choice:";
        cin>>choice;
    }



}