#include<iostream>
#include<algorithm>
using namespace std;
//邻接矩阵，距离数组，访问数组
int vis[100],dis[100];
int inf=99999;
int arr[100][100];
int path[100];
//dijkstra算法
void dijkstra(int n)
{
	//初始化
	int ans,k;
	for(int i=0;i<n;i++)
	{
		dis[i]=arr[0][i];
		vis[i]=0;
		path[i]=-1;
	}
	//
	vis[0]=1;
	for(int i=0;i<n;i++)
	{
		ans=-1;
		for(int j=0;j<n;j++)
		{
			if(vis[j]==0&&dis[j]>ans&&dis[j]>0)
			{
				ans=dis[j];
				k=j;
			}
		}
		vis[k]=1;
		if(ans==-1) break;
		for(int j=0;j<n;j++)
		{
			if(!vis[j]&&arr[k][j]+dis[k]>dis[j]&&arr[k][j]!=0)//点能够途经且费用更大
			{
				dis[j]=arr[k][j]+dis[k];
				path[j]=k;
			}
		}
	}
}
int main()
{
	int n,num1,num2,cost;
	cin>>n;
	for(int i=0;i<n-1;i++)
	{
		cin>>num1>>num2>>cost;
		arr[num1][num2]=cost;
		arr[num2][num1]=cost;
	}
	dijkstra(n);
	sort(dis,dis+n);
	cout<<dis[n-1]<<endl;
}

