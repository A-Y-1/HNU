#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
int main()
{
	string a;
	string x[10]={};//存放所有数字
	string result="";
	getline(cin,a);
	int len=a.length();
	int count = 0;
	for(int i=0;i<len;i+=2)
	{
		x[count]=a[i];
		count++;
	}
	sort(x,x+count); 
	for(int i=0;i<count;i++)
	{
		result+=x[i];
		if(result[0]=='0') 
		{
			result[0]=x[i][0];
			result[i]='0';
		}
	}
	cout<<result<<endl;
	return 0;
}
