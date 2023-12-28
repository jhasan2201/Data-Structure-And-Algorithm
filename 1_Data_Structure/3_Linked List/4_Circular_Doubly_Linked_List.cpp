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
Node* createFirstNode(int data) {
    Node *temp=new Node(data);
    temp->next=temp;
    temp->prev=temp;
}
void addNodeAtEnd(Node *&head,int data){
    if(head==NULL){
        head= createFirstNode(data);
        return;
    }
    Node *temp=new Node(data);
    Node *ptr=head->prev;
    temp->next=head;
    temp->prev=ptr;
    ptr->next=temp;
    head->prev=temp;
}
void addNodeAtBeg(Node *&head,int data){
    if(head==NULL){
        head= createFirstNode(data);
        return;
    }
    Node *temp=new Node(data);
    Node *ptr=head->prev;
    temp->next=head;
    temp->prev=ptr;
    ptr->next=temp;
    head->prev=temp;
    head=temp;
}
void addNodeAtPos(Node *&head,int data,int pos){
    if(head==NULL){
        head= createFirstNode(data);
        return;
    }
    Node *temp=new Node(data);
    pos--;
    Node *ptr=head;
    while (pos!=1){
        ptr=ptr->next;
        pos--;
    }
    temp->next=ptr->next;
    temp->prev=ptr;
    ptr->next->prev=temp;
    ptr->next=temp;
}
void deleteAtFirst(Node *&head){
    Node *ptr=head->prev;
    head=head->next;
    delete(head->prev);
    head->prev=ptr;
    ptr->next=head;
}
void deleteLastNode(Node *&head){
    Node *ptr=head->prev->prev;
    delete(ptr->next);
    ptr->next=head;
    head->prev=ptr;
}
void deleteAtPos(Node *&head,int pos){
    if(pos==1){
        deleteAtFirst(head);
        return;
    }
    pos--;
    Node *ptr=head;
    while (pos!=1){
        ptr=ptr->next;
        pos--;
    }
    Node *del=ptr->next;
    del->next->prev=ptr;
    ptr->next=del->next;
    delete(del);

}
void deleteFullLinkedList(Node *&head){
    Node *ptr=head;
    Node *prev=NULL;
    do{
        prev=ptr;
        ptr=ptr->next;
        delete(prev);
    } while (ptr!=head);
    head=NULL;
}
void printLinkedList(Node *&head){
    if(head==NULL){
        cout<<"Linked list is empty"<<endl;
        return;
    }
    Node *ptr=head;
    do{
        cout<<ptr->data<<" ";
        ptr=ptr->next;
    } while (ptr!=head);
    cout<<endl;
}
int countNode(Node *&head){
    int count=0;
    Node *ptr=head;
    do{
        count++;
        ptr=ptr->next;
    } while (ptr!=head);
    return count;
}       //255
bool ascendingChecker(Node *&head){
    return (head==NULL || head->next==NULL ||
            ((head->data <head->next->data) && (ascendingChecker(head->next))));
}       //211
bool descendingChecker(Node *&head){
    return (head==NULL || head->next==NULL ||
            ((head->data >head->next->data) &&(descendingChecker(head->next))));
}       //212

int searchElement(Node *&head,int srch){
    int i=0;
    Node *ptr=head;
    do{
        if(srch== ptr->data){
            return i;
        }
        ptr=ptr->next;
        i++;
    } while (ptr!=NULL);
    return -1;
}       //258
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

int main(){
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
            case 1: {
                cout << "Node:";
                cin >> num;
                head = createFirstNode(num);
                break;
            }
            case 2: {
                cout << "Node:";
                cin >> num;
                addNodeAtEnd(head, num);
                break;
            }
            case 3: {
                cout << "Node:";
                cin >> num;
                addNodeAtBeg(head, num);
                break;
            }
            case 4: {
                cout << "Node:";
                cin >> num;
                cout << "Position:";
                cin >> pos;
                addNodeAtPos(head, num, pos);
                break;
            }
            case 5: {
                deleteAtFirst(head);
                break;
            }
            case 6: {
                deleteLastNode(head);
                break;
            }
            case 7: {
                cout << "Position:";
                cin >> pos;
                deleteAtPos(head, pos);
                break;
            }
            case 8: {
                deleteFullLinkedList(head);
                break;
            }
            case 9: {
                printLinkedList(head);
                break;
            }
            case 10: {
                cout << countNode(head) << endl;
                break;
            }
            case 11: {
                if (ascendingChecker(head)) {
                    cout << "Ascending order" << endl;
                } else {
                    cout << "Not Ascending order" << endl;
                }
                break;
            }
            case 12: {
                if (descendingChecker(head)) {
                    cout << "Descending order" << endl;
                } else {
                    cout << "Not Descending order" << endl;
                }
                break;
            }
            case 13: {
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
            case 14: {
                createLinkedList(head);
                break;
            }
        }
        cout << endl << "Choice:";
        cin >> choice;
    }
}