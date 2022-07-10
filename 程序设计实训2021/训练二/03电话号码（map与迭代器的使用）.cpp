#include<string>
#include<math.h>
#include<iostream>
#include<set>
#include<map>
using namespace std;

int main()
{
	map<string,int> phonenum;
	map<string,int>::iterator it;
	int n,len;
	string a,temp;
	cin>>n;
	for (int i =0;i<n;i++)
	{
		cin>>a;
		len=a.length();
		temp="";
		for (int j=0;j<len;j++)
		{
			
			if (a[j]=='A'||a[j]=='B'||a[j]== 'C') temp+='2';
			else if (a[j]=='D'||a[j]=='E'||a[j]== 'F') temp+='3';
			else if (a[j]=='G'||a[j]=='H'||a[j]== 'I') temp+='4';
			else if (a[j]=='J'||a[j]=='K'||a[j]== 'L') temp+='5';
			else if (a[j]=='M'||a[j]=='N'||a[j]== 'O') temp+='6';
			else if (a[j]=='R'||a[j]=='S'||a[j]== 'P') temp+='7';
			else if (a[j]=='T'||a[j]=='U'||a[j]== 'V') temp+='8';
			else if (a[j]=='X'||a[j]=='Y'||a[j]== 'W') temp+='9';
			else if(a[j]=='0') temp+='0';
			else if(a[j]=='1') temp+='1';
			else if(a[j]=='2') temp+='2';
			else if(a[j]=='3') temp+='3';
			else if(a[j]=='4') temp+='4';
			else if(a[j]=='5') temp+='5';
			else if(a[j]=='6') temp+='6';
			else if(a[j]=='7') temp+='7';
			else if(a[j]=='8') temp+='8';
			else if(a[j]=='9') temp+='9';
			if(temp.length()==3)
			{
                temp += '-';//在第三位数字后加上连接符
            }
            
            
		
		}
		if (phonenum.count(temp)==0) phonenum[temp]=0;
		phonenum[temp]++;
	}
	for(it=phonenum.begin();it!=phonenum.end();it++)
	{
		if (it->second>1) cout<<it->first<<" "<<it->second<<endl;		
	}
	
	return 0;
}
