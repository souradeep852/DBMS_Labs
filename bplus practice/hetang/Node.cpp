#include "Node.h"
#include <bits.h>

using namespace std;

Node::Node()
{
    //ctor
}

Node::Node(int cap, bool isD)
{
    capacity = cap;
    isData = isD;
    parent = nullptr;
    if(isData){
        for(int i=0;i<=capacity;i++){
            pointers.push_back(nullptr);
        }
    }
}

Node::~Node()
{
    //dtor
}
