#include<iostream>
#include<queue>
#include<set>
#include<vector>
using namespace std;

struct node
{
	int level;
	vector<int> snode;
};

node nodes[200002];
int visited [200002]={};
void BFS()
{
	queue<int> bfs0;
	bfs0.push(1);
	int level0=1;
	int node1,size;
	vector<int>::iterator it;
	while(!bfs0.empty())
	{
		size=bfs0.size();
		while(size--)
		{
			node1=bfs0.front();
			bfs0.pop();
			for(it=nodes[node1].snode.begin();it!=nodes[node1].snode.end();it++)
			{
				bfs0.push(*it);
			}
			nodes[node1].level=level0;
			visited[node1]=1;
		}
		level0++;
	}
}

int main()
{
	int n,num1,num2;
	cin>>n;
	for(int i=1;i<=n-1;i++)
	{
		cin>>num1>>num2;
		if(num1==1)
		{
			nodes[num1].snode.push_back(num2);
			visited[1]=visited[num2]=1;
		}
		if(visited[num1]==1)
		{
			nodes[num1].snode.push_back(num2);
			visited[num2]=1;
		}
		else 
		{
			nodes[num2].snode.push_back(num1);
			visited[num1]=1;
		}
	}
	BFS();
	/*
	for(int i=1;i<=n;i++)
	{
		cout<<i<<" "<<nodes[i].level<<endl;
	}
	*/
	int maxlevel=0,t;
	bool flag=true;
	for(int i=0;i<n;i++)
	{
		cin>>t;
		//cout<<"t="<<t<<" "<<"level="<<nodes[t].level<<endl;
		if(nodes[t].level==maxlevel||nodes[t].level>maxlevel)
		{
			maxlevel=nodes[t].level;
		}
		else {flag=false;break;}
	}
	if(flag==true) cout<<"Yes"<<endl;
	else cout<<"No"<<endl;
	return 0;
	
}
