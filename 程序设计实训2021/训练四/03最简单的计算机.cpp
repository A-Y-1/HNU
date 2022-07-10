#include<iostream>
#include<map>
using namespace std;

int m1,m2,r1,r2,r3;

void function(char a)
{
	if (a=='A') r1=m1;
	else if(a=='B') r2=m2;
	else if(a=='C') m1=r3;
	else if(a=='D') m2=r3;
	else if(a=='E') r3=r1+r2;
	else if(a=='F') r3=r1-r2;
}


int main()
{
	string request;
	int len;
	while(cin>>m1>>m2)
	{
		cin>>request;
		len=request.length();
		for(int i=0;i<len;i++) function(request[i]);
		cout<<m1<<","<<m2<<endl;
	}
	
	return 0;
}
