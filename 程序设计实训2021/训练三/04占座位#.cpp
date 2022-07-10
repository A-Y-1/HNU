#include<iostream>
#include<string>
using namespace std;
struct p{
	int start,end,id;
	bool reserveif=false;
};
int main()
{
	int n,m,k,id,num;
	string request;
	cin>>n>>m;
	m=n*n;
	int seat[10001]={};
	cin>>m;
	p info[m];
	for(int i=0;i<m;i++)
	{
		cin>>request;
		if(request=="in") cin>>id>>num;
		else cin>>id;
		if(info[id].reserveif==true&&request=="in") 
		{
			cout<<"no"<<endl;
			continue;
		}
		else if(request=="out"&&info[id].reserveif==false)
		{
			continue;
		}
		if(request=="in")
		{
			k=0;
			for(int j=0;j<n*n;j++)
			{
				if(j==0&&seat[0]==0) k=1;
				else if(j!=0&&seat[j]==0&&seat[j-1]!=0) k=1;
				else if(j!=0&&seat[j]==0&&seat[j-1]==0) k++;
				else k=0;
				if(k==num)
				{
					info[id].reserveif=true;
					info[id].end=j;
					info[id].start=j-num+1;
				}
			}
			if(info[id].reserveif==true)
			{
				for(int j=info[id].start;j<=info[id].end;j++)
				{
					seat[j]=1;
				}
				cout<<"yes"<<endl;
			}
			else cout<<"no"<<endl;
		}
		else if(request=="out")
		{
			for(int j=info[id].start;j<=info[id].end;j++)
			{
				seat[j]=0;
			}
			cout<<"yes"<<endl;
		}
		
		/*for(int j=0;j<n*n;j++)
		{
			cout<<seat[j]<<" ";
		}*/
		//cout<<endl;
	}
	return 0;
	
}
