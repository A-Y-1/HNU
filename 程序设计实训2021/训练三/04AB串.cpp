#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
int main()
{
	int len,result=0;
	string str;
	cin>>str;
	len=str.length();
	int prea[len+1],preb[len+1];
	for(int i=0;i<len;i++)
	{
		if(i==0&&str[i]=='a') 
		{
			prea[0]=1;
			preb[0]=0;
			continue;
		}
		else if(i==0&&str[i]=='b') 
		{
			prea[0]=0;
			preb[0]=1;
			continue;
		}
		if(str[i]=='a')
		{
			prea[i]=prea[i-1]+1;
			preb[i]=preb[i-1];
		}
		else if(str[i]=='b')
		{
			prea[i]=prea[i-1];
			preb[i]=preb[i-1]+1;
		}
		//cout<<"i="<<i<<" "<<"prea="<<prea[i]<<" "<<"preb"<<preb[i]<<endl;	
	}
	for(int i=0;i<len;i++)
	{
		for(int j=i;j<len;j++){
			result=max(result,len-(preb[i]+prea[j]-prea[i]+preb[len-1]-preb[j]));
			//cout<<"i="<<i<<" "<<"j="<<j<<" "<<prea[i]<<" "<<preb[j]-preb[i]<<" "<<prea[len-1]-prea[j]<<endl;
		}
	}
	cout<<result<<endl;
	return 0;
}
