#include <bits/stdc++.h>
#include "node.h"
#include "bPlus_tree.h"
using namespace std;

int main()
{
//    bPlus_tree tree(2,1);
//    tree.insertElement(1);
//    tree.insertElement(5);
//    tree.insertElement(3);
//    tree.insertElement(4);
//    tree.insertElement(2);
//    tree.inOrderTraversal();

    int d,t;
    cin >> d >> t;
    bPlus_tree tree(d,t);
    int opCode;
    while(cin >> opCode){
        switch(opCode){
            case 1 : {
                int n;
                cin >> n;
                tree.insertElement(n);
                break;
            }
            case 2 : {
                tree.showStatus();
                break;
            }
            case 3 : {
                return 0;
            }
        }
    }
    return 0;
}
