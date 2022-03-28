#include <bits/stdc++.h>
#define loop(i,n) for(long long i=0;i<n;i++)
#define revLoop(i,n) for(long long i=n-1;i>=0;i--)
#define all(x) (x).begin(), (x).end()

using namespace std;
 
void makeCombiUtil(vector<vector<int> >& ans,
	vector<int>& tmp, int n, int left, int k)
{

	if (k == 0) {
		ans.push_back(tmp);
		return;
	}

	for (int i = left; i <= n; ++i)
	{
		tmp.push_back(i);
		makeCombiUtil(ans, tmp, n, i + 1, k - 1);
		tmp.pop_back();
	}
}

vector<vector<int> > makeCombi(int n, int k)
{
	vector<vector<int> > ans;
	vector<int> tmp;
	makeCombiUtil(ans, tmp, n, 1, k);
	return ans;
}

bool isSubset(vector<int>v1,vector<int>v2)
{
    sort(all(v1));sort(all(v2));
    int siz1=v1.size(),siz2=v2.size();
    loop(i,siz1)
    {
        if(find(all(v2),v1[i])==v2.end()) return false;
    }
    return true;
}

vector<int> findAttrClosure(int n,multimap<vector<int>,vector<int>>m,vector<int>closure)
{
    vector<int>check=closure;
    do
    {
        check=closure;
        for(auto i:m)
        {
            vector<int>temp1=i.first;
            vector<int>temp2=i.second;
            int siz1=temp1.size(),siz2=temp2.size();
            if(isSubset(temp1,closure))
            {
                loop(j,siz2)
                {
                    if(find(all(closure),temp2[j])==closure.end()) closure.push_back(temp2[j]);
                }
            }
        }
    }while(check!=closure);
    
    return closure;
}

bool checkIfAlreadySubset(vector<vector<int>>v1,vector<int>v2)
{
    int siz=v1.size();
    loop(i,siz)
    {
        if(isSubset(v1[i],v2)) return true;
    }
    return false;
}

vector<int>returnVectorFrom(string s)
{
	vector<int>ret;
	vector<string> vstrings; 
	istringstream iss(s); 
	for(string s; iss >> s; ) 
    	vstrings.push_back(s); 
	int siz=vstrings.size();
	loop(i,siz)
	{
		int n=stoi(vstrings[i]);
		ret.push_back(n);
	}
	return ret;
}

bool sortSiz(const vector<int>& v1,const vector<int>& v2) { 
    return v1.size() < v2.size(); 
} 
    
void solve()
{
    int n=0,f=0;
    cin>>n>>f;
    multimap<vector<int>,vector<int>>m;
    pair<vector<int>,vector<int>>p;
    vector<string>v;
    string s;
    getline(cin,s);
    loop(i,2*f)
    {
        getline(cin,s);
        v.push_back(s);
    }
    for(int i=0;i<2*f;i+=2)
    {
        string left=v[i];
        string right=v[i+1];
        p.first=returnVectorFrom(left);
        p.second=returnVectorFrom(right);
        m.insert(p);
    }
    vector<int>closure;
    vector<int>check(n);
    loop(i,n) check[i]=i+1;
    vector<vector<int>>candidateKeys;
    for(int i=1;i<=n;i++)
    {
        vector<vector<int>>combi=makeCombi(n,i);
        int siz=combi.size();
        loop(j,siz)
        {
            closure=combi[j];
            int siz1=candidateKeys.size();
            if(!checkIfAlreadySubset(candidateKeys,closure))
            {
                closure=findAttrClosure(n,m,closure);
                sort(all(closure));
                if(closure==check) candidateKeys.push_back(combi[j]);
                closure.clear();
            } 
        }
    }
    sort(all(candidateKeys),sortSiz);
    int siz=candidateKeys.size();
    cout<<siz<<endl;
    loop(i,siz)
    {
        int siz1=candidateKeys[i].size();
        loop(j,siz1) cout<<candidateKeys[i][j]<<" ";
        cout<<endl;
    }
}

int main()
{
    solve();
    return 0;
}