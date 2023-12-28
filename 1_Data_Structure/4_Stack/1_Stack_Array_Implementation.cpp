#include "iostream"
#define N 100
using namespace std;
class Stack{                                //301
    int *stk;
    int top;
public:
    Stack(){
        stk=new int(N);
        top=-1;
    }
    void push(int data);
    void pop();
    int Top();
    bool IsEmpty();
};
void Stack::push(int data) {
    if(top==N-1){
        cout<<"Stack overflow"<<endl;
        return;
    }
    top++;
    stk[top]=data;
}
void Stack::pop() {
    if(top==-1){
        cout<<"Stack underflow"<<endl;
        return;
    }
    top--;
}
int Stack::Top() {
    if(top==-1){
        cout<<"Stack underflow"<<endl;
        exit(0);
    }
    return stk[top];
}
bool Stack::IsEmpty() {
    return (top==-1);
}
int main(){
    Stack st;
    int data,choice;
    cout<<"Choice:";
    cin>>choice;
    while (choice){
        switch (choice) {
            case 1:{
                cout<<"Push:";
                cin>>data;
                st.push(data);
                break;
            }
            case 2:{
                cout<<"Top:";
                cout<<st.Top()<<endl;
                break;
            }
            case 3:{
                cout<<"Pop"<<endl;
                st.pop();
                break;
            }
            case 4:{
                if(st.IsEmpty()){
                    cout<<"Stack is empty"<<endl;
                }else{
                    cout<<"Stack is not empty"<<endl;
                }
                break;
            }


        }
        cout<<"Choice:";
        cin>>choice;
    }
}
