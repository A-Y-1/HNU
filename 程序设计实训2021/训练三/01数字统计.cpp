#include<iostream>
#include<math.h>
#include<string>
#include<map>
using namespace std;
int main()
{
	map<char,int> result;
	string  temp;
	cin>>temp;
	int len=temp.length();
	for(int i=0;i<len;i++)
	{
		if (result.count(temp[i])==0) result[temp[i]]=0;
		result[temp[i]]++;
	}
	map<char,int>::iterator it;
	for(it=result.begin();it!=result.end();it++)
	{
		cout<<it->first<<":"<<it->second<<endl;
	}
	return 0;
}
