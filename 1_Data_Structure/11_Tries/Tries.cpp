#include "iostream"

using namespace std;

class TrieNode{
public:
    char data;
    TrieNode *children[26];
    bool isTerminal;

    TrieNode(char data){
        this->data=data;
        for (int i = 0; i < 26; ++i) {
            children[i]= NULL;
        }
        isTerminal= false;
    }
};

class Trie{
public:
    TrieNode *root;

    Trie(){
       root=new TrieNode('\0');
    }

    void insertUtil(TrieNode *root,string word){
        if(word.length()==0){
            root->isTerminal= true;
            return;
        }

        int index=word[0]-'A';

        TrieNode *child;
        //present
        if(root->children[index] != NULL){
            child=root->children[index];
        }
        else{
            child = new TrieNode(word[0]);
            root->children[index] = child;
        }

        //recursion
        insertUtil(root,word.substr(1));
    }

    void insert(string word){
        insertUtil(root,word);
    }

    bool searchUtil(TrieNode *root,string word){
        if(word.length()==0){
           return root->isTerminal;
        }

        int index =word[0] - 'A';

        TrieNode *child;
        if(root->children[index] !=NULL){
            child=root->children[index];
        }else{
            return false;
        }
        return searchUtil(child,word.substr(1));

    }

    bool searchWord(string word){
        return searchUtil(root,word);
    }

};


int main(){
    Trie *t=new Trie();


    int choice;
    cout<<"Choice:";
    cin>>choice;
    while (choice){
        switch (choice) {
            case 1:{
                t->insert("abcd");
                break;
            }
            case 2:{
                t->insert("abcd");
                if(t->searchWord("abcd")){
                    cout<<"Present"<<endl;
                }
                else{
                    cout<<"Not"<<endl;
                }
                break;
            }
        }
        cout<<"Choice:";
        cin>>choice;
    }
}
