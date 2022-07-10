#include<iostream>
#include<map>
#include<string>
using namespace std;
int main()
{
	string a,b;
	map<char,int> all;
	map<char,int> need;
	map<char,int>::iterator it;
	int inade=0;
	bool buyif=true;
	cin>>a>>b;
	for(unsigned int i=0;i<a.length();i++)
	{
		if(all.count(a[i])==0)
		{
			all[a[i]]=1;
		}
		else all[a[i]]++;
	}
	for(unsigned int i=0;i<b.length();i++)
	{
		if(need.count(b[i])==0)
		{
			need[b[i]]=1;
		}
		else need[b[i]]++;
	}
	for(it=need.begin();it!=need.end();it++)
	{
		if(all.count(it->first)==0)
		{
			inade+=it->second;
			buyif=false;
		}
		else if(all[it->first]<it->second)
		{
			inade+=it->second-all[it->first];
			buyif=false;
		}
	}
	if(buyif==false) cout<<"No"<<" "<<inade<<endl;
	else cout<<"Yes"<<" "<<a.length()-b.length()<<endl;
	return 0;
}
