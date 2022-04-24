#include <bits/stdc++.h>
#define loop(i,n) for(long long i=0;i<n;i++)
#define revLoop(i,n) for(long long i=n-1;i>=0;i--)
#define all(x) (x).begin(), (x).end()
#define sqr(a) (a)*(a);
#define cy cout<<"YES"<<endl;
#define cn cout<<"NO"<<endl;
#define SENTINEL INT_MAX
 
typedef long long ll;
typedef unsigned long long ull;
int recordsPerPage,bufferCap,noOfRecords,passNo=0;

using namespace std;
vector<vector<int>>pages;

double log_a_to_base_b(ll a, ll b)
{
    return log(a) / log(b);
}

int calcFilledSlots(vector<vector<int>>v)
{
    int ct=0;
    int siz=v.size();
    loop(i,siz)
    {
        if(!v[i].empty()) ct++;
    }
    return ct;
}

vector<vector<int>>kWayMerge(vector<vector<int>>memory)
{
    vector<int>ptrs(bufferCap-1,0);
    int ctr=calcFilledSlots(memory)*recordsPerPage;
    vector<vector<int>>ret;
    vector<int>minAll;
    int k=calcFilledSlots(memory);
    loop(i,ctr)
    {
        minAll.clear();
        loop(j,k) minAll.push_back(memory[j][ptrs[j]]);
        auto it=min_element(all(minAll));
        memory[bufferCap-1].push_back(*it);
        int idx=it-minAll.begin();
        ptrs[idx]++;
        if(memory[bufferCap-1].size()==recordsPerPage) 
        {
            ret.push_back(memory[bufferCap-1]);
            memory[bufferCap-1].clear();
        }
    }
    return ret;
}

    
void solve()
{
    cin>>bufferCap>>recordsPerPage>>noOfRecords;
    vector<int>temp;
    int ctr=0;
    int a;
    vector<vector<int>>memory(bufferCap);
    for(int i=0;i<noOfRecords;i+=recordsPerPage)
    {
        loop(j,min(recordsPerPage,noOfRecords-i))
        {
            cin>>a;
            temp.push_back(a);
        }
        pages.push_back(temp);
        temp.clear();
    }
    int noOfPages=noOfRecords/recordsPerPage+(noOfRecords%recordsPerPage!=0);
    int pass0=noOfPages/bufferCap+(noOfPages%bufferCap!=0);
    int noOfPasses=ceil((double)log_a_to_base_b(pass0,bufferCap-1))+1;
    
    //pass0;
    for(int i=0;i<noOfPages;i+=bufferCap)
    {
        loop(j,bufferCap) memory[j].clear(); 
        int j;
        loop(j,min(bufferCap,noOfPages-i)) memory[j]=pages[i+j];
        int siz=calcFilledSlots(memory);
        loop(k,siz) sort(all(memory[k]));
        int k;
        for(k=i;k<(i+siz);k++) 
            pages[k]=memory[k-i];
    }
    //memory.clear();
    passNo++;
    loop(i,noOfPages) pages[i].push_back(SENTINEL);

    //pass1
    for(int i=0;i<noOfPages;i+=(bufferCap-1))
    {
        loop(j,bufferCap) memory[j].clear(); 
        vector<vector<int>>passed;
        int j;
        int rem=noOfPages-i;
        loop(j,min(bufferCap-1,rem)) memory[j]=pages[j+i];
        passed=kWayMerge(memory);
        loop(j,passed.size()) pages[i+j]=passed[j];
    }

    loop(i,pages.size())
    {
        int siz=pages[i].size();
        loop(j,siz) cout<<pages[i][j]<<" ";
        cout<<endl;
    }
}

int main()
{
    solve();
    return 0;
} 