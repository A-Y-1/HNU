#include<iostream>
using namespace std;
int main()
{
	int n,x=0,y=1,k;
	cin>>n;
	int stepx[n],stepy[n];
	for(int i=0;i<n;i++)
	{
		stepx[i]=i+2;
		stepy[i]=i;
	}
	for(int i=0;i<n;i++)
	{
		y=stepy[i]+y;
		cout<<y<<" ";
		k=y;
		for(int j=x;j<n-1;j++)
		{
			k+=stepx[j];
			cout<<k<<" ";
		}
		x++;
		cout<<endl;
	}	
}
