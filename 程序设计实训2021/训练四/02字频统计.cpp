#include<iostream>
#include<string>
using namespace std;

int main()
{
	int n,ab,ba;
	string temp;
	while(1)
	{
		cin>>n;
		cin>>temp;
		ab=0,ba=0;
		if(n==0) break;
		for(int i=0;i<n;i++)
		{
			if(i==n-1) continue;
			if(temp.substr(i,2)=="ab") ab++;
			else if(temp.substr(i,2)=="ba") ba++;
		}
		cout<<ab-ba<<endl;
	}
	return 0;	
}
