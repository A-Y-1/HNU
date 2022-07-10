#include<iostream>
#include<algorithm>
using namespace std;
int main()
{
	int n,res=0;
	cin>>n;
	int count[n];
	for(int i=0;i<n;i++)
	{
		count[i]=1;
	}
	int num[n];
	for(int i=0;i<n;i++)
	{
		cin>>num[i];
	}
	for(int j=0;j<n;j++)
	{
		if(j!=0&&num[j]>num[j-1])
		{
			count[j]=count[j-1]+1;
		}
	}
	
	sort(count,count+n);
	res=count[n-1];
	cout<<res<<endl;
	system("pause");
	return 0;
}
