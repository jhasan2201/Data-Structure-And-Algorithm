#include "iostream"
using namespace std;
class Node{
public:
    int data;
    Node *prev;
    Node *next;
    Node(int num){
        data=num;
        prev=NULL;
        next=NULL;
    }
};
Node* createFirstNode(int data){
    Node *head=new Node(data);
    return head;
}
void addNodeAtEnd(Node *&head,int data){
    if(head==NULL){
        head=createFirstNode(data);
        return;
    }
    Node *temp=new Node(data);
    Node *ptr=head;
    while (ptr->next!=NULL){
        ptr=ptr->next;
    }
    temp->prev=ptr;
    ptr->next=temp;
}
void addNodeAtBeg(Node *&head,int data){
    if(head==NULL){
        head= createFirstNode(data);
        return;
    }
    Node *temp=new Node(data);
    temp->next=head;
    head->prev=temp;
    head=temp;
}
void addNodeAtPos(Node *&head,int data,int pos){
    if(head==NULL){
        head= createFirstNode(data);
        return;
    }
    if(pos==1){
        addNodeAtBeg(head,data);
        return;
    }
    Node *temp=new Node(data);
    Node *ptr=head;
    pos--;
    while (pos!=1){
        ptr=ptr->next;
        pos--;
    }
    temp->prev=ptr;
    temp->next=ptr->next;
    ptr->next->prev=temp;
    ptr->next=temp;
}
void deleteAtFirst(Node *&head){
    if(head==NULL || head->next==NULL){
        head=NULL;
        return;
    }
    Node *ptr=head;
    head=head->next;
    head->prev=NULL;
    delete(ptr);
}
void deleteLastNode(Node *&head){
    if(head==NULL || head->next==NULL){
        head=NULL;
        return;
    }
    Node *ptr=head;
    while (ptr->next->next!=NULL){
        ptr=ptr->next;
    }
    Node *del=ptr->next;
    ptr->next=NULL;
    delete(del);
}
void deleteAtPos(Node *&head,int pos){
    if(head==NULL){
        cout<<"Linked list is empty"<<endl;
        return;
    }
    if(pos==1 || head->next==NULL){
        deleteAtFirst(head);
        return;
    }
    pos--;
    Node *ptr=head;
    while (pos!=1){
        ptr=ptr->next;
        pos--;
    }
//    if(ptr->next==NULL){     //last node
//        deleteLastNode(head);
//        return;
//    }
    Node *del=ptr->next;
    ptr->next->next->prev=ptr;
    ptr->next=ptr->next->next;
    delete(del);
}
void deleteFullLinkedList(Node *&head){
    if(head==NULL){
        cout<<"Linked list is empty"<<endl;
        return;
    }
    Node *ptr=head;
    Node *prev=NULL;
    while (ptr!=NULL){
        prev=ptr;
        ptr=ptr->next;
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
        ptr=ptr->next;
    }
    cout<<endl;
}
int countNode(Node *&head){
    Node *ptr=head;
    int count=0;
    while (ptr!=NULL){
        count++;
        ptr=ptr->next;
    }
    return count;
}
bool ascendingChecker(Node *&head){
    return (head==NULL || head->next==NULL || ((head->data <head->next->data)&& (ascendingChecker(head->next))));
}
bool descendingChecker(Node *&head){
    return (head==NULL || head->next==NULL || ((head->data >head->next->data)&& (descendingChecker(head->next))));
}
int searchElement(Node *&head,int srch){
    int i;
    Node *ptr=head;
    while (ptr!=NULL){
        if(ptr->data==srch){
            return i;
        }
        ptr=ptr->next;
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
void reverseLinkedList(Node *&head){
    Node *ptr1=NULL,*ptr2=NULL;
    while (head!=NULL){
        ptr2=head->next;
        head->next=ptr1;
        head->prev=ptr2;
        ptr1=head;
        head=ptr2;
    }
    head=ptr1;
}
void insertNodeAfter(Node *&head,int afterNum,int data){
    Node *temp=new Node(data);
    Node *ptr=head;
    while (ptr!=NULL){
        if(ptr->data==afterNum){
            temp->prev=ptr;
            temp->next=ptr->next;
            ptr->next->prev=temp;
            ptr->next=temp;
            break;
        }
        ptr=ptr->next;
    }
}
void insertNodeBefore(Node* &head,int beforeNum,int data){
    if(head->data=beforeNum){
        addNodeAtBeg(head,data);
        return;
    }
    Node *temp=new Node(data);
    Node *ptr=head;
    while (ptr!=NULL){
        if(ptr->data==beforeNum){

        }
        ptr=ptr->next;
    }
}
void deleteNode(Node *&head,int data){
    Node *ptr=head;
    if(data==head->data){
        head=head->next;
        delete(ptr);
        return;
    }
    while (ptr!=NULL){
        if(ptr->data==data){
            ptr->prev->next=ptr->next;
            ptr->next->prev=ptr->prev;
            delete(ptr);
            return;
        }
        ptr=ptr->next;
        if(ptr->next==NULL){
            ptr->prev->next=NULL;
            delete(ptr);
            return;
        }
    }
}
int main() {
    Node *head = NULL;
    head=createFirstNode(5);
    addNodeAtEnd(head,7);
    addNodeAtEnd(head,2);
    addNodeAtEnd(head,15);
    int choice, num, pos;
    cout << endl << "Choice:";
    cin >> choice;
    while (choice) {
        switch (choice) {
            case 216: {
                cout << "Node:";
                cin >> num;
                head = createFirstNode(num);
                break;
            }
            case 217: {
                cout << "Node:";
                cin >> num;
                addNodeAtEnd(head, num);
                break;
            }
            case 218: {
                cout << "Node:";
                cin >> num;
                addNodeAtBeg(head, num);
                break;
            }
            case 219: {
                cout << "Node:";
                cin >> num;
                cout << "Position:";
                cin >> pos;
                addNodeAtPos(head, num, pos);
                break;
            }
            case 220: {
                deleteAtFirst(head);
                break;
            }
            case 221: {
                deleteLastNode(head);
                break;
            }
            case 222: {
                cout << "Position:";
                cin >> pos;
                deleteAtPos(head, pos);
                break;
            }
            case 223: {
                deleteFullLinkedList(head);
                break;
            }
            case 224: {
                printLinkedList(head);
                break;
            }
            case 225: {
                cout << countNode(head) << endl;
                break;
            }
            case 226: {
                if (ascendingChecker(head)) {
                    cout << "Ascending order" << endl;
                } else {
                    cout << "Not Ascending order" << endl;
                }
                break;
            }
            case 227: {
               if (descendingChecker(head)) {
                    cout << "Descending order" << endl;
                } else {
                    cout << "Not Descending order" << endl;
                }
                break;
            }
            case 228: {
                int srch;
                cout << "Search:";
                cin >> srch;
                int find = searchElement(head, srch);
                if (find == -1) {
                    cout << "Not found" << endl;
                } else {
                    cout << "Found at " << find << " position" << endl;
                }
            }
            case 229: {
                createLinkedList(head);
                break;
            }
            case 230:{
                reverseLinkedList(head);
                break;
            }
            case 269:{
                cout<<"Node:";
                cin>>num;
                int after;
                cout<<"After:";
                cin>>after;
                insertNodeAfter(head,after,num);
                break;
            }
            case 273:{
                cout<<"Node:";
                cin>>num;
                int before;
                cout<<"Before:";
                cin>>before;
                insertNodeBefore(head,before,num);
                break;
            }
            case 277:{
                cout<<"Node:";
                cin>>num;
                deleteNode(head,num);
                break;
            }
        }
        cout << endl << "Choice:";
        cin >> choice;
    }
}

