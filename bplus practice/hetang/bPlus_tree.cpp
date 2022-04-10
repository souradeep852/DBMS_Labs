#include "bPlus_tree.h"
#include <bits/stdc++.h>
using namespace std;
bPlus_tree::bPlus_tree()
{
    //ctor
    root = nullptr;
}

bPlus_tree::bPlus_tree(int data_cap, int ind_cap)
{
    //ctor
    dataCap = 2*data_cap;
    indCap = 2*ind_cap+1;
    root = nullptr;
}

void bPlus_tree::insertAssist(Node *n){
    cout << "assist " << n->capacity << " " << n->values.size() << endl;
    if(n->capacity >= n->values.size())return;
//    cout << "node full " << n->values.size() << " " << n->isData << " " << dataCap <<  endl;
    int shiftIndex = n->capacity/2;
//    if(n->isData==false)shiftIndex++;
//    cout << "shift index is " << shiftIndex << endl;
    Node * par = n->parent;
    Node *left ;
    Node *right;
    if(n->isData){
        left = new Node(dataCap,true);
        right= new Node(dataCap,true);
    }
    else{
        left = new Node(indCap,false);
        right= new Node(indCap,false);
    }
    if(par==nullptr){
        par = new Node(indCap,false);
        par->values.push_back(n->values[shiftIndex]);
        for(int i=0;i<=shiftIndex;i++){
            if(i<shiftIndex)left->values.push_back(n->values[i]);
            if(!n->isData)left->pointers.push_back(n->pointers[i]);
        }
        for(int i=shiftIndex;i<=n->capacity+1;i++){
            if(n->isData==false && i==shiftIndex)continue;
            if(i<=n->capacity)right->values.push_back(n->values[i]);
            if(!n->isData)right->pointers.push_back(n->pointers[i]);
        }
        delete n;
        left->parent = par;
        right->parent = par;
        par->pointers.push_back(left);
        par->pointers.push_back(right);
        cout << "assigning root " << endl;
        root = par;
    }else{
        par = n->parent;
        int index = upper_bound(par->values.begin(),par->values.end(),n->values[shiftIndex])-par->values.begin();
        cout << "index is " << index << endl;
        par->values.push_back(0);
        // shift the values in parent node
        for(int i=n->values.size()-1;i>index;i--){
            par->values[i] = par->values[i-1];
        }

        // pushing the index element to the parent
        par->values[index] = n->values[shiftIndex];
        // split the node n into two nodes left and right
        for(int i=0;i<shiftIndex;i++){
            left->values.push_back(n->values[i]);
        }
        for(int i=shiftIndex;i<=n->capacity;i++){
            // no need to transfer the index node to right if it is not part of data
            if(n->isData==false && i==shiftIndex)continue;
            right->values.push_back(n->values[i]);
        }
        cout << "left and right have " << left->values.size() << " " << right->values.size() << endl;
        delete n;
        left->parent = par;
        right->parent = par;
        // rearrange the pointers
        par->pointers.push_back(nullptr);
        for(int i=par->pointers.size()-1;i>index+1;i--){
            par->pointers[i] = par->pointers[i-1];
        }
        par->pointers[index]=left;
        par->pointers[index+1]=right;
        cout << "parent value and pointer have " << par->values.size() << " " << par->pointers.size() << endl;
        showStatus();
        // check the conditions for parent node
        insertAssist(par);
    }
}


void bPlus_tree::insertElement(int val){
    if(root == nullptr){
        Node * ptr = new Node(dataCap,true);
        ptr->values.push_back(val);
        root = ptr;
        return;
    }

    Node * curr = root;
    int index;
    // traverse down the tree as long as the curr node is not a datanode
    while(curr!=nullptr){
        if(curr->isData)break;
        cout << "not data" << endl;
        index = upper_bound(curr->values.begin(),curr->values.end(),val)-curr->values.begin();
        cout << "index is " << index << " for " << val << endl;
        curr = curr->pointers[index];
//        if(index == curr->values.size()){
//            curr = curr->pointers[index+1];
//        }else{
//        }
    }
    cout << "outside while" << endl;
    if(curr==nullptr){
        cout << "nullptr!" << endl;
    }
    index = upper_bound(curr->values.begin(),curr->values.end(),val)-curr->values.begin();
    if(index == curr->values.size()){
        curr->values.push_back(val);
    }else{
        curr->values.push_back(0);
        for(int i=curr->values.size()-1;i>index;i--){
            curr->values[i] = curr->values[i-1];
        }
        curr->values[index] = val;
    }
    // check if there is overflow in the the current node
    insertAssist(curr);
}

void bPlus_tree::inOrderTraversalRec(Node * n){
    if(n==nullptr)return;
    for(int i=0;i<n->pointers.size();i++){
        if(n->pointers.size()!=0)inOrderTraversalRec(n->pointers[i]);
        if(i<n->values.size())cout << " " << n->values[i] << " " ;
//        if(n->pointers.size()!=0)inOrderTraversalRec(n->pointers[i+1]);
    }
}

void bPlus_tree::inOrderTraversal(){
    cout << "inorder traversal:" ;


    inOrderTraversalRec(root);
    cout << endl;

}

void bPlus_tree::countNodes(Node * n){
    if(n==nullptr)return;
    cout << "counting " << endl;
    if(n->isData){
        dataNodes++;
    }else{
        indexNodes++;
    }
    if(n->pointers.size()!=0){
        for(int i=0;i<n->pointers.size();i++){
            countNodes(n->pointers[i]);
        }
    }
}

void bPlus_tree::showStatus(){
    dataNodes=0;
    indexNodes=0;
    cout << "pointers is root " << root->pointers.size() << endl;
    countNodes(root);
    cout << indexNodes << " " << dataNodes << " " ;
    for(int i=0;i<root->values.size();i++){
        cout << root->values[i] << " " ;
    }
    cout << endl;
    inOrderTraversal();
}

bPlus_tree::~bPlus_tree()
{
    //dtor
}
