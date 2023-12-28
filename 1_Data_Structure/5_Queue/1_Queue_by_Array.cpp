#include "iostream"
#define QSize 100
using namespace std;
class Queue{
public:
    int *q;
    int front;
    int back;
    Queue(){
        q=new int(QSize);
        front=-1;
        back=-1;
    }
    void Push(int data);
    int Front();
    void Pop();
    bool IsEmpty();
};                                                  //401
void Queue::Push(int data){
    if(back==QSize-1){
        cout<<"Queue overflow"<<endl;
        return;
    }
    back++;
    q[back]=data;

    if(front==-1){
        front++;
    }
}
int Queue::Front(){
    if(front==-1 || front>back){
        cout<<"Queue underflow"<<endl;
        exit(0);
    }
    return q[front];
}
void Queue::Pop(){
    if(front==-1 || front>back){
        cout<<"Queue underflow"<<endl;
        exit(0);
    }
    front++;
}
bool Queue::IsEmpty(){
    return (front==-1 || front>back);
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