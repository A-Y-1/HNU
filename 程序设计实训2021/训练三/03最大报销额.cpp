#include<iostream>
#include<map>
#include<algorithm>
#include<string>
#include<stdio.h>
using namespace std;

int main()
{
	float sum,num,max0,max,up,n;// 单张总金额，单项金额，当前最大金额，最大金额
	bool flag;
	float info[30]={};
	int count,temp;
	char type;
	while(1)
	{
		cin>>up>>n;
		if(n==0)break;
		count=0;
		for(int i=0;i<n;i++)
		{
			flag=true;
			sum=0;
			cin>>temp;
			for(int j=0;j<temp;j++)
			{
				getchar();type=getchar();getchar();
				cin>>num;
				sum+=num;
				if(num>600) flag=false;
				if(type!='A'&&type!='B'&&type!='C') flag=false;
			}
			if(sum>1000) flag=false;
			if(flag==true) {info[count]=sum;count++;}
			else continue;
			
		}
		sort(info,info+count);
		max=0;
		for(int i=count-1;i>=0;i--)
		{
			max0=info[i];
			for (int j=i-1;j>=0;j--)
			{
				if (max0+info[j]<=up) max0+=info[j];
				else continue;
			}
			if (max0>max) max=max0;
		}
		printf("%.2f",max);
		cout<<endl;
		
	}
	
	return 0;
}
