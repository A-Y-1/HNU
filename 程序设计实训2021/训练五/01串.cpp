#include<iostream>
using namespace std;
int main()
{
	int n;
	cin>>n;
	int num[n];
	int dp[n];
	int result=0;
	for(int i=0;i<n;i++)
	{
		cin>>num[i];
	}
	for(int i=0;i<n;i++)
	{
		if(i==0&&num[0]==0) dp[0]=1;
		else if(i==0&&num[0]==1) dp[0]=0;
		if(i!=0&&num[i]==0) dp[i]=dp[i-1]+1;
		else if (i!=0&&num[i]==1) dp[i]=dp[i-1];
	}
	for(int i=0;i<n;i++)
	{
		for(int j=i+1;j<n;j++)
		{
			if(i-dp[i]+1+n-j-1-dp[n-1]+dp[j]+dp[j]-dp[i]>result) result=i-dp[i]+1+n-j-1-dp[n-1]+dp[j]+dp[j]-dp[i];
		}
		
	}
	cout<<result<<endl;
	return 0;
}


