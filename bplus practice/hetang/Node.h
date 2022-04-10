#ifndef NODE_H
#define NODE_H
#include <bits/stdc++.h>
using namespace std;


class Node
{
    public:
        Node();
        Node(int cap,bool isD);
        virtual ~Node();
        int capacity;
        bool isData;
        vector<int> values;
        vector<Node*> pointers;
        Node * parent;


    protected:

    private:
};

#endif // NODE_H
