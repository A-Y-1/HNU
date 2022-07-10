#include<iostream>
#include<string>
using namespace std;


int main()
{
	int count[10]={};
	string x[10]={"(Zero)","(One)","(Two)","(Three)","(Four)","(Five)","(Six)","(Seven)","(Eight)","(Nine)",};
	string str,result;
	getline(cin,str);
	int len=str.length();
	int temp;
	for (int i=0;i<len;i++)
	{
		temp=str[i]-'0';
		if(temp==0||temp==1||temp==2||temp==3||temp==4||temp==5||temp==6||temp==7||temp==8||temp==9)
		{
			count[temp]++;
			result+=x[temp];
		}
		else result+=str[i];
	}
	cout<<result<<endl;
	for (int i=0;i<10;i++) cout<<count[i]<<" ";
	cout<<endl;
	return 0;
	
}
