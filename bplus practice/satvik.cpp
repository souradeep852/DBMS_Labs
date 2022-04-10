#include <bits/stdc++.h>
#include <iostream>

using namespace std;

int data_node=0;
int index_node=0;

class bnode
{
   


    
public:
   vector <int> data;
   vector <bnode*> nodeArr;
   bool leaf;
   int data_node_size;
   int index_node_size;
   
   
   
    bnode(int leaf_size, int non_leaf_size, bool leaf);
    int getDataSize();
    void insert(int key, int* val, bnode* &newentry);
    bnode* makeroot(int val,bnode* m1);
    void split(int* val, bnode* &newentry);
    void enter(bnode* newentry, int val, int pos);
    
    
    ~bnode();
};




// bnode banaya hai 

bnode:: bnode(int leaf_size, int non_leaf_size, bool leaf)
{
    this->data_node_size=leaf_size;
    this->index_node_size=non_leaf_size;
    this->leaf=leaf;
  
}

// split kra hai

void bnode:: split(int* val, bnode* &newentry ){
    int t = (index_node_size+1)/2;
    index_node++;
	newentry = new bnode(data_node_size, index_node_size, false);
	*val = this->data[t-1];

	for(int i = t; i < 2*t; i++){
		newentry->data.push_back(this->data[i]);
	}
	this->data.resize(t-1);
	for(int i = t; i <= 2*t; i++){
        newentry->nodeArr.push_back(this->nodeArr[i]);
    }
	this->nodeArr.resize(t);
}


// root banaya hai

bnode* bnode::makeroot(int val,bnode* m1){
    index_node++;
    bnode* roots = new bnode(data_node_size, index_node_size, false);
    roots->data.push_back(val);
    roots->nodeArr.push_back(this);
    roots->nodeArr.push_back(m1);
    return roots;
}

// index node mei daala hai
void bnode :: enter(bnode* newentry, int val, int pos){
    data.insert(data.begin()+pos, val);
    nodeArr.insert(nodeArr.begin()+pos+1, newentry);
}


// insert function jo main kaam kr rha hai
void bnode::insert(int key, int* val, bnode* &newentry){
    if (leaf==true){
        vector <int> :: iterator it = lower_bound(data.begin(), data.end(), key);
        data.insert(it, key);
        if (data.size()>data_node_size){
            data_node++;
            int g=data.size()/2;
            newentry = new bnode(data_node_size, index_node_size, true);
            *val = this->data[g];
            for(int i = g; i <= 2*g; i++){
                newentry->data.push_back(this->data[i]);
            }
            this->data.resize(g);
        }


    }
    else{
        int i = 0;
		while(i < data.size() && key >= data[i]){
            i++;
        }
		nodeArr[i]->insert(key, val, newentry);
        if(newentry==nullptr){
            return;        }
        enter(newentry, *val, i);
        if (data.size() <= index_node_size){			
			newentry = nullptr;
		}
		else{
			split(val, newentry);
		}


    }
}

// baaki sab tatti hai

int bnode:: getDataSize(){
    return data.size();
}

bnode::~bnode()
{
}


class btree
{
    bnode* root;
    int D_size;
    int I_size;

public:
    btree(int d,int t);
    ~btree();
    void insert(int n);
    void display();
    
};

void btree::display(){
    cout<<index_node<<' '<<data_node<<' ';
    int e=root->data.size();
    for(int i=0;i<e;i++){
        cout<<root->data[i]<<' ';
    }
    cout<<endl;
}

btree::btree(int d,int I)
{
    data_node++;
    root=new bnode(d,I,true);
    this->D_size=d;
    this->I_size=I;
}



void btree::insert(int n){
    bnode* m1=nullptr;
    int val=0;
    root->insert(n,&val,m1);
    if (m1!=nullptr){
        root = root->makeroot(val,m1);
    }

}



btree::~btree()
{
}

int main(){
    btree* tree = NULL;
    int inp;
    
    int non_leaf_size;
    		int leaf_size;
    		// cout << "Enter number of keys in index node and data node" << endl;
    		cin >> leaf_size>>non_leaf_size;
    		if (tree)
    			delete(tree);
            leaf_size=2*leaf_size;
            non_leaf_size=2*non_leaf_size+1;

    		tree = new btree(leaf_size, non_leaf_size);
            cin >> inp;

    while(inp != 3){
    	if (inp == 1){
    		int x;
            cin >> x;
            tree->insert(x);
    	}
        else if (inp == 2){
            tree->display();
        }
        cin >> inp;
    }
    return 0;
}