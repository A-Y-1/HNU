#include<iostream>
#include<map>
#include<algorithm>
#include<string>
#include<stdio.h>
using namespace std;

int main()
{
	int n;
	cin>>n;
	int info[25]={};
	int count[25]={};
	for(int i=0;i<n;i++)
	{
		cin>>info[i];
		count[i]=1;
	}
	for(int i=0;i<n;i++)//从第一发开始
	{
		for(int j=0;j<i;j++)// 遍历之前的每一个
		{
			if (info[j]>=info[i]&&count[j]>=count[i]) count[i]=count[j]+1; 
		}
	}
	sort(count,count+n);
	cout<<count[n-1]<<endl;
	return 0;
}
