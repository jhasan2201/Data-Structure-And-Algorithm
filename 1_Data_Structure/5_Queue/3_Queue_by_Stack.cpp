#include "iostream"
#include "stack"
using namespace std;

class Queue{
public:
    stack<int> st1;
    stack<int> st2;

    void Push(int data){
        st1.push(data);                         //push in stack1
    }
    int Pop(){
        if(st1.empty() && st2.empty()){           //both stack is empty
            cout<<"Queue is empty"<<endl;
            exit(0);
        }
        if(st2.empty()){                         //if Stack2 is empty
            while (!st1.empty()){               //push every element from stack1 to stack2
                st2.push(st1.top());
                st1.pop();
            }
        }
        int topVal=st2.top();                 //return topMost value of stack2  (bottom of the stack1)
        st2.pop();
        return topVal;
    }
    bool IsEmpty(){
        return (st1.empty() && st2.empty());
    }
};
class Queue2{
public:
    stack<int> st;
    void Push(int data){
        st.push(data);                            //push in stack
    }
    int Pop(){
        if(st.empty()){                            //stack is empty
            cout<<"Queue is empty"<<endl;
            exit(0);
        }
        int topMost=st.top();                   //get topMost element of the stack
        st.pop();

        if(st.empty()){                         //if stack has only one(topMost) element :: return that
            return topMost;
        }

        int item= Pop();                     //recursively find theLastElement
        st.push(topMost);                 //keep the topMost element under theLastElement of the stack
        return item;                        //return theLastElement
    }
    bool IsEmpty(){
        return st.empty();
    }
};         //alternative (with one stack)
int main(){
    Queue q;
    int data,choice;
    cout<<"Choice:";
    cin>>choice;
    while (choice){
        switch (choice) {
            case 1:{
                cout<<"Push:";
                cin>>data;
                q.Push(data);
                break;
            }

            case 2:{
                cout<<"Pop:";
                cout<<q.Pop()<<endl;
                break;
            }
            case 3:{
                if(q.IsEmpty()){
                    cout<<"Queue is empty"<<endl;
                }else{
                    cout<<"Queue is not empty"<<endl;
                }
                break;
            }


        }
        cout<<"Choice:";
        cin>>choice;
    }

}