#include<iostream>
#include<string>
using namespace std;
int a[3],b[3],result[3];

int main()
{
	cin>>a[0];
	getchar();
	cin>>a[1];
	getchar();
	cin>>a[2];
	cin>>b[0];
	getchar();
	cin>>b[1];
	getchar();
	cin>>b[2];
	bool flag=true;
	if (b[0]<a[0]) flag=false;
	else if(b[0]==a[0]&&a[1]>b[1]) flag=false;
	else if(b[0]==a[0]&&a[1]==b[1]&&a[2]>b[2]) flag=false;
	if(flag==true)
	{
		for(int i=2;i>=0;i--)
		{
			if(i==2&&b[2]>a[2])  result[2]=b[2]-a[2];
			else if(i==2&&b[2]<a[2])
			{
				b[1]-=1;
				b[2]+=29;
				result[2]=b[2]-a[2];
			}
			if(i==1&&b[1]>a[1])  result[1]=b[1]-a[1];
			else if(i==1&&b[1]<a[1])
			{
				b[0]-=1;
				b[1]+=17;
				result[1]=b[1]-a[1];
			}
			if(i==0) result[0]=b[0]-a[0];
		}
		cout<<result[0]<<"."<<result[1]<<"."<<result[2]<<endl;
	}
	else{
		for(int i=2;i>=0;i--)
				{
					if(i==2&&a[2]>b[2])  result[2]=a[2]-b[2];
					else if(i==2&&a[2]<b[2])
					{
						a[1]-=1;
						a[2]+=29;
						result[2]=a[2]-b[2];
					}
					if(i==1&&a[1]>b[1])  result[1]=a[1]-b[1];
					else if(i==1&&a[1]<b[1])
					{
						a[0]-=1;
						a[1]+=17;
						result[1]=a[1]-b[1];
					}
					if(i==0) result[0]=a[0]-b[0];
				}
		cout<<"-"<<result[0]<<"."<<result[1]<<"."<<result[2]<<endl;	
	}
	system("pause");
	return 0;
}
