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


Node* createFirstNode(int data){
    Node *head=new Node(data);
    return head;
}
void addNodeAtEnd(Node *&head,int data){
    if(head==NULL){
        cout<<"Linked list is empty"<<endl;
        return;
    }
    Node *temp=new Node(data);
    Node *ptr=head;
    while (ptr->link!=NULL){
        ptr=ptr->link;
    }
    ptr->link=temp;
}
void addNodeAtBeg(Node *&head,int data){
    if(head==NULL){
        head= createFirstNode(data);
        return;
    }
    Node *temp=new Node(data);
    temp->link=head;
    head=temp;
}
void addNodeAtPos(Node *&head,int data,int pos){
    if(pos==1 || head==NULL){
         addNodeAtBeg(head,data);
        return;
    }
    Node *temp=new Node(data);
    Node *ptr=head;
    pos--;
    while (pos!=1){
        ptr=ptr->link;
        pos--;
    }
    temp->link=ptr->link;
    ptr->link=temp;
}
void deleteAtFirst(Node *&head){
    if(head==NULL || head->link==NULL){
        head=NULL;
        return;
    }
    Node *ptr=head;
    head=head->link;
    delete(ptr);
}
void deleteLastNode(Node *&head){
    if(head==NULL || head->link==NULL){
        head=NULL;
        return;
    }
    Node *ptr=head;
    while (ptr->link->link!=NULL){
        ptr=ptr->link;
    }
    delete(ptr->link);
    ptr->link=NULL;
}
void deleteAtPos(Node *&head,int pos){
    if(head->link==NULL || pos==1){
        deleteAtFirst(head);
        return;
    }
    Node *ptr=head;
    pos--;
    while (pos!=1){
        ptr=ptr->link;
        pos--;
    }
    Node *ptr2=ptr->link;
    ptr->link=ptr->link->link;
    delete(ptr2);

}
void deleteFullLinkedList(Node *&head){
    Node *ptr=head;
    Node *prev=NULL;
    while (ptr!=NULL){
        prev=ptr;
        ptr=ptr->link;
        delete(prev);
    }
    head=NULL;
}
void printLinkedList(Node *&head){
    if(head==NULL){
        cout<<"Linked list is empty"<<endl;
        return;
    }
    Node *ptr=head;
    while (ptr!=NULL){
        cout<<ptr->data<<" ";
        ptr=ptr->link;
    }
    cout<<endl;
}
int countNode(Node *&head){
    int count=0;
    Node *ptr=head;
    while (ptr!=NULL){
        count++;
        ptr=ptr->link;
    }
    return count;
}
bool ascendingChecker(Node *&head){
    return (head==NULL || head->link==NULL ||
    ((head->data <head->link->data) && (ascendingChecker(head->link))));
}
bool descendingChecker(Node *&head){
    return (head==NULL || head->link==NULL ||
            ((head->data >head->link->data) &&(descendingChecker(head->link))));
}
int searchElement(Node *&head,int srch){
    int i=0;
    Node *ptr=head;
    while (ptr!=NULL){
        if(ptr->data==srch){
            return i;
        }
        ptr=ptr->link;
        i++;
    }
    return -1;
}
void createLinkedList(Node *&head){
    int n,data;
    cout<<"Insert size of the list:";
    cin>>n;
    if(n==0){
        cout<<"Linked list is empty";
        return;
    }
    cout<<"Node 1:";
    cin>>data;
    head=createFirstNode(data);
    if(n==1){
        return;
    }
    for (int i = 1; i < n; ++i) {
        cout<<"Node "<<i+1<<":";
        cin>>data;
        addNodeAtEnd(head,data);
    }
}
void reverseList(Node *&head){
    Node *ptr1=NULL;
    Node *ptr2=NULL;
    while (head!=NULL){
        Node *ptr2=head->link;
        head->link=ptr1;
        ptr1=head;
        head=ptr2;
    }
    head=ptr1;
}
int findMiddle(Node *&head){
    Node *ptr=head;
    Node *prevPtr=head;
    while (ptr->link!=NULL){
        prevPtr=prevPtr->link;
        ptr=ptr->link->link;
    }
    return prevPtr->data;
}
void insertNodeAfter(Node *&head,int afterNum,int data){
    Node *temp=new Node(data);
    Node *ptr=head;
    while (ptr!=NULL){
        if(ptr->data==afterNum){
            temp->link=ptr->link;
            ptr->link=temp;
            return;
        }
        ptr=ptr->link;
    }
}
void insertNodeBefore(Node* &head,int beforeNum,int data){
    Node *temp=new Node(data);
    Node *ptr=head;
    Node *backleg=NULL;
    while (ptr!=NULL){
        if(ptr->data==beforeNum){
            temp->link=ptr;
            backleg->link=temp;
            return;
        }
        backleg=ptr;
        ptr=ptr->link;
    }
}
void deleteNode(Node *&head,int data){
    if(head->data==data){
        Node *ptr=head;
        head=head->link;
        delete(ptr);
        return;
    }
    Node *ptr=head;
    Node *backLeg=NULL;
    while (ptr!=NULL){
        if(ptr->data==data){
            backLeg->link=ptr->link;
            delete(ptr);
            break;
        }
        backLeg=ptr;
        ptr=ptr->link;
    }
}
int main(){
    Node *head=NULL;
    head=createFirstNode(5);
    addNodeAtEnd(head,7);
    addNodeAtEnd(head,2);
    addNodeAtEnd(head,15);
    int choice,num,pos;
    cout<<endl<<"Choice:";
    cin>>choice;
    while (choice){
        switch (choice) {
            case 1:{
                cout<<"Node:";
                cin>>num;
                head= createFirstNode(num);
                break;
            }
            case 2:{
                cout<<"Node:";
                cin>>num;
                addNodeAtEnd(head,num);
                break;
            }
            case 3:{
                cout<<"Node:";
                cin>>num;
                addNodeAtBeg(head,num);
                break;
            }
            case 4:{
                cout<<"Node:";
                cin>>num;
                cout<<"Position:";
                cin>>pos;
                addNodeAtPos(head,num,pos);
                break;
            }
            case 5:{
                deleteAtFirst(head);
                break;
            }
            case 6:{
                deleteLastNode(head);
                break;
            }
            case 7:{
                cout<<"Position:";
                cin>>pos;
                deleteAtPos(head,pos);
                break;
            }
            case 8:{
                deleteFullLinkedList(head);
                break;
            }
            case 9:{
                printLinkedList(head);
                break;
            }
            case 10:{
                cout<<countNode(head)<<endl;
                break;
            }
            case 11:{
                if(ascendingChecker(head)){
                    cout<<"Ascending order"<<endl;
                }else{
                    cout<<"Not Ascending order"<<endl;
                }
                break;
            }
            case 12:{
                if(descendingChecker(head)){
                    cout<<"Descending order"<<endl;
                }
                else{
                    cout<<"Not Descending order"<<endl;
                }
                break;
            }
            case 13:{
                int srch;
                cout<<"Search:";
                cin>>srch;
                int find= searchElement(head,srch);
                if(find==-1){
                    cout<<"Not found"<<endl;
                }
                else{
                    cout<<"Found at "<<find<<" position"<<endl;
                }
            }
            case 14:{
                createLinkedList(head);
                break;
            }
            case 15:{
                reverseList(head);
                break;
            }
            case 16:{
                cout<<findMiddle(head)<<endl;
                break;
            }
            case 17:{
                cout<<"Node:";
                cin>>num;
                int after;
                cout<<"After:";
                cin>>after;
                insertNodeAfter(head,after,num);
                break;
            }
            case 18:{
                cout<<"Node:";
                cin>>num;
                int before;
                cout<<"Before:";
                cin>>before;
                insertNodeBefore(head,before,num);
                break;
            }
            case 19:{
                cout<<"Node:";
                cin>>num;
                deleteNode(head,num);
                break;
            }

        }
        cout<<endl<<"Choice:";
        cin>>choice;
    }
}
