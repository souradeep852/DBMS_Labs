#include <bits/stdc++.h>
using namespace std;
multimap<vector<int>, vector<int>> mm;
int n;
int f;

void makeCombiUtil(vector<vector<int>> &ans, vector<int> &tmp, int n, int left, int k)
{

    if (k == 0)
    {
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

vector<vector<int>> makeCombi(int n, int k)
{
    vector<vector<int>> ans;
    vector<int> tmp;
    makeCombiUtil(ans, tmp, n, 1, k);
    return ans;
}

bool FirstIsSubsetOfSecond(vector<int> v1, vector<int> v2)
{
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    for (auto it = v1.begin(); it < v1.end(); it++)
    {
        if (find(v2.begin(), v2.end(), *it) == v2.end())
            return false;
    }
    return true;
}

bool AlreadyIsSubset(vector<int> a, vector<vector<int>> b)
{
    int siz = b.size();
    for (int i = 0; i < siz; i++)
    {
        if (FirstIsSubsetOfSecond(a, b[i]))
        {
            return true;
        }
    }
    return false;
}

vector<int> findAttrClosure(vector<int> a)
{
    vector<int> temp;
    do
    {
        temp = a;
        for (auto i : mm)
        {
            vector<int> leftpart = i.first;
            vector<int> rightpart = i.second;
            if (FirstIsSubsetOfSecond(leftpart, a))
            {
                for (auto j : rightpart)
                {
                    if (find(a.begin(), a.end(), j) == a.end())
                        a.push_back(j);
                }
            }
        }
        if (temp == a)
            break;
        else
            temp = a;
    } while (1);

    return a;
}

bool FirstIsSupersetOfEachVectorInSecond(vector<int> a, vector<vector<int>> b)
{
    int ss=b.size();
    for(int i=0;i<ss;i++)
    {
        if(!FirstIsSubsetOfSecond(b[i],a))
        {
            return false;
        }
    }
    return true;
}


bool checkIfAlreadySubset(vector<vector<int>>v1,vector<int>v2)
{
    int siz=v1.size();
    for(int i=0;i<siz;i++)
    {
        if(FirstIsSubsetOfSecond(v1[i],v2)) return true;
    }
    return false;
}

bool sortlex(const vector<int> &v1, const vector<int> &v2)
{
    return v1.size()<v2.size();
}

void solve()
{
    cin >> n >> f;
    string s;
    getline(cin, s);
    vector<string> v;
    for (int i = 0; i < 2 * f; i++)
    {
        getline(cin, s);
        v.push_back(s);
    }
    for (int i = 0; i < 2 * f; i += 2)
    {
        string sleft = v[i];
        string sright = v[i + 1];
        istringstream my_left(v[i]);
        istringstream my_right(v[i + 1]);
        vector<int> leftv, rightv;
        int u;
        int w;
        while (my_left)
        {
            my_left >> u;
            leftv.push_back(u);
        }
        while (my_right)
        {
            my_right >> w;
            rightv.push_back(w);
        }
        mm.insert(make_pair(leftv, rightv));
        leftv.clear();
        rightv.clear();
    }
    vector<vector<int>> cand_keys;
    vector<vector<int>> all_combi;
    vector<int> closure;
    vector<int> check(n);
    vector<vector<int>> superkey;

    for (int i = 0; i < n; i++)
    {
        check[i] = i + 1;
    }

    for (int i = 0; i < n; i++)
    {
        all_combi = makeCombi(n, i);
        int sz = all_combi.size();
        for (int j = 0; j < sz; j++)
        {
            closure = all_combi[j];
            if(!checkIfAlreadySubset(cand_keys,closure))
            {
                closure=findAttrClosure(closure);
                sort(closure.begin(),closure.end());
                if(closure==check)
                    cand_keys.push_back(all_combi[j]);

            }
            // closure = findAttrClosure(closure);
            // sort(closure.begin(), closure.end());
            // if (check == closure)
            // {
            //     superkey.push_back(all_combi[j]);
            // }
            // if (!FirstIsSupersetOfEachVectorInSecond(all_combi[j], cand_keys)) 
            // {
            //     cand_keys.push_back(all_combi[j]);
            // }
        }
    }

    int num_of_cand = cand_keys.size();
    cout << num_of_cand << endl;
    sort(cand_keys.begin(),cand_keys.end(),sortlex);
    
    
    //sorting cand_keys baaki hai abhi bhi

    for (int i = 0; i < num_of_cand; i++)
    {
        for (auto k : cand_keys[i])
        {
            cout << k << " ";
        }
        cout << endl;
    }
}

int main()
{
    solve();
    return 0;
}