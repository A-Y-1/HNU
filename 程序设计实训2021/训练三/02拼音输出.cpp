#include<iostream>
#include<string>
#include<map>
#include<set>
#include<stack>
#include<algorithm>
using namespace std;


int main()
{
	string x;
	int sum=0;
	string y[]={"ling","yi","er","san","si","wu","liu","qi","ba","jiu"};
	cin>>x;
	int len=x.length();
	for (int i=0;i<len;i++)
	{
		sum=sum+x[i]-'0';
	}
	string result=to_string(sum);
	len = result.length();
	for(int i =0;i<len;i++)
	{
	
		if (i==len-1)cout<<y[result[i]-'0'];
		else cout<<y[result[i]-'0']<<" ";
	}
	return 0;
	
}

