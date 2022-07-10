#include<iostream>
#include<stack>
#include<vector>
#include<queue>
using namespace std;
//definition of node
struct node{
	int pnode=0,edge=0,num=0;
	queue<int> cnode;
};
//definition of arr,queue
node nodes[100001];
int res=0;
//DFS
void DFS(int i)
{
	stack<int> stack1;
	stack1.push(i);
	int temp;
	while(!stack1.empty())
	{
		temp=stack1.top();
		//cout<<"processing:"<<temp<<endl;
		stack1.pop();
		nodes[temp].edge+=nodes[nodes[temp].pnode].edge;
		//cout<<"pnode:"<<nodes[temp].pnode<<" "<<"edge="<<nodes[temp].edge<<endl;
		if(nodes[temp].edge>nodes[temp].num) res++;
		while(!nodes[temp].cnode.empty())
		{
			stack1.push(nodes[temp].cnode.front());
			(nodes[temp].cnode).pop();
		}
	}
}
//main
int main()
{
	int n;
	long long num1,num2;
	cin>>n;
	//load
	for(int i=1;i<=n;i++)
	{
		cin>>nodes[i].num;
	}
	for(int i=1;i<=n-1;i++)
	{
		cin>>num1>>num2;
		nodes[i+1].edge=num2;
		nodes[num1].cnode.push(i+1);
		nodes[i+1].pnode=num1;
	}
	//DFS
	for(int i=n;i>=1;i--)
	{
		DFS(i);
	}
	cout<<res<<endl;
}
