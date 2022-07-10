#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
struct runner
{
	int pos;
	int index;
	int v;
};
bool compv(runner a,runner b)   //∞¥ÀŸ∂»≈≈–Ú
{
	if (a.v==b.v) return false;
	else return a.v<b.v;
}
bool comppos(runner a,runner b)
{
	if (a.pos==b.pos) return false;
	else return a.pos<b.pos;
}
int main()
{
	int n,start,index=1,record,v0,uneffected=0;
	cin>>n>>start;
	runner info[n];
	for(int i=0;i<n;i++)
	{
		info[i].index=index;
		if (index==start) 
		cin>>info[i].pos;
		index++;
	}
	for(int i=0;i<n;i++)
	{
		cin>>info[i].v;
	}
	sort(info,info+n,comppos);
	for (int i =0;i<n;i++)
	{
		if (info[i].index==start) record=i;v0=info[i].v;
	}	
	sort(info,info+record,compv);
	int vmax=info[record].v;
	for (int i =record;i<n;i++)
	{
		if (info[i].v>vmax) uneffected++;
	}	
	sort(info+record,info+n,compv);
	for (int i =0;i<record;i++)
	{
		if (info[i].v<info[record].v) uneffected++;
	}
	cout<<n-uneffected<<endl;
	return 0;
}

