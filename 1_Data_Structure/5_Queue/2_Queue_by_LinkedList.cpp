#include "iostream"
using namespace std;
class Node{
public:
    int data;
    Node *link;
    Node(int num){
        data=num;
        link=NULL;
    }
};
class Queue{
    Node *front;
    Node *back;
public:
    Queue(){
        front=NULL;
        back=NULL;
    }
    void Push(int data);
    void Pop();
    int Front();
    bool IsEmpty();
};
void Queue::Push(int data){
    Node *temp=new Node(data);

    if(front == NULL){
        front=temp;
        back=temp;
        return;
    }
    back->link=temp;
    back=temp;
}
void Queue::Pop(){
    if(front==NULL){
        cout<<"Queue underflow"<<endl;
        return;
    }
    Node *ptr=front;
    front=front->link;
    delete(ptr);
}
int  Queue::Front(){
    if(front==NULL){
        cout<<"Queue underflow"<<endl;
        exit(0);
    }
    return front->data;
}
bool Queue::IsEmpty(){
    return front==NULL;
}
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
                cout<<"Top:";
                cout<<q.Front()<<endl;
                break;
            }
            case 3:{
                cout<<"Pop"<<endl;
                q.Pop();
                break;
            }
            case 4:{
                if(q.IsEmpty()){
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