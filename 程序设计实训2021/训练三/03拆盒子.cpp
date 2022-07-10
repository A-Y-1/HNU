#include<iostream>
#include<map>
#include<algorithm>
#include<string>
#include<stdio.h>
using namespace std;

int main()
{
	int len,e;
	string a;
	while(cin>>a)
	{
		e=0;
		len=a.length();
		for(int i=0;i<len;i++)
		{
			if(a[i]=='(') e++;
			else if (a[i]=='B') break;
			else if(a[i]==')') e--;
		}
		cout<<e<<endl;	
	}
	return 0;
}
