#include <bits/stdc++.h>
#define loop(i,n) for(long long i=0;i<n;i++)
#define revLoop(i,n) for(long long i=n-1;i>=0;i--)
#define all(x) (x).begin(), (x).end()
#define sqr(a) (a)*(a);
#define cy cout<<"YES"<<endl;
#define cn cout<<"NO"<<endl;
 
typedef long long ll;
typedef unsigned long long ull;
 
using namespace std;
int globalTime=0,bucketSize=0,globalDepth=0;

class buckets
{
    private:
        int occupancy,localDepth,creationTime;
        
    public:
        vector<int>bucket;
        buckets(int );
        int getOccupancy(){return occupancy;};
        int getLocalDepth(){return localDepth;};
        int getCreationTime(){return creationTime;};
        void decrOccupancy(){occupancy--;};
        void incrOccupancy(){occupancy++;};
        void setCreationTime(int a){creationTime=a;};
        void incrLocalDepth(){localDepth++;};
        void decrLocalDepth(){localDepth--;};
        void makeBucketEmpty()
        {
            loop(i,bucketSize) bucket[i]=-1;
            occupancy=bucketSize;
        };
        void setLocalDepth(int n)
        {
            localDepth=n;
        }
};

void facilitateRedistribution(map<int,buckets*>&directory,int hashVal,int toInsert);
void redistribute(map<int,buckets*>&directory,vector<int>toInsert,int hashVal);
void doubleDirectory(map<int,buckets*>&directory,int hashVal,int toInsert);
 
void printVector(vector<int>v)
{
    int siz=v.size();
    loop(i,siz) cout<<v[i]<<" ";
    cout<<endl;
}

void print2Dvector(vector<vector<int>>v)
{
    int siz=v.size();
    loop(i,siz)
    {
        printVector(v[i]);
    }
}

string convertNtoBin(int n,int howMany)
{
    string ret="";
    loop(i,howMany)
    {
        if(n>>i&1) ret.push_back('1');
        else ret.push_back('0');
    }
    reverse(all(ret));
    return ret;
}

int calcHashValue(int n,int k)
{
    string s=convertNtoBin(n,k);
    int ret=0;
    n=s.length(),k=0;
    for(int i=n-1;i>=0;i--)
    {
        ret+=pow(2,k)*(s[i]=='1');
        k++;
    }
    return ret;
}

int nextPos(vector<int>v)
{
    int siz=v.size();
    loop(i,siz) if(v[i]==-1) return i;
    return -1;
}    

template <typename T>
void remove_duplicates(std::vector<T>& vec)
{
  std::sort(vec.begin(), vec.end());
  vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
}

buckets :: buckets(int ld)
{
    occupancy = bucketSize;
    creationTime = globalTime;
    globalTime++;
    localDepth = ld;
    loop(i,bucketSize) bucket.push_back(-1);
}

int calcMirror(int n)
{
    int real=n;
    int mir1=real+pow(2,globalDepth-1);
    int mir2=pow(2,globalDepth);
    int mirror = (mir1)%(mir2);
    return mirror;
}

void facilitateRedistribution(map<int,buckets*>&directory,int hashVal,int toInsert)
{
    vector<int>temp;
    temp=directory[hashVal]->bucket;
    int ld=directory[hashVal]->getLocalDepth();
    buckets* b=directory[hashVal];
    vector<int>store;
    for(auto i:directory)
    {
        if(i.second==b) {store.push_back(i.first);}
    }
    int k=store.size();
    temp.push_back(toInsert);
    if(k==2)
    {
        directory[store[0]]->makeBucketEmpty();
        directory[store[0]]->incrLocalDepth();
        b=new buckets(ld+1);
        directory[store[1]]=b;
    }
    else
    {
        vector<int>store1,store2;
        loop(i,k) 
        {
            if(i%2==0) store1.push_back(store[i]);
            else store2.push_back(store[i]);
        }
        directory[store1[0]]->makeBucketEmpty();
        directory[store1[0]]->incrLocalDepth();
        b=new buckets(directory[store1[0]]->getLocalDepth());
        for(auto i:store2) 
            directory[i]=b;
    }
    
    redistribute(directory,temp,hashVal);
}

void redistribute(map<int,buckets*>&directory,vector<int>toInsert,int hashVal)
{
    int ld = directory[hashVal]->getLocalDepth();
    for(auto i:toInsert)
    {
        hashVal=calcHashValue(i,globalDepth);
        if(directory[hashVal]->getOccupancy()>0)
        {
            directory[hashVal]->bucket.at(nextPos(directory[hashVal]->bucket))=i;
            directory[hashVal]->decrOccupancy();
        }
        else
        {
            if(ld<globalDepth)
            {
                facilitateRedistribution(directory,hashVal,i);
            }
            else
            {
                doubleDirectory(directory,hashVal,i);
            }
        }
    }
}

