#include<string>
#include<iostream>
#include<cmath>
using namespace std;
int main()
{
	int result,num,len;
	string a,b;
	while(cin>>a>>b)
	{
		len=a.length();
		result=0;
		num=0;
		for(int i=0;i<len;i++)
		{
			if(a[i]=='?') num++;
		}
		for(int i=0;i<len;i++)
		{
			if(a[i]!='?')
			{
				if(a[i]>b[i]) 
				{
					result+=pow(10,num);
					break;
				}
				else if(a[i]<b[i]) break;
			}
			else
			{
				num--;
				result+=(9-(b[i]-'0'))*pow(10,num);
			}
		}
		cout<<result<<endl;
	}
	return 0;
}
