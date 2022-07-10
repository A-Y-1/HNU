#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
int dp[101][3];
int main()
{
	int n,x;
	memset(dp,1000000,sizeof dp);
	dp[0][0]=dp[0][1]=dp[0][2]=0;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>x;
		dp[i][0]=min(dp[i-1][0],min(dp[i-1][1],dp[i-1][2]))+1;
		if(x==1||x==3)
		{
			dp[i][1]=min(dp[i-1][0],dp[i-1][2]);
		}
		if(x==2||x==3)
		{
			dp[i][2]=min(dp[i-1][0],dp[i-1][1]);
		}
	}
	cout<<min(dp[n][0],min(dp[n][1],dp[n][2]))<<endl;
}
