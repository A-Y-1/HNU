#include<iostream>
#include<math.h>
#include<string>
#include<map>
#include<algorithm>
using namespace std;

bool check(int a,int b)
{
	if (a==b) return true;
	if ((a==0&&b==1)||(a==0&&b==7)||(a==0&&b==8)) return true;
	else if((a==1&&b==0)||(a==1&&b==4)||(a==1&&b==7)||(a==1&&b==8)||(a==1&&b==9)||(a==1&&b==3))return true;
	else if((a==2&&b==8)) return true;
	else if((a==3&&b==7)||(a==3&&b==8)||(a==3&&b==9)||(a==3&&b==1)) return true;
	else if((a==4&&b==1)||(a==4&&b==8)||(a==4&&b==9)) return true;
	else if((a==5&&b==6)||(a==5&&b==8)||(a==5&&b==9)) return true;
	else if(a==6&&b==8)return true;
	else if((a==7&&b==0)||(a==7&&b==1)||(a==7&&b==3)||(a==7&&b==8)||(a==7&&b==9)) return true;
	else if(a==8)return true;
	else if((a==9&&b==1)||(a==9&&b==4)||(a==9&&b==7)||(a==9&&b==8)||(a==9&&b==5)||(a==9&&b==3))	return true;
	return false;
}
int main()
{
	string x;
	int a=0,b=0;
	while(1)
	{
		getline(cin,x);
		if (x=="-1") break;
		bool flag = true;
		for (int i=0;i<19;i+=2)
		{
			if (i==18) break;
			a=x[i]-'0';
			b=x[i+2]-'0';
			if(check(a,b)==true) continue;
			else
			{
				flag=false;
				break; 
			}
			
		}
		if(flag==true) cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
	
	return 0;
}