void doubleDirectory(map<int,buckets*>&directory,int hashVal,int toInsert)
{
    int gd=globalDepth;
    globalDepth++;
    map<int,buckets*>m=directory;
    for(auto i:m)
    {
        if(i.first!=hashVal)
        {
            directory[i.first+pow(2,gd)]=directory[i.first];
        }
        else
        {
            int temp1=i.first;
            buckets* temp2 = i.second;
        }
    }
    vector<int>temp=directory[hashVal]->bucket;
    temp.push_back(toInsert);
    remove_duplicates(temp);
    directory[hashVal]->makeBucketEmpty();
    directory[hashVal]->incrLocalDepth();
    directory[hashVal+pow(2,gd)]=new buckets(directory[hashVal]->getLocalDepth());
    directory[hashVal+pow(2,gd)]->setLocalDepth(directory[hashVal]->getLocalDepth());
    for(auto i:temp)
    {
        hashVal=calcHashValue(i,globalDepth);
        if(directory[hashVal]->getOccupancy()>0)
        {
            directory[hashVal]->bucket.at(nextPos(directory[hashVal]->bucket))=i;
            directory[hashVal]->decrOccupancy();
        }
        else
        {
            if(directory[hashVal]->getLocalDepth()<globalDepth)
            {
                facilitateRedistribution(directory,hashVal,i);
            }
            else
            {
                doubleDirectory(directory,hashVal,i);
            }
        }
    }
}

int searchVal(map<int,buckets*>directory,int n)
{
    int hashVal=calcHashValue(n,globalDepth);
    vector<int>temp=directory[hashVal]->bucket;
    if(find(all(temp),n)!=temp.end()) return hashVal;
    else return -1;
}

void deleteVal(map<int,buckets*>&directory,int n)
{
    if(searchVal(directory,n)==-1) return;
    else 
    {
        int hashVal=calcHashValue(n,globalDepth);
        vector<int>temp=directory[hashVal]->bucket;
        auto it=find(all(temp),n);
        int idx=it-temp.begin();
        directory[hashVal]->bucket.at(idx)=-1;
        directory[hashVal]->incrOccupancy();
    }
}

vector<buckets*> numBuckets(map<int,buckets*>directory)
{
    vector<buckets*>v;
    for(auto i:directory)
    {
        v.push_back(i.second);
    }
    remove_duplicates<buckets*>(v);
    return v;
}

bool sortTime(buckets* b1, buckets* b2)
{
    return (b1->getCreationTime()<b2->getCreationTime());
}

void showStatus(map<int,buckets*>directory)
{
    cout<<globalDepth<<endl;
    vector<buckets*>v=numBuckets(directory);
    cout<<v.size()<<endl;
    sort(all(v),sortTime);
    loop(i,v.size()) 
    {
        cout<<bucketSize-v[i]->getOccupancy()<<" "<<v[i]->getLocalDepth()<<endl;
    }
}

void compressDirectory(map<int,buckets*>&directory)
{
    for (auto i : directory)
    {
        int mirror = calcMirror(i.first);
        if (mirror < i.first)
        {
            directory[i.first] = nullptr;
            directory.erase(i.first);
        }
    }
    globalDepth--;
    return;
}

bool checkIfDirCompressible(map<int,buckets*>directory)
{
    for(auto i:directory)
    {
        int mirror = calcMirror(i.first);
        if(directory[i.first]!=directory[mirror]) return false;
    }
    return true;
}

void fullDelete(map<int,buckets*>&directory,int n)
{
    if(searchVal(directory,n)==-1) return;
    int val=searchVal(directory,n);
    deleteVal(directory,n);
    if(!checkIfDirCompressible(directory))
    {
        if(directory[val]->getOccupancy()==bucketSize)
        {
            directory[val]=directory[calcMirror(val)];
            directory[val]->decrLocalDepth();
            directory[calcMirror(val)]->decrLocalDepth();
        }
        if(checkIfDirCompressible(directory))
        {
            compressDirectory(directory);
        }
        else return;
    }
    else
    {
        compressDirectory(directory);
    }
}

void solve()
{
    cin>>globalDepth>>bucketSize;
    int a,temp;
    vector<vector<int>>instr;
    while(cin>>a)
    {
        if(a==2||a==3||a==4)
        {
            cin>>temp;
            instr.push_back({a,temp});
        }
        else instr.push_back({a});
    }
    map<int,buckets*>directory;
    int upto=pow(2,globalDepth);
    loop(i,upto)
    {
        buckets* b=new buckets(globalDepth);
        directory[i]=b;
    }
    
    for(auto i:instr)
    {
        if(i[0]==2)
        {
            int hashVal=calcHashValue(i[1],globalDepth);
            int ld = directory[hashVal]->getLocalDepth();
            if(directory[hashVal]->getOccupancy()>0)
            {
                directory[hashVal]->bucket.at(nextPos(directory[hashVal]->bucket))=i[1];
                directory[hashVal]->decrOccupancy();
            }
            else
            {
                if(ld<globalDepth)
                {
                    facilitateRedistribution(directory,hashVal,i[1]);
                }
                else
                {
                    doubleDirectory(directory,hashVal,i[1]);
                }
            }
            
        }
        else if(i[0]==3)
        {
            if(searchVal(directory,i[1])!=-1) cout<<"Found\n";
            else cout<<"Not found\n";
        }
        else if(i[0]==4) deleteVal(directory,i[1]);
        else if(i[0]==5) showStatus(directory);
        else return;
    }
}

int main()
{
    solve();
    return 0;
}