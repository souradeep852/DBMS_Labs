#include <bits/stdc++.h>
#define loop(i,n) for(long long i=0;i<n;i++)
#define revLoop(i,n) for(long long i=n-1;i>=0;i--)
#define all(x) (x).begin(), (x).end()
#define sqr(a) (a)*(a);
#define cy cout<<"YES"<<endl;
#define cn cout<<"NO"<<endl;
#define vll vector<ll>
 
typedef long long ll;
typedef unsigned long long ull;
 
using namespace std;

int t,d;

int nextPos(vector<int>v)
{
    int siz=v.size();
    loop(i,siz) if(v[i]==INT_MAX) return i;
    return -1;
}  

int findIdx(vector<int>v,int a)
{
    int n=v.size();
    loop(i,n-1)
    {
        if(v[i]<a&&v[i+1]>a) return i;
    }
    return -1;
}

class Node
{
    private:
        int freeSlots;
        bool isLeaf;
    public:
        vector<int>data;
        vector<Node*>ptrs;
        void setLeafStatus(bool a){isLeaf=a;};
        void setFreeSlots(int a){freeSlots=a;};
        void incrFreeSlots(){freeSlots++;};
        void decrFreeSLots(){freeSlots--;};
        int getFreeSLots(){return freeSlots;};
        bool getLeafStatus(){return isLeaf;};
        Node* makeIndexNode();
        Node* makeDataNode();
};

Node* Node::makeIndexNode()
{
    Node* node = new Node();
    node->isLeaf=false;
    loop(i,2*t+1) node->data.push_back(INT_MAX);
    loop(i,2*t+2) node->ptrs.push_back(nullptr);
    node->setFreeSlots(2*t+1);
    return node;
}
Node* Node::makeDataNode()
{
    Node* node = new Node();
    node->isLeaf=true;
    loop(i,2*d) node->data.push_back(INT_MAX);
    node->setFreeSlots(2*d);
    return node;
}

class BpTree
{
    public:
        Node* root;
        BpTree();
        void insert(int a);
        Node* getApprDataNode(Node*,int);
        Node* splitNode(Node* ,int);
        Node* getParent(Node*, int);
};

BpTree::BpTree()
{
    root = nullptr;
}

Node* BpTree::getParent(Node* node,int a)
{
    if(node->ptrs[0]->getLeafStatus()) return node;
    if(find(all(node->data),a)!=node->data.end())
    {
        auto it=find(all(node->data),a);
        int idx=it-node->data.begin();
        return getApprDataNode(node->ptrs.at(idx+1),a);
    }
    else if(a<node->data.at(0)) return getApprDataNode(node->ptrs.at(0),a);
    else if(a>node->data.at(2*t)) return getApprDataNode(node->ptrs.at(2*t+1),a);
    else
    {
        int idx=findIdx(node->data,a);
        return getApprDataNode(node->ptrs.at(idx+1),a);
    }
}

Node* BpTree::splitNode(Node* node,int a)
{
    vector<int>temp=node->data;
    temp.push_back(a);
    sort(all(node->data));
    loop(i,2*d) node->data.at(i)=INT_MAX;
    node->setFreeSlots(2*d);
    loop(i,d) {node->data.at(i)=temp[i];node->decrFreeSLots();}
    Node* split=new Node();
    split=split->makeDataNode();
    int k=0;
    for(int i=d;i<2*d;i++)
    {
        split->data.at(k)=temp[i];
        k++;
        split->decrFreeSLots();
    }
    split->data.at(nextPos(split->data))=a;
    split->decrFreeSLots();
    return split;
}

Node* BpTree::getApprDataNode(Node* node,int a)
{
    if(node->getLeafStatus()) return node;
    if(find(all(node->data),a)!=node->data.end())
    {
        auto it=find(all(node->data),a);
        int idx=it-node->data.begin();
        return getApprDataNode(node->ptrs.at(idx+1),a);
    }
    else if(a<node->data.at(0)) return getApprDataNode(node->ptrs.at(0),a);
    else if(a>node->data.at(2*t)) return getApprDataNode(node->ptrs.at(2*t+1),a);
    else
    {
        int idx=findIdx(node->data,a);
        return getApprDataNode(node->ptrs.at(idx+1),a);
    }
}

void BpTree::insert(int a)
{
    if(root==nullptr)
    {
        Node* node = new Node();
        node=node->makeDataNode();
        node->data.at(nextPos(node->data))=a;
        node->decrFreeSLots();
        root=node;
        return;
    }
    if(root->getLeafStatus())
    {
        if(root->getFreeSLots()>0)
        {
            root->data.at(nextPos(root->data))=a;
            root->decrFreeSLots();
            sort(all(root->data));
            return;
        }
        else
        {
            Node* node = new Node();
            node=node->makeDataNode();
            int k=0;
            for(int i=d;i<2*d;i++)
            {
                node->data.at(k)=root->data.at(i);
                k++;
                node->decrFreeSLots();
                root->data.at(i)=INT_MAX;
                root->incrFreeSlots();
            }
            node->data.at(nextPos(node->data))=a;
            node->decrFreeSLots();
            Node* temp=root;
            root = root->makeIndexNode();
            root->ptrs.at(0)=temp;
            root->ptrs.at(1)=node;
            root->data.at(nextPos(root->data))=node->data.at(0);
            root->decrFreeSLots();
        }
        return;
    }
    else
    {
        Node* node=getApprDataNode(root,a);
        if(node->getFreeSLots()>0)
        {
            node->data.at(nextPos(node->data))=a;
            sort(all(node->data));
            node->decrFreeSLots();
            return;
        }
        else
        {
            Node* split=splitNode(node,a);
            Node* parent=getParent(root,node->data.at(0));
            if(parent->getFreeSLots()>0)
            {
                int d=split->data.at(0),idx,upto;
                loop(i,2*t+1)
                {
                    if(parent->data.at(i)>d){idx=i;break;}
                }
                if(parent->data.at(idx)==INT_MAX)
                {
                    parent->data.at(idx)=d;
                    parent->ptrs.at(idx+1)=split;
                    parent->decrFreeSLots();
                    return;
                }
                loop(i,2*t+1)
                {
                    if(parent->data.at(i)==INT_MAX){upto=i;break;}
                }
                for(int i=upto;i>idx;i--) parent->data.at(i)=parent->data.at(i-1);
                parent->data.at(idx)=split->data.at(0);
                parent->decrFreeSLots();
                for(int i=upto+1;i>idx+1;i--) parent->ptrs.at(i)=parent->ptrs.at(i-1);
                parent->ptrs.at(idx+1)=split;
                return;
            }
            else
            {
                
            }
        }
    }
}    

void solve()
{
    BpTree tree;
    int a,temp;
    vector<vector<int>>instr;
    cin>>d>>t;
    loop(i,21)
    {
        cin>>a;
        if(a==1)
        {
            cin>>temp;
            instr.push_back({a,temp});
        }
        else instr.push_back({a});
    }
    for(auto i:instr)
    {
        if(i[0]==1)
        {
            tree.insert(i[1]);
        }
    }   
}

int main()
{
    solve();
    return 0;
}