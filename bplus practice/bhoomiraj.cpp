#include <bits/stdc++.h>
using namespace std;

typedef long double LD;
typedef long long ll;
#define pb push_back
#define REP(i,n) for (int i = 0; i < n; i++)
#define FOR(i,a,b) for (int i = a; i < b; i++)
#define REPD(i,n) for (int i = n-1; i >= 0; i--)
#define FORD(i,a,b) for (int i = a; i >= b; i--)
#define FAST_IO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define printarr(temp, occ) REP(i,occ)cout<<temp[i]<<" ";cout<<endl;

int t,d;

int insertkey(int* keys, int occupancy, int key){
    int insrt=occupancy;
    int temp;bool ins=false;
    REP(i,occupancy+1){
        if(!ins){
            if(i==occupancy)keys[occupancy]=key;
            else if(keys[i]>key){
                temp=keys[i];
                keys[i]=key;insrt=i;
                ins=1;
            }
        }
        else swap(temp,keys[i]);
    }
    return insrt;
}

class node{
    private:
        int* keys;
        node** childs;
        node* parent;
        bool isdata;
        int occupancy;
        int maxocc;
        //int minocc;
    public:
        node(bool dataNode){
            isdata=dataNode;
            occupancy=0;
            if(!isdata){
                maxocc = 2*t+1; //minocc = t;
                childs=(node**)malloc(sizeof(node*)*(2*t+2));
            }else{
                maxocc = 2*d; //minocc = d;
                childs=nullptr;
            }
            keys=(int*)malloc(sizeof(int)*(maxocc));
            parent=nullptr;
        }
        bool isFull(){ if(occupancy<maxocc)return 0; else return 1; }
        void shiftchilds(int k){
            for(int i=2*t+2;  i>k;i--)
                childs[i]=childs[i-1];
            childs[k]=nullptr;
        }
        int insert(int key){
            if(!isFull()){
                int z=insertkey( keys, occupancy, key);
                occupancy++;
                if(!isdata)
                    shiftchilds(z+1);
                return z;
            }return -1;
        }
        bool getisdata(){return isdata;}
        int getkey(int k){return keys[k];}
        int* getkeys(){return keys;}
        node* getchild(int k){return childs[k];}
        node** getchilds(){return childs;}
        void setchild(node* node, int k){childs[k]=node;}
        node* getparent(){return parent;}
        void setparent(node* p){parent=p;}
        int getocc(){return occupancy;}
        void clr(){occupancy=0;}
        //void del(int key){}
        void printnode(){
            //cout<<"occ:"<<occupancy<<"/"<<maxocc<<endl;
            REP(i,occupancy)
                cout<<keys[i]<<" ";
        }
};

void insertchild(node** childs, int occupancy, int x, node* n1){
    node* temp;bool ins=false;
    REP(i,occupancy+1){
        if(!ins){
            if(i==x){
                temp=childs[i];
                childs[i]=n1;
                ins=1;
            }
        }
        else swap(temp,childs[i]);
    }
}

pair<int,int> count(node* n1){
    int i=0; int d=0;
    if(n1!=nullptr){
        if(n1->getisdata())
            d++;
        else {
            i++;
            for(int x=0;x<(n1->getocc()+1);x++){
                pair<int,int> p=count(n1->getchild(x));
                i+=p.first;
                d+=p.second;
            }
        }
    }
    return make_pair(i,d);
}

void printtree(node* n1){
    if(n1==nullptr)return;
    //cout<<"{"<<n1->getisdata()<<"} ";
    n1->printnode();
    
    if(n1->getisdata()==0){ //if n1 != index node
        cout<<" c( ";
        int occ=n1->getocc();
        REP(i,occ+1){
            printtree(n1->getchild(i));
            cout<<" :: ";
        }
        cout<<") ";
    }
    
}

