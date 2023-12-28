#include "iostream"
#include "queue"
using namespace std;                         //307
class Stack{
    int size;
    queue<int> q1;
    queue<int> q2;
public:
    Stack(){
        size=0;
    }

    void Push(int data){
        q2.push(data);                   //push int the Queue2
        size++;

        while (!q1.empty()){               //push every Queue1 element to Queue2
            q2.push(q1.front());
            q1.pop();
        }

        queue<int> tempQueue=q1;          //exchange Queue1 and Queue2
        q1=q2;
        q2=tempQueue;
    }

    void Pop(){

        if(size==0){
            cout<<"Stack is empty"<<endl;
            return;
        }
        q1.pop();                    //delete from the Queue1
        size--;
    }
    int Top(){
        if(size==0){
            cout<<"Stack is empty"<<endl;
            exit(0);
        }
        return q1.front();            //return from the Queue1
    }
    int Size(){
        return size;
    }
    bool IsEmpty(){
        return (size==0);
    }
};
class Stack2{
    int size;
    queue<int> q1;
    queue<int> q2;
public:
    Stack2(){
        size=0;
    }
    void Push(int data){
        q1.push(data);                            //push data to queue1
        size++;
    }
    void Pop(){
        if(q1.empty()){
            cout<<"Stack is empty"<<endl;
            return;
        }

        while (q1.size() != 1){                 //push element from queue1 to queue2 (until queue1 have one element)
            q2.push(q1.front());
            q1.pop();
        }

        q1.pop();                              //pop queue1's that element
        size--;

        queue<int> tempQueue=q1;             //exchange queue1 and queue2
        q1=q2;
        q2=tempQueue;
    }
    int Top(){
        if(q1.empty()){
            cout<<"Stack is empty"<<endl;
            exit(0);
        }

        while (q1.size() !=1){
            q2.push(q1.front());
            q1.pop();
        }

        int ans=q1.front();
        q2.push(ans);

        queue<int> tempQueue=q1;
        q1=q2;
        q2=tempQueue;

        return ans;
    }
    int Size(){
        return size;
    }
    bool IsEmpty(){
        return size==0;
    }
};
int main(){
    Stack2 st;
    int data,choice;
    cout<<"Choice:";
    cin>>choice;
    while (choice){
        switch (choice) {
            case 1:{
                cout<<"Push:";
                cin>>data;
                st.Push(data);
                break;
            }
            case 2:{
                cout<<"Pop"<<endl;
                st.Pop();
                break;
            }
            case 3:{
                cout<<"Top:";
                cout<<st.Top()<<endl;
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
            case 5:{
                cout<<st.Size()<<endl;
                break;
            }


        }
        cout<<"Choice:";
        cin>>choice;
    }

}