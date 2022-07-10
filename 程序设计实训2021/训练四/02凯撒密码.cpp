#include<iostream>
#include<string>
using namespace std;

string conver(string a)
{
	int len=a.length();
	for(int i=0;i<len;i++)
	{
		if(65<=a[i]&&a[i]<=90)
		{
			if(a[i]-5<65) a[i]=a[i]+26-5;
			else a[i]-=5;
		}
	}
	return a;
}


int main()
{
	string code,res,temp;
	while(1)
	{
		cin>>temp;
		getchar();
		if(temp=="ENDOFINPUT") break;
		getline(cin,code);
		cin>>temp;
		res=conver(code);
		cout<<res<<endl;
	}
	return 0;
}
