#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

struct runner{
	int pos;
	int index;
	int v;
}; 

bool comp(runner a,runner b)
{
	if(a.pos==b.pos)
	{
		return a.v>b.v;
	}
	else return a.pos<b.pos;
}

int main()
{
	int n,s,t;
	cin>>n>>s;
	runner r[n];
	for (int i=0;i<n;i++)
	{
		cin>>t;
		r[i].pos=t;
		r[i].index=i+1;
	}
	for(int i=0;i<n;i++)
	{
		cin>>t;
		r[i].v=t;
	}
	sort(r,r+n,comp);
	int vmax=0,vmin=1000000;
	int o=0;
	for(int i=0;i<n;i++)
	{
		if (r[i].v>vmax) vmax=r[i].v;
		if(r[i].index==s) 
		{
			o=i;
			break;
		}
	}
	int safe=0;
	for(int i=o;i<n;i++)
	{
		if(r[i].v<vmin) vmin=r[i].v;
		if(r[i].v>=vmax) safe++;
	}
	for (int i=0;i<o;i++)
	{
		if (r[i].v<=vmin) safe++;
	}
	cout<<n-safe<<endl;
	system("pause");
	return 0;
}
