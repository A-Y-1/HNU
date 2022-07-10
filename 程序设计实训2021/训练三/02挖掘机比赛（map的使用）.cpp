#include<iostream>
#include<string>
#include<map>
using namespace std;


int main()
{
	int n,temp1,temp2;
	map<int,int> info;
	map<int,int>::iterator it;
	cin>>n;
	for (int i=0;i<n;i++)
	{
		cin>>temp1>>temp2;
		if (info.count(temp1)==0)
		{
			info[temp1]=temp2;
		}
		else info[temp1]+=temp2;
		
	}
	int maxscore=0,win=0;
	for (it=info.begin();it!=info.end();it++)
	{
		if (it->second>maxscore) 
		{
			win=it->first;
			maxscore=it->second;
			
		}
	}
	cout<<win<<" "<<maxscore<<endl;
	
	
	return 0;
}
