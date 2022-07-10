#include<iostream>
using namespace std;

int main()
{
	int n,count;
	while(1)
	{
		count=0;
		cin>>n;
		if(n==0) break;
		int num[5000]={};
		for (int i=0;i<n;i++)
		{
			cin>>num[i];
		}
		for(int i=0;i<n;i++)
		{
			for(int j=i;j<n;j++)
			{
				if(num[j]<num[i])count++;
			}
		}
		cout<<count<<endl;
		
	}
}
