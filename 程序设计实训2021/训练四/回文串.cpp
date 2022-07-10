#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
bool check(string a)
{
	string b=a;
	reverse(a.begin(),a.end());
	if(a==b) return true;
	else return false;
}
int main()
{
	string t,temp1,temp2;
	int len,res=0;
	while(cin>>len)
	{
		if(len==0) break;
		cin>>t;
		for(int i=0;i<=len;i++)
		{
			temp1=t.substr(0,i);
			reverse(temp1.begin(),temp1.end());
			//cout<<temp1<<endl;
			temp2=t+temp1;
			//cout<<temp2<<endl;
			if(check(temp2)) {res=i;break;}
		}
		cout<<res<<endl;
	}
}
