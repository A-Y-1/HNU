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
	for(int i=0;i<n;i++)//�ӵ�һ����ʼ
	{
		for(int j=0;j<i;j++)// ����֮ǰ��ÿһ��
		{
			if (info[j]>=info[i]&&count[j]>=count[i]) count[i]=count[j]+1; 
		}
	}
	sort(count,count+n);
	cout<<count[n-1]<<endl;
	return 0;
}
