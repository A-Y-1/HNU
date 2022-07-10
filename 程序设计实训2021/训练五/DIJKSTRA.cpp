#include<iostream>
using namespace std;
int inf=9999999;
int matrix[10001][10001];
int dis[10001],path[10001],vis[10001];
void pathout(int x)
{
	if(path[x]==-1) return;
	pathout(path[x]);
	cout<<path[x]<<" ";
	return;
}
int main()
{
	int n,m,k,t1,t2,t3,ans;
	cin>>n>>m;

	//初始化邻接矩阵
	for(int i=0;i<n+1;i++)
	{
		for(int j=1;j<n+1;j++)
		{
			matrix[i][j]=inf;
		}
	}
	//输入图
	for(int i=0;i<m;i++)
	{
		cin>>t1>>t2>>t3;
		matrix[t1][t2]=t3;
		matrix[t2][t1]=t3;
	}
	//初始化
	for(int i=0;i<n+1;i++)
	{
		dis[i]=matrix[1][i];
		path[i]=-1;
		vis[i]=0;
	}
	dis[1]=0;
	vis[1]=1;
	for(int i=1;i<n+1;i++)
	{
		ans=inf;
		for(int j=1;j<n+1;j++)
		{
			if(vis[j]==0&&dis[j]<ans)
			{
				ans=dis[j];
				k=j;
			}
		}
		vis[k]=1;
		if(ans==inf) break;
		for(int j=1;j<n+1;j++)
		{
			if(!vis[j]&&dis[j]>matrix[j][k]+dis[k])
			{
				dis[j]=matrix[j][k]+dis[k];
				path[j]=k;
			}
		}
	}
	if(dis[n]==inf) cout<<-1<<endl;
	else 
	{
		cout<<1<<" ";
		pathout(n);
		cout<<n<<endl;
	}
}
