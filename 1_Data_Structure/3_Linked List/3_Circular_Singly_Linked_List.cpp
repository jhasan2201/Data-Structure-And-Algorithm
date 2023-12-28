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
    head->link=head;
    return head;
}
void addNodeAtEnd(Node *&head,int data){
    if(head==NULL){
        head= createFirstNode(data);
        return;
    }
    Node *temp=new Node(data);
    Node *ptr=head;
    do{
        ptr=ptr->link;
    } while (ptr->link!=head);
    temp->link=head;
    ptr->link=temp;

}
void addNodeAtBeg(Node *&head,int data){
    if(head==NULL){
        head= createFirstNode(data);
        return;
    }
    Node *temp=new Node(data);
    Node *ptr=head;
    do{
        ptr=ptr->link;
    } while (ptr->link!=head);
    temp->link=head;
    ptr->link=temp;
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
        ptr=ptr->link;
        pos--;
    }
    temp->link=ptr->link;
    ptr->link=temp;
}
void deleteAtFirst(Node *&head){
    if(head==NULL || head->link==head){
        free(head);
        head=NULL;
        return;
    }

    Node *ptr=head;
    do{
        ptr=ptr->link;
    } while (ptr->link!=head);
    ptr->link=head->link;
    Node *del=head;
    head=head->link;
    delete(del);
}
void deleteLastNode(Node *&head){
    if(head==NULL || head->link==head){
        free(head);
        head=NULL;
        return;
    }
    Node *ptr=head;
    do{
        ptr=ptr->link;
    } while (ptr->link->link!=head);
    delete(ptr->link);
    ptr->link=head;
}
void deleteAtPos(Node *&head,int pos){
    if(head==NULL || head->link==head || pos==1){
        free(head);
        head=NULL;
        return;
    }
    Node *ptr=head;
    pos--;
    while (pos!=1){
        ptr=ptr->link;
        pos--;
    }
    Node *del=ptr->link;
    ptr->link=ptr->link->link;
    delete(del);
}
void deleteFullLinkedList(Node *&head){
    if(head==NULL){
        cout<<"Linked list is empty"<<endl;
        return;
    }
    Node *ptr=head;
    Node *prev=NULL;
    do{
        prev=ptr;
        ptr=ptr->link;
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
        ptr=ptr->link;
    } while (ptr!=head);
}
int countNode(Node *&head){
    int count=0;
    Node *ptr=head;
    do{
        count++;
        ptr=ptr->link;
    } while (ptr!=head);
    return count;
}
int searchElement(Node *&head,int srch){
    int i=0;
    Node *ptr=head;
    do{
        if(srch==ptr->data){
            return i;
        }
        ptr=ptr->link;
    } while (ptr!=head);
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
bool checkCircular(Node *&head){
    Node *ptr=head;
    do{
        ptr=ptr->link;
    }while (ptr!=NULL && ptr!=head);
    if(ptr!=NULL){
        return true;
    }
    else{
        return false;
    }
}
void exchangeFirstAndLast(Node *&head){
    Node *ptr=head;
    while (ptr->link->link!=head){
        ptr=ptr->link;
    }
    Node *del=ptr->link;
    ptr->link=head;
    del->link=head->link;
    head->link=del;
    head=del;
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
//            case 11: {
//                if (ascendingChecker(head)) {
//                    cout << "Ascending order" << endl;
//                } else {
//                    cout << "Not Ascending order" << endl;
//                }
//                break;
//            }
//            case 12: {
//                if (descendingChecker(head)) {
//                    cout << "Descending order" << endl;
//                } else {
//                    cout << "Not Descending order" << endl;
//                }
//                break;
//            }
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
            case 16:{
                if(checkCircular(head)){
                    cout<<"Circular"<<endl;
                }else{}
                cout<<"Not circular"<<endl;
            }
            case 17:{
                exchangeFirstAndLast(head);
                break;
            }
        }
        cout << endl << "Choice:";
        cin >> choice;
    }
}