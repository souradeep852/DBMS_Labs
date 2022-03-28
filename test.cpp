#include<bits/stdc++.h>
using namespace std;

int main()
{
    vector<int> v1={23,2,52,31};
    vector<int> v2={23,31,66,11};
    set_union(v1.begin(),v1.end(),v2.begin(),v2.begin(),v1.begin());
    return 0;
}