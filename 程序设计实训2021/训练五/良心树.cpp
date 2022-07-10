#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
int main()
{
	int n,m=0;
	cin>>n;
	int p[n],b[n],res[n];
	for(int i=0;i<n;i++)
	{
		cin>>p[i]>>b[i];
	}
	for(int i=0;i<n;i++)
	{
		if(b[i]==1)
		{
			bool flag=true;
			int count=0;
			for(int j=0;j<n;j++)
			{
				if(p[j]==i+1&&b[j]==0)
				{
					//cout<<"出现尊重的子节点："<<j<<endl;
					flag=false;
					break;
				}
				else if(p[j]!=i+1) count++;
			}
			if(count==0) flag=false;
			//cout<<"检查第"<<i+1<<"个点"<<" "<<flag<<endl;
			if(flag==true)
			{
				res[m]=i+1;
				m++;
				for(int j=0;j<n;j++)
				{
					if(p[j]==i) p[j]=p[i];
				}
			}
		}
	}
	if(m==0) cout<<-1<<endl;
	else for(int i=0;i<m;i++)
	{
		cout<<res[i]<<" ";
	}
	cout<<endl;	
}