node* splitindexnode(node* n1, int key, node* n2 ){
    //split index node...
    int* temp1=n1->getkeys();//copy all keys
    int occ=n1->getocc(); 
    int temp[occ+1];
    copy(temp1, temp1+occ, temp);
    int z=insertkey(temp, occ, key); //insert new key 

    node** temp2=n1->getchilds();//copy all childs
    node* tmpchilds[occ+2];
    copy(temp2, temp2+occ+1, tmpchilds);
    insertchild(tmpchilds, occ+1 , z+1, n2);//insert new child n2

    node* newnode=new node(0);
    node* toReturn=nullptr;
    if(n1->getparent()==nullptr){
        node* parent =new node(0);
        toReturn=parent;
        parent->setchild(n1,0);
        n1->setparent(parent);
    }
    node* p=n1->getparent();
    
    n1->clr();
    FOR(i,0, t){
        n1->insert(temp[i]);
        n1->setchild(tmpchilds[i], i);
    }n1->setchild(tmpchilds[t], t);
    int j=0;
    FOR(i,t+1, occ+1){
        newnode->insert(temp[i]);
        newnode->setchild(tmpchilds[i], j);
        tmpchilds[i]->setparent(newnode);
        j++;
    }newnode->setchild(tmpchilds[occ+1], j);
    tmpchilds[occ+1]->setparent(newnode);
    if(!p->isFull()){
        int y= p->insert(temp[t]);
        p->setchild(newnode,y+1);newnode->setparent(p);
    }else{
        //cout<<"Index Node's parent is Full\n";
        toReturn=splitindexnode(p, temp[t], newnode);
    }
    return toReturn;
}

node* splitDataNode(node* n1, int key){
    int* temp1=n1->getkeys();
    int occ=n1->getocc(); 
    int temp[occ+1];
    copy(temp1, temp1+occ, temp);
    insertkey(temp, occ, key);

    node* newnode=new node(1);
    node* toReturn=nullptr;
    if(n1->getparent()==nullptr){
        node* parent =new node(0);
        toReturn=parent;
        parent->setchild(n1,0);
        n1->setparent(parent);
    }
    node* p=n1->getparent();
    n1->clr();
    FOR(i,0, d){n1->insert(temp[i]);}
    FOR(i,d, occ+1){newnode->insert(temp[i]);}

    if(!p->isFull()){
        int x= p->insert(newnode->getkey(0));
        p->setchild(newnode,x+1);newnode->setparent(p);
    }else{
        toReturn=splitindexnode(p, newnode->getkey(0), newnode);
    }
    return toReturn;
}

class BPlusTree{
    private:
        node* root;
    public:
        BPlusTree(){
            root=nullptr;
        }
        void insert(int key){
            if(root==nullptr){
                root=new node(1);
                root->insert(key);
                return;
            }else{
                //travel to data node...
                node* curr=root;
                while(!curr->getisdata()){
                    int i=0;
                    for(;i<curr->getocc();i++)
                        if(key < curr->getkey(i))
                            {curr=curr->getchild(i);break;}
                    if(i==curr->getocc())
                        curr=curr->getchild(curr->getocc());
                }
                if(!curr->isFull()){
                    curr->insert(key);
                }else{
                    node* n2=splitDataNode(curr,key);
                    if(n2!=nullptr)root=n2;
                }
            }
        }
        void print(){
            if(root!=nullptr){
                pair<int, int> p=count(root);
                cout<<p.first<<" "<<p.second<<" ";
                root->printnode();
                cout<<endl;
            }else cout<<"0 0\n";
        }
        void print2(){
            printtree(root);
            cout<<endl;
        }
};

signed main(){
    FAST_IO
    cin>>d>>t;
    BPlusTree T;
    int x;
    while(cin>>x)
        switch(x){
            case 1: int y; cin>>y; T.insert(y); break;
            case 2: T.print(); break;
            case 3: goto end; break;
            case 4: T.print2(); break;
            default: cout<<".\n"; break;
        }
    
    end:
    return 0;
}