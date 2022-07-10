#include<iostream>
#include<string>
#include<cmath>
using namespace std;
int main()
{
	int n,day,month,year,daypast,countnum;
	string haabmonth[]={"pop","no","zip","zotz","tzec","xul","yoxkin","mol","chen","yax","zac","ceh","mac","kankin","muan","pax","koyab","cumhu","uayet"};
	string tmonth[]={"imix","ik","akbal","kan","chicchan","cimi","manik","lamat","muluk","ok","chuen","eb","ben","ix","mem","cib","caban","eznab","canac","ahau"};
	string temp,monthname;
	cin>>n;
	for(int i=0;i<n;i++)
	{
		day=0,daypast=0,countnum=0,month=0;
		cin>>temp>>year;
		int len=temp.length();
		for(int j=0;j<len;j++)
		{
			if(temp[j]=='.')
			{
				monthname=temp.substr(j+1,len-j-1);
				temp=temp.substr(0,j);
				break;
			}
		}
		len=temp.length();
		for(int j=0;j<len;j++)
		{
			day+=(temp[j]-'0')*pow(10,len-j-1);
		}
		for(int j=0;j<19;j++)
		{
			if(monthname==haabmonth[j]) month=j;
		}
		daypast=year*365+month*20+day+1;
		//开始求新历法的日期
		year=daypast/260;
		daypast=daypast%260;
		month=daypast%20;
		while(daypast>0)
		{
			countnum++;
			if(countnum>13) countnum-=13;
			daypast--;
		}
		cout<<countnum<<" "<<tmonth[month-1]<<" "<<year<<endl;
	}
	return 0;
}
