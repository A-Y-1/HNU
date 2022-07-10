#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define met(a,b) memset(a,b,sizeof(a))
#define inf 0x3f3f3f3f
const int maxn = 1e5+10;
typedef long long ll;
vector<pair<int,ll> > v[maxn];
int visited[maxn];
int num[maxn];
ll ans;

void dfs(int x,ll sum)
{
    visited[x]=1;
    if(sum<=num[x])
        ans++;
    else
        return;
    for(int i=0;i<v[x].size();i++)
    {
        if(!visited[v[x][i].first])
        {
            dfs(v[x][i].first,max((ll)0,sum+v[x][i].second));
        }
    }
}

int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>num[i];
    for(int i=2;i<=n;i++)
    {
        int a;
        ll b;
        cin>>a>>b;
        v[i].push_back(make_pair(a,b));
        v[a].push_back(make_pair(i,b));
    }
    met(visited,0);
    ans=0;
    dfs(1,0);
    cout<<n-ans<<endl;
}
