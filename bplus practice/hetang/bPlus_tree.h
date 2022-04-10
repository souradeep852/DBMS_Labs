#ifndef BPLUS_TREE_H
#define BPLUS_TREE_H
#include "Node.h"
#include <bits/stdc++.h>
using namespace std;

class bPlus_tree
{
    public:
        bPlus_tree();
        bPlus_tree(int data_cap,int ind_cap);
        virtual ~bPlus_tree();
        int dataCap;
        int indCap;
        void insertElement(int val);
        void insertAssist(Node *);
        void displayTree();
        Node *root;
        void inOrderTraversal();
        void inOrderTraversalRec(Node*);
        void showStatus();
        void countNodes(Node *);

    protected:

    private:
        int dataNodes,indexNodes;
};

#endif // BPLUS_TREE_H
