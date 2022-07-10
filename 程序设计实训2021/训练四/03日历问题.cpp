#include<iostream>
#include<stdio.h>
using namespace std;
int isleapyear(int a)
{
	if(a%4==0)
	{
		if (a%100==0&&a%400!=0) return 0;
		else return 1;
	}
	return 0;
}
int main()
{
	int num,month[2][12]={{31,28,31,30,31,30,31,31,30,31,30,31},{31,29,31,30,31,30,31,31,30,31,30,31}},year[2]={365,366};
	string weekday[]={"Saturday","Sunday","Monday","Tuesday","Wednesday","Thursday","Friday"};
	int tmonth,tyear;
	while(cin>>num)
	{
		if(num==-1) break;
		tmonth=0,tyear=2000;
		string x=weekday[num%7];
		while(num>=year[isleapyear(tyear)]) 
		{
			num-=year[isleapyear(tyear)];
			tyear++;
		}
		while(num>=month[isleapyear(tyear)][tmonth])
		{
			num-=month[isleapyear(tyear)][tmonth];
			tmonth++;
		}
		printf("%04d-%02d-%02d",tyear,tmonth+1,num+1);
		cout<<" "<<x<<endl;	
	}
}
