#include "iostream"
using namespace std;
class Node{
public:
    double coef;
    int expo;
    Node *link;
    Node(double co,int ex){
        coef=co;
        expo=ex;
        link=NULL;
    }
};
void insertPolynomial(Node *&head,double co,int ex){
    Node *temp=new Node(co,ex);
    if(head==NULL || head->expo < ex){      //insert first
        temp->link=head;
        head=temp;
        return;
    }
    Node *ptr=head;
    while (ptr->link!=NULL){
        if(ptr->expo == ex){              //insert if exponent match
            (ptr->coef)+=co;
            break;
        }
        else if(ptr->expo > ex && ptr->link->expo <ex){         //insert if exponent doesn't match
            temp->link=ptr->link;
            ptr->link=temp;
            break;
        }
        ptr=ptr->link;
    }
    if(ptr->link==NULL){                  //insert last
        if(ptr->expo==ex){                 //if match
            (ptr->coef)+=co;
        }else{                             //add node at last
            ptr->link=temp;
        }
    }
}
void printpolynomial(Node *&head){
    if(head==NULL){
        cout<<"Polynomial is empty"<<endl;
        return;
    }
    Node *ptr=head;
    while (ptr!=NULL){
        cout<<ptr->coef<<"X^"<<ptr->expo<<" ";
        if(ptr->link!=NULL){
            cout<<"+ ";
        }
        ptr=ptr->link;
    }
    cout<<endl;
}
Node* addPolynomial(Node *&head1,Node *&head2){
    Node *ptr1=head1;
    Node *ptr2=head2;
    Node *ptr=NULL;
    while (ptr1!=NULL && ptr2!=NULL){
        if(ptr1->expo == ptr2->expo){
            insertPolynomial(ptr,ptr1->coef+ptr2->coef,ptr1->expo);
            ptr1=ptr1->link;
            ptr2=ptr2->link;
        }
        else if(ptr1->expo > ptr2->expo){
            insertPolynomial(ptr,ptr1->coef,ptr1->expo);
            ptr1=ptr1->link;
        }
        else if(ptr1->expo < ptr2->expo){
            insertPolynomial(ptr,ptr2->coef,ptr2->expo);
            ptr2=ptr2->link;
        }
    }
    while (ptr1!=NULL){
        insertPolynomial(ptr,ptr1->coef,ptr1->expo);
        ptr1=ptr1->link;
    }
    while (ptr2!=NULL){
        insertPolynomial(ptr,ptr2->coef,ptr2->expo);
        ptr2=ptr2->link;
    }
    return ptr;
}
Node* multiplyPolynomial(Node *&head1,Node *&head2){
    Node *ptr1=head1;
    Node *ptr2=head2;
    Node *ptr=NULL;
    while (ptr1!=NULL){
        while (ptr2!=NULL){
            insertPolynomial(ptr,(ptr1->coef)*(ptr2->coef),(ptr1->expo)+(ptr2->expo));
            ptr2=ptr2->link;
        }
        ptr1=ptr1->link;
        ptr2=head2;
    }
    return ptr;
}
Node* createPolynomial(){
    Node *ptr=NULL;
    int n;
    cout<<"Size of the polynomial:";
    cin>>n;
    for (int i = 0; i < n; ++i) {
        int coef,expo;
        cout<<"Polynomial:";
        cin>>coef;
        cout<<"X";
        cin>>expo;
        insertPolynomial(ptr,coef,expo);
    }
    return ptr;
}
int main(){
    Node *head=NULL;
    int coef,expo,choice;
    cout<<"Choice:";
    cin>>choice;
    while (choice){
        switch (choice) {
            case 1:{
                cout<<"Polynomial:";
                cin>>coef;
                cout<<"X";
                cin>>expo;
                insertPolynomial(head,coef,expo);
                break;
            }
            case 2:{
                cout<<endl;
                printpolynomial(head);
                break;
            }
            case 3:{
                Node *head1=createPolynomial();
                Node *head2=createPolynomial();
                head= addPolynomial(head1,head2);
                break;
            }
            case 4:{
                Node *head1=createPolynomial();
                Node *head2=createPolynomial();
                head= multiplyPolynomial(head1,head2);
                break;
            }
        }
        cout<<"Choice:";
        cin>>choice;
    }

}