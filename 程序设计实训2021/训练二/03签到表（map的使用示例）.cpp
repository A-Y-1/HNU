#include<string>
#include<math.h>
#include<iostream>
#include<set>
#include<map>
using namespace std;

int main()
{
	map<string,int> stu;
	int n;
	string a;
	map<string,int>::iterator it;
	while(cin>>n)
	{
		stu.clear();
		for (int i=0;i<(2*n-1);i++)
		{
			cin>>a;
			if (stu.count(a)==0)
			{
				stu[a]=0;
			}
			stu[a]++;
		}
		for(it=stu.begin();it!=stu.end();it++)
		{
			if (it->second%2!=0) cout<<it->first<<endl;
		}
		
	}
	return 0;
}
