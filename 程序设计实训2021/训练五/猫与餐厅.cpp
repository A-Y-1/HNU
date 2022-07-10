#include<iostream>
#include<stack>
#include<queue>
#include<cstring>
using namespace std;
struct node{
	int p=-1;
	bool cat;
	queue<int> snode;
};

node nodes[100001];
queue<int> rest;
void DFS( )
{
	stack<int> dfs;
	int t;
	dfs.push(1);
	while(!dfs.empty())
	{
		t=dfs.top();
		dfs.pop();
		if(nodes[t].snode.empty()) {rest.push(t);}
		while(!nodes[t].snode.empty())
		{
			dfs.push(nodes[t].snode.front());
			nodes[t].snode.pop();
		}
	}
}

int main()
{
	int n,m,cats,temp1,temp2;
	cin>>n>>m;
	int vis[n+1];
	memset(vis,0,sizeof(vis));
	vis[1]=1;
	for(int i=1;i<=n;i++)
	{
		cin>>nodes[i].cat;
	}
	for(int i=1;i<=n-1;i++)
	{
		cin>>temp1>>temp2;
		if(vis[temp1]==1)
		{
			nodes[temp2].p=temp1;
			nodes[temp1].snode.push(temp2);
			vis[temp2]=1;
		}
		else if(vis[temp2]==1)
		{
			nodes[temp1].p=temp2;
			nodes[temp2].snode.push(temp1);
			vis[temp1]=1;
		}
	}
	DFS();
	int res=0;
	while(!rest.empty())
	{
		bool flag=true;
		int a=rest.front();
		rest.pop();
		cats=0;
		//cout<<"rest:"<<a<<endl;
		while(nodes[a].p!=-1)
		{
			if(nodes[a].cat==1)
			{
				cats++;
			}
			else cats=0;
			if(cats>m)
			{
				flag=false;
				break;
			}
			a=nodes[a].p;
			//cout<<"cat"<<cats<<" "<<"point:"<<a<<endl;
		}
		if(cats+nodes[1].cat>m) flag=false;
		if(flag==true) 
		{
			res++;
		}
	}
	cout<<res<<endl;
}
