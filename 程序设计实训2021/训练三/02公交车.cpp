#include<iostream>
using namespace std;
int main()
{
	int n,w,max=0,min=100,temp,num=0,res=0;
	cin>>n>>w;
	for(int i=0;i<n;i++)
	{
		cin>>temp;
		num+=temp;
		if(num>max) max=num;
		if(num<min) min=num;
	}
	for(int i=0;i<=w;i++)
	{
		if(i+max<=w&&i+min>=0) res++;
	}
	cout<<res<<endl;
	return 0;
}
