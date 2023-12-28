#include "iostream"
using namespace std;
class Node{                                   //302
public:
    int data;
    Node *link;
    Node(int num){
        data=num;
        link=NULL;
    }
};
class Stck{
    Node *top;
public:
    Stck(){
        top=NULL;
    }
    void push(int data);
    void pop();
    int Top();
    bool IsEmpty();
};
void Stck::push(int data){
    Node *temp=new Node(data);

    if(top==NULL){
        top=temp;
        return;
    }
    temp->link=top;
    top=temp;
}
void Stck::pop(){
    if(top==NULL){
        cout<<"Linked list is empty";
        return;
    }
    Node *ptr=top;
    top=top->link;
    delete(ptr);
}
int Stck::Top(){
    if(top==NULL){
        cout<<"Linked list is empty";
        exit(0);
    }
    return top->data;
}
bool Stck::IsEmpty() {
    return (top==NULL);
}


int main(){
    Stck st;
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