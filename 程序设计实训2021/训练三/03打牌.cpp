#include<iostream>
#include<string>
#include<queue>
using namespace std;
int pai[11];
void sort(string a)
{
	int len=a.length();
	int x;
	for(int i=0;i<len;i++)
	{
		x=a[i]-'0';
		if (x==1) pai[1]++;
		else if(x==2) pai[2]++;
		else if(x==3) pai[3]++;
		else if(x==4) pai[4]++;
		else if(x==5) pai[5]++;
		else if(x==6) pai[6]++;
		else if(x==7) pai[7]++;
		else if(x==8) pai[8]++;
		else if(x==9) pai[9]++;
	}
}
int main()
{
	string base;
	string opp,out;
	int num,lenopp;
	cin>>base;
	sort(base);
	getchar();
	while(cin>>opp)
	{
		lenopp=opp.length();
		queue<string> result;
		bool flag=false;//判断是否有大过的牌
		//case<4
		if(lenopp<=4)
		{
			num=opp[0]-'0';
			for(int i=num+1;i<=9;i++)
			{
				out="";
				if(pai[i]>=lenopp)
				{
					flag=true;
					for(int j=0;j<lenopp;j++) out+=to_string(i);
				}
				if(flag==true&&out.length()>0)	result.push(out);//out>0
			}
		}
		//case=5
		if(lenopp==5)
		{
			if(opp=="12345")
			{
				if(pai[2]>=1&&pai[3]>=1&&pai[4]>=1&&pai[5]>=1&&pai[6]>=1) result.push("23456");
				if(pai[7]>=1&&pai[3]>=1&&pai[4]>=1&&pai[5]>=1&&pai[6]>=1) result.push("34567");
				if(pai[7]>=1&&pai[8]>=1&&pai[4]>=1&&pai[5]>=1&&pai[6]>=1) result.push("45678");	
				if(pai[7]>=1&&pai[8]>=1&&pai[9]>=1&&pai[5]>=1&&pai[6]>=1) result.push("56789");
			}
			else if(opp=="23456")
			{
				if(pai[7]>=1&&pai[3]>=1&&pai[4]>=1&&pai[5]>=1&&pai[6]>=1) result.push("34567");
				if(pai[7]>=1&&pai[8]>=1&&pai[4]>=1&&pai[5]>=1&&pai[6]>=1) result.push("45678");	
				if(pai[7]>=1&&pai[8]>=1&&pai[9]>=1&&pai[5]>=1&&pai[6]>=1) result.push("56789");				
			}
			else if(opp=="34567")
			{
				if(pai[7]>=1&&pai[8]>=1&&pai[4]>=1&&pai[5]>=1&&pai[6]>=1) result.push("45678");	
				if(pai[7]>=1&&pai[8]>=1&&pai[9]>=1&&pai[5]>=1&&pai[6]>=1) result.push("56789");				
			}
			else if(opp=="45678")
			{
				if(pai[7]>=1&&pai[8]>=1&&pai[9]>=1&&pai[5]>=1&&pai[6]>=1) result.push("56789");			
			}
		}
		//输出结果
		if(!result.empty())
		{
			cout<<"YES";
			while(!result.empty())
			{
				cout<<" "<<result.front();
				result.pop();
			}
			cout<<endl;
		}
		else cout<<"NO"<<endl;
	}
	return 0;
}
